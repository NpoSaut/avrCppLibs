/*
 * interrupt-dynamic.h
 *
 * ������������ ����������� ����������
 * ***********************************
 *
 *  ~~~ ��������: ~~~
 *  AVR GCC � �������� ������������ ���������� ����� �������� ������ ���������� ������� � ������������������ �������
 *
 *
 *	~~~ ������: ~~~
 *	- ������ ������������ ������� (����. ����� ������� ������) ��� ���������� ����������
 *	- ����� ����������� ������ ������� ��������� ���������� �� ����� ���������� ���������
 *
 *
 * 	~~~ �������: ~~~
 * 	- ��������� ���������� �������� ������� �� ���������. ���������� ��������� ����� ������.
 * 	- ��� ������������� (! �������� ����� ��� ��������� ������������ !):
 * 		- � ��������� ����������� �� ���������� ����������� ������� ���������
 * 		  ������ ����, ����������� ��� ������ ������� �� ��������
 * 		- ��� ����������� �������� �� ���������� ��������� ����������� � �������� �����������.
 * 		  ��� ��� ����������� ��������� �� ��� ��������, � ������ ������.
 *
 *
 *  ~~~ ���������: ~~~
 *  INTERRUPT_POINTER_DECLARE(NAME)
 *  - ��������� ��������� � ������ NAME_handler.
 *  - ������ ��������� ����������� ���������� ���������� NAME_vect, ������� �������� ������� �� ��������� NAME_handler
 *
 *  INTERRUPT_HANDLER(function_name)
 *  - ��������� �������� ������� ����������� ���������� � ���������� signal
 *    ����� ���� ������� ����� ���� ������� � NAME_handler ��� ����, ����� ��� ���������� ��� ������������� ����������
 *
 *
 *  ~~~ �����������: ~~~
 *  1. �������� �� ��, ��� � ������� �������� ����������� ������ ������ ���������� �������,
 *     �� �� ����� ������ ����������� ���� ��������� �� ������ ������� ��������.
 *     ���� � ���, ��� �� flash ������ ����������, ����� ������ ������.
 *     ������� �������� ����� � �������� ����� ����� ������ � ������ ��������.
 *  2. AVR GCC ����� ��������� ����������������� ��������, ������� ����� ���� ������������� � ����� ������� ��� ������
 *     �������� ��������� � ��� ��������. ���� � �������� ��������� ��� �������� ������������ �� ������ ������ �������,
 *     �� ���������� �� �������� ������������ ������ � �������� ��������� �� ������ �������.
 *     ���� ������� �� ������� ���� ���������, �� ���������� ��� ������������� ����������,
 *     �� ��� ���� ��������� �������� � ���.
 *     ���������� ��������� � ������������ ������, ������ ��������� ���������� ������ ��������� �������� ���� ������������ ���������.
 *     ���� �� ���������� �� ������� �������.
 *  3. � ����� ������ � ����������� ���������� ������ ��������� ������� �� ���������.
 *     �� ��������� �� �� �����, ��� ��� �� �������, �� ������ ��������� ��� ����������������� �������� (12 ����).
 *     ������ ��� ��� ��������� ������� ������ �� ����� � ���, ��� ��� ���������� �� ����������, � ������������ �� ��,
 *     ��� ��� �������� ������������ �������.
 *     ����� �������, ���� � �������� ����������� ���������� ����������� ����� ���� ��������� � �� ������� �� ������� �������� �������,
 *     ��� �������� � ������, �� ������� �� ���������� (� ��������������!) 12 ��������� ����� ������������ �������� ������ �����������.
 *  4. ��� ������� ���� �������� ��������� ���������� ����������� � ���������� naked,
 *     �.�. ��������� ������ ��� ������� � ���� �� �������� ret(i) � �����.
 *     ��� ��������� 4 ��������, ����� ������� �������� ���������� �� ���������. ������� ������� ����������� � ����������������� ��� 4 ��������.
 *     �������� ���������� ����������� � ���������� signal, ��� ���������� ����� �������, ��� ����� �� ��� �������� ������������ ����������.
 *     � ����� ���� ������� ������ �������� ret ����� reti, ������� ������ ��� sei. ������� ����� �� �� ������������ � ��������� ����������
 *     ����������� cli. ��� �������� �������� ������������� ������ ����������. ������� ��������� ���������� ����� ���������� ������ ����������� ��
 *     ���������� �����������.
 *  5. �������� used ��� ���������� ��������� ����������� �����������, ��� ������� �� ����� �������� ��� �������������� ��� �����������.
 *  6. �� ��������� �������� �� warning: '****' appears to be a misspelled signal handler. �� �������� ���� ��, ��� ��� �������,
 *     ����������� ��� ���������� ����������, �� ������������ ����������������� ������.
 *     ������� ����� ���� ������� �� ����� �������� � ������� ����������.
 *  7. ���� ���������� � �������� ����������� ���������� ������ ����� ������� ������, ��
 *     ���������� �������� ��������� �� ������� �������, ���� ��������� �� �������-���� � ������ ������.
 *     ��� ��������� ������ GCC ��� ������������� ����� -Wno-pmf-conversions
 *     ������ ������ � �������.
 *
 *
 *  ~~~ ������ �������������: ~~~
    // ���������..
    INTERRUPT_POINTER_DECLARE(INT2);

    // ���������� �������
    INTERRUPT_HANDLER(func);

    // ��� ������...
    INT2_handler = InterruptHandler::from_function<&func>();


    // ����� ������
    class Cl
	{
	public:
		INTERRUPT_HANDLER(cfunc)
		{
			sei ();
		}
	};

	// ��� ������...
	Cl obj; // ������ ������
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
// ��� ���� (!) ���������� � �������� ����������� � ��������.
// ��� ��������   3,8 ��    �� flash!
//			  �   136 ����  �  ram!

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
