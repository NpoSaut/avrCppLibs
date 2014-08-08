#ifndef __AVR_CPP_IO_H_HOLE_FIELD__
#define __AVR_CPP_IO_H_HOLE_FIELD__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif

// Дырявые поля используются
// для корректной работы c разбросанными битами
template < typename Enum, uint32_t mask >
class HoleField
{
public:
	void operator= (Enum a) volatile
	{
		var = Enum ( (var & (~mask)) | (a & mask) );
	}
	void operator= (Enum a)
	{
		var = Enum ( (var & (~mask)) | (a & mask) );
	}
	operator Enum ()
	{
		return Enum (var & mask);
	}
private:
	Enum var;
};

#endif // ifndef __AVR_CPP_IO_H_HOLE_FIELD__

