/*
 * interrupt-dynamic.h
 *
 * Динамические обработчики прерываний
 * ***********************************
 *
 *  ~~~ Проблема: ~~~
 *  AVR GCC в качестве обработчиков прерываний может задавать только глобальные функции с зарезервированными именами
 *
 *
 *	~~~ Задача: ~~~
 *	- Задать произвольную функцию (напр. метод объекта класса) как обработчик прерываний
 *	- Иметь возможность менять функцию обработки прерываний во время выполнения программы
 *
 *
 * 	~~~ Решение: ~~~
 * 	- Фиктивный обработчик вызывает функцию по указателю. Содержимое указателя можно менять.
 * 	- Для эффективности (! особенно важно для маленьких обработчиков !):
 * 		- В фиктивном обработчике не происходит сохраниение никаких регистров
 * 		  помимо двух, необходимых для вызова функции по уазателю
 * 		- Все стандартные действия по сохранению регистров выполняются в реальном обработчике.
 * 		  Это даёт возможность сохранять не все регистры, а только нужные.
 *
 *
 *  ~~~ Интерфейс: ~~~
 *  INTERRUPT_POINTER_DECLARE(NAME)
 *  - Объявляет указатель с именем NAME_handler.
 *  - Создаёт фиктивный стандартный обработчик прерывания NAME_vect, который вызывает функцию по указателю NAME_handler
 *
 *  INTERRUPT_HANDLER(function_name)
 *  - Объявляет реальную функцию обработчика прерываний с аттрибутом signal
 *    Адрес этой функции может быть записан в NAME_handler для того, чтобы она вызывалась при возникновении прерывания
 *
 *
 *  ~~~ Комментарии: ~~~
 *  1. Несмотря на то, что в таблице векторов расположены именно адреса вызываемых функций,
 *     мы не можем просто расположить наши указатели по адресу таблицы векторов.
 *     Дело в том, что во flash нельзя записывать, можно только читать.
 *     Поэтому помесить адрес в уазатель можно будет только в момент описания.
 *  2. AVR GCC имеет некоторые зарезервированные регистры, которые могут быть использованны в любой функции без боязни
 *     затереть имеющиеся в них значения. Если в основной программе эти регистры используются на момент вызова функции,
 *     то сохранение их значений производится именно в основной программе до вызова функции.
 *     Если функции не хватает этих регистров, то оставшиеся она задействовует оставшиеся,
 *     но уже сама сохраняет значения в них.
 *     Прерывание возникает в произвольный момент, поэтом обрботчик прерывания должен сохранять значения всех используемых регистров.
 *     Этим он отличается от обычной функции.
 *  3. В нашем случае в обработчике прерываний просто вызвается функция по указателю.
 *     Но поскольку он не знает, что это за функция, он должен сохранить все зарезервированные регистры (12 штук).
 *     Потому что эта вызываема функция ничего не знает о том, что она вызывается из прерывания, и рассчитывает на то,
 *     что эти регистры подготовлены заранее.
 *     Таким образом, если в реальном обработчике прерываний исползуется всего пару регистров и он состоит из десятка машинных комманд,
 *     что зачастую и бывает, то затраты на сохранение (и восстановление!) 12 регистров будут превосходить реальную работу обработчика.
 *  4. Для решения этой проблемы фиктивный обрабочкик объявляется с аттрибутом naked,
 *     т.е. содержить только код функции и даже не содержит ret(i) в конце.
 *     Ему требуется 4 регистра, чтобы вызвать реальный обработчик по указателю. Поэтому вручную сохраняются и восстанавливаются эти 4 регистра.
 *     Реальный обработчик объявляется с аттрибутом signal, что генерирует такую функцию, как будто бы она являлась обработчиком прерываний.
 *     В конце этой функции вместо обычного ret стоит reti, которая делает ещё sei. Поэтому сразу же по возрвращение в фиктивный обработчик
 *     выполняется cli. Эта машинная комманда гарантировано должна выполнится. Поэтому следующее прерывание может возникнуть только возвращения из
 *     фиктивного обработчика.
 *  5. Аттрибут used при объявлении релаьного обработчика гарантирует, что функция не будет выкинута как неиспользуемая при оптимизации.
 *  6. Не обращайте внимания на warning: '****' appears to be a misspelled signal handler. Он означает лишь то, что имя функции,
 *     объявленной как обработчик прерывания, не соответсвует зарезервированным именам.
 *     Поэтому адрес этой функции не будет добавлен в таблицу прерываний.
 *  7. Если необходимо в качестве обработчика прерываний задать метод объекта класса, то
 *     необходимо получить указатель на обычную функцию, зная указатель на функцию-член и объект класса.
 *     Это позволяет делать GCC при использовании опции -Wno-pmf-conversions
 *     Пример смотри в примере.
 *
 *
 *  ~~~ Пример использования: ~~~
    // глобально..
    INTERRUPT_POINTER_DECLARE(INT2);

    // глобальная функция
    INTERRUPT_HANDLER(func);

    // где угодно...
    INT2_handler = InterruptHandler::from_function<&func>();


    // метод класса
    class Cl
	{
	public:
		INTERRUPT_HANDLER(cfunc)
		{
			sei ();
		}
	};

	// где угодно...
	Cl obj; // объект класса
	INT2_handler = InterruptHandler::from_method<Cl,&Cl::cfunc> (&obj);
 *
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <cpp/delegate/Clugston/FastDelegate.h>
using namespace fastdelegate;

typedef FastDelegate<void ()> InterruptHandler;

#define INTERRUPT_POINTER_DECLARE(NAME_without_vect)\
	InterruptHandler NAME_without_vect ## _handler;\
	extern "C" void NAME_without_vect ## _vect (void) __attribute__ ((signal, used, externally_visible));\
	void NAME_without_vect ## _vect (void)\
	{\
		NAME_without_vect ## _handler ();\
	}
////	extern "C" void NAME_without_vect ## _vect (void) __attribute__ ((signal, used, externally_visible, naked));
//	void NAME_without_vect ## _vect (void)
//	{
//		asm volatile ("push r30");
//		asm volatile ("push r31");
//		asm volatile ("push r24");
//		asm volatile ("push r25");
//		NAME_without_vect ## _handler ();
//		asm volatile ("cli");
//		asm volatile ("pop r25");
//		asm volatile ("pop r24");
//		asm volatile ("pop r31");
//		asm volatile ("pop r30");
//		asm volatile ("reti");
//	}

//#define INTERRUPT_HANDLER(function_name)
//	void __attribute__ ((signal, used)) function_name ()
#define INTERRUPT_HANDLER(function_name)\
	void function_name ()


// ------------------------------------------------------------------------------------------------
// ------------------------------------- !CAUTION! ------------------------------------------------
// ------------------------------- TERRIBLE OVERHEAD HERE -----------------------------------------
// ------------------------------------------------------------------------------------------------
// Для всех (!) прерываний я объявляю обработчики и делегаты.
// Это занимает   3,8 кб    во flash!
//			  и   136 байт  в  ram!

#ifdef INT0_vect
INTERRUPT_POINTER_DECLARE(INT0)
#endif

#ifdef INT1_vect
INTERRUPT_POINTER_DECLARE(INT1)
#endif

#ifdef INT2_vect
INTERRUPT_POINTER_DECLARE(INT2)
#endif

#ifdef INT3_vect
INTERRUPT_POINTER_DECLARE(INT3)
#endif

#ifdef INT4_vect
INTERRUPT_POINTER_DECLARE(INT4)
#endif

#ifdef INT5_vect
INTERRUPT_POINTER_DECLARE(INT5)
#endif

#ifdef INT6_vect
INTERRUPT_POINTER_DECLARE(INT6)
#endif

#ifdef INT7_vect
INTERRUPT_POINTER_DECLARE(INT7)
#endif

#ifdef TIMER2_COMP_vect
INTERRUPT_POINTER_DECLARE(TIMER2_COMP)
#endif

#ifdef TIMER2_OVF_vect
INTERRUPT_POINTER_DECLARE(TIMER2_OVF)
#endif

#ifdef TIMER1_CAPT_vect
INTERRUPT_POINTER_DECLARE(TIMER1_CAPT)
#endif

#ifdef TIMER1_COMPA_vect
INTERRUPT_POINTER_DECLARE(TIMER1_COMPA)
#endif

#ifdef TIMER1_COMPB_vect
INTERRUPT_POINTER_DECLARE(TIMER1_COMPB)
#endif

#ifdef TIMER1_COMPC_vect
INTERRUPT_POINTER_DECLARE(TIMER1_COMPC)
#endif

#ifdef TIMER1_OVF_vect
INTERRUPT_POINTER_DECLARE(TIMER1_OVF)
#endif

#ifdef TIMER0_COMP_vect
INTERRUPT_POINTER_DECLARE(TIMER0_COMP)
#endif

#ifdef TIMER0_OVF_vect
INTERRUPT_POINTER_DECLARE(TIMER0_OVF)
#endif

#ifdef CANIT_vect
INTERRUPT_POINTER_DECLARE(CANIT)
#endif

#ifdef OVRIT_vect
INTERRUPT_POINTER_DECLARE(OVRIT)
#endif

#ifdef SPI_STC_vect
INTERRUPT_POINTER_DECLARE(SPI_STC)
#endif

#ifdef USART0_RX_vect
INTERRUPT_POINTER_DECLARE(USART0_RX)
#endif

#ifdef USART0_UDRE_vect
INTERRUPT_POINTER_DECLARE(USART0_UDRE)
#endif

#ifdef USART0_TX_vect
INTERRUPT_POINTER_DECLARE(USART0_TX)
#endif

#ifdef ANALOG_COMP_vect
INTERRUPT_POINTER_DECLARE(ANALOG_COMP)
#endif

#ifdef ADC_vect
INTERRUPT_POINTER_DECLARE(ADC)
#endif

#ifdef EE_READY_vect
INTERRUPT_POINTER_DECLARE(EE_READY)
#endif

#ifdef TIMER3_CAPT_vect
INTERRUPT_POINTER_DECLARE(TIMER3_CAPT)
#endif

#ifdef TIMER3_COMPA_vect
INTERRUPT_POINTER_DECLARE(TIMER3_COMPA)
#endif

#ifdef TIMER3_COMPB_vect
INTERRUPT_POINTER_DECLARE(TIMER3_COMPB)
#endif

#ifdef TIMER3_COMPC_vect
INTERRUPT_POINTER_DECLARE(TIMER3_COMPC)
#endif

#ifdef TIMER3_OVF_vect
INTERRUPT_POINTER_DECLARE(TIMER3_OVF)
#endif

#ifdef USART1_RX_vect
INTERRUPT_POINTER_DECLARE(USART1_RX)
#endif

#ifdef USART1_UDRE_vect
INTERRUPT_POINTER_DECLARE(USART1_UDRE)
#endif

#ifdef USART1_TX_vect
INTERRUPT_POINTER_DECLARE(USART1_TX)
#endif

#ifdef TWI_vect
INTERRUPT_POINTER_DECLARE(TWI)
#endif

#ifdef SPM_READY_vect
INTERRUPT_POINTER_DECLARE(SPM_READY)
#endif





#endif /* INTERRUPT_H_ */
