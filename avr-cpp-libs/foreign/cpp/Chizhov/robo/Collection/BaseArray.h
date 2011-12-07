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

#ifndef __AVR_CPP_BASE_ARRAY_H__
#define __AVR_CPP_BASE_ARRAY_H__


/**********************************************************************************************************************\

	AVRCppLib collection objects

\**********************************************************************************************************************/

namespace AVRCpp
{
	namespace Collection
	{
	

/**********************************************************************************************************************\

	Base array class

	This class should never be instantized directly!

\**********************************************************************************************************************/

template <typename DataType, typename SizeType, typename ListType> class BaseArray
{
	protected:
		ListType data;
		SizeType current_size;

		/**
		 *	Resize array to certain length
		 */
		inline bool Resize(const SizeType size, const DataType &values = DataType())
		{
			// Fill new sections with default value
			for (register SizeType index = this->current_size; index < size; index++)
			{
				this->data[index] = values;
			}

			this->current_size = size;

			return true;
		}

		/**
		 *  Add item to the end of array
		 */
		inline bool Add(const DataType &value)
		{
			// Increase size and add item
			this->data[this->current_size++] = value;

			return true;
		}

		/**
		 *  Insert item to the pos
		 */
		inline bool Insert(const DataType &value, const SizeType pos)
		{
			// Shift data to right when adding to middle
			if (pos < this->current_size)
			{
				for (register SizeType index = this->current_size; index > pos; index--)
				{
					this->data[index] = this->data[index - 1];
				}
			}

			// Increase size
			this->current_size++;
			this->data[pos] = value;

			return true;
		}

		/**
		 *	Remove item at pos
		 */
		inline bool Remove(const SizeType pos)
		{
			// Check constraints
			if (pos >= this->current_size)
			{
				return false;
			}

			// Shift data to left when removing from middle
			if (pos < this->current_size - 1)
			{
				for (register SizeType index = pos + 1; index < this->current_size; index++)
				{
					this->data[index - 1] = this->data[index];
				}
			}

			// Decrease size
			this->current_size--;

			return true;
		}

	public:

		/**
		 *	Constructor
		 */
		BaseArray()
		{
			this->current_size	= 0;
		}

		/**
		 *	Return array size
		 */
		inline SizeType GetSize(void)
		{
			return this->current_size;
		}

		/**
		 *	Return whether the array is empty or not
		 */
		inline bool IsEmpty(void)
		{
			return (this->current_size == 0);
		}

		/**
		 *	Clear array
		 */
		inline bool Clear()
		{
			this->current_size = 0;

			return true;
		}

		/**
		 *  Return reference of item at specified position
		 *  NB! For speed purposes does not check constraints!
		 */
		inline DataType &At(SizeType pos)
		{
			return this->data[pos];
		}

}; // class BaseArray


/**********************************************************************************************************************/

	} // namespace Collection
	
} // namespace AVRCpp


/**********************************************************************************************************************/

#endif // ifndef __AVR_CPP_BASE_ARRAY_H__
