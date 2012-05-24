/*
 * eeprom.h
 *
 * Оболочка для переменных, хранящихся в eeprom-памяти
 * ***************************************************
 *
 *  ~~~ Проблема: ~~~
 *  Размещение переменной в eeprom в gcc-avr реализовано с помощью аттрибута EEMEM.
 *  Для работы с такой переменной требуются специальных функции наподобии eeprom_read_byte, что не очень красиво.
 *
 *  ~~~ Задача: ~~~
 *  Создать обёртку над переменной, которая бы стандартными средствами C++
 *  предоставляла привычный интерфейс работы с переменной.
 *
 *  ~~~ Решение: ~~~
 *  Перегрузка операторов.
 *
 *  ~~~ Интерфейс: ~~~
 *  Если необходимо создать переменную типа Type в eeprom, вы пишите: Type var EEMEM;
 *  Теперь вы можете написать: Eeprom<Type> var EEMEM;
 *  после чего можно работать с переменной как обычно:
 *  var = 3;
 *  test = var;
 *
 *  ~~~ Пример использования: ~~~
	uint8_t a;
	Eeprom<uint8_t> var EEMEM;
	Eeprom<uint8_t> var2 EEMEM;

	int main ()
	{
		var = 1;
		a = var;
		var2 = var;
	}
 *
 */

#ifndef CPP_EEPROM_H_
#define CPP_EEPROM_H_

#include <avr/eeprom.h>

template<typename Type>
class Eeprom
{
public:
	explicit Eeprom ()
	{
		static_assert ( sizeof(Type)==1 || sizeof(Type)==2 || sizeof(Type)==4,
						"Unsupported type");
	}

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
			eeprom_update_byte( (uint8_t*)(this), var.var );
		if ( sizeof(Type) == 2 )
			eeprom_update_word( (uint16_t*)(this), var.var );
		if ( sizeof(Type) == 4 )
			eeprom_update_dword( (uint32_t*)(this), var.var );
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

private:
	Type var;
};

#endif /* CPP_EEPROM_H_ */
