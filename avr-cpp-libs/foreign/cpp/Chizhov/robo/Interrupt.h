/**********************************************************************************************************************\

	C++ library for Atmel AVR microcontrollers
	Copyright (C) 2007 Lauri Kirikal, Mikk Leini, MTÜ TTÜ Robotiklubi

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	See http://creativecommons.org/licenses/GPL/2.0/

	MTÜ TTÜ Robotiklubi  http://www.robotiklubi.ee robotiklubi@gmail.com
	Lauri Kirikal        laurikirikal@gmail.com
	Mikk Leini           mikk.leini@gmail.com

\**********************************************************************************************************************/

#ifndef __AVR_CPP_INTERRUPT_H__
#define __AVR_CPP_INTERRUPT_H__

#include "IO.h"
#include "Assembler.h"

#ifndef EXCLUDE_INTERRUPT_HANDLERS

#define INTERRUPT_HANDLER(interruptName) \
		extern "C" void interruptName ## _vect(void) __attribute__ ((signal)); \
		void interruptName ## _vect(void)

#define RECURSIVE_INTERRUPT_HANDLER(interruptName)	\
		extern "C" void interruptName ## _vect(void) __attribute__ ((interrupt)); \
		void interruptName ## _vect(void)

#define EVOCABLE_INTERRUPT_HANDLER(interruptName) \
		extern "C" void interruptName ## _vect(void) __attribute__ ((signal)); \
		void interruptName ## _vect(void) { AVRCpp::interruptName ## _struct::Evoke(); } \
		void AVRCpp::interruptName ## _struct::Evoke(void)

#define EVOCABLE_RECURSIVE_INTERRUPT_HANDLER(interruptName) \
		extern "C" void interruptName ## _vect(void) __attribute__ ((interrupt)); \
		void interruptName ## _vect(void) { AVRCpp::interruptName ## _struct::Evoke(); } \
		void AVRCpp::interruptName ## _struct::Evoke(void)

#define EXCLUDE_INTERRUPT(interruptName) \
		extern "C" void interruptName ## _vect(void) __attribute__ ((naked)); \
		void interruptName ## _vect(void) {  __asm__ __volatile__ ("reti" ::); }

#define __DELEGATE_HANDLER__(vector) \
		extern "C" void vector(void) __attribute__ ((signal)); \
		void vector (void)

#define USING_MULTI_DELEGATE(interruptName) \
		namespace AVRCpp { namespace interruptName ## _ns { namespace Internal { CppDelegate::MultiDelegate interruptName ## Delegate; } \
		void interruptName ## _struct::Evoke() { interruptName ## _ns::Internal::interruptName ## Delegate(); } \
		template <> CppDelegate::MultiDelegate & interruptName ## _struct::Me<CppDelegate::MultiDelegate>() { return interruptName ## _ns::Internal::interruptName ## Delegate; } } } \
		__DELEGATE_HANDLER__(interruptName ## _vect) { AVRCpp::interruptName ## _ns::Internal::interruptName ## Delegate(); }

#define USING_FAST_DELEGATE(interruptName) \
		namespace AVRCpp { namespace interruptName ## _ns	{ namespace Internal { CppDelegate::FastDelegate interruptName ## Delegate; } \
		void interruptName ## _struct::Evoke() { interruptName ## _ns::Internal::interruptName ## Delegate(); } \
		template <> CppDelegate::FastDelegate & interruptName ## _struct::Me<CppDelegate::FastDelegate>() { return interruptName ## _ns::Internal::interruptName ## Delegate; } } } \
		__DELEGATE_HANDLER__(interruptName ## _vect) { AVRCpp::interruptName ## _ns::Internal::interruptName ## Delegate(); }

#define USING_DATA_DELEGATE(interruptName, controllerName) \
		namespace AVRCpp { namespace interruptName ## _ns { namespace Internal { controllerName interruptName ## Controller; } \
		void interruptName ## _struct::Evoke() { interruptName ## _ns::Internal::interruptName ## Controller(); } \
		template <> CppDelegate::DataDelegate<controllerName> & interruptName ## _struct::Me<CppDelegate::DataDelegate<controllerName> >() { return interruptName ## _ns::Internal::interruptName ## Controller.Delegate(); } \
		template <> controllerName & interruptName ## _struct::Controller<controllerName>() { return (controllerName &)interruptName ## _ns::Internal::interruptName ## Controller; } } } \
		__DELEGATE_HANDLER__(interruptName ## _vect) { AVRCpp::interruptName ## _ns::Internal::interruptName ## Controller(); }


#endif // ifndef EXCLUDE_INTERRUPT_HANDLERS


/**
 * Temporarily disable interrupts.
 * Use INTERRUPT_SAFE to execute commands that need to run uninterrupted. Interruptsafe disables interrupts,
 * executes your command(s) and finally enables interrupts, if they were enabled before using INTERRUPT_SAFE.
 * To disable interrupts during one command, use the following code:
 * @code
 * // Interrupts are disabled during MyImportantCommand()
 * INTERRUPT_SAFE
 *     MyImportantCommand();
 * @endcode
 * If you need to run a block of code without any interrupts between or during the commands, enclose it
 * with braces:
 * @code
 * // Interrupts are disabled during execution of the code block in braces
 * INTERRUPT_SAFE
 * {
 *     VariableX = new_value;
 *     methodThatDependsOnVariableX();
 *     methodThatHasToFollowImmediately();
 * }
 * @endcode
 * \attention If GlobalInterrupts::Enable() is called within the INTERRUPT_SAFE block, the interrupts will be
 *			  enabled. INTERRUPT_SAFE just disables interrupts in the beginning and restores the previous
 *			  state in the end. Any code in between can freely enable and disable interrupts.
 * \note INTERRUPT_SAFE is quite effective: it adds 5 commands to your program, while manually saving SREG, disabling
 *		 interrupts and restoring SREG
 */
#define INTERRUPT_SAFE for(AVRCpp::GlobalInterrupts::Internal::InterruptDisabler safeObject; !safeObject.IsFinished(); safeObject.Finished() )

namespace AVRCpp
{
	namespace GlobalInterrupts
	{
		inline void Enable() { Assembler::SEI(); }
		inline void Disable() { Assembler::CLI(); }
		inline uint8_t IsEnabled() { return IsBitsSet<_SREG>(_SREG_I); }
		inline void WaitForInterrupt() { Assembler::SLEEP(); }
		
		namespace Internal
		{
			class InterruptDisabler
			{
			private:
			
				uint8_t sreg;
				
			public:
				
				InterruptDisabler()
				{
					sreg = SREG;
					sreg &= ~_SREG_C;
					GlobalInterrupts::Disable();
					
				} // InterruptDisabler CONSTRUCTOR
				
				inline void Finished() { sreg |= _SREG_C; }
				inline bool IsFinished() { return sreg & _SREG_C; }
				
				~InterruptDisabler()
				{
					SREG = sreg;
					
				} // InterruptDisabler DESTRUCTOR
				
			}; // class InterruptDisabler
			
		} // namespace Internal
		
	} // namespace GlobalInterrupts
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_INTERRUPT_H__
