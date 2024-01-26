/*
   Copyright (c) 2020-2023 Sibi Siddharthan

   Distributed under the MIT license.
   Refer to the LICENSE file at the root directory for details.
*/

#ifndef WLIBC_H
#define WLIBC_H

#include <corecrt.h>

#if BUILDING_WLIBC
#	ifdef WLIBC_DLL
#		define WLIBC_API __declspec(dllexport)
#	else
#		define WLIBC_API
#	endif
#else
#	define WLIBC_API /*__declspec(dllimport)*/
#endif

/* For C++ compilers compiling C code */
#ifdef __cplusplus
#	define _WLIBC_BEGIN_DECLS extern "C" {
#	define _WLIBC_END_DECLS }
#else
#	define _WLIBC_BEGIN_DECLS
#	define _WLIBC_END_DECLS
#endif


#if defined __GNUC__
#	define WLIBC_INLINE   __attribute__((always_inline))
#	define WLIBC_NORETURN __attribute__((noreturn))
#	define WLIBC_UNUSED   __attribute__((unused))
#	define WLIBC_NONNULL  __attribute__((nonnull))
#elif defined _MSC_VER
#	define WLIBC_INLINE   __forceinline
#	define WLIBC_NORETURN __declspec(noreturn)
#	define WLIBC_UNUSED   __pragma(warning(suppress: 4100, 4505))
#	define WLIBC_NONNULL  _Notnull_
#endif

#endif
