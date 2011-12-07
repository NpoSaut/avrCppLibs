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

#ifndef __AVR_CPP_BASE_STRING_H__
#define __AVR_CPP_BASE_STRING_H__

#include "StrDefs.h"

namespace AVRCpp
{
	namespace Collection
	{
		
		class BaseString
		{
		protected:
			
			/// Pointer to character array
			str_t me;
			
			/// My string length
			uint16_t length;
			
			/// Number of characters currently allocated from memory
			uint16_t size;
			
			/**
			 * Makes sure that required number of bytes can be stored in buffer.
			 * Only derived class handles memory allocation.
			 * @return true if there is enough space, otherwise false.
			 */
			virtual bool EnsureCapacity(uint16_t required) = 0;
			
			/* Internal subfunctions */
			bool		SubJoin(cstr_t joinable, uint16_t joinableLength);
			bool		SubJoin(cstr_t joinable, uint16_t n, uint16_t joinableLength);
			bool		SubCopy(cstr_t source, uint16_t sourceLength);
			bool		SubReplace(uint16_t begin, uint16_t end, cstr_t replaceWith, uint16_t replaceWithLength);
			uint16_t	SubFind(uint16_t index, cstr_t value, uint16_t valueLength) const;
			uint16_t	SubIFind(uint16_t index, cstr_t value, uint16_t valueLength) const;
			
			template <uint8_t radix, uint8_t requiredSpace> bool SubFromInt(int16_t i)
			{
				if (!EnsureCapacity(requiredSpace) )
					return false;
				
				ToString(i, me, radix);
				
				length = StrLength(me);
				return true;
				
			} // SubFromInt
			
		public:
			
			/// @see BaseString::Find
			enum FindResult
			{
				NotFound = 0xFFFF
				
			}; // enum FindResult
			
			BaseString() : me(NULL), length(0), size(0) {}
			virtual ~BaseString() {}
			
			/**
			 * Returns length of this string.
			 */
			inline uint16_t GetLength() const { return length; }
			
			/**
			 * Returns pointer to null-terminated string.
			 * \note Do not modify the content pointed by the returned value. It is for read only!
			 */
			inline cstr_t Get()	const { return me != NULL ? me : STR_NULL; }
			
			/**
			 * Returns pointer to null-terminated string from specified index.
			 * \note Do not modify the content pointed by the returned value. It is for read only!
			 */
			inline cstr_t Get(uint16_t index) const { return (index < length) ? me + index : STR_NULL; }
			
			/**
			 * Truncates string to the 'newLength'.
			 * @return true on success. If 'newLength' is not greater than current string length then false is returned.
			 */
			bool SetLength(uint16_t newLength);
			
			/**
			 * Gives this string new value reflecting numeric value in decimal string representation.
			 */
			inline bool FromInt(int16_t i) { return SubFromInt<10, 7>(i); }
			
			/**
			 * Gives this string new value reflecting numeric value in binary string representation.
			 */
			inline bool FromIntBin(int16_t i) { return SubFromInt<2, 18>(i); }
			
			/**
			 * Gives this string new value reflecting numeric value in octal string representation.
			 */
			inline bool FromIntOct(int16_t i) { return SubFromInt<8, 8>(i); }
			
			/**
			 * Gives this string new value reflecting numeric value in hexadecimal string representation.
			 */
			inline bool FromIntHex(int16_t i) { return SubFromInt<16, 6>(i); }
			
			/**
			 * Gives this string new value reflecting numeric value in decimal string representation.
			 */
			bool FromDouble(double d);
			
			/**
			 * Gives new value to this string.
			 */
			inline bool Copy(cstr_t source) { return SubCopy(source, StrLength(source) ); }
			
			/**
			 * Gives new value to this string.
			 */
			inline bool Copy(const BaseString &source) { return SubCopy(source.Get(), source.GetLength() ); }
			
			/**
			 * Gives new value to this string. Only 'n' first characters are copied from source to this string.
			 */
			bool Copy(cstr_t source, uint16_t n);
			
			/**
			 * Gives new value to this string. Only 'n' first characters are copied from source to this string.
			 */
			inline bool Copy(const BaseString &source, uint16_t n) { return Copy(source.Get(), n); }
			
			/**
			 * Appends 'value' to this string.
			 */
			inline bool Join(cstr_t value) { return SubJoin(value, StrLength(value) ); }
			
			/**
			 * Appends 'value' to this string.
			 */
			inline bool Join(const BaseString &value) { return SubJoin(value.Get(), value.GetLength() ); }
			
			/**
			 * Appends 'n' characters from 'value' to this string.
			 */
			inline bool Join(cstr_t value, uint16_t n) { return SubJoin(value, n, StrLength(value) ); }
			
			/**
			 * Appends 'n' characters from 'value' to this string.
			 */
			inline bool Join(const BaseString &value, uint16_t n) { return SubJoin(value.Get(), n, value.GetLength() ); }
			
			/**
			 * Finds the first occurrence of 'value' from character position specified with 'index'.
			 * Comparison is case-sensetive.
			 * @return On success returns index pointing to the starting of the substring, otherwise
			 * 	BaseString::NotFound is returned.
			 */
			inline uint16_t Find(uint16_t index, const BaseString &value) { return SubFind(index, value.Get(), value.GetLength() ); }
			
			/**
			 * Finds the first occurrence of 'value' from character position specified with 'index'.
			 * Comparison is case-sensetive.
			 * @return On success returns index pointing to the starting of the substring, otherwise
			 * 	BaseString::NotFound is returned.
			 */
			inline uint16_t Find(uint16_t index, cstr_t value) { return SubFind(index, value, StrLength(value) ); }
			
			/**
			 * Finds the first occurrence of 'value' from character position specified with 'index'.
			 * Case is ignored during the comparison.
			 * @return On success returns index pointing to the starting of the substring, otherwise
			 * 	BaseString::NotFound is returned.
			 */
			inline uint16_t IFind(uint16_t index, const BaseString &value) { return SubIFind(index, value.Get(), value.GetLength() ); }
			
			/**
			 * Finds the first occurrence of 'value' from character position specified with 'index'.
			 * Case is ignored during the comparison.
			 * @return On success returns index pointing to the starting of the substring, otherwise
			 * 	BaseString::NotFound is returned.
			 */
			inline uint16_t IFind(uint16_t index, cstr_t value) { return SubIFind(index, value, StrLength(value) ); }
			
			/**
			 * Replaces string from index 'begin' to index 'end' with 'replaceWith'.
			 * @return true on success.
			 */
			inline bool Replace(uint16_t begin, uint16_t end, const BaseString &replaceWith) { return SubReplace(begin, end, replaceWith.Get(), replaceWith.GetLength() ); }
			
			/**
			 * Replaces string from index 'begin' to index 'end' with 'replaceWith'.
			 * @return true on success.
			 */
			inline bool Replace(uint16_t begin, uint16_t end, cstr_t replaceWith) { return SubReplace(begin, end, replaceWith, StrLength(replaceWith) ); }
			
			/**
			 * Inserts 'value' into this string to the character position specified with 'index'.
			 */
			inline bool Insert(uint16_t index, const BaseString &value) { return Replace(index, index, value); }
			
			/**
			 * Inserts 'value' into this string to the character position specified with 'index'.
			 */
			inline bool Insert(uint16_t index, cstr_t value) { return Replace(index, index, value); }
			
			/**
			 * Returns character from specified index.
			 * @return '\0' if index is out of bounds.
			 */
			inline char_t GetChar(uint16_t index) const { return (index < length) ? me[index] : '\0'; }
			
			/**
			 * Returns true if first characters match with 'value'. Comparison is case-sensetive.
			 * @return Always false in case length of 'value' is greater than length of this string.
			 */
			inline bool StartsWith(cstr_t value) const { return StrNCompare(Get(), value, StrLength(value) ) == 0; }
			
			/**
			 * Returns true if first characters match with 'value'. Comparison is case-sensetive.
			 * @return Always false in case length of 'value' is greater than length of this string.
			 */
			inline bool StartsWith(BaseString &value) const { return StrNCompare(Get(), value.Get(), value.GetLength() ) == 0; }
			
			/**
			 * Returns true if first characters match with 'value'. Case is ignored during the comparison.
			 * @return Always false in case length of 'value' is greater than length of this string.
			 */
			inline bool IStartsWith(cstr_t value) const { return StrNICompare(Get(), value, StrLength(value) ) == 0; }
			
			/**
			 * Returns true if first characters match with 'value'. Case is ignored during the comparison.
			 * @return Always false in case length of 'value' is greater than length of this string.
			 */
			inline bool IStartsWith(BaseString &value) const { return StrNICompare(Get(), value.Get(), value.GetLength() ) == 0; }
			
			/**
			 * Returns true if last characters match with 'value'. Comparison is case-sensetive.
			 * @return Always false in case length of 'value' is greater than length of this string.
			 */
			bool EndsWith(cstr_t value) const;
			
			/**
			 * Returns true if last characters match with 'value'. Comparison is case-sensetive.
			 * @return Always false in case length of 'value' is greater than length of this string.
			 */
			bool EndsWith(const BaseString &value) const;
			
			/**
			 * Returns true if last characters match with 'value'. Case is ingored during the comparison.
			 * @return Always false in case length of 'value' is greater than length of this string.
			 */
			bool IEndsWith(cstr_t value) const;
			
			/**
			 * Returns true if last characters match with 'value'. Case is ingored during the comparison.
			 * @return Always false in case length of 'value' is greater than length of this string.
			 */
			bool IEndsWith(const BaseString &value) const;
			
			/**
			 * To set preferred capacity (in characters) of this string container.
			 * Allocator object only takes it into consideration. It is not guaranteed
			 * that buffer is taking exactly the the amount of memory specified with 'size'
			 * after calling this function.
			 * @return true on success - it means capacity is not less than 'size' characters. 
			 */
			inline bool Reserve(uint16_t size) { return EnsureCapacity(size); }
			
			/**
			 * Converts the whole string to upper case.
			 */
			inline void ToUpper() { if (me) StrToUpper(me); }
			
			/**
			 * Converts the whole string to lower case.
			 */
			inline void ToLower() { if (me) StrToLower(me); }
			
			/**
			 * Returns numeric representation from the beginning of the string.
			 */
			inline double GetDouble() const { return ToDouble(Get() ); }
			
			/**
			 * Returns numeric representation from the beginning of the string.
			 */
			inline int GetInteger() const { return ToInteger(Get() ); }
			
			/**
			 * Case-sensetive string compare.
			 * @return zero in case equal
			 */
			inline int Compare(cstr_t comparable) const { return StrCompare(Get(), comparable); }
			
			/**
			 * Case-sensetive string compare.
			 * @return zero in case equal
			 */
			inline int Compare(BaseString &comparable) const { return StrCompare(Get(), comparable.Get() ); }
			
			/**
			 * String compare that ignores case.
			 * @return zero in case equal
			 */
			inline int ICompare(cstr_t comparable) const { return StrICompare(Get(), comparable); }
			
			/**
			 * String compare that ignores case.
			 * @return zero in case equal
			 */
			inline int ICompare(BaseString &comparable) const { return StrICompare(Get(), comparable.Get() ); }
			
			/**
			 * Returns pointer to null-terminated string.
			 * \note Do not modify the content pointed by the returned value. It is for read only!
			 */
			inline cstr_t operator () () const { return Get(); }
			
			/**
			 * Returns pointer to null-terminated string from specified index.
			 * \note Do not modify the content pointed by the returned value. It is for read only!
			 */
			inline cstr_t operator () (uint16_t index) const { return Get(index); }
			
			/**
			 * Returns character from specified index.
			 * @return '\0' if index is out of bounds.
			 */
			inline char_t operator [] (uint16_t index) const { return GetChar(index); }
			
			/**
			 * Appends 's' to this string.
			 */
			inline BaseString &operator += (BaseString &s) { Join(s.Get() ); return *this; }
			
			/**
			 * Appends 's' to this string.
			 */
			inline BaseString &operator += (cstr_t s) { Join(s); return *this; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator < (BaseString &s) const { return Compare(s) < 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator > (BaseString &s) const { return Compare(s) > 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator <= (BaseString &s) const { return Compare(s) <= 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator >= (BaseString &s) const { return Compare(s) >= 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator == (BaseString &s) const { return Compare(s) == 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator != (BaseString &s) const { return Compare(s) != 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator < (cstr_t s) const { return Compare(s) < 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator > (cstr_t s) const { return Compare(s) > 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator <= (cstr_t s) const { return Compare(s) <= 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator >= (cstr_t s) const { return Compare(s) >= 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator == (cstr_t s) const { return Compare(s) == 0; }
			
			/**
			 * Case-sensetive comparison.
			 */
			inline bool operator != (cstr_t s) const { return Compare(s) != 0; }
			
		}; // abstract class BaseString
		
	} // namespace Collection
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_BASE_STRING_H__
