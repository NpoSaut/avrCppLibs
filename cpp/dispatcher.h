/*
 * dispatcher.h
 *
 * Потоко-безопасные переменные
 * ****************************
 *
 *  ~~~ Проблема: ~~~
 *  Если переменная используются одновременно в обработчике прерывания и коде, который может быть прерван этим прерыванием, то:
 *  1. Оптимизатор, считающий что значение переменной не может измениться из другого места, генерирует неверный код
 *  2. Если размер переменной более 1 байта, то возможна следующая ситуация:
 *     когда считана часть значения, возникнет прерывание и изменяет значение переменной,
 *     далее будет считана оставшаяся часть значени, но уже нового.
 *
 *  ~~~ Задача: ~~~
 *  1. Не использовать оптимизацию при работе с этой переменной.
 *  2. Если переменная более 1 байта, то обеспечить атомарность при чтении/записи значения:
 *  	т.е. выключать прерывания на момент чтения/записи.
 *  3. Там где это возможно обеспечить возможность обычной раобты с переменной: оптимизированной и неатомарной.
 *
 *  ~~~ Решение: ~~~
 *  1. Использовать volatile
 *  2. Исользовать ATOMIC из библиотеки Чижова
 *  3. Объединить в union volatile и не-volatile переменные.
 *
 *  ~~~ Интерфейс: ~~~
 *  Для обеспечения безопасной работы с переменной типа Type,
 *  создаётся шаблонный класс Safe<Type> и переменная объявляется этого типа.
 *  При этом:
 *  - Обычные операции присвоения и взятия значения функционируют обычно (не безопасно)
 *  - Оператор <<= обеспечивает безопасную запись и извлечение значений
 *
 *  ~~~ Комментарии: ~~~
 *  1. Атомарность обеспечивается на минимально возможном интервале:
 *     при копировании из обыной переменной в безопасную:
 *     а) сначала значение обычной переменной извлекаетс в регистры,
 *     б) потом из регистров оно записывается в безопасную переменную.
 *     Прерывания запрещены только при выполнении б)
 *  2. При использовании типа uint8_t нет необходимости в атомарности, достаточно только volatile.
 *     Поэтому для этого типа использются специализации шаблона.
 *
 *  ~~~ Пример использования: ~~~
	uint16_t v;
	Safe<uint16_t> sv;

	sv <<= v;	// Безопасное присвоение
	v <<= sv;   // Безопасное извлечение

	// В обработчике прерывания нет необходимости в безопасности,
	// там используем обычные операции:
	sv = v;
	v = sv;
 *
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <cpp/delegate/delegate.hpp>

typedef Delegate<void (uint16_t)> SoftIntHandler;

//struct Sixteen
//{
//	uint8_t val	:4;
//	uint8_t		:4;
//};
//register Sixteen head asm ("r2");
//register Sixteen tail asm ("r3");

struct Command
{
	SoftIntHandler handler;
	uint16_t parameter;
};

class Dispatcher
{
public:
	typedef ::Command Command;

	Dispatcher ()
		: head (0), tail (0)
	{}

	void add (const SoftIntHandler& handler_, const uint16_t& param)
	{
		command[ blockNumber() ] = {handler_, param};
	}
	void add (const Command& com)
	{
		command[ blockNumber() ] = com;
	}

	void invoke ()
	{
		Command com;
		ATOMIC
		{
			if (head != tail)
			{
				com = command[head];
				head++;
			}
		}

		if (com.handler)
		{
			currentCommandPointer = (uint16_t)com.handler.object_ptr;
			com.handler (com.parameter);
			currentCommandPointer = 0xFFFF;
		}
//		else
//			asm volatile ("nop");
	}
	
	Delegate<void (uint16_t)> overflowHandler;

private:
	Command command[256];
	volatile uint8_t head;
	volatile uint8_t tail;
	volatile uint16_t currentCommandPointer;

	uint8_t blockNumber ()
	{
		uint8_t blockedNumber;
		bool overflow = false;
		ATOMIC
		{
			blockedNumber = tail;
			if ( ++tail == head )
			{
				++head;
				overflow = true;
			}
		}
		
		if (overflow)
			overflowHandler (currentCommandPointer);
			
		return blockedNumber;
	}
};

Dispatcher dispatcher;

#endif /* DISPATCHER_H_ */
