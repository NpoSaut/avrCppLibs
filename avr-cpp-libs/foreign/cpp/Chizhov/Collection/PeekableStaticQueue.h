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

#ifndef __AVR_CPP_PEEKABLE_STATIC_QUEUE_H__
#define __AVR_CPP_PEEKABLE_STATIC_QUEUE_H__

#include "StaticQueue.h"


/**********************************************************************************************************************\

	AVRCppLib collection objects

\**********************************************************************************************************************/

namespace AVRCpp
{
	namespace Collection
	{
	
/**
 * Extended StaticQueue to peek items without poping them out of the queue.
 * \attention It is not tested yet. Do not trust this code.
 */
template <typename DataType, typename SizeType, SizeType queue_capacity> class PeekableStaticQueue : public StaticQueue/*<int, uint8_t, 15>*/<DataType, SizeType, queue_capacity>
{
private:

	SizeType peek_pointer;
	
public:
	
	PeekableStaticQueue<DataType, SizeType, queue_capacity>()
	{
		StaticQueue<DataType, SizeType, queue_capacity>();
	}
	
	/**
	 * Moves peek cursor to point the next item to pop.
	 */
	inline void PeekReset()
	{
		peek_pointer = this->read_pointer;
		
	} // PeekReset
	
	/**
	 * Lets to get the value of item referenced by peek pointer (cursor).
	 * By default peek cursor is pointed to the next item to pop.
	 * You can move the peek pointer by calling CanPeekNext.
	 * It is possible to iterate through all queue items
	 * by the help of Peek, CanPeek and CanPeekNext memberfunctions:
	 \code
	 PeekableStaticQueue<uint16_t, uint8_t, 100> queue;
	 uint16_t v;
	 
	 queue.Push(5);
	 queue.Push(10);
 	 queue.Push(2);
	 
	 if (queue.CanPeek() )
		do
		{
			queue.Peek(v);
			
			if (v == 2)
			{
				queue.PopAllPeeked()
				break;
			}
			
		} while (queue.CanPeekNext() )
	 \endcode
	 */
	bool Peek(DataType &value)
	{
		// If queue empty then exit
		if (this->IsEmpty()) return false;
		
		// Read item and increase read pointer
		value = this->data[this->peek_pointer];
		
		// Queue can't be full now
		this->is_full = 0;
		
		return true;
		
	} // Peek
	
	/**
	 * Pops item out of the queue. Moves peek cursor to point the next item to pop.
	 * @return true on success, false in case queue is empty.
	 */
	bool Pop(DataType &value = 0)
	{
		bool result = ((StaticQueue<DataType, SizeType, queue_capacity> *)this)->Pop(value);
		
		peek_pointer = this->read_pointer;
		
		return result;
		
	} // Pop
	
	/**
	 * Moves peek cursor to point the next queue item.
	 * @return true on success, false if there is any queue item to peek
	 */
	bool CanPeekNext(void)
	{
		if (CanPeek() )
		{
			peek_pointer++;
			peek_pointer %= queue_capacity;
			
			return CanPeek();
		}
		
		return false;
		
	} // CanPeekNext
	
	/**
	 *	Returns whether the queue can be peeked at the current peek position
	 */
	inline bool CanPeek(void)
	{
		return this->peek_pointer != this->write_pointer;
		
	} // CanPeek

	/**
	 * Pops all items before peek cursor.
	 */
	inline void PopAllPeeked()
	{
		this->read_pointer = peek_pointer;
		
	} // FlushPeeked


}; // class PeekableStaticQueue

/**********************************************************************************************************************/

	} // namespace Collection

} // namespace AVRCpp


/**********************************************************************************************************************/

#endif // ifndef __AVR_CPP_PEEKABLE_STATIC_QUEUE_H__
