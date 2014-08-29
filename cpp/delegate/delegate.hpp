/*
	(c) Sergey Ryazanov (http://home.onego.ru/~ryazanov)

	Fast delegate compatible with C++ Standard.
*/
#ifndef SRUTIL_DELEGATE_INCLUDED
#define SRUTIL_DELEGATE_INCLUDED

// Gcc(2.95+), and versions of Digital Mars, Intel and Comeau support it
#if defined (__DMC__) || defined(__GNUC__) || defined(__ICL) || defined(__COMO__)
#define SRUTIL_DELEGATE_PREFERRED_SYNTAX
#endif

namespace srutil
{
#ifdef SRUTIL_DELEGATE_PREFERRED_SYNTAX
	template <typename TSignature> class Delegate;
	template <typename TSignature> class Delegate_invoker;
#endif
}

#ifdef _MSC_VER
#define SRUTIL_DELEGATE_CALLTYPE __fastcall
#else
#define SRUTIL_DELEGATE_CALLTYPE
#endif

#include "detail/delegate_list.hpp"

#undef SRUTIL_DELEGATE_CALLTYPE

using namespace srutil;

#endif//SRUTIL_DELEGATE_INCLUDED
