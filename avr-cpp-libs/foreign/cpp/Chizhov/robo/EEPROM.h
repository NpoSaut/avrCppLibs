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


#ifndef __AVR_CPP_EEPROM_H__
#define __AVR_CPP_EEPROM_H__

#define __EEPROM_SIMPLE__		0x00
#define __EEPROM_ERASEBLE__		0x01
#define __EEPROM_NEW_NAMES__	0x02
#define __EEPROM_OLD_FLASH__	0x04
#define __EEPROM_LONG_FLASH__	0x08

#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega8515__)

#define __EEPROM_PROPERTIES__	(__EEPROM_SIMPLE__ | __EEPROM_OLD_FLASH__)

#elif defined(__AVR_ATmega128__) || defined(__AVR_ATmega64__) 

#define __EEPROM_PROPERTIES__	(__EEPROM_SIMPLE__)

#elif defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega644__) \
		|| defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega644P__)

#define __EEPROM_PROPERTIES__	(__EEPROM_SIMPLE__ | __EEPROM_NEW_NAMES__ | __EEPROM_ERASEBLE__)

#elif defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)

#define __EEPROM_PROPERTIES__	(__EEPROM_SIMPLE__ | __EEPROM_NEW_NAMES__ | __EEPROM_ERASEBLE__ | __EEPROM_LONG_FLASH__)

#else

#error "Device is not selected or selected device is not supported."

#endif

#ifdef __EEPROM_PROPERTIES__

#include "IO.h"

#define EEPROM_SIZE E2END

#define EE_RDY_ns		EEPROM
#define EE_RDY_struct	EE_RDY_ns::ReadyInterrupt

/**********************************************************************************************************************\
	
	Universal bit and register name definitions according to device EEPROM properties.

\**********************************************************************************************************************/
#if __EEPROM_PROPERTIES__ & __EEPROM_NEW_NAMES__

#define __EEMPE__ _EEMPE
#define __EEPE__ _EEPE

#else

#define __EEMPE__ _EEMWE
#define __EEPE__ _EEWE

#endif // if __EEPROM_PROPERTIES__ & __EEPROM_NEW_NAMES__


#if __EEPROM_PROPERTIES__ & __EEPROM_LONG_FLASH__
#define __SPMEN__ _SELFPRGEN
#else
#define __SPMEN__ _SPMEN
#endif

#if __EEPROM_PROPERTIES__ & __EEPROM_OLD_FLASH__
#define __SPMCSR__	_SPMCR
#else
#define __SPMCSR__	_SPMCSR
#endif

/**********************************************************************************************************************/


/**********************************************************************************************************************\

	EEPROM read/write functionality

\**********************************************************************************************************************/

namespace AVRCpp
{
	namespace EEPROM
	{
		/**
		 * The EEPROM Ready interrupt generates a constant interrupt
		 * when the write access time has elapsed. The interrupt will not be generated during EEPROM write or SPM.
		 */
		struct ReadyInterrupt : BasicInterrupt<Bits<_EECR, _EERIE> > { __INTERRUPT_HANDLER_SUPPORT__ };
		
		/// Returns true if writing proccess is taking place.
		inline bool IsWriting() {	return IsBitsSet<_EECR>(__EEPE__); }
		/// Blocks while writing proccess is present.
		inline void WaitWhileWriting() { while (IsWriting() ); }
		/// Tries to set address even if previous writing operation has not finished.
		inline void SetAddressUnsafe(uint16_t address) { EEAR = address; }
		/// Waits for previous writing operation to finish, then sets address.
		inline void SetAddress(uint16_t address) { WaitWhileWriting(); SetAddressUnsafe(address); }
		/// Returns current address.
		inline uint16_t GetAddress() {	return EEAR; }
		/// Writes data to previously set address. It must not be interrupted by another request to read or write.
		void Write(uint8_t data);
		/// Writes data to given address. It must not be interrupted by another request to read or write.
		void Write(uint16_t address, uint8_t data);
		/// Increments current address unless it is pointing to the last byte in EEPROM memory.
		bool MoveNext();
		
		/// Read one byte from previously set (current) address.
		inline uint8_t Read()
		{
			WaitWhileWriting();
			
			SetBits<_EECR>(_EERE);
			
			return EEDR;
			
		} // Read 1
		
		/// Read one byte from given address.
		inline uint8_t Read(uint16_t address)
		{
			SetAddress(address);
			
			SetBits<_EECR>(_EERE);
			
			return EEDR;
			
		} // Read 2

#if __EEPROM_PROPERTIES__ & __EEPROM_ERASEBLE__

		enum Mode
		{
			/// In Erase Mode, data is being erased instead of written.
			EraseOnly		= _EEPM0,
			/// In Write Only Mode, data is being written without erasing the memory first. Erase memory explicitly if necessary.
			WriteOnly		= _EEPM1,
			/// In Erase Write Mode, memory at the specified address is erased and filled with new data in one operation.
			EraseAndWrite	= _EEPM0 |_EEPM1

		}; // enum Mode
		
		/// Sets EEPROM writing mode.
		inline void SetMode(Mode mode) { ChangeBits<_EECR>(_EEPM0 | _EEPM1, mode); }
		/// Returns EEPROM writing mode.
		inline uint8_t GetMode() { return SelectBits<_EECR>(_EEPM0 | _EEPM1); }
		/// Erase array of data from previously set address. After this operation, the address is set to the byte after last erased byte.
		bool Erase(uint16_t numberOfBytes);
		
#endif // if __EEPROM_PROPERTIES & __EEPROM_ERASEBLE__

		
		// Functions from this namespace should not be called by user
		namespace Internal
		{
			
			bool LoadingProcess(uint16_t lastByteAddr, uint8_t *uint8Data);
			bool SavingProcess(uint16_t lastByteAddr, uint8_t *uint8Data);
			
			template<typename T> static inline bool LoadSaveOperation(bool isSaving, T *data, uint16_t elementsCount)
			{
				// Is there anything to read or write ?
				if (sizeof(T) == 0 || elementsCount == 0)
					return true;
				
				{
					uint16_t lastByteAddr = EEAR + sizeof(T) * elementsCount - 1;
					uint8_t *uint8Data = (uint8_t *)(data);
					
					if (isSaving)
						return SavingProcess(lastByteAddr, uint8Data);
					else
						return LoadingProcess(lastByteAddr, uint8Data);
				}
				
			} // LoadSaveOperation
			
		} // namespace Internal
		
		/**
		 * Saves data to EEPROM to the current address. Data can be from any type specified with template parameter 'T'.
		 * @return true on success.
		 */
		template <typename T> bool Save(T data) { return Internal::LoadSaveOperation<T>(true, &data, 1); }

		/**
		 * Reads data from EEPROM from the current address. Data can be from any type specified with template parameter 'T'.
		 * @return true on success.
		 */
		template <typename T> bool Load(T &data) { return Internal::LoadSaveOperation<T>(false, &data, 1); }
			
		/**
		 * Save array of data to previously set address. After this operation, the address points to the first byte after the written array.
		 * @return true on success.
		 */
		template <typename T> bool SaveArray(T *data, uint16_t elementsCount) { return Internal::LoadSaveOperation<T>(true, data, elementsCount); }

		/**
		 * Load array of data from previously set address. After this operation, the address points to the first byte after the written array.
		 * @return true on success.
		 */
		template <typename T> bool LoadArray(T *data, uint16_t elementsCount) { return Internal::LoadSaveOperation<T>(false, data, elementsCount); }
		
	} // namespace EEPROM
	
} // namespace AVRCpp

/**********************************************************************************************************************/

#endif // ifdef __EEPROM_PROPERTIES__

#endif // ifndef __AVR_CPP_EEPROM_H__
