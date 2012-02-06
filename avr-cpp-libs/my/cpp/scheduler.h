/*
 * scheduler.h
 *
 * Планировщик
 * ***********
 *
 *  ~~~ Задача: ~~~
 *  1. Предоставить возможность выполнять некоторую комманду (делегат с заданным значением параметра) через определённое время
 *
 *  ~~~ Решение: ~~~
 *  1. Задачи (комманда + время) храняться в массиве с заданным на момент компиляции размером. Потому что malloc слишком дорог.
 *     Как следствие, (а) нужно резервировать место в памяти, (б) может не оказаться свободных мест.
 *  2. Используются системные часы. В момент постановки задания происходит расчёт времени, в которое нужно начать выполнение.
 *  3. Задачи выполняются из функции invoke(), которая должна регулярно вызываться (например в main).
 *     Запуск задачи происходит при условии, что текущее время больше, чем время начала выполнения задачи.
 *  4. Задачи храняться неупорядоченно. При постановке задача помечается активной, в момент выполнения флаг активности снимается.
 *     Каждый раз при постановке происходит перебор всех ячеек до тех пор, пока не будет найдена пустая (не активная).
 *     Если все ячейки заняты, то возвращается false.
 *     Каждый раз при invoke() происходит перебов всех ячеек, для активным происходит сравнение времён.
 *
 *  ~~~ Интерфейс: ~~~
 *  1. Шаблонный клас Scheduler. В шаблоне:
 *     - тип и ссылка на часы, которые использовать в качестве источника времени. В единицах этих часов и будет задаваться время.
 *     - число ячеек под задачи. Т.е. одновременно не более N задач могут ожидать выполнения.
 *     - тип переменной времени в runIn (время, через которое будет выполнена задача)
 *  2. Функция runIn (Command command, InTime time)
 *     ставит комманду command в очередь на выполнение ЧЕРЕЗ time. time в единицах дискрета часов.
 *  3. Функция invoke() проверяет не пора ли вополнять задачи.
 *     Если существую задачи, которые должны быть выполнены в момент времени раньше, чем текущий, то выполняет их.
 *     Если задач несколько, то порядок выполенения случайный.
 *     Функцию invoke() нельзя вызывать из кода, который может прервать функцию runIn()
 *
 *  ~~~ Комментарии: ~~~
 *  1. Экономим память под время для каждой задачи.
 *    1.1 Не хотелось бы вносить дополнительные ограничения на диапазон значений параметра runIn().
 *        Поэтому стоит выбирать между uint8_t или uint16_t. uint8_t может оказаться нереально мало.
 *    1.2 Но чтобы в invoke ответить на вопрос о том, прошло ли заданное время, необходимо хранить ещё один старший бит.
 *        Например младшие 2 байта времени 0xDCBA, мы ставим задачу через 20000 и получаем время 0x2ADA - раньше текущего.
 *
 *  ~~~ Пример использования: ~~~
Clock< Alarm<Alarm1A, 1000>, uint32_t > clock;
Scheduler<  Clock<Alarm<Alarm1A, 1000>, uint16_t>, clock,
			16, uint16_t > scheduler;

void f (uint16_t nextTime)
{
	reg.portC.pin4.toggle(); // мигаем светодиодом
	scheduler.runIn( Command{SoftIntHandler::from_function<&f>(), (nextTime*9/10)}, nextTime );
}

int main ()
{
	scheduler.runIn( Command{SoftIntHandler::from_function<&f>(), 1000}, 1000 );

	// Светодиоды
	reg.portC.pin4.out();

	sei ();
    for (;;)
    {
    	scheduler.invoke();
    }
}
 *
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <cpp/universal.h>
#include <cpp/dispatcher.h>
#include <cpp/timers.h>

template< class Clock, Clock& clock,
		  uint8_t size,
		  typename InTime = uint16_t  >
class Scheduler
{
public:
	Scheduler ()
	{
		static_assert (sizeof(InTime) < sizeof(typename Clock::Time), "Тип InTime должен быть меньше, чем Clock::Time");
	}
	bool runIn (Command command, InTime time)
	{
		for (Task& t : task)
		{
			uint8_t sreg = SREG; // Remember last state
			cli ();

			if (t.active != 1 && t.blocked != 1) // Empty and unblocked
			{
				t.blocked = 1;
				SREG = sreg;

				t.time = clock.getTime() + time;
				t.command = command;
				t.active = 1;
				t.blocked = 0;
				return true;
			}
			else
				SREG = sreg;
		}
		return false;
	}

	void invoke ()
	{
		for (Task& t : task)
		{
			if ( t.active )
			{
				Bitfield<Time> time( clock.getTime() );
				if ( t.timeHighBit == time->highBit	&& t.timeLowPart < time->lowPart )
				{
					t.command.handler (t.command.parameter);
					t.active = 0;
				}
			}
		}
	}

	static constexpr uint32_t discreetMks = Clock::discreetMks;

private:
	typedef typename Clock::Time ClockTime;
	struct Task
	{
		Command command;
		union
		{
			struct
			{
				volatile ClockTime time		:sizeof(InTime)*8+1;
				volatile ClockTime active	:1;
				volatile ClockTime blocked	:1;
			};
			struct
			{
				volatile ClockTime timeLowPart	:sizeof(InTime)*8;
				volatile ClockTime timeHighBit	:1;
				volatile ClockTime				:2;
			};
		};
	};
	union Time
	{
		ClockTime full;
		struct
		{
			ClockTime lowPart	:sizeof(InTime)*8;
			ClockTime highBit	:1;
		};
	};

	Task task[size];
};


#endif /* SCHEDULER_H_ */
