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

#ifndef __AVR_CPP_STRING_H__
#define __AVR_CPP_STRING_H__

#include "BaseString.h"

namespace AVRCpp
{
	namespace Collection
	{
		
		/**
		 * Constant capacity memory buffer is allocated when object is created.
		 */
		template <uint16_t capacity> class StaticString : public BaseString
		{
		private:
			
			/**
			 * Makes sure that required number of bytes can be stored in buffer.
			 * @return true if there is enough space, otherwise false.
			 */
			bool EnsureCapacity(uint16_t required);
			
		protected:
			
			/// Buffer container
			char content[capacity];
			
		public:
			
			/// Constructor initalizes class members.
			StaticString<capacity>() : BaseString() {}
			
		}; // class StaticString
		
		
		/**
		 * Memory is allocated from heap. The smallest memory buffer change in bytes is 
		 * specified with 'blockSize' template parameter.
		 */
		template <uint16_t blockSize = 1> class DynamicString : public BaseString
		{
		private:
			
			/// Calculates new buffer size.
			uint16_t GetBlockSize(uint16_t required);

			/**
			 * Makes sure that required number of bytes can be stored in buffer.
			 * @return true if there is enough space, otherwise false.
			 */
			bool EnsureCapacity(uint16_t required);
			
		public:
			
			/// Constructor initalizes class members.
			DynamicString<blockSize>() : BaseString() {}
			/// Destructor releases allocated memory.
			~DynamicString<blockSize>() { if (me) free(me); }
			
		}; // class DynamicString
		
		/**
		 * DynamicString specialisation.
		 */
		template <> class DynamicString<1> : public BaseString
		{
		private:
			
			/**
			 * Makes sure that required number of bytes can be stored in buffer.
			 * @return true if there is enough space, otherwise false.
			 */
			bool EnsureCapacity(uint16_t required);
			
		public:
			
			/// Constructor initalizes class members.
			DynamicString<1>() : BaseString() {}
			/// Destructor releases allocated memory.
			~DynamicString<1>() { if (me) free(me); }
			
		}; // class StaticString SPECIALISATION
		
		
		/// The most typical string type
		typedef DynamicString<1> String;
		
		
		template <uint16_t blockSize> uint16_t DynamicString<blockSize>::GetBlockSize(uint16_t required)
		{
			uint16_t k = required / blockSize + 1;
			return k * blockSize;
			
		} // GetBlockSize
		
		
		template <uint16_t blockSize> bool DynamicString<blockSize>::EnsureCapacity(uint16_t required)
		{
			if (me)
			{
				if (size < required)
				{
					required = GetBlockSize(required);
					me = StrRealloc(me, required);
				}
				else
					return true;
			}
			else
			{
				required = GetBlockSize(required);
				me = StrAlloc(required);
			}
			
			if (me)
			{
				size = required;
				return true;
			}
			
			size = 0;
			length = 0;
			return false;
			
		} // EnsureCapasity


		template <uint16_t capacity> bool StaticString<capacity>::EnsureCapacity(uint16_t required)
		{
			if (required > capacity)
				return false;
			
			me = content;
			
			return true;
			
		} // EnsureCapasity
		
	} // namespace Collection
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_STRING_H__

