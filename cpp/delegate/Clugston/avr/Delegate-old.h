//
//	Efficient delegates in C++ that generate only two lines of asm code!
//  Documentation is found at http://www.codeproject.com/cpp/FastDelegate.asp
//
//						- Don Clugston, Mar 2004.
//		Major contributions were made by Jody Hagins.
//
//
//		Adapted for WinAVR by Lauri Kirikal, Mar 2007.
//
// History:
// 24-Apr-04 1.0  * Submitted to CodeProject. 
// 28-Apr-04 1.1  * Prevent most unsafe uses of evil static function hack.
//				  * Improved syntax for horrible_cast (thanks Paul Bludov).
//				  * Tested on Metrowerks MWCC and Intel ICL (IA32)
//				  * Compiled, but not run, on Comeau C++ and Intel Itanium ICL.
//	27-Jun-04 1.2 * Now works on Borland C++ Builder 5.5
//				  * Now works on /clr "managed C++" code on VC7, VC7.1
//				  * Comeau C++ now compiles without warnings.
//				  * Prevent the virtual inheritance case from being used on 
//					  VC6 and earlier, which generate incorrect code.
//				  * Improved warning and error messages. Non-standard hacks
//					 now have compile-time checks to make them safer.
//				  * implicit_cast used instead of static_cast in many cases.
//				  * If calling a const member function, a const class pointer can be used.
//				  * MakeDelegate() global helper function added to simplify pass-by-value.
//				  * Added fastdelegate.Clear()
// 16-Jul-04 1.2.1* Workaround for gcc bug (const member function pointers in templates)
// 30-Oct-04 1.3  * Support for (non-void) return values.
//				  * No more workarounds in client code!
//					 MSVC and Intel now use a clever hack invented by John Dlugosz:
//				     - The FASTDELEGATEDECLARE workaround is no longer necessary.
//					 - No more warning messages for VC6
//				  * Less use of macros. Error messages should be more comprehensible.
//				  * Added include guards
//				  * Added FastDelegate::Empty() to test if invocation is safe (Thanks Neville Franks).
//				  * Now tested on VS 2005 Express Beta, PGI C++
// 24-Dec-04 1.4  * Added DelegateMemento, to allow collections of disparate delegates.
//                * <,>,<=,>= comparison operators to allow storage in ordered containers.
//				  * Substantial reduction of code size, especially the 'Closure' class.
//				  * Standardised all the compiler-specific workarounds.
//                * MFP conversion now works for CodePlay (but not yet supported in the full code).
//                * Now compiles without warnings on _any_ supported compiler, including BCC 5.5.1
//				  * New syntax: FastDelegate< int (char *, double) >. 
// 14-Feb-05 1.4.1* Now treats =0 as equivalent to .Clear(), ==0 as equivalent to .Empty(). (Thanks elfric).
//				  * Now tested on Intel ICL for AMD64, VS2005 Beta for AMD64 and Itanium.
// 30-Mar-05 1.5  * Safebool idiom: "if (dg)" is now equivalent to "if (!dg.Empty())"
//				  * Fully supported by CodePlay VectorC
//                * Bugfix for Metrowerks: Empty() was buggy because a valid MFP can be 0 on MWCC!
//                * More optimal assignment,== and != operators for static function pointers.

/*
	Minor Changes For AVR C++ Lib Compatibility
	
	STARTS ...
*/
#ifndef __AVR_CPP_DELEGATE_H__
#define __AVR_CPP_DELEGATE_H__

#if !(defined(EXCLUDE_FAST_DELEGATE) && defined(EXCLUDE_MULTI_DELEGATE) && defined(EXLUDE_DATA_DELEGATE))

#ifndef __cplusplus
#error "Delegate.h needs C++ compiler."
#else

/*
	Header file memory.h is missing in WinAVR.
	Needed functions are defined in string.h
	
	Lauri Kirikal
*/
#ifdef __AVR__
#include <string.h>
#else
#include <memory.h> // to allow <,> comparisons
#endif

/* 
	... ENDS

	Lauri Kirikal
*/

////////////////////////////////////////////////////////////////////////////////
//						Configuration options
//
////////////////////////////////////////////////////////////////////////////////

// Uncomment the following #define for optimally-sized delegates.
// In this case, the generated asm code is almost identical to the code you'd get
// if the compiler had native support for delegates.
// It will not work on systems where sizeof(dataptr) < sizeof(codeptr). 
// Thus, it will not work for DOS compilers using the medium model.
// It will also probably fail on some DSP systems.
#define FASTDELEGATE_USESTATICFUNCTIONHACK

// Uncomment the next line to allow function declarator syntax.
// It is automatically enabled for those compilers where it is known to work.
//#define FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX

////////////////////////////////////////////////////////////////////////////////
//						Compiler identification for workarounds
//
////////////////////////////////////////////////////////////////////////////////

// Compiler identification. It's not easy to identify Visual C++ because
// many vendors fraudulently define Microsoft's identifiers.
#if defined(_MSC_VER) && !defined(__MWERKS__) && !defined(__VECTOR_C) && !defined(__ICL) && !defined(__BORLANDC__)
#define FASTDLGT_ISMSVC

#if (_MSC_VER <1300) // Many workarounds are required for VC6.
#define FASTDLGT_VC6
#pragma warning(disable:4786) // disable this ridiculous warning
#endif

#endif

// Does the compiler uses Microsoft's member function pointer structure?
// If so, it needs special treatment.
// Metrowerks CodeWarrior, Intel, and CodePlay fraudulently define Microsoft's 
// identifier, _MSC_VER. We need to filter Metrowerks out.
#if defined(_MSC_VER) && !defined(__MWERKS__)
#define FASTDLGT_MICROSOFT_MFP

#if !defined(__VECTOR_C)
// CodePlay doesn't have the __single/multi/virtual_inheritance keywords
#define FASTDLGT_HASINHERITANCE_KEYWORDS
#endif
#endif

// Does it allow function declarator syntax? The following compilers are known to work:
#if defined(FASTDLGT_ISMSVC) && (_MSC_VER >=1310) // VC 7.1
#define FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX
#endif

// Gcc(2.95+), and versions of Digital Mars, Intel and Comeau in common use.
#if defined (__DMC__) || defined(__GNUC__) || defined(__ICL) || defined(__COMO__)
#define FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX
#endif

// It works on Metrowerks MWCC 3.2.2. From boost.Config it should work on earlier ones too.
#if defined (__MWERKS__)
#define FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX
#endif

#ifdef __GNUC__ // Workaround GCC bug #8271 
	// At present, GCC doesn't recognize constness of MFPs in templates
#define FASTDELEGATE_GCC_BUG_8271
#endif



////////////////////////////////////////////////////////////////////////////////
//						General tricks used in this code
//
// (a) Error messages are generated by typdefing an array of negative size to
//     generate compile-time errors.
// (b) Warning messages on MSVC are generated by declaring unused variables, and
//	    enabling the "variable XXX is never used" warning.
// (c) Unions are used in a few compiler-specific cases to perform illegal casts.
// (d) For Microsoft and Intel, when adjusting the 'this' pointer, it's cast to
//     (char *) first to ensure that the correct number of *bytes* are added.
//
////////////////////////////////////////////////////////////////////////////////
//						Helper templates
//
////////////////////////////////////////////////////////////////////////////////

/*
	namespace names modified:
		fastdelegate -> CppDelegate
		detail -> Internal
	
	Lauri Kirikal
*/

namespace CppDelegate {
namespace Internal {	// we'll hide the implementation details in a nested namespace.

//		implicit_cast< >
// I believe this was originally going to be in the C++ standard but 
// was left out by accident. It's even milder than static_cast.
// I use it instead of static_cast<> to emphasize that I'm not doing
// anything nasty. 
// Usage is identical to static_cast<>
template <class OutputClass, class InputClass>
inline OutputClass implicit_cast(InputClass input){
	return input;
}

//		horrible_cast< >
// This is truly evil. It completely subverts C++'s type system, allowing you 
// to cast from any class to any other class. Technically, using a union 
// to perform the cast is undefined behaviour (even in C). But we can see if
// it is OK by checking that the union is the same size as each of its members.
// horrible_cast<> should only be used for compiler-specific workarounds. 
// Usage is identical to reinterpret_cast<>.

// This union is declared outside the horrible_cast because BCC 5.5.1
// can't inline a function with a nested class, and gives a warning.
template <class OutputClass, class InputClass>
union horrible_union{
	OutputClass out;
	InputClass in;
};

template <class OutputClass, class InputClass>
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

////////////////////////////////////////////////////////////////////////////////
//						Workarounds
//
////////////////////////////////////////////////////////////////////////////////

// Backwards compatibility: This macro used to be necessary in the virtual inheritance
// case for Intel and Microsoft. Now it just forward-declares the class.
#define FASTDELEGATEDECLARE(CLASSNAME)	class CLASSNAME;

// Prevent use of the static function hack with the DOS medium model.
#ifdef __MEDIUM__
#undef FASTDELEGATE_USESTATICFUNCTIONHACK
#endif

//			DefaultVoid - a workaround for 'void' templates in VC6.
//
//  (1) VC6 and earlier do not allow 'void' as a default template argument.
//  (2) They also doesn't allow you to return 'void' from a function.
//
// Workaround for (1): Declare a dummy type 'DefaultVoid' which we use
//   when we'd like to use 'void'. We convert it into 'void' and back
//   using the templates DefaultVoidToVoid<> and VoidToDefaultVoid<>.
// Workaround for (2): On VC6, the code for calling a void function is
//   identical to the code for calling a non-void function in which the
//   return value is never used, provided the return value is returned
//   in the EAX register, rather than on the stack. 
//   This is true for most fundamental types such as int, enum, void *.
//   Const void * is the safest option since it doesn't participate 
//   in any automatic conversions. But on a 16-bit compiler it might
//   cause extra code to be generated, so we disable it for all compilers
//   except for VC6 (and VC5).
#ifdef FASTDLGT_VC6
// VC6 workaround
typedef const void * DefaultVoid;
#else
// On any other compiler, just use a normal void.
typedef void DefaultVoid;
#endif

// Translate from 'DefaultVoid' to 'void'.
// Everything else is unchanged
template <class T>
struct DefaultVoidToVoid { typedef T type; };

template <>
struct DefaultVoidToVoid<DefaultVoid> {	typedef void type; };

// Translate from 'void' into 'DefaultVoid'
// Everything else is unchanged
template <class T>
struct VoidToDefaultVoid { typedef T type; };

template <>
struct VoidToDefaultVoid<void> { typedef DefaultVoid type; };



////////////////////////////////////////////////////////////////////////////////
//						Fast Delegates, part 1:
//
//		Conversion of member function pointer to a standard form
//
////////////////////////////////////////////////////////////////////////////////

// GenericClass is a fake class, ONLY used to provide a type.
// It is vitally important that it is never defined, so that the compiler doesn't
// think it can optimize the invocation. For example, Borland generates simpler
// code if it knows the class only uses single inheritance.

// Compilers using Microsoft's structure need to be treated as a special case.
#ifdef  FASTDLGT_MICROSOFT_MFP

#ifdef FASTDLGT_HASINHERITANCE_KEYWORDS
	// For Microsoft and Intel, we want to ensure that it's the most efficient type of MFP 
	// (4 bytes), even when the /vmg option is used. Declaring an empty class 
	// would give 16 byte pointers in this case....
	class __single_inheritance GenericClass;
#endif
	// ...but for Codeplay, an empty class *always* gives 4 byte pointers.
	// If compiled with the /clr option ("managed C++"), the JIT compiler thinks
	// it needs to load GenericClass before it can call any of its functions,
	// (compiles OK but crashes at runtime!), so we need to declare an 
	// empty class to make it happy.
	// Codeplay and VC4 can't cope with the unknown_inheritance case either.
	class GenericClass {};
#else
	class GenericClass;
#endif

// The size of a single inheritance member function pointer.
const int SINGLE_MEMFUNCPTR_SIZE = sizeof(void (GenericClass::*)());

//						SimplifyMemFunc< >::Convert()
//
//	A template function that converts an arbitrary member function pointer into the 
//	simplest possible form of member function pointer, using a supplied 'this' pointer.
//  According to the standard, this can be done legally with reinterpret_cast<>.
//	For (non-standard) compilers which use member function pointers which vary in size 
//  depending on the class, we need to use	knowledge of the internal structure of a 
//  member function pointer, as used by the compiler. Template specialization is used
//  to distinguish between the sizes. Because some compilers don't support partial 
//	template specialisation, I use full specialisation of a wrapper struct.

// general case -- don't know how to convert it. Force a compile failure
template <int N>
struct SimplifyMemFunc {
	template <class X, class XFuncType, class GenericMemFuncType>
	inline static GenericClass *Convert(X *pthis, XFuncType function_to_bind, 
		GenericMemFuncType &bound_func) { 
		// Unsupported member function type -- force a compile failure.
	    // (it's illegal to have a array with negative size).
		typedef char ERROR_Unsupported_member_function_pointer_on_this_compiler[N-100];
		return 0; 
	}
};

// For compilers where all member func ptrs are the same size, everything goes here.
// For non-standard compilers, only single_inheritance classes go here.
template <>
struct SimplifyMemFunc<SINGLE_MEMFUNCPTR_SIZE>  {	
	template <class X, class XFuncType, class GenericMemFuncType>
	inline static GenericClass *Convert(X *pthis, XFuncType function_to_bind, 
			GenericMemFuncType &bound_func) {
#if defined __DMC__  
		// Digital Mars doesn't allow you to cast between abitrary PMF's, 
		// even though the standard says you can. The 32-bit compiler lets you
		// static_cast through an int, but the DOS compiler doesn't.
		bound_func = horrible_cast<GenericMemFuncType>(function_to_bind);
#else 
        bound_func = reinterpret_cast<GenericMemFuncType>(function_to_bind);
#endif
        return reinterpret_cast<GenericClass *>(pthis);
	}
};

////////////////////////////////////////////////////////////////////////////////
//						Fast Delegates, part 1b:
//
//					Workarounds for Microsoft and Intel
//
////////////////////////////////////////////////////////////////////////////////


// Compilers with member function pointers which violate the standard (MSVC, Intel, Codeplay),
// need to be treated as a special case.
#ifdef FASTDLGT_MICROSOFT_MFP

/*
	... ERASED for shorter compiling time ...

	Lauri Kirikal
*/

#error "MSVC, Intel, Codeplay compilers support erased from this file."

#endif // MS/Intel hacks

}  // namespace Internal

////////////////////////////////////////////////////////////////////////////////
//						Fast Delegates, part 2:
//
//	Define the delegate storage, and cope with static functions
//
////////////////////////////////////////////////////////////////////////////////

// DelegateMemento -- an opaque structure which can hold an arbitary delegate.
// It knows nothing about the calling convention or number of arguments used by
// the function pointed to.
// It supplies comparison operators so that it can be stored in STL collections.
// It cannot be set to anything other than null, nor invoked directly: 
//   it must be converted to a specific delegate.

// Implementation:
// There are two possible implementations: the Safe method and the Evil method.
//				DelegateMemento - Safe version
//
// This implementation is standard-compliant, but a bit tricky.
// A static function pointer is stored inside the class. 
// Here are the valid values:
// +-- Static pointer --+--pThis --+-- pMemFunc-+-- Meaning------+
// |   0				|  0       |   0        | Empty          |
// |   !=0              |(dontcare)|  Invoker   | Static function|
// |   0                |  !=0     |  !=0*      | Method call    |
// +--------------------+----------+------------+----------------+
//  * For Metrowerks, this can be 0. (first virtual function in a 
//       single_inheritance class).
// When stored stored inside a specific delegate, the 'dontcare' entries are replaced
// with a reference to the delegate itself. This complicates the = and == operators
// for the delegate class.

//				DelegateMemento - Evil version
//
// For compilers where data pointers are at least as big as code pointers, it is 
// possible to store the function pointer in the this pointer, using another 
// horrible_cast. In this case the DelegateMemento implementation is simple:
// +--pThis --+-- pMemFunc-+-- Meaning---------------------+
// |    0     |  0         | Empty                         |
// |  !=0     |  !=0*      | Static function or method call|
// +----------+------------+-------------------------------+
//  * For Metrowerks, this can be 0. (first virtual function in a 
//       single_inheritance class).
// Note that the Sun C++ and MSVC documentation explicitly state that they 
// support static_cast between void * and function pointers.

/*
	DelegateMemento moved from CppDelegate namespace to CppDelegate::Internal namespace
	
	Lauri Kirikal
*/
namespace Internal
{
class DelegateMemento {
protected: 
	// the data is protected, not private, because many
	// compilers have problems with template friends.
	typedef void (Internal::GenericClass::*GenericMemFuncType)(); // arbitrary MFP.
	Internal::GenericClass *m_pthis;
	GenericMemFuncType m_pFunction;

#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
	typedef void (*GenericFuncPtr)(); // arbitrary code pointer
	GenericFuncPtr m_pStaticFunction;
#endif

public:
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
	DelegateMemento() : m_pthis(0), m_pFunction(0), m_pStaticFunction(0) {};
	void Clear() {
		m_pthis=0; m_pFunction=0; m_pStaticFunction=0;
	}
#else
	DelegateMemento() : m_pthis(0), m_pFunction(0) {};
	void Clear() {	m_pthis=0; m_pFunction=0;	}
#endif
public:
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
	inline bool IsEqual (const DelegateMemento &x) const{
	    // We have to cope with the static function pointers as a special case
		if (m_pFunction!=x.m_pFunction) return false;
		// the static function ptrs must either both be equal, or both be 0.
		if (m_pStaticFunction!=x.m_pStaticFunction) return false;
		if (m_pStaticFunction!=0) return m_pthis==x.m_pthis;
		else return true;
	}
#else // Evil Method
	inline bool IsEqual (const DelegateMemento &x) const{
		return m_pthis==x.m_pthis && m_pFunction==x.m_pFunction;
	}
#endif
	// Provide a strict weak ordering for DelegateMementos.
	inline bool IsLess(const DelegateMemento &right) const {
		// deal with static function pointers first
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		if (m_pStaticFunction !=0 || right.m_pStaticFunction!=0) 
				return m_pStaticFunction < right.m_pStaticFunction;
#endif
		if (m_pthis !=right.m_pthis) return m_pthis < right.m_pthis;
	// There are no ordering operators for member function pointers, 
	// but we can fake one by comparing each byte. The resulting ordering is
	// arbitrary (and compiler-dependent), but it permits storage in ordered STL containers.
		return memcmp(&m_pFunction, &right.m_pFunction, sizeof(m_pFunction)) < 0;

	}
	// BUGFIX (Mar 2005):
	// We can't just compare m_pFunction because on Metrowerks,
	// m_pFunction can be zero even if the delegate is not empty!
	inline bool operator ! () const		// Is it bound to anything?
	{ return m_pthis==0 && m_pFunction==0; }
	inline bool Empty() const		// Is it bound to anything?
	{ return m_pthis==0 && m_pFunction==0; }
public:
	DelegateMemento & operator = (const DelegateMemento &right)  {
		SetMementoFrom(right); 
		return *this;
	}
	inline bool operator <(const DelegateMemento &right) {
		return IsLess(right);
	}
	inline bool operator >(const DelegateMemento &right) {
		return right.IsLess(*this);
	}
	DelegateMemento (const DelegateMemento &right)  : 
		m_pthis(right.m_pthis), m_pFunction(right.m_pFunction)
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		, m_pStaticFunction (right.m_pStaticFunction)
#endif
		{}
protected:
	void SetMementoFrom(const DelegateMemento &right)  {
		m_pFunction = right.m_pFunction;
		m_pthis = right.m_pthis;
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		m_pStaticFunction = right.m_pStaticFunction;
#endif
	}
};
} // namespace Internal

//						ClosurePtr<>
//
// A private wrapper class that adds function signatures to DelegateMemento.
// It's the class that does most of the actual work.
// The signatures are specified by:
// GenericMemFunc: must be a type of GenericClass member function pointer. 
// StaticFuncPtr:  must be a type of function pointer with the same signature 
//                 as GenericMemFunc.
// UnvoidStaticFuncPtr: is the same as StaticFuncPtr, except on VC6
//                 where it never returns void (returns DefaultVoid instead).

// An outer class, FastDelegateN<>, handles the invoking and creates the
// necessary typedefs.
// This class does everything else.

namespace Internal {

template < class GenericMemFunc, class StaticFuncPtr, class UnvoidStaticFuncPtr>
class ClosurePtr : public DelegateMemento {
public:
	// These functions are for setting the delegate to a member function.

	// Here's the clever bit: we convert an arbitrary member function into a 
	// standard form. XMemFunc should be a member function of class X, but I can't 
	// enforce that here. It needs to be enforced by the wrapper class.
	template < class X, class XMemFunc >
	inline void bindmemfunc(X *pthis, XMemFunc function_to_bind ) {
		m_pthis = SimplifyMemFunc< sizeof(function_to_bind) >
			::Convert(pthis, function_to_bind, m_pFunction);
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		m_pStaticFunction = 0;
#endif
	}
	// For const member functions, we only need a const class pointer.
	// Since we know that the member function is const, it's safe to 
	// remove the const qualifier from the 'this' pointer with a const_cast.
	// VC6 has problems if we just overload 'bindmemfunc', so we give it a different name.
	template < class X, class XMemFunc>
	inline void bindconstmemfunc(const X *pthis, XMemFunc function_to_bind) {
		m_pthis= SimplifyMemFunc< sizeof(function_to_bind) >
			::Convert(const_cast<X*>(pthis), function_to_bind, m_pFunction);
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		m_pStaticFunction = 0;
#endif
	}
#ifdef FASTDELEGATE_GCC_BUG_8271	// At present, GCC doesn't recognize constness of MFPs in templates
	template < class X, class XMemFunc>
	inline void bindmemfunc(const X *pthis, XMemFunc function_to_bind) {
		bindconstmemfunc(pthis, function_to_bind);
#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)
		m_pStaticFunction = 0;
#endif
	}
#endif
	// These functions are required for invoking the stored function
	inline GenericClass *GetClosureThis() const { return m_pthis; }
	inline GenericMemFunc GetClosureMemPtr() const { return reinterpret_cast<GenericMemFunc>(m_pFunction); }

// There are a few ways of dealing with static function pointers.
// There's a standard-compliant, but tricky method.
// There's also a straightforward hack, that won't work on DOS compilers using the
// medium memory model. It's so evil that I can't recommend it, but I've
// implemented it anyway because it produces very nice asm code.

#if !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)

//				ClosurePtr<> - Safe version
//
// This implementation is standard-compliant, but a bit tricky.
// I store the function pointer inside the class, and the delegate then
// points to itself. Whenever the delegate is copied, these self-references
// must be transformed, and this complicates the = and == operators.
public:
	// The next two functions are for operator ==, =, and the copy constructor.
	// We may need to convert the m_pthis pointers, so that
	// they remain as self-references.
	template< class DerivedClass >
	inline void CopyFrom (DerivedClass *pParent, const DelegateMemento &x) {
		SetMementoFrom(x);
		if (m_pStaticFunction!=0) {
			// transform self references...
			m_pthis=reinterpret_cast<GenericClass *>(pParent);
		}
	}
	// For static functions, the 'static_function_invoker' class in the parent 
	// will be called. The parent then needs to call GetStaticFunction() to find out 
	// the actual function to invoke.
	template < class DerivedClass, class ParentInvokerSig >
	inline void bindstaticfunc(DerivedClass *pParent, ParentInvokerSig static_function_invoker, 
				StaticFuncPtr function_to_bind ) {
		if (function_to_bind==0) { // cope with assignment to 0
			m_pFunction=0;
		} else { 
			bindmemfunc(pParent, static_function_invoker);
        }
		m_pStaticFunction=reinterpret_cast<GenericFuncPtr>(function_to_bind);
	}
	inline UnvoidStaticFuncPtr GetStaticFunction() const { 
		return reinterpret_cast<UnvoidStaticFuncPtr>(m_pStaticFunction); 
	}
#else

//				ClosurePtr<> - Evil version
//
// For compilers where data pointers are at least as big as code pointers, it is 
// possible to store the function pointer in the this pointer, using another 
// horrible_cast. Invocation isn't any faster, but it saves 4 bytes, and
// speeds up comparison and assignment. If C++ provided direct language support
// for delegates, they would produce asm code that was almost identical to this.
// Note that the Sun C++ and MSVC documentation explicitly state that they 
// support static_cast between void * and function pointers.

	template <class DerivedClass>
	inline void CopyFrom (DerivedClass *pParent, const DelegateMemento &right) {
		SetMementoFrom(right);
	}
	// For static functions, the 'static_function_invoker' class in the parent 
	// will be called. The parent then needs to call GetStaticFunction() to find out 
	// the actual function to invoke.
	// ******** EVIL, EVIL CODE! *******
	template <class DerivedClass, class ParentInvokerSig>
	inline void bindstaticfunc(DerivedClass *pParent, ParentInvokerSig static_function_invoker, 
				StaticFuncPtr function_to_bind) {
		if (function_to_bind==0) { // cope with assignment to 0
			m_pFunction=0;
		} else { 
		   // We'll be ignoring the 'this' pointer, but we need to make sure we pass
		   // a valid value to bindmemfunc().
			bindmemfunc(pParent, static_function_invoker);
        }

		// WARNING! Evil hack. We store the function in the 'this' pointer!
		// Ensure that there's a compilation failure if function pointers 
		// and data pointers have different sizes.
		// If you get this error, you need to #undef FASTDELEGATE_USESTATICFUNCTIONHACK.
		typedef int ERROR_CantUseEvilMethod[sizeof(GenericClass *)==sizeof(function_to_bind) ? 1 : -1];
		m_pthis = horrible_cast<GenericClass *>(function_to_bind);
		// MSVC, SunC++ and DMC accept the following (non-standard) code:
		// m_pthis = static_cast<GenericClass *>(static_cast<void *>(function_to_bind));
		// BCC32, Comeau and DMC accept this method. MSVC7.1 needs __int64 instead of long
		// m_pthis = reinterpret_cast<GenericClass *>(reinterpret_cast<long>(function_to_bind));
	}
	// ******** EVIL, EVIL CODE! *******
	// This function will be called with an invalid 'this' pointer!!
	// We're just returning the 'this' pointer, converted into
	// a function pointer!
	inline UnvoidStaticFuncPtr GetStaticFunction() const {
		// Ensure that there's a compilation failure if function pointers 
		// and data pointers have different sizes.
		// If you get this error, you need to #undef FASTDELEGATE_USESTATICFUNCTIONHACK.
		typedef int ERROR_CantUseEvilMethod[sizeof(UnvoidStaticFuncPtr)==sizeof(this) ? 1 : -1];
		return horrible_cast<UnvoidStaticFuncPtr>(this);
	}
#endif // !defined(FASTDELEGATE_USESTATICFUNCTIONHACK)

	// Does the closure contain this static function?
	inline bool IsEqualToStaticFuncPtr(StaticFuncPtr funcptr){
		if (funcptr==0) return Empty(); 
	// For the Evil method, if it doesn't actually contain a static function, this will return an arbitrary
	// value that is not equal to any valid function pointer.
		else return funcptr==reinterpret_cast<StaticFuncPtr>(GetStaticFunction());
	}
};


} // namespace Internal

////////////////////////////////////////////////////////////////////////////////
//						Fast Delegates, part 3:
//
//				Wrapper classes to ensure type safety
//
////////////////////////////////////////////////////////////////////////////////


// Once we have the member function conversion templates, it's easy to make the
// wrapper classes. So that they will work with as many compilers as possible, 
// the classes are of the form
//   FastDelegate3<int, char *, double>
// They can cope with any combination of parameters. The max number of parameters
// allowed is 8, but it is trivial to increase this limit.
// Note that we need to treat const member functions seperately.
// All this class does is to enforce type safety, and invoke the delegate with
// the correct list of parameters.

// Because of the weird rule about the class of derived member function pointers,
// you sometimes need to apply a downcast to the 'this' pointer.
// This is the reason for the use of "implicit_cast<X*>(pthis)" in the code below. 
// If CDerivedClass is derived from CBaseClass, but doesn't override SimpleVirtualFunction,
// without this trick you'd need to write:
//		MyDelegate(static_cast<CBaseClass *>(&d), &CDerivedClass::SimpleVirtualFunction);
// but with the trick you can write
//		MyDelegate(&d, &CDerivedClass::SimpleVirtualFunction);

// RetType is the type the compiler uses in compiling the template. For VC6,
// it cannot be void. DesiredRetType is the real type which is returned from
// all of the functions. It can be void.

// Implicit conversion to "bool" is achieved using the safe_bool idiom,
// using member data pointers (MDP). This allows "if (dg)..." syntax
// Because some compilers (eg codeplay) don't have a unique value for a zero
// MDP, an extra padding member is added to the SafeBool struct.
// Some compilers (eg VC6) won't implicitly convert from 0 to an MDP, so
// in that case the static function constructor is not made explicit; this
// allows "if (dg==0) ..." to compile.


/*
	Member function names modified:
		bind -> Bind
		empty -> IsEmpty
		clear -> Clear
	
	Functions GetMemento and SetMemento: public -> protected
	
	Lauri Kirikal
*/

// N=0
template<class RetType=Internal::DefaultVoid>
class FastDelegate0 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)();
	typedef RetType (*UnvoidStaticFunctionPtr)();
	typedef RetType (Internal::GenericClass::*GenericMemFn)();
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate0 type;

	// Construction and comparison functions
	FastDelegate0() { Clear(); }
	FastDelegate0(const FastDelegate0 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate0 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate0 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate0 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate0 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate0 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate0(Y *pthis, DesiredRetType (X::* function_to_bind)() ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)()) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate0(const Y *pthis, DesiredRetType (X::* function_to_bind)() const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)() const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate0(DesiredRetType (*function_to_bind)() ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)() ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)()) {
		m_Closure.bindstaticfunc(this, &FastDelegate0::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType Invoke() const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(); }
	inline RetType operator() () const {
	return Invoke(); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear(); }
protected:
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }
private:	// Invoker for static functions
	RetType InvokeStaticFunction() const {
	return (*(m_Closure.GetStaticFunction()))(); }
};

// N=1
template<class Param1, class RetType=Internal::DefaultVoid>
class FastDelegate1 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1);
	typedef RetType (Internal::GenericClass::*GenericMemFn)(Param1 p1);
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate1 type;

	// Construction and comparison functions
	FastDelegate1() { Clear(); }
	FastDelegate1(const FastDelegate1 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate1 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate1 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate1 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate1 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate1 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate1(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1) ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1)) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate1(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate1(DesiredRetType (*function_to_bind)(Param1 p1) ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1) ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)(Param1 p1)) {
		m_Closure.bindstaticfunc(this, &FastDelegate1::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType Invoke(Param1 p1) const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(p1); }
	inline RetType operator() (Param1 p1) const {
	return Invoke(p1); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear(); }
protected:
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }
private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1) const {
	return (*(m_Closure.GetStaticFunction()))(p1); }
};

//N=2
template<class Param1, class Param2, class RetType=Internal::DefaultVoid>
class FastDelegate2 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2);
	typedef RetType (Internal::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2);
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate2 type;

	// Construction and comparison functions
	FastDelegate2() { Clear(); }
	FastDelegate2(const FastDelegate2 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate2 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate2 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate2 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate2 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate2 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate2(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2) ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2)) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate2(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate2(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2) ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2) ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2)) {
		m_Closure.bindstaticfunc(this, &FastDelegate2::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2) const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(p1, p2); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear();}
protected:
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2) const {
	return (*(m_Closure.GetStaticFunction()))(p1, p2); }
};

//N=3
template<class Param1, class Param2, class Param3, class RetType=Internal::DefaultVoid>
class FastDelegate3 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3);
	typedef RetType (Internal::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3);
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate3 type;

	// Construction and comparison functions
	FastDelegate3() { Clear(); }
	FastDelegate3(const FastDelegate3 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate3 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate3 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate3 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate3 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate3 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate3(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3) ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3)) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate3(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate3(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3) ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3) ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3)) {
		m_Closure.bindstaticfunc(this, &FastDelegate3::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3) const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear();}
protected:
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3) const {
	return (*(m_Closure.GetStaticFunction()))(p1, p2, p3); }
};

//N=4
template<class Param1, class Param2, class Param3, class Param4, class RetType=Internal::DefaultVoid>
class FastDelegate4 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4);
	typedef RetType (Internal::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4);
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate4 type;

	// Construction and comparison functions
	FastDelegate4() { Clear(); }
	FastDelegate4(const FastDelegate4 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate4 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate4 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate4 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate4 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate4 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate4(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate4(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate4(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
		m_Closure.bindstaticfunc(this, &FastDelegate4::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4) const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear();}
protected:	
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const {
	return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4); }
};

//N=5
template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=Internal::DefaultVoid>
class FastDelegate5 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5);
	typedef RetType (Internal::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5);
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate5 type;

	// Construction and comparison functions
	FastDelegate5() { Clear(); }
	FastDelegate5(const FastDelegate5 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate5 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate5 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate5 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate5 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate5 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate5(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate5(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate5(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) {
		m_Closure.bindstaticfunc(this, &FastDelegate5::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear();}
protected:
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const {
	return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4, p5); }
};

//N=6
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=Internal::DefaultVoid>
class FastDelegate6 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6);
	typedef RetType (Internal::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6);
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate6 type;

	// Construction and comparison functions
	FastDelegate6() { Clear(); }
	FastDelegate6(const FastDelegate6 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate6 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate6 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate6 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate6 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate6 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate6(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate6(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate6(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) {
		m_Closure.bindstaticfunc(this, &FastDelegate6::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear();}
protected:
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const {
	return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4, p5, p6); }
};

//N=7
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType=Internal::DefaultVoid>
class FastDelegate7 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7);
	typedef RetType (Internal::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7);
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate7 type;

	// Construction and comparison functions
	FastDelegate7() { Clear(); }
	FastDelegate7(const FastDelegate7 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate7 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate7 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate7 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate7 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate7 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate7(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate7(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate7(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) {
		m_Closure.bindstaticfunc(this, &FastDelegate7::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6, p7); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear();}
protected:
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const {
	return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4, p5, p6, p7); }
};

//N=8
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType=Internal::DefaultVoid>
class FastDelegate8 {
private:
	typedef typename Internal::DefaultVoidToVoid<RetType>::type DesiredRetType;
	typedef DesiredRetType (*StaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8);
	typedef RetType (*UnvoidStaticFunctionPtr)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8);
	typedef RetType (Internal::GenericClass::*GenericMemFn)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8);
	typedef Internal::ClosurePtr<GenericMemFn, StaticFunctionPtr, UnvoidStaticFunctionPtr> ClosureType;
	ClosureType m_Closure;
public:
	// Typedefs to aid generic programming
	typedef FastDelegate8 type;

	// Construction and comparison functions
	FastDelegate8() { Clear(); }
	FastDelegate8(const FastDelegate8 &x) {
		m_Closure.CopyFrom(this, x.m_Closure); }
	void operator = (const FastDelegate8 &x)  {
		m_Closure.CopyFrom(this, x.m_Closure); }
	bool operator ==(const FastDelegate8 &x) const {
		return m_Closure.IsEqual(x.m_Closure);	}
	bool operator !=(const FastDelegate8 &x) const {
		return !m_Closure.IsEqual(x.m_Closure); }
	bool operator <(const FastDelegate8 &x) const {
		return m_Closure.IsLess(x.m_Closure);	}
	bool operator >(const FastDelegate8 &x) const {
		return x.m_Closure.IsLess(m_Closure);	}
	// Binding to non-const member functions
	template < class X, class Y >
	FastDelegate8(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) ) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind); }
	template < class X, class Y >
	inline void Bind(Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8)) {
		m_Closure.bindmemfunc(Internal::implicit_cast<X*>(pthis), function_to_bind);	}
	// Binding to const member functions.
	template < class X, class Y >
	FastDelegate8(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X*>(pthis), function_to_bind);	}
	template < class X, class Y >
	inline void Bind(const Y *pthis, DesiredRetType (X::* function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const) {
		m_Closure.bindconstmemfunc(Internal::implicit_cast<const X *>(pthis), function_to_bind);	}
	// Static functions. We convert them into a member function call.
	// This constructor also provides implicit conversion
	FastDelegate8(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) ) {
		Bind(function_to_bind);	}
	// for efficiency, prevent creation of a temporary
	void operator = (DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) ) {
		Bind(function_to_bind);	}
	inline void Bind(DesiredRetType (*function_to_bind)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8)) {
		m_Closure.bindstaticfunc(this, &FastDelegate8::InvokeStaticFunction, 
			function_to_bind); }
	// Invoke the delegate
	RetType operator() (Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const {
	return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6, p7, p8); }
	// Implicit conversion to "bool" using the safe_bool idiom
private:
	typedef struct SafeBoolStruct {
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
    typedef StaticFunctionPtr SafeBoolStruct::*unspecified_bool_type;
public:
	operator unspecified_bool_type() const {
        return IsEmpty()? 0: &SafeBoolStruct::m_nonzero;
    }
	// necessary to allow ==0 to work despite the safe_bool idiom
	inline bool operator==(StaticFunctionPtr funcptr) {
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);	}
	inline bool operator!=(StaticFunctionPtr funcptr) { 
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);    }
	inline bool operator ! () const	{	// Is it bound to anything?
			return !m_Closure; }
	inline bool IsEmpty() const	{
			return !m_Closure; }
	void Clear() { m_Closure.Clear();}
protected:
	// Conversion to and from the DelegateMemento storage class
	const Internal::DelegateMemento & GetMemento() { return m_Closure; }
	void SetMemento(const Internal::DelegateMemento &any) { m_Closure.CopyFrom(this, any); }

private:	// Invoker for static functions
	RetType InvokeStaticFunction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const {
	return (*(m_Closure.GetStaticFunction()))(p1, p2, p3, p4, p5, p6, p7, p8); }
};

/*
	... part 4, part 5 ERASED ...

	And now on only AVR-specific code with GPL license

	Lauri Kirikal
 */

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

#ifndef EXCLUDE_FAST_DELEGATE
	typedef FastDelegate0<void> FastDelegate;
#endif

#if !defined(EXCLUDE_DATA_DELEGATE) || !defined(EXCLUDE_MULTI_DELEGATE)

	namespace Internal
	{
		template <class Delegate, class FastDelegate> bool AddFastDelegate(Delegate &delegate, FastDelegate &addable)
		{
			
			if (!delegate.me)
			{
				delegate.me = addable;
			}
			else
			{
				if (delegate.next == NULL)
				{
					delegate.next = new Delegate(addable);
					if (delegate.next == NULL) return false;
				}
				else
				{
					return delegate.next->Add(addable);
				}
			}
			
			return true;
			
		} // AddFastDelegate
		
		template <class Delegate, typename Function> bool AddFunction(Delegate &delegate, Function function)
		{
			if (!delegate.me)
			{
				delegate.me.Bind(function);
			}
			else
			{
				if (delegate.next == NULL)
				{
					delegate.next = new Delegate(function);
					if (delegate.next == NULL) return false;
				}
				else
				{
					return delegate.next->Add(function);
				}
			}
			
			return true;
			
		} // AddFunction
		
		template <class Delegate, class Object, typename MemberFunction>
				bool AddMemberFunction(Delegate &delegate, Object *object, MemberFunction function)
		{
			if (!delegate.me)
			{
				delegate.me.Bind(object, function);
			}
			else
			{
				if (delegate.next == NULL)
				{
					delegate.next = new Delegate(object, function);
					if (delegate.next == NULL) return false;
				}
				else
				{
					return delegate.next->Add(object, function);
				}
			}
			
			return true;
			
		} // AddMemberFunction
		
		template <class Delegate, class FastDelegate> bool RemoveAll(Delegate &delegate, FastDelegate &removable)
		{
			if (removable == delegate.me)
			{
				if (delegate.next == NULL)
				{
					delegate.me.Clear();
				}
				else
				{
					Delegate *cutOut, *cutOutNext = delegate.next;
					
					while (cutOutNext->me == removable)
					{
						cutOut = cutOutNext;
						cutOutNext = cutOut->next;
						
						delete cutOut;
						
						if (cutOutNext == NULL)
						{
							delegate.next = NULL;
							delegate.me.Clear();
							return true;
						}
					}
					
					delegate.me = cutOutNext->me;
					delegate.next = cutOutNext->next;
					
					delete cutOutNext;
					
					if (delegate.next != NULL)
						delegate.next->RemoveAll(removable);
					
				}
			}
			else
			{
				if (delegate.next == NULL)
					return false;
				else
					return delegate.next->RemoveAll(removable);
			}
			
			return true;
			
		} // RemoveAll
		
		template <class Delegate, class FastDelegate> bool Remove(Delegate &delegate, FastDelegate &removable)
		{
			if (removable == delegate.me)
			{
				if (delegate.next == NULL)
				{
					delegate.me.Clear();
				}
				else
				{
					Delegate *cutOut = delegate.next;
					
					delegate.me = cutOut->me;
					delegate.next = cutOut->next;
					
					delete cutOut;
				}
			}
			else
			{
				if (delegate.next == NULL)
					return false;
				else
					return delegate.next->Remove(removable);
			}
			
			return true;
			
		} // Remove
		
		template <class Delegate> void Clear(Delegate &delegate)
		{
			if (delegate.next != NULL)
			{
				delegate.next->Clear();
				delete delegate.next;
				delegate.next = NULL;
			}
			delegate.me.Clear();
			
		} // Clear
		
	} // namespace Internal

#endif // if !defined(EXCLUDE_DATA_DELEGATE) || !defined(EXCLUDE_MULTI_DELEGATE)

#ifndef EXCLUDE_DATA_DELEGATE

	template<class Derived> class DelegateController;

	template <class Controller> class DataDelegate
	{
	public:
		
		typedef void (*Function)(Controller &);
		typedef FastDelegate1<Controller &> FastDelegate;
		
	private:
		
		friend class DelegateController<Controller>;
		template <class Delegate, class FastDelegate> friend bool Internal::AddFastDelegate(Delegate &delegate, FastDelegate &addable);
		template <class Delegate, typename Function> friend bool Internal::AddFunction(Delegate &delegate, Function function);
		template <class Delegate, class Object, typename MemberFunction> friend bool Internal::AddMemberFunction(Delegate &delegate, Object *object, MemberFunction function);
		template <class Delegate, class FastDelegate> friend bool Internal::RemoveAll(Delegate &delegate, FastDelegate &removable);
		template <class Delegate, class FastDelegate> friend bool Internal::Remove(Delegate &delegate, FastDelegate &removable);
		template <class Delegate> friend void Internal::Clear(Delegate &delegate);
		
		DataDelegate<Controller> *	next;
		FastDelegate				me;
		
		DataDelegate() : next(NULL), me() {}
		DataDelegate(Function function) : next(NULL), me(function) {}
		DataDelegate(const FastDelegate &_me) : next(NULL), me(_me) {}
		template <class X, class Y> DataDelegate(X *object, void (Y::* function)(Controller &) ) : next(NULL), me(object, function) {}
		template <class X, class Y> DataDelegate(const X *object, void (Y::* function)(Controller &) const) : next(NULL), me(object, function) {}
		
		void Invoke(Controller &controller) const
		{
			if (!me.IsEmpty() )
			{
				me(controller);
				if (next != NULL) next->Invoke(controller);
			}
			
		} // OPERATOR ()
		
		inline void operator() (Controller &controller) const { Invoke(controller); }
		
	public:

		inline bool Add(FastDelegate &addable)
		{
			return Internal::AddFastDelegate<DataDelegate<Controller>, FastDelegate>(*this, addable);
			
		} // Add 1
		
		inline bool Add(Function function)
		{
			return Internal::AddFunction<DataDelegate<Controller>, Function>(*this, function);
			
		} // Add 2
		
		template <class X, class Y> inline bool Add(X *object, void (Y::* function)(Controller &) )
		{
			return Internal::AddMemberFunction<DataDelegate<Controller>, X, void (Y::*)(Controller &)>(*this, object, function);
			
		} // Add 3
		
		template <class X, class Y> inline bool Add(const X *object, void (Y::* function)(Controller &) const)
		{
			return Internal::AddMemberFunction<DataDelegate<Controller>, const X, void (Y::*)(Controller &) const>(*this, object, function);
			
		} // Add 4
		
		inline bool RemoveAll(FastDelegate &removable)
		{
			return Internal::RemoveAll<DataDelegate<Controller>, Function>(*this, removable);
			
		} // RemoveAll 1
		
		inline bool RemoveAll(Function function)
		{
			FastDelegate removable(function);
			
			return RemoveAll(removable);
			
		} // RemoveAll 2
		
		template <class X, class Y> inline bool RemoveAll(X *object, void (Y::* function)(Controller &) )
		{
			FastDelegate removable(object, function);
			
			return RemoveAll(removable);
			
		} // RemoveAll 3
		
		template <class X, class Y> inline bool RemoveAll(const X *object, void (Y::* function)(Controller &) const)
		{
			FastDelegate removable(object, function);
			
			return RemoveAll(removable);
			
		} // RemoveAll 4
		
		inline bool Remove(FastDelegate &removable)
		{
			return Internal::Remove<DataDelegate<Controller>, FastDelegate>(*this, removable);
			
		} // Remove 1
		
		inline bool Remove(Function function)
		{
			FastDelegate removable(function);
			
			return Remove(removable);
			
		} // Remove 2
		
		template <class X, class Y> inline bool Remove(X *object, void (Y::* function)(Controller &) )
		{
			FastDelegate removable(object, function);
			
			return Remove(removable);
			
		} // Remove 3
		
		template <class X, class Y> inline bool Remove(const X *object, void (Y::* function)(Controller &) const)
		{
			FastDelegate removable(object, function);
			
			return Remove(removable);
			
		} // Remove 4
		
		inline void Clear() { Internal::Clear<DataDelegate<Controller> >(*this); }
		inline bool IsEmpty() { return !me; }
		inline bool operator ! () { return IsEmpty(); }
		inline bool operator += (Function function) { return Add(function); }
		inline bool operator += (FastDelegate &addable) { return Add(addable); }
		inline bool operator -= (Function function) { return Remove(function); }
		inline bool operator -= (FastDelegate &removable) { return Remove(removable); }
		
		~DataDelegate() { Clear(); }
		
	}; // class DataDelegate
	
	
	template <class Derived> class DelegateController
	{
	protected:
		
		virtual bool Before() = 0;
		virtual void After() {};
		
	private:
		
		DataDelegate<Derived> dataDelegate;
		
	public:
		
		DelegateController() : dataDelegate() {}
		DataDelegate<Derived> &Delegate() { return dataDelegate; }
		
		void Invoke()
		{
			if (Before() )
			{
				dataDelegate(*((Derived *)this));
				After();
			}
			
		} // operator ()
		
		inline void operator() () { Invoke(); }
		virtual ~DelegateController() {}
		
	}; // class DelegateController

#endif // ifndef EXCLUDE_DATA_DELEGATE

#ifndef EXCLUDE_MULTI_DELEGATE
	
	class MultiDelegate
	{
	public:
		
		typedef void (*Function)(void);
		typedef FastDelegate0<> FastDelegate;
		
	private:
		
		MultiDelegate *	next;
		FastDelegate	me;
		
		template <class Delegate, class FastDelegate> friend bool Internal::AddFastDelegate(Delegate &delegate, FastDelegate &addable);
		template <class Delegate, typename Function> friend bool Internal::AddFunction(Delegate &delegate, Function function);
		template <class Delegate, class Object, typename MemberFunction> friend bool Internal::AddMemberFunction(Delegate &delegate, Object *object, MemberFunction function);
		template <class Delegate, class FastDelegate> friend bool Internal::RemoveAll(Delegate &delegate, FastDelegate &removable);
		template <class Delegate, class FastDelegate> friend bool Internal::Remove(Delegate &delegate, FastDelegate &removable);
		template <class Delegate> friend void Internal::Clear(Delegate &delegate);
		
	public:
		
		MultiDelegate() : next(NULL), me() {}
		MultiDelegate(Function function) : next(NULL), me(function) {}
		MultiDelegate(const FastDelegate &_me) : next(NULL), me(_me) {}
		template <class X, class Y> MultiDelegate(X *object, void (Y::* function)() ) : next(NULL), me(object, function) {}
		template <class X, class Y> MultiDelegate(const X *object, void (Y::* function)() const) : next(NULL), me(object, function) {}
		
		void Invoke() const
		{
			if (!me.IsEmpty() )
			{
				me();
				if (next != NULL) next->Invoke();
			}
			
		} // OPERATOR ()

		inline bool Add(FastDelegate &addable)
		{
			return Internal::AddFastDelegate<MultiDelegate, FastDelegate>(*this, addable);
			
		} // Add 1
		
		inline bool Add(Function function)
		{
			return Internal::AddFunction<MultiDelegate, Function>(*this, function);
			
		} // Add 2

		template <class X, class Y> inline bool Add(X *object, void (Y::* function)() )
		{
			return Internal::AddMemberFunction<MultiDelegate, X, void (Y::*)()>(*this, object, function);
			
		} // Add 3
		
		template <class X, class Y> inline bool Add(const X *object, void (Y::* function)() const)
		{
			return Internal::AddMemberFunction<MultiDelegate, const X, void (Y::*)() const>(*this, object, function);
			
		} // Add 4
		
		inline bool RemoveAll(FastDelegate &removable)
		{
			return Internal::RemoveAll<MultiDelegate, FastDelegate>(*this, removable);
			
		} // RemoveAll 1
		
		inline bool RemoveAll(Function function)
		{
			FastDelegate removable(function);
			
			return RemoveAll(removable);
			
		} // RemoveAll 2
		
		template <class X, class Y> inline bool RemoveAll(X *object, void (Y::* function)() )
		{
			FastDelegate removable(object, function);
			
			return RemoveAll(removable);
			
		} // RemoveAll 3
		
		template <class X, class Y> inline bool RemoveAll(const X *object, void (Y::* function)() const)
		{
			return RemoveAll<X, Y>(object, (void (Y::*)(void))function);
			
		} // RemoveAll 4
		
		inline bool Remove(FastDelegate &removable)
		{
			return Internal::Remove<MultiDelegate, FastDelegate>(*this, removable);
			
		} // Remove 1
		
		inline bool Remove(Function function)
		{
			FastDelegate removable(function);
			
			return Remove(removable);
			
		} // Remove 2
		
		template <class X, class Y> inline bool Remove(X *object, void (Y::* function)() )
		{
			FastDelegate removable(object, function);
			
			return Remove(removable);
			
		} // Remove 3
		
		template <class X, class Y> inline bool Remove(const X *object, void (Y::* function)() const)
		{
			return Remove(object, (void (Y::*)(void))function);
			
		} // Remove 4
		
		inline void Clear() { Internal::Clear<MultiDelegate>(*this);	}
		inline bool IsEmpty() const { return !me; }
		inline void operator() () const { Invoke(); }
		inline bool operator ! () const { return IsEmpty(); }
		inline bool operator += (Function function) { return Add(function); }
		inline bool operator += (FastDelegate &addable) { return Add(addable); }
		inline bool operator -= (Function function) { return Remove(function); }
		inline bool operator -= (FastDelegate &removable) { return Remove(removable); }
		~MultiDelegate() { Clear(); }
		
	}; // class MultiDelegate

#endif // ifndef EXCLUDE_MULTI_DELEGATE

 // clean up after ourselves...
#undef FASTDLGT_RETTYPE

} // namespace CppDelegate

#endif // ifdef __cplusplus
#endif // if !(defined(EXCLUDE_FAST_DELEGATE) && defined(EXCLUDE_MULTI_DELEGATE) && defined(EXLUDE_DATA_DELEGATE))
#endif // ifndef __AVR_CPP_DELEGATE_H__

