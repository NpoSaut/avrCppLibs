/*
 * can_async.h
 *
 * Created: 29.10.2014 15:49:25
 *  Author: Nazemnykh Anton <nazemnykh.anton@gmail.com>
 */ 


#ifndef CAN-ASYNC_H_
#define CAN-ASYNC_H_

#include "can-dat.h"
#include "dispatcher.h"
#include "heap.h"

template <typename CanDat, CanDat &canDat,
		  typename Dispatcher, Dispatcher &dispatcher,
			uint8_t sendQueueSize >
class CanAsync
{
public:
	CanAsync ()
		: store (Message ())
	{ }

	template<uint16_t descriptor>
	bool send (const uint8_t (&data)[descriptor & 0xF])
	{
		if ( canDat.template send<descriptor> (data) )
		{
			return true;
		}
		else
		{
			uint8_t id;
			if ( id = store.save (Message (data)) )
			{
				dispatcher.add( Command {SoftIntHandler::from_method<CanAsync, &CanAsync::trySend<descriptor> > (this), id} );
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	template<uint16_t descriptor>
	bool send ()
	{
		trySendEmpty<descriptor> (0);
		return true;
	}

	template <uint16_t descriptor>
	const uint8_t (&get())[descriptor & 0xF]
	{
		return canDat.template get<descriptor> ();
	}

	template <uint16_t descriptor>
	SoftIntHandler& rxHandler()
	{
		return canDat.template rxHandler<descriptor> ();
	}

	template <uint16_t descriptor>
	SoftIntHandler& txHandler()
	{
		return canDat.template txHandler<descriptor> ();
	}
	
	void setBusOffHandler (Delegate<void ()> handler)
	{
		canDat.setBussOffHandler(handler);
	}
	Delegate<void ()> getBusOffHandler () const
	{
		return canDat.getBusOffHandler(); 
	}
	
private:
	class Message
	{
	public:
		Message ()
			: bytes ({0,0,0,0,0,0,0,0})
		{ }
		
		Message (const Message &msg)
		{
			for (uint8_t i = 0; i < 8; i ++)
				bytes[i] = msg.bytes[i];
		}
		
		template<uint8_t size>
		Message (const uint8_t (&data)[size])
		{
			for (uint8_t i = 0; i < 8; i ++)
			bytes[i] = (i <= size) ? data[i] : 0;
		}
		
		template<uint8_t size>
		void getData (uint8_t (&data)[size])
		{
			for (uint8_t i = 0; i < size; i ++)
				data[i] = bytes[i];
		}
		
	private:
		uint8_t bytes[8];
	};
	Heap<Message, sendQueueSize> store;

	template<uint16_t descriptor>
	void trySend (uint16_t id)
	{
		Message message;
		if ( store.get(id, message) )
		{
			uint8_t data[descriptor & 0xF];
			message.getData(data);
			
			if ( canDat.template send<descriptor> (data) )
			{
				store.del (id);
			}
			else
				dispatcher.add( Command {SoftIntHandler::from_method<CanAsync, &CanAsync::trySend<descriptor> > (this), id} );
		}		
	}
	
	template<uint16_t descriptor>
	void trySendEmpty (uint16_t )
	{
		if ( !canDat.template send<descriptor> () )
			dispatcher.add( Command {SoftIntHandler::from_method<CanAsync, &CanAsync::trySendEmpty<descriptor> > (this), 0} );
	}
};


#endif /* CAN-ASYNC_H_ */