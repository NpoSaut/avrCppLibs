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

#ifndef __AVR_CPP_STATIC_QUEUE_H__
#define __AVR_CPP_STATIC_QUEUE_H__

#include "BaseQueue.h"


/**********************************************************************************************************************\

	AVRCppLib collection objects

\**********************************************************************************************************************/

namespace AVRCpp
{
	namespace Collection
	{
	

/**********************************************************************************************************************\

	Static queue (FIFO) class
	
	Supports item pushing to the end of queue and popping out first one. Fixed size.

\**********************************************************************************************************************/

template <typename DataType, typename SizeType, SizeType queue_capacity> class StaticQueue : public BaseQueue<DataType, SizeType, DataType[queue_capacity]>
{
	public:
	
		/**
		 *	Constructor
		 */
		StaticQueue()
		{
			BaseQueue<DataType, SizeType, DataType[queue_capacity]>();
		}
	
		/**
		 *  Push item to the queue
		 */
		bool Push(const DataType &value)
		{
			// If queue full then exit
			if (this->is_full) return false;

			// Write item and increase write pointer
			this->data[this->write_pointer++] = value;
			this->write_pointer %= queue_capacity;

			// If new write pointer matches read pointer then mark queue as full
			if (this->write_pointer == this->read_pointer) this->is_full = 1;

			return true;
		}
		
		/**
		 *  Pop item out of the queue
		 */
		bool Pop(DataType &value = 0)
		{
			// If queue empty then exit
			if (this->IsEmpty()) return false;

			// Read item and increase read pointer
			value = this->data[this->read_pointer++];
			this->read_pointer %= queue_capacity;
			
			// Queue can't be full now
			this->is_full = 0;
			
			return true;
		}

		/**
		 *	Return queue capacity
		 */
		inline SizeType GetCapacity(void)
		{
			return queue_capacity;
		}

		/**
		 *	Return queue size
		 */
		volatile SizeType GetSize(void)
		{
			// If queue marked full then return total size
			if (this->is_full) return queue_capacity;

 			// This functions relies on assumption that read pointer never passes write pointer!
			// Described situation cannot be evoked by user, only by software bug
			if (this->read_pointer <= this->write_pointer)
				return (this->write_pointer - this->read_pointer);
			else
				return ((queue_capacity - this->read_pointer) + this->write_pointer);
		}

}; // class StaticQueue


/**********************************************************************************************************************/

	} // namespace Collection

} // namespace AVRCpp


/**********************************************************************************************************************/

#endif // ifndef __AVR_CPP_STATIC_QUEUE_H__
