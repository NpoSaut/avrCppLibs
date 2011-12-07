/*
 *  Работа с регистрами и портами с помощью битовых полей
 *  *****************************************************
 *
 *
 */

#ifndef __AVR_CPP_IO_H__
#define __AVR_CPP_IO_H__

#include <avr/io.h>
#include <cpp/thread-safe.h>
#include <cpp/universal.h>
#include <cpp/io/timers.h>
#include <cpp/io/usart.h>
#include <cpp/io/spi.h>
#include <cpp/io/watchdog.h>



template <uint8_t n>
class Pin
{
public:
	inline void operator = (const bool& a)
	{
		port = a;
	}
	inline operator bool() const
	{
		return pin;
	}
	inline void in ()
	{
		dir = 0;
	}
	inline void inPulled ()
	{
		dir = 0;
		port = 1;
	}
	inline void out ()
	{
		dir = 1;
	}
	inline void set ()
	{
		port = 1;
	}
	inline void clear ()
	{
		port = 0;
	}
	inline void toggle ()
	{
		pin = 1;
	}

private:
	struct //PIN
	{
		volatile uint8_t		:n;
		volatile uint8_t pin	:1;
		volatile uint8_t		:(7-n);
	};
	struct //DDR
	{
		volatile uint8_t		:n;
		volatile uint8_t dir	:1;
		volatile uint8_t		:(7-n);
	};
	struct //PORT
	{
		volatile uint8_t		:n;
		volatile uint8_t port	:1;
		volatile uint8_t		:(7-n);
	};
};


union Port
{
public:
	inline void operator = (const uint8_t& a)
	{
		port_ = a;
	}
	// Чтение из p и запись в порт. DDR не копируется.
	inline void operator = (const Port& p)
	{
		port_ = (uint8_t) p;
	}
	inline operator volatile uint8_t() const
	{
		return pin_;
	}
	inline void in ()
	{
		dir_ = 0;
	}
	inline void out ()
	{
		dir_ = 0xff;
	}
	inline void toggle ()
	{
		pin_ = 0xff;
	}
	template<uint8_t pinN>
	Pin<pinN>& pin ()
	{ return (*(Pin<pinN>*)this); }

	Pin<0> pin0;
	Pin<1> pin1;
	Pin<2> pin2;
	Pin<3> pin3;
	Pin<4> pin4;
	Pin<5> pin5;
	Pin<6> pin6;
	Pin<7> pin7;
private:
	struct
	{
		volatile uint8_t pin_, dir_, port_;
	};
};


// Подбирает беззнаковый тип нужного размера (в байтах)
template <uint8_t size> struct TypeSelect;
	template <> struct TypeSelect<1> { typedef uint8_t Result; };
	template <> struct TypeSelect<2> { typedef uint16_t Result; };
	template <> struct TypeSelect<4> { typedef uint32_t Result; };

// Для имеющиейся структуры с битовыми полями Bit
// предосталяет доступ как к целому
// также сохраняя доступ к элементам через оператор ->
template< typename Bit >
class Bitfield
{
private:
	typedef typename TypeSelect< sizeof(Bit) >::Result Base;
public:
	explicit Bitfield (const Base& a = 0)
		: base (a) {}
	explicit Bitfield (const volatile Base& a)
		: base (a) {}
	Bitfield (const Bit& a)
	{
		operator= (a);
	}
	void operator = (const Base& a) volatile
	{
		base = a;
	}
	void operator = (const Bitfield& a) volatile
	{
		base = a.base;
	}
	void operator = (const Bit& a) volatile
	{
		base = horrible_cast<Base>(a);
	}
	operator volatile Base () volatile const
	{
		return base;
	}

	Bit* operator-> ()
	{
		return &bit;
	}

	union
	{
		Base base;
		Bit bit;
	};
};

// Если размер Bit не соответсвует никакому базовому типу,
// то предлагается использовать BitfieldDummy, который не выполняет никаких функций, но
// предоставляет доступ к элементам Bit через -> для единообразия
template< typename Bit >
class BitfieldDummy
{
public:
	Bit* operator-> ()
	{
		return &bit;
	}
	Bit bit;
};


// Описания классов битовых регистров
#include <cpp/io/timers.h>
#include <cpp/io/usart.h>
#include <cpp/io/can.h>


struct Register
{
	Port portA; // 0x20
	Port portB; // 0x23
	Port portC; // 0x26
	Port portD; // 0x29
	Port portE; // 0x2C
	Port portF; // 0x2F
	Port portG; // 0x32

	Bitfield< TimerInterruptFlag8 >		timer0InterruptFlag; // 0x35
	Bitfield< TimerInterruptFlag16 >	timer1InterruptFlag; // 0x36
	Bitfield< TimerInterruptFlag8 >		timer2InterruptFlag; // 0x37
	Bitfield< TimerInterruptFlag16 >	timer3InterruptFlag; // 0x38

	volatile uint8_t reserved39; // 0x39
	volatile uint8_t reserved3A; // 0x3A
	volatile uint8_t reserved3B; // 0x3B

	volatile uint8_t externalInterruptFlag; // 0x3C
	volatile uint8_t externalInterruptMask; // 0x3D

	volatile uint8_t general0; // 0x3E

	volatile uint8_t eepromControl; // 0x3F
	volatile uint8_t eepromData; // 0x40
	volatile uint16_t eepromAddress; // 0x41

	volatile uint8_t			timerGeneral; // 0x43
	Bitfield< TimerControl8 >	timer0Control; // 0x44
	volatile uint8_t			reserved45; // 0x45
	volatile uint8_t			timer0Counter; // 0x46
	volatile uint8_t			timer0Compare; // 0x47

	volatile uint8_t reserved48; // 0x48
	volatile uint8_t reserved49; // 0x49

	volatile uint8_t general1; // 0x4A
	volatile uint8_t general2; // 0x4B

	Bitfield< SpiStatusControl >	spiStatusControl; // 0x4C
	volatile uint8_t 				spiData; // 0x4E

	volatile uint8_t reserved4F; // 0x4F

	volatile uint8_t analogCompStatusControl; // 0x50

	volatile uint8_t debbuger; // 0x51

	volatile uint8_t reserved52; // 0x52

	volatile uint8_t sleepMode; // 0x53

	volatile uint8_t mcuStatus; // 0x54
	volatile uint8_t mcuControl; // 0x55
	volatile uint8_t reserved56; // 0x56
	volatile uint8_t pgmStore; // 0x57

	volatile uint8_t reserved58; // 0x58
	volatile uint8_t reserved59; // 0x59
	volatile uint8_t reserved5A; // 0x5A

	volatile uint8_t zPointerExtend; // 0x5B
	volatile uint8_t reserved5C; // 0x5C
	volatile uint16_t stackPointer; // 0x5D
	volatile uint8_t status; // 0x5F

	Bitfield< WatchdogControl > watchdogControl; // 0x60
	volatile uint8_t clockPrescale; // 0x61

	volatile uint8_t reserved62; // 0x62
	volatile uint8_t reserved63; // 0x63
	volatile uint8_t reserved64; // 0x64
	volatile uint8_t reserved65; // 0x65

	volatile uint8_t oscillatorCalibration; // 0x66

	volatile uint8_t reserved67; // 0x67
	volatile uint8_t reserved68; // 0x68

	volatile uint8_t externalInterruptAsyncControl; // 0x69
	volatile uint8_t externalInterruptSyncControl; // 0x6A

	volatile uint8_t reserved6B; // 0x6B
	volatile uint8_t reserved6C; // 0x6C
	volatile uint8_t reserved6D; // 0x6D

	Bitfield< TimerInterruptMask8 >		timer0InterruptMask; // 0x6E
	Bitfield< TimerInterruptMask16 >	timer1InterruptMask; // 0x6F
	Bitfield< TimerInterruptMask8 >		timer2InterruptMask; // 0x70
	Bitfield< TimerInterruptMask16 >	timer3InterruptMask; // 0x71

	volatile uint8_t reserved72; // 0x72
	volatile uint8_t reserved73; // 0x73

	volatile uint16_t externalMemoryControl; // 0x74

	volatile uint8_t reserved76; // 0x76
	volatile uint8_t reserved77; // 0x77

	volatile uint16_t	adcData; // 0x78
	volatile uint16_t	adcStatusControl; // 0x7A
	volatile uint8_t	adcMultiplexer; // 0x7C
	volatile uint8_t	reserved7D; // 0x7D
	volatile uint16_t	adcDigitalInputDisable; // 0x7E

	BitfieldDummy< TimerControl16 >	timer1Control; // 0x80
	volatile uint8_t 				reserved83; // 0x83
	volatile uint16_t 				timer1Counter; // 0x84
	volatile uint16_t				timer1InputCapture; // 0x86
	volatile uint16_t				timer1CompareA; // 0x88
	volatile uint16_t				timer1CompareB; // 0x8A
	volatile uint16_t				timer1CompareC; // 0x8C

	volatile uint8_t reserved8E; // 0x8E
	volatile uint8_t reserved8F; // 0x8F

	BitfieldDummy< TimerControl16 >	timer3Control; // 0x90
	volatile uint8_t 				reserved93; // 0x93
	volatile uint16_t 				timer3Counter; // 0x94
	volatile uint16_t				timer3InputCapture; // 0x96
	volatile uint16_t				timer3CompareA; // 0x98
	volatile uint16_t				timer3CompareB; // 0x9A
	volatile uint16_t				timer3CompareC; // 0x9C

	volatile uint8_t reserved9E; // 0x9E
	volatile uint8_t reserved9F; // 0x9F
	volatile uint8_t reservedA0; // 0xA0
	volatile uint8_t reservedA1; // 0xA1
	volatile uint8_t reservedA2; // 0xA2
	volatile uint8_t reservedA3; // 0xA3
	volatile uint8_t reservedA4; // 0xA4
	volatile uint8_t reservedA5; // 0xA5
	volatile uint8_t reservedA6; // 0xA6
	volatile uint8_t reservedA7; // 0xA7
	volatile uint8_t reservedA8; // 0xA8
	volatile uint8_t reservedA9; // 0xA9
	volatile uint8_t reservedAA; // 0xAA
	volatile uint8_t reservedAB; // 0xAB
	volatile uint8_t reservedAC; // 0xAC
	volatile uint8_t reservedAD; // 0xAD
	volatile uint8_t reservedAE; // 0xAE
	volatile uint8_t reservedAF; // 0xAF

	Bitfield< TimerControl8_2 > timer2Control; // 0xB0
	volatile uint8_t 			reservedB1; // 0xB1
	volatile uint8_t			timer2Counter; // 0xB2
	volatile uint8_t			timer2Compare; // 0xB3
	volatile uint8_t 			reservedB4; // 0xB4
	volatile uint8_t 			reservedB5; // 0xB5
	volatile uint8_t			timer2Async; // 0xB6
	volatile uint8_t 			reservedB7; // 0xB7

	volatile uint8_t twiBitRate; // 0xB8
	volatile uint8_t twiStatus; // 0xB9
	volatile uint8_t twiAddress; // 0xBA
	volatile uint8_t twiData; // 0xBB
	volatile uint8_t twiControl; // 0xBC

	volatile uint8_t reservedBD; // 0xBD
	volatile uint8_t reservedBE; // 0xBE
	volatile uint8_t reservedBF; // 0xBF

	BitfieldDummy< UsartControl >	usart0Control; // 0xC0
	volatile uint8_t							reservedC3;	// 0xC3
	Bitfield< UsartBaudRate >		usart0BaudRate; // 0xC4
	volatile uint8_t							usart0Data; // 0xC6

	volatile uint8_t	reservedC7;	// 0xC7

	BitfieldDummy< UsartControl >	usart1Control; // 0xC8
	volatile uint8_t							reservedCB;	// 0xCB
	Bitfield< UsartBaudRate >		usart1BaudRate; // 0xCC
	volatile uint8_t							usart1Data; // 0xCE

	volatile uint8_t reservedCF; // 0xCF
	volatile uint8_t reservedD0; // 0xD0
	volatile uint8_t reservedD1; // 0xD1
	volatile uint8_t reservedD2; // 0xD2
	volatile uint8_t reservedD3; // 0xD3
	volatile uint8_t reservedD4; // 0xD4
	volatile uint8_t reservedD5; // 0xD5
	volatile uint8_t reservedD6; // 0xD6
	volatile uint8_t reservedD7; // 0xD7

	Bitfield< CanGeneralConfig >			canGeneralConfig; // 0xD8
	Bitfield< CanGeneralStatus >			canGeneralStatus; // 0xD9
	Bitfield< CanGeneralInterruptFlag >		canGeneralInterruptFlag; // 0xDA
	Bitfield< CanGeneralInterruptEnable >	canGeneralInterruptEnable; // 0xDB
	Bitfield< CanMobEnable >				canMobEnable; // 0xDC
	Bitfield< CanMobInterruptEnable >		canMobInterruptEnable; // 0xDE
	Bitfield< CanMobInterruptFlag >			canMobInterruptFlag; // 0xE0
	BitfieldDummy< CanTiming >				canTiming; // 0xE2
	volatile uint8_t						canTimerPrescale; // 0xE5
	volatile uint16_t						canTimerCounter; // 0xE6
	volatile uint16_t						canTtcTimerCounter; // 0xE8
	volatile uint8_t						canTxErrorCounter; // 0xEA
	volatile uint8_t						canRxErrorCounter; // 0xEB
	Bitfield< CanHighestPriorityMob >		canHighestPriorityMob; // 0xEC
	Bitfield< CanPage >						canPage; // 0xED

	Bitfield< CanMobStatus >	canMobStatus; // 0xEE
	Bitfield< CanMobControl >	canMobControl; // 0xEF
	Bitfield< CanMobId >		canMobId; // 0xF0
	Bitfield< CanMobMask >		canMobMask; // 0xF4
	volatile uint16_t			canMobTimerStamp; // 0xF8
	volatile uint8_t			canMobData; // 0xFA

	volatile uint8_t reservedFB; // 0xFB
	volatile uint8_t reservedFC; // 0xFC
	volatile uint8_t reservedFD; // 0xFD
	volatile uint8_t reservedFE; // 0xFE
	volatile uint8_t reservedFF; // 0xFF
};

#define reg (*(Register*) (0x20))








//
//
//
//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++ ПИНЫ +++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ASM
//template <uint8_t n>
//class Pin
//{
//public:
//	inline void operator = (const bool& a)
//	{
//		if (a)
//			set ();
//		else
//			clear();
//	}
//	inline operator bool() const
//	{
//		return ( pin & (1 << n) );
//	}
//	inline void in ()
//	{
//		asm ("cbi %[portAdr], %[pinN]":
//				:
//				[portAdr] "M" (&dir), [pinN] "I" (n) );
//	}
//	inline void inPulled ()
//	{
//		in ();
//		set();
//	}
//	inline void out ()
//	{
//		asm ("sbi %[portAdr], %[pinN]":
//				:
//				[portAdr] "M" (&dir), [pinN] "I" (n) );
//	}
//	inline void set ()
//	{
//		asm ("sbi %[portAdr], %[pinN]":
//				:
//				[portAdr] "M" (&port), [pinN] "I" (n) );
//	}
//	inline void clear ()
//	{
//		asm ("cbi %[portAdr], %[pinN]":
//				:
//				[portAdr] "M" (&port), [pinN] "I" (n) );
//	}
//	inline void toggle ()
//	{
//		asm ("sbi %[portAdr], %[pinN]":
//				:
//				[portAdr] "M" (&pin), [pinN] "I" (n) );
//	}
//
//private:
//	volatile uint8_t pin;
//	volatile uint8_t dir;
//	volatile uint8_t port;
//};
//
//
//
//
//template <uint8_t n>
//class Pin
//{
//public:
//	inline void operator = (const bool& a)
//	{
//		if (a)
//			set ();
//		else
//			clear();
//	}
//	inline operator bool() const
//	{
//		return ( pin & (1 << n) );
//	}
//	inline void in ()
//	{
//		dir &= ~(uint8_t)(1 << n);
//	}
//	inline void inPulled ()
//	{
//		dir &= ~(uint8_t)(1 << n);
//		port |= (1 << n);
//	}
//	inline void out ()
//	{
//		dir |= (1 << n);
//	}
//	inline void set ()
//	{
//		port |= (1 << n);
//	}
//	inline void clear ()
//	{
//		port &= ~(uint8_t)(1 << n);
//	}
//	inline void toggle ()
//	{
//		pin |= (1 << n);
//	}
//
//private:
//	volatile uint8_t pin;
//	volatile uint8_t dir;
//	volatile uint8_t port;
//};
//
//#define TpinVoid Holder<PinVoid, 0x0>
//
//#ifdef PINA
//#define pinA(n) (*(Pin<n>*)(&PINA))
//#define TpinA(n) Holder<Pin<n>, 0x20>
//#endif
//#ifdef PINB
//#define pinB(n) (*(Pin<n>*)(&PINB))
//#define TpinB(n) Holder<Pin<n>, 0x23>
//#endif
//#ifdef PINC
//#define pinC(n) (*(Pin<n>*)(&PINC))
//#define TpinC(n) Holder<Pin<n>, 0x26>
//#endif
//#ifdef PIND
//#define pinD(n) (*(Pin<n>*)(&PIND))
//#define TpinD(n) Holder<Pin<n>, 0x29>
//#endif
//#ifdef PINE
//#define pinE(n) (*(Pin<n>*)(&PINE))
//#define TpinE(n) Holder<Pin<n>, 0x2C>
//#endif
//#ifdef PINF
//#define pinF(n) (*(Pin<n>*)(&PINF))
//#define TpinF(n) Holder<Pin<n>, 0x2F>
//#endif
//#ifdef PING
//#define pinG(n) (*(Pin<n>*)(&PING))
//#define TpinG(n) Holder<Pin<n>, 0x32>
//#endif
//
//
//
//
// Ещё одна реализация портов
//template<uint16_t adrPin>
//class Port
//{
//public:
//	inline void operator = (const uint8_t& a)
//	{
//		(*(uint8_t*)(port)) = a;
//	}
//	// Чтение из p и запись в порт. DDR не копируется.
//	inline void operator = (const Port& p)
//	{
//		(*(uint8_t*)(port)) = (uint8_t) p;
//	}
//	inline operator uint8_t() const
//	{
//		return (*(uint8_t*)(pin));
//	}
//	inline void in ()
//	{
//		(*(uint8_t*)(dir)) = 0;
//	}
//	inline void out ()
//	{
//		(*(uint8_t*)(dir)) = 0xff;
//	}
//	inline void toggle ()
//	{
//		(*(uint8_t*)(pin)) = 0xff;
//	}
//
//private:
//	enum
//	{
//		pin = adrPin,
//		dir = adrPin+1,
//		port = adrPin+2
//	};
//};
//typedef Port<0x20> PortA;
//typedef Port<0x23> PortB;
//
//#ifdef PINA
//#define portA  (*(Port*)   (&PINA))
//typedef Holder<Port, 0x20> TportA ;
//#endif
//#ifdef PINB
//#define portB  (*(Port*)   (&PINB))
//typedef Holder<Port, 0x23> TportB ;
//#endif
//#ifdef PINC
//#define portC  (*(Port*)   (&PINC))
//typedef Holder<Port, 0x26> TportC;
//#endif
//#ifdef PIND
//#define portD  (*(Port*)   (&PIND))
//typedef Holder<Port, 0x29> TportD;
//#endif
//#ifdef PINE
//#define portE  (*(Port*)   (&PINE))
//typedef Holder<Port, 0x2C> TportE;
//#endif
//#ifdef PINF
//#define portF  (*(Port*)   (&PINF))
//typedef Holder<Port, 0x2F> TportF;
//#endif
//#ifdef PING
//#define portG  (*(Port*)   (&PING))
//typedef Holder<Port, 0x32> TportG;
//#endif



//template <class T>
//inline void setBit (T& reg, const uint8_t& num, const bool& val)
//{
//	reg = ( reg & ~(1 << num) ) | (val << num);
//}
//
//template <class T>
//inline void setBit (Safe<T>& reg, const uint8_t& num, const bool& val)
//{
//	if (val)
//		ATOMIC reg = reg | (1 << num);
//	else
//		ATOMIC reg = reg & ~(1 << num);
////	volatile T bit = (val << num);
////	volatile T mask = ~(1 << num);
////	ATOMIC reg = ( reg & mask ) | bit;
//}

#endif // ifndef __AVR_CPP_IO_H__

