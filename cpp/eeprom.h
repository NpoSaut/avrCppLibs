/*
 * eeprom.h
 *
 * Оболочка для переменных, хранящихся в eeprom-памяти
 * ***************************************************
 *
 *  ~~~ Проблема: ~~~
 *  Размещение переменной в eeprom в gcc-avr реализовано с помощью аттрибута EEMEM.
 *  Для работы с такой переменной реализованы специальных функции наподобии eeprom_read_byte, что не очень красиво.
 *  Также не предусмотрена возможность неблокирующей записи, что актуально, т.к. время записи 1 байта составляет 4,5 мсек.
 *
 *  ~~~ Задача: ~~~
 *  1. Создать обёртку над переменной, которая бы стандартными средствами C++
 *     предоставляла интерфейс для работы с переменной в eeprom сходный с интерфейсом работы с обычной переменной.
 *  2. Добавить функцию неблокирующей записи с возможностью получения результата в конце записи.
 *
 *  ~~~ Решение: ~~~
 *  1. Перегрузкой оператора = вызывать функцию eeprom_update_byte.
 *  2. Работать с прерыванием по записи в eeprom.
 *     По окончанию записи добавлять пользовательский делегат в диспетчер. В аргументе передаётся адрес записанной переменной.
 *     Функция неблокирующей записи возвращает false в случае:
 *     - если на момент вызова происходит неблокирующая запись с помощью класса Eeprom
 *     - если на момент вызова происходит запись в eeprom с помощью любых методов
 *
 *  ~~~ Условия, налагаемые на работу с eeprom помимо класса Eeprom: ~~~
 *  Совместно с объектами класса Eeprom в eeprom-памяти могут быть расположены традиционные переменные.
 *  Класс Eeprom полностью совместим со стандартными функциями eeprom_write_byte.
 *  Однако может оказаться не совместимым со сторонними реализациями неблокирующей записи.
 *
 *  ~~~ Интерфейс: ~~~
 *  Чтобы создать переменную типа Type в eeprom раньше вы писали: Type var EEMEM;
 *  Теперь вы можете написать: Eeprom<Type> var EEMEM;
 *  после чего можно работать с переменной как обычно:
 *  var = 3;
 *  test = var;
 *
 *  Или же использовать неблокирующую запись:
 *  void wait (uint16_t pointer); // функция для вызова по завершению записи
 *  var.updateUnblock( 5, SoftIntHandler::from_function<&wait>() );
 *
 *
 *  ~~~ Пример использования: ~~~
	#include <cpp/eeprom.h>

	uint8_t a;
	Eeprom<uint8_t> var EEMEM;
	Eeprom<uint8_t> var2 EEMEM;

	void waitEndOfUnblockWrite (uint16_t pointerToWrittenVariable) // функция для вызова по завершению неблокирующей записи.
																   // Аргументом передаётся указатель на записанную переменную.
	{
		Eeprom<uint8_t>& var = *((Eeprom<uint8_t> *) pointerToWrittenVariable); // Ссылка на переменную
		if ( var.isReady() ) // Проверяет нет ли активных операций с eeprom
		{
			//значит чтение можно начать незамедлительно
			a = var; // чтение записанной переменной
		}
		else // eeprom занят
		{
			// Повторим попытку позже
			dispatcher.add ( SoftIntHandler::from_function<&waitEndOfUnblockWrite>() , pointerToWrittenVariable );
		}
	}

	int main ()
	{
		var = 1; // блокирующая запись.
				 // На этом месте исполнение программы остановится на время записи (4,5 мсек на байт)
				 // Также если не закончена другая запись, то сначала функция будет дожидаться её завершения.
		a = var; // блокирующее чтение.
				 // Задержка возможна только в случае занятости eeprom другой операцией (из-за неблокирующей записи в другом месте)
		var2 = var; // блокирующие чтение и запись

		if ( !var.updateUnblock( 3, SoftIntHandler::from_function<&waitEndOfUnblockWrite>() ) ) // попытка неблокирующей записи.
			// Выполнение программы продолжится сразу же, не дожидаясь окончания записи.
			// В момент окончания в диспетчер будет поставлен делегат функции waitEndOfUnblockWrite>()
		{
			// Действия в случае неготовности eeprom
		}

		for (;;)
		{
			dispatcher.invoke ();
		}
	}
 *
 */

#ifndef CPP_EEPROM_H_
#define CPP_EEPROM_H_

#include <avr/eeprom.h>

#include <cpp/io.h>
#include <cpp/interrupt-dynamic.h>
#include <cpp/dispatcher.h>


namespace EepromStaticPrivate
{
	bool updateMode = false;
	volatile uint8_t byteNumber = 0; 	// 0 - no active write, 1...4 - active
	Complex<uint32_t> writingVar;		// 4 байта максимум
	uint8_t* startAddress;				// address of low byte
	SoftIntHandler afterWrite;

	void writeNextByte ();
	void updateNextByte ();
	void interruptHandler ();
	void interruptHandler (uint16_t) { interruptHandler(); }

	class Init
	{
	public:
		Init () { EE_READY_handler = InterruptHandler::from_function<&interruptHandler>(); }
	} init;
}

template<typename Type>
class Eeprom
{
public:
	explicit Eeprom ();

	void operator= (const Type& var) volatile
	{
		if ( sizeof(Type) == 1 )
			eeprom_update_byte( (uint8_t*)(this), var );
		if ( sizeof(Type) == 2 )
			eeprom_update_word( (uint16_t*)(this), var );
		if ( sizeof(Type) == 4 )
			eeprom_update_dword( (uint32_t*)(this), var );
	}
	void operator= (const Eeprom& var) volatile
	{
		if ( sizeof(Type) == 1 )
			eeprom_update_byte( (uint8_t*)(this), var );
		if ( sizeof(Type) == 2 )
			eeprom_update_word( (uint16_t*)(this), var );
		if ( sizeof(Type) == 4 )
			eeprom_update_dword( (uint32_t*)(this), var );
	}
	operator Type () volatile const
	{
		Type var;
		if ( sizeof(Type) == 1 )
			var = eeprom_read_byte( (uint8_t*)(this) );
		if ( sizeof(Type) == 2 )
			var = eeprom_read_word( (uint16_t*)(this) );
		if ( sizeof(Type) == 4 )
			var = eeprom_read_dword( (uint32_t*)(this) );
		return var;
	}

	bool writeUnblock( const Type& var, const SoftIntHandler& runAfterWriteEnd = SoftIntHandler(), const bool& updateMode = false );
	bool updateUnblock( const Type& var, const SoftIntHandler& runAfterWriteEnd = SoftIntHandler() );
	bool isReady () volatile const { return EepromStaticPrivate::byteNumber == 0 && !reg.eepromControl && !(reg.pgmStore & 1); }

private:
	Type var;
};


template<typename Type>
Eeprom<Type>::Eeprom ()
{
	static_assert ( sizeof(Type)==1 || sizeof(Type)==2 || sizeof(Type)==4,
					"Unsupported type");
}

template<typename Type>
bool Eeprom<Type>::writeUnblock(const Type& var, const SoftIntHandler& runAfterWriteEnd, const bool& updateMode )
{
	volatile uint8_t sreg = reg.status;
	cli ();
	if ( EepromStaticPrivate::byteNumber == 0  ) // no active write
	{
		EepromStaticPrivate::byteNumber = sizeof(Type);
		reg.status = sreg;

		EepromStaticPrivate::updateMode = updateMode;
		EepromStaticPrivate::writingVar = (uint32_t) var;
		EepromStaticPrivate::startAddress = (uint8_t *)this;
		EepromStaticPrivate::afterWrite = runAfterWriteEnd;

		cli();
		if ( !reg.eepromControl && !(reg.pgmStore & 1) ) // no flag in eepromControl
		{
			EepromStaticPrivate::writeNextByte();
			reg.status = sreg;
			return true;
		}
		else
		{
			EepromStaticPrivate::byteNumber = 0; // free
			reg.status = sreg;
			return false;
		}
	}
	else
	{
		reg.status = sreg;
		return false;
	}
}

template<typename Type>
bool Eeprom<Type>::updateUnblock(const Type& var, const SoftIntHandler& runAfterWriteEnd)
{
	return writeUnblock( var, runAfterWriteEnd, true );
}

namespace EepromStaticPrivate
{
	void writeNextByte ()
	{
		uint8_t num = --byteNumber;
		reg.eepromAddress = startAddress+num;

		Bitfield<EepromControl> ctr (0);
		if (updateMode)
		{
			// Read before write
			ctr.readEnable = true;
			reg.eepromControl = ctr;

			if (reg.eepromData == writingVar[num])
			{
				interruptHandler();
				return;
			}
		}
		reg.eepromData = writingVar[num];

		ctr.readEnable = false;
		ctr.writeEnable = false;
		ctr.masterWriteEnable = true;
		ctr.interruptEnable = true;
		reg.eepromControl = ctr; // Prepare

		ctr.readEnable = false;
		ctr.writeEnable = true;
		ctr.masterWriteEnable = true;
		ctr.interruptEnable = true;
		reg.eepromControl = ctr; // Start!
	}

	void updateNextByte ()
	{
		uint8_t num = --byteNumber;
		reg.eepromAddress = startAddress+num;

		// Read before write
		Bitfield<EepromControl> ctr (0);
		ctr.readEnable = true;
		reg.eepromControl = ctr;

		if (reg.eepromData != writingVar[num])
		{
			reg.eepromData = writingVar[num];

			ctr.readEnable = false;
			ctr.writeEnable = false;
			ctr.masterWriteEnable = true;
			ctr.interruptEnable = true;
			reg.eepromControl = ctr; // Prepare

			ctr.readEnable = false;
			ctr.writeEnable = true;
			ctr.masterWriteEnable = true;
			ctr.interruptEnable = true;
			reg.eepromControl = ctr; // Start!
		}
		else
			interruptHandler();
	}

	void interruptHandler ()
	{
		if ( byteNumber != 0 )
			writeNextByte();
		else
		{
			reg.eepromControl = 0;
			sei ();
			if ( afterWrite )
				dispatcher.add( afterWrite, (uint16_t)startAddress );
		}
		sei ();
	}
}

#endif /* CPP_EEPROM_H_ */
