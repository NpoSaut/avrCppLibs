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

#ifndef __AVR_CPP_STRING_DEFINITIONS_H__
#define __AVR_CPP_STRING_DEFINITIONS_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STR_NULL ""
#define END_LINE "\x0D\x0A"

typedef char			char_t;
typedef const char_t	cchar_t;
typedef char_t *		str_t;
typedef const char_t *	cstr_t;

inline uint16_t	StrLength(const char *s) { return (uint16_t)strlen(s); }
inline char *	StrJoin(char *dest, const char *src) { return strcat(dest, src); }
inline int		StrCompare(const char *s1, const char *s2) { return strcmp(s1, s2); }
inline int		StrICompare(const char *s1, const char *s2) { return strcasecmp(s1, s2); }
inline int		StrNCompare(const char *s1, const char *s2, size_t  maxlen) { return strncmp(s1, s2, maxlen); }
inline int		StrNICompare(const char *s1, const char *s2, size_t maxlen) { return strncasecmp(s1, s2, maxlen); }
inline char	*	StrCopy(char *dest, const char *src) { return strcpy(dest, src); }
inline char *	StrNCopy(char *dest, const char *src, size_t maxlen) { return strncpy(dest, src, maxlen); }
inline int		ToInteger(const char *s) { return atoi(s); }
inline double	ToDouble(const char *s) { return atof(s); }
inline double	ToDoubleEx(const char *s, char **endptr) { return strtod(s, endptr); }
inline char *	ToString(int value, char *string, int radix) { return itoa(value, string, radix); }
inline int		DoubleToString(char *buffer, double value) { return sprintf(buffer, "%f", value); }
inline char *	FindChar(char *s, int c, size_t n) { return (char *)memchr((void *)s, c, n); }
inline char *	StrAlloc(size_t size) { return (char *)malloc(size * sizeof(char)); }
inline char *	StrRealloc(char *block, size_t size) { return (char *)realloc((char *)block, size * sizeof(char)); }
inline char *	StrToUpper(char *s) { return strupr(s); }
inline char *	StrToLower(char *s) { return strlwr(s); }
inline char *	StrFind(const char *s1, const char *s2) { return strstr(s1, s2); }
inline char *	StrIFind(const char *s1, const char *s2) { return strcasestr(s1, s2); }

#endif // ifndef __AVR_CPP_STRING_DEFINITIONS_H__
