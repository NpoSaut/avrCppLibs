/*
 * timers.h
 *
 *  Created on: 11.07.2011
 *      Author: nazemnyh
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include <stdint.h>
#include <stdlib.h>
#include <cpp/interrupt-dynamic.h>
#include <cpp/io.h>



//template < 	typename control, typename counter, typename compare,
//			typename interruptMask, InterruptHandler* compareInterrupt  >
//class Alarm
//{
//public:
//	Alarm (uint32_t Tmks, InterruptHandler interruptHandler_)
//	{
//		// Устанавливаем обработчик
//		*compareInterrupt = interruptHandler_;
//
//		// Рассчёт оптимального делителя и счётчика для обеспечения Tmks
//		const uint32_t clock = F_CPU / 1000000;
//		enum
//		{
//			prescale1 = 1,
//			prescale2 = 8,
//			prescale3 = 64,
//			prescale4 = 256,
//			prescale5 = 1024
//		};
//		uint32_t result1;
//		uint32_t result2;
//		uint32_t result3;
//		uint32_t result4;
//		uint32_t result5;
//
//		typedef typename counter::Type::ParrentType cType;
//		cType n1;
//		cType n2;
//		cType n3;
//		cType n4;
//		cType n5;
//
//		// Определение масимально возможного числа, помещающегося в cType
//		cType t = 0;
//		t = t - 1; // max of unsigned variable
//		uint64_t cMax = uint64_t (t) + 1;
////		uint64_t cMax = pow (2, sizeof(cType)*8) - 1;
//
//		#define CALC(prescale, res, n)\
//			{\
//				if ( (Tmks * clock / prescale - 1) > cMax )\
//				{\
//					n = 0;\
//					res = 0;\
//				}\
//				else\
//				{\
//					cType N = Tmks * clock / prescale - 1;\
//					uint32_t r[2];\
//					r[0] = ( uint32_t (N+1) * prescale / clock);\
//					r[1] = ( uint32_t (N-0) * prescale / clock);\
//					if ( labs ( long (r[0]) - Tmks) < labs ( long (r[1]) - Tmks) )\
//					{\
//						n = N;\
//						res = r[0];\
//					}\
//					else\
//					{\
//						n = N-1;\
//						res = r[1];\
//					}\
//				}\
//			}
//
//		CALC (prescale1, result1, n1);
//		CALC (prescale2, result2, n2);
//		CALC (prescale3, result3, n3);
//		CALC (prescale4, result4, n4);
//		CALC (prescale5, result5, n5);
//
//		#undef CALC
//
//
//		#define RET_IF_BETTER(retRes, oRes1, oRes2, oRes3, oRes4)\
//			if ( labs ( long (result ## retRes) - Tmks) <= labs ( long (result ## oRes1) - Tmks) &&\
//				 labs ( long (result ## retRes) - Tmks) <= labs ( long (result ## oRes2) - Tmks) &&\
//				 labs ( long (result ## retRes) - Tmks) <= labs ( long (result ## oRes3) - Tmks) &&\
//				 labs ( long (result ## retRes) - Tmks) <= labs ( long (result ## oRes4) - Tmks) )\
//			{\
//				_(compare) = n ## retRes;\
//				cli ();\
//				_(control).clockType_ = (typename control::Type::ClockType) (retRes);\
//				cli ();\
//				period = result ## retRes;\
//			}
//
//		RET_IF_BETTER (1, 5, 2, 3, 4);
//		RET_IF_BETTER (2, 1, 5, 3, 4);
//		RET_IF_BETTER (3, 1, 2, 5, 4);
//		RET_IF_BETTER (4, 1, 2, 3, 5);
//		RET_IF_BETTER (5, 1, 2, 3, 4);
//
//		#undef RET_IF_BETTER
//
//		// Конфигурирование таймера
//		_(control).waveform_ = control::Type::ClearOnCompare;
//		_(control).outputMode_ = control::Type::OutPinDisconnect;
//		_(interruptMask).CompInterrupt = true;
//	}
//
//	void enable ()
//	{
//		_(interruptMask).CompInterrupt = true;
//	}
//	void disable ()
//	{
//		_(interruptMask).CompInterrupt = false;
//	}
//
//	static InterruptHandler interruptHandler;
//	uint32_t period;
//};
//
////  8-битные таймеры.
////  max:    262 144 мкс / F_CPU_Mhz ( для 12Мгц:    21 845 )
//typedef Alarm < Ttccr0, Ttcnt0, Tocr0, Ttimsk0, &TIMER0_COMP_handler > Alarm0;
//typedef Alarm < Ttccr2, Ttcnt2, Tocr2, Ttimsk2, &TIMER2_COMP_handler > Alarm2;
//
//// 16-битные таймеры.
////  max: 67 108 864 мкс / F_CPU_Mhz ( для 12Мгц: 5 592 405 )
//typedef Alarm < Ttccr1, Ttcnt1, Tocr1a, Ttimsk1, &TIMER1_COMPA_handler > Alarm1A;
//typedef Alarm < Ttccr3, Ttcnt3, Tocr3a, Ttimsk3, &TIMER3_COMPA_handler > Alarm3A;



template< class TimerType > struct TimerSize;
	template<> struct TimerSize< Bitfield<TimerControl8> >  { typedef uint8_t Result; };
	template<> struct TimerSize< Bitfield<TimerControl8_2> >  { typedef uint8_t Result; };
	template<> struct TimerSize< BitfieldDummy<TimerControl16> > { typedef uint16_t Result; };

template< class TimerType > struct TimerInterruptMaskType;
	template<> struct TimerInterruptMaskType< Bitfield<TimerControl8> >  { typedef Bitfield<TimerInterruptMask8>  Result; };
	template<> struct TimerInterruptMaskType< Bitfield<TimerControl8_2> >  { typedef Bitfield<TimerInterruptMask8>  Result; };
	template<> struct TimerInterruptMaskType< BitfieldDummy<TimerControl16> > { typedef Bitfield<TimerInterruptMask16> Result; };

template< class TimerType > struct TimerInterruptFlagType;
	template<> struct TimerInterruptFlagType< Bitfield<TimerControl8> >  { typedef Bitfield<TimerInterruptFlag8>  Result; };
	template<> struct TimerInterruptFlagType< Bitfield<TimerControl8_2> >  { typedef Bitfield<TimerInterruptFlag8>  Result; };
	template<> struct TimerInterruptFlagType< BitfieldDummy<TimerControl16> > { typedef Bitfield<TimerInterruptFlag16> Result; };


template < 	class TimerType, TimerType Register::* control,
			volatile typename TimerSize<TimerType>::Result Register::* counter,
			volatile typename TimerSize<TimerType>::Result Register::* compare,
			typename TimerInterruptMaskType<TimerType>::Result Register::* interruptMask,
			typename TimerInterruptFlagType<TimerType>::Result Register::* interruptFlag,
			InterruptHandler* compareInterrupt,
			uint32_t tMks>
class Alarm
{
private:
	template <typename CompareType, typename PeriodType>
	static constexpr CompareType selectCompare (PeriodType period, const uint64_t prescale)
	{
		return 	period * (F_CPU/1000000) / prescale - 1 < maxForType<CompareType>() &&
				period == (CompareType(period * (F_CPU/1000000) / prescale - 1)+1) * prescale / (F_CPU/1000000)
					? period * (F_CPU/1000000) / prescale - 1
					: maxForType<CompareType> ();
	}

	typedef decltype((reg.*control).bit) ControlType;
	typedef typename ControlType::ClockType ClockType;

public:
	Alarm (InterruptHandler interruptHandler_)
	{
		// Устанавливаем обработчик
		*compareInterrupt = interruptHandler_;

		// Рассчёт оптимального делителя и счётчика для обеспечения Tmks
		typedef typename TimerSize<TimerType>::Result CompareType;

		constexpr CompareType compare1 = selectCompare<CompareType> (tMks, 1);
		constexpr CompareType compare8 = selectCompare<CompareType> (tMks, 8);
		constexpr CompareType compare64 = selectCompare<CompareType> (tMks, 64);
		constexpr CompareType compare256 = selectCompare<CompareType> (tMks, 256);
		constexpr CompareType compare1024 = selectCompare<CompareType> (tMks, 1024);
		constexpr CompareType max = maxForType<CompareType> ();

		static_assert
			( compare1 + compare8 + compare64 + compare256 + compare1024 < 5 * max,
			  "Valid values for presclare and compare register can't be find for required period with given CPU clock. Try to change period." );

		CompareType comp;
		ClockType prsc;
		if 		( compare1		!= max ) { comp = compare1;	 	prsc = ClockType::Prescale1; }
		else if ( compare8 		!= max ) { comp = compare8;		prsc = ClockType::Prescale8; }
		else if ( compare64 	!= max ) { comp = compare64;	prsc = ClockType::Prescale64; }
		else if ( compare256	!= max ) { comp = compare256;	prsc = ClockType::Prescale256; }
		else if ( compare1024 	!= max ) { comp = compare1024;	prsc = ClockType::Prescale1024; }

		(reg.*compare) = comp;
		(reg.*control)->clockType_ = prsc;
		(reg.*control)->waveform_ = ControlType::ClearOnCompare;
		(reg.*control)->outputMode_ = ControlType::OutPinDisconnect;
		(reg.*interruptMask)->CompInterrupt = true;
	}

	void enable ()
	{
		(reg.*counter) = 0;
		(reg.*interruptFlag)->CompOccur = 1; // clear
		(reg.*interruptMask)->CompInterrupt = true;
	}

	void disable ()
	{
		(reg.*interruptMask)->CompInterrupt = false;
	}

	void newInterruptHandler (InterruptHandler interruptHandler_)
	{
		disable ();
		*compareInterrupt = interruptHandler_;
		enable ();
	}

	static constexpr uint32_t periodMks = tMks;
};

//  8-битные таймеры.
//  max:    262 144 мкс / F_CPU_Mhz ( для 12Мгц:    21 845 )
#define Alarm0 	Bitfield<TimerControl8>, &Register::timer0Control, &Register::timer0Counter, &Register::timer0Compare, &Register::timer0InterruptMask, &Register::timer0InterruptFlag, &TIMER0_COMP_handler
#define Alarm2 	Bitfield<TimerControl8_2>, &Register::timer2Control, &Register::timer2Counter, &Register::timer2Compare, &Register::timer2InterruptMask, &Register::timer2InterruptFlag, &TIMER2_COMP_handler

// 16-битные таймеры.
//  max: 67 108 864 мкс / F_CPU_Mhz ( для 12Мгц: 5 592 405 )
#define Alarm1A	BitfieldDummy<TimerControl16>, &Register::timer1Control, &Register::timer1Counter, &Register::timer1CompareA, &Register::timer1InterruptMask, &Register::timer1InterruptFlag, &TIMER1_COMPA_handler
#define Alarm3A	BitfieldDummy<TimerControl16>, &Register::timer3Control, &Register::timer3Counter, &Register::timer3CompareA, &Register::timer3InterruptMask, &Register::timer3InterruptFlag, &TIMER3_COMPA_handler


//template < 	class TimerType, TimerType Register::* control,
//			volatile typename TimerSize<TimerType>::Result Register::* counter,
//			volatile typename TimerSize<TimerType>::Result Register::* compare,
//			typename TimerInterruptMaskType<TimerType>::Result Register::* interruptMask,
//			typename TimerInterruptFlagType<TimerType>::Result Register::* interruptFlag,
//			InterruptHandler* compareInterrupt,
//			uint32_t tMks>
//class AlarmProlong
//{
//private:
//	template <typename CompareType, typename PeriodType>
//	static constexpr CompareType selectCompare (PeriodType period, const uint64_t prescale)
//	{
//		return 	period * (F_CPU/1000000) / prescale - 1 < maxForType<CompareType>() &&
//				period == (CompareType(period * (F_CPU/1000000) / prescale - 1)+1) * prescale / (F_CPU/1000000)
//					? period * (F_CPU/1000000) / prescale - 1
//					: maxForType<CompareType> ();
//	}
//
//	typedef decltype((reg.*control).bit) ControlType;
//	typedef typename ControlType::ClockType ClockType;
//
//	Alarm <TimerType, control, counter, compare, interruptMask, interruptFlag, compareInterrupt, > alarm;
//
//public:
//	AlarmProlong
//	{
//			// Устанавливаем обработчик
//			*compareInterrupt = interruptHandler_;
//
//			// Рассчёт оптимального делителя и счётчика для обеспечения Tmks
//			typedef typename TimerSize<TimerType>::Result CompareType;
//
//			constexpr CompareType compare1 = selectCompare<CompareType> (tMks, 1);
//			constexpr CompareType compare8 = selectCompare<CompareType> (tMks, 8);
//			constexpr CompareType compare64 = selectCompare<CompareType> (tMks, 64);
//			constexpr CompareType compare256 = selectCompare<CompareType> (tMks, 256);
//			constexpr CompareType compare1024 = selectCompare<CompareType> (tMks, 1024);
//			constexpr CompareType max = maxForType<CompareType> ();
//
//			static_assert
//				( compare1 + compare8 + compare64 + compare256 + compare1024 < 5 * max,
//				  "Valid values for presclare and compare register can't be find for required period with given CPU clock. Try to change period." );
//	}
//
//	void enable ()
//	{
//		(reg.*counter) = 0;
//		(reg.*interruptFlag)->CompOccur = 1; // clear
//		(reg.*interruptMask)->CompInterrupt = true;
//	}
//
//	void disable ()
//	{
//		(reg.*interruptMask)->CompInterrupt = false;
//	}
//
//	void newInterruptHandler (InterruptHandler interruptHandler_)
//	{
//		disable ();
//		*compareInterrupt = interruptHandler_;
//		enable ();
//	}
//};

template< class ClockSampleAlarm, typename TimeT = uint32_t >
class Clock
{
public:
	typedef TimeT Time;
	static constexpr uint32_t discreetMks =  ClockSampleAlarm::periodMks;

	Clock ()
		: alarm ( InterruptHandler (this, &Clock::incTime) ),
		  time (0)
	{}
	const Time& getTime () const
	{
		return time;
	}

private:
	ClockSampleAlarm alarm;
	Time time;

	void incTime ()
	{
		time ++;
	}
};

#endif /* TIMERS_H_ */
