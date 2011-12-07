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

#ifndef __AVR_CPP_STATIC_ARRAY_H__
#define __AVR_CPP_STATIC_ARRAY_H__

#include "BaseArray.h"


/**********************************************************************************************************************\

	AVRCppLib collection objects

\**********************************************************************************************************************/

namespace AVRCpp
{
	namespace Collection
	{


/**********************************************************************************************************************\

	Static array class

	Fixed size list. Supports item adding, inserting and removing within limited size.

\**********************************************************************************************************************/

template <typename DataType, typename SizeType, SizeType array_capacity> class StaticArray : public BaseArray<DataType, SizeType, DataType[array_capacity]>
{	
	public:
	
		/**
		 *	Constructor
		 */
		StaticArray()
		{			
			BaseArray<DataType, SizeType, DataType[array_capacity]>();
		}
		
		/**
		 *	Resize array to certain length
		 */
		bool Resize(const SizeType size, const DataType &values = DataType())
		{
			// If new size is larger than maximum capacity then abort
			if (size >= array_capacity) return false;

			return BaseArray<DataType, SizeType, DataType[array_capacity]>::Resize(size, values);
		}

		/**
		 *  Add item to the end of array
		 */
		bool Add(const DataType &value)
		{
			// If new size is larger than maximum capacity then abort
			if (this->current_size >= array_capacity) return false;

			return BaseArray<DataType, SizeType, DataType[array_capacity]>::Add(value);
		}

		/**
		 *  Insert item to the pos
		 */
		bool Insert(const DataType &value, const SizeType pos)
		{
			// If new size is larger than maximum capacity then abort
			if (this->current_size >= array_capacity) return false;

			// Check constraints
			if (pos > this->current_size) return false;

			return BaseArray<DataType, SizeType, DataType[array_capacity]>::Insert(value, pos);
		}

  		/**
		 *	Remove item at pos
		 */
		bool Remove(const SizeType pos)
		{
			return BaseArray<DataType, SizeType, DataType[array_capacity]>::Remove(pos);
		}

		/**
		 *	Return array capacity
		 */
		SizeType GetCapacity(void)
		{
			return array_capacity;
		}
		
		/**
		 *	Return whether the array is full or not
		 */
		inline bool IsFull(void)
		{
			return (this->current_size == array_capacity);
		}

}; // class StaticArray


/**********************************************************************************************************************/

	} // namespace Collection

} // namespace AVRCpp


/**********************************************************************************************************************/

#endif // ifndef __AVR_CPP_STATIC_ARRAY_H__
