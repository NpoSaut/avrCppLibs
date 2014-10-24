/*
 * universal.h
 *
 *	Разные универсальные удобные классы и функции
 *	*********************************************
 *
 *
 *
 */

#ifndef UNIVERSAL_H_
#define UNIVERSAL_H_

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include <cpp/loki/TypeTraits.h>

//#include <avr/cpp/Delegate.h>
//
//using namespace CppDelegate;

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);
extern "C" void __cxa_pure_virtual(void);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual(void) {};

//void * operator new(size_t size)
//{
  //return malloc(size);
//}
//void operator delete(void * ptr)
//{
  //free(ptr);
//}
//void * operator new[](size_t size)
//{
    //return malloc(size);
//}
//void operator delete[](void * ptr)
//{
    //free(ptr);
//}

// Опасное приведение типов - просто один тип назывется другим
// Единственная проверка - совпадение размеров
template <typename OutputClass, typename InputClass>
union horrible_union{
	OutputClass out;
	InputClass in;
};

template <typename OutputClass, typename InputClass>
inline OutputClass horrible_cast(const InputClass input){
	horrible_union<OutputClass, InputClass> u;
	// Cause a compile-time error if in, out and u are not the same size.
	// If the compile fails here, it means the compiler has peculiar
	// unions which would prevent the cast from working.
	typedef int ERROR_CantUseHorrible_cast[sizeof(InputClass)==sizeof(u)
		&& sizeof(InputClass)==sizeof(OutputClass) ? 1 : -1];
	u.in = input;
	return u.out;
}

// Предствление переменной, как имеющей другой тип
#define _cast(type, var) ( *(type*)(&var) )


// Представляет любую переменную как массив байт
// нумерация начинается с наименее значащего байта
template<class Base, uint8_t politic = Loki::TypeTraits<Base>::isFundamental || Loki::TypeTraits<Base>::isPointer>
class Complex;

// For ordinal types used specialization -->
template<class Base>
class Complex<Base, 1>
{
public:
	Complex (const Base& a =0)
		: base (a) {}
	Complex (const volatile Base& a)
		: base (a) {}

	template<typename... Args>
	Complex (const uint8_t& byte0, const Args&... bytes)
		{ init (0, byte0, bytes...); }
	template<typename... Args>
	Complex (const volatile uint8_t& byte0, const volatile Args&... bytes)
		{ init (0, byte0, bytes...); }

	operator Base& ()
		{ return base; }
	operator volatile Base& () volatile
		{ return base; }

	// Доступ к N-тому байту. 0 байт - наименее значащий
	uint8_t& operator[] (uint8_t byteNumber)
		{ return *((uint8_t*)this + byteNumber); }

	Base base;

private:
	void init (uint8_t n) {}

	template< typename... Args >
	void init (uint8_t n, uint8_t byte, Args... bytes)
	{
		operator[] (n) = byte;
		init (n+1, bytes...);
	}
};

template<class Base>
class Complex<Base, 0> : public Base
{
public:
	explicit Complex () : Base () {}
	Complex (const Base& a) : Base (a) {}

	using Base::operator=;

	template<typename... Args>
	Complex (const uint8_t& byte0, const Args&... bytes)
		{ init (0, byte0, bytes...); }
	template<typename... Args>
	Complex (const volatile uint8_t& byte0, const volatile Args&... bytes)
		{ init (0, byte0, bytes...); }


	// Доступ к N-тому байту. 0 байт - наименее значащий
	uint8_t& operator[] (uint8_t byteNumber)
		{ return *((uint8_t*)this + byteNumber); }

private:
	void init (uint8_t n) {}

	template< typename... Args >
	void init (uint8_t n, uint8_t byte, Args... bytes)
	{
		operator[] (n) = byte;
		init (n+1, bytes...);
	}
};

Complex<uint16_t> swap (const uint16_t& a)
{
	return {Complex<uint16_t>(a)[1], Complex<uint16_t>(a)[0]};
}

//
//#define PortDeclare(Letter) \
//	struct Port ## Letter{\
//		static volatile uint8_t &port()\
//		{\
//			return PORT ## Letter;\
//		}\
//		static volatile uint8_t &dir()\
//		{\
//			return DDR ## Letter;\
//		}\
//		static volatile uint8_t &pin()\
//		{\
//			return PIN ## Letter;\
//		}\
//	};\
//
//PortDeclare(A)
//PortDeclare(B)
//PortDeclare(C)
//PortDeclare(D)
//PortDeclare(E)
//PortDeclare(F)
//PortDeclare(G)
//
//
//class Functionoid
//{
//public:
//	virtual void operator() () = 0;
//};
//
//class Functionoid1
//{
//public:
//	virtual void operator() (uint8_t ) = 0;
//};
//
////: public Functionoid
//
//#define FunctionoidDeclare(Name) \
//class F ## Name \
//	{ \
//	public: \
//	  inline void operator() (); \
//	}; \
//F ## Name Name;
//
//#define Functionoid1Declare(Name) \
//class F ## Name : public Functionoid1 \
//	{ \
//	public: \
//	  inline void operator() (uint8_t ); \
//	}; \
//F ## Name Name;
//


template <typename RetType, typename BaseType, typename ExpType>
constexpr RetType pow (const BaseType base, const ExpType exp)
{
	return ( exp == 0 ) ? 1 : ( base * pow<RetType> (base, exp-1) );
}

template <typename TestType>
constexpr TestType maxForType (const TestType a = 0)
{
	return 	( pow<TestType>(2, sizeof(TestType)*8 -1) - 1 ) * 2 + 1;
}

#endif /* UNIVERSAL_H_ */
