/*
 * smartdog.h
 * ----------
 * 
 * Watchdog, говорящий предсмертное слово
 *  Перед перезагрузкой по watchdog сообщает указатель в каком месте исполняется программа.
 *
 *
 * Created: 28.10.2014 11:52:26
 *  Author: nazemnyh
 */ 


#ifndef SMARTDOG_H_
#define SMARTDOG_H_

// ------------------------------------------- Интерфейс ----------------------------------------?
// Указывает какой таймер-счетчик использовать (от этого зависит возможности настройки времени)
//#define SMARTDOG_ALARM Alarm2
// Настройка времени Watchdog
//#define SMARTDOG_WDT_TIME WDTO_30MS
// Настройка времени после которого возникате предсметрное событие (в микросекундах)
//#define SMARTDOG_ALARM_TIME 19968

// Указатель на функцию, которая будет вызывана незадолго (SMARTDOG_WDT_TIME - SMARTDOG_ALARM_TIME = 20 мс в текущих настройках) до срабатывания watchdog
//  Функция будет вызвана из обработчика прерывания, прерывания будут отключены
void (*smartdog_deathAlarm) (uint16_t lastPointer);

// Включает, выключает и сбрасывает Smartdog 
void smartdog_on ();
void smartdog_off ();
void smartdog_reset ();

// ------------------------------------------- Реализация ---------------------------------------?
#include <avr/wdt.h>
#include "cpp/timers.h"
#include "cpp/Chizhov/AVR/atomic.h"

void smartdog_internal_alarmInterrupt ();
//AlarmAdjust< SMARTDOG_ALARM > smartdog_internal_alarmTimer (5000, InterruptHandler::from_function <&smartdog_internal_alarmInterrupt> ());
//Или использовать возвращаемое значение setPeriod()
Alarm< SMARTDOG_ALARM, SMARTDOG_ALARM_TIME > smartdog_internal_alarmTimer (InterruptHandler::from_function <&smartdog_internal_alarmInterrupt> ());
//volatile uint8_t smartdog_internal_interruptCounter = 0;

void smartdog_on ()
{
	ATOMIC
	{
		wdt_enable (SMARTDOG_WDT_TIME);
		smartdog_internal_alarmTimer.start();
		//smartdog_internal_interruptCounter = 0;
	}
}

void smartdog_off ()
{
	ATOMIC
	{
		wdt_disable ();
		smartdog_internal_alarmTimer.disable();
	}
}

void smartdog_reset ()
{
	ATOMIC
	{
		wdt_reset ();
		smartdog_internal_alarmTimer.reset();
		//smartdog_internal_interruptCounter = 0;
	}
}

void smartdog_internal_alarmInterrupt ()
{
	//if (++smartdog_internal_interruptCounter >= 5)
	//{
		uint8_t ptr_h, ptr_l;
		ptr_h = *((uint8_t *) (reg.stackPointer + 19));
		ptr_l = *((uint8_t *) (reg.stackPointer + 20));
		smartdog_deathAlarm (uint16_t (ptr_h)*256 + ptr_l);
	//}
}


#endif /* SMARTDOG_H_ */