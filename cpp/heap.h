/*
 * heap.h
 *
 * Created: 30.10.2014 9:48:11
 *  Author: nazemnyh
 */ 


#ifndef HEAP_H_
#define HEAP_H_

#include <avr/io.h>
#include <stdlib.h>

template <typename Type, uint8_t size>
class Heap
{
public:
	Heap (Type initValue)
	{
		static_assert (size < 255, "Size of Heap must be less then 255");
		for (Entry &e : buffer)
		{
			e.inUse = false;
			e.val = initValue;
		}
	}
	
	uint8_t save (const Type &value)
	{
		uint8_t i = 0;
		for (Entry &e : buffer)
		{
			i ++;
			if ( !e.inUse )
			{
				e.inUse = true;
				e.val = value;
				return i;
			}
		}
		return 0;
	}
	
	uint8_t get (uint8_t id, Type &value)
	{
		id = id - 1;
		if ( buffer[id].inUse )
		{
			value = buffer[id].val;
			return true;
		}
		else
			return false;
	}
	
	void del (uint8_t id)
	{
		buffer[id-1].inUse = false;
	}
	
private:
	struct Entry
	{
		uint8_t inUse;
		Type val;
	};
	Entry buffer[size];
};

#endif /* HEAP_H_ */