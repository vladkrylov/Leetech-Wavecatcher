/*============================================================================*/
/*                    L a b W i n d o w s / C V I                             */
/*----------------------------------------------------------------------------*/
/*        Copyright (c) National Instruments 2009-2009.  All Rights Reserved. */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:    stdint.h                                                         */
/* Purpose:  Include file for ISO/IEC 9899:1999 Standard C providing          */
/*              definitions of integer types having specified widths.         */
/*                                                                            */
/*============================================================================*/

#ifndef _STDINT_H_
#define _STDINT_H_

#include "cvidef.h"
#include "cvirte.h"

#ifdef __cplusplus
    extern "C" {
#endif

/* Exact-width integer types */

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef signed __int64      int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned __int64    uint64_t;

/* Minimum-width integer types */

typedef signed char         int_least8_t;
typedef signed short        int_least16_t;
typedef signed int          int_least32_t;
typedef signed __int64      int_least64_t;
typedef unsigned char       uint_least8_t;
typedef unsigned short      uint_least16_t;
typedef unsigned int        uint_least32_t;
typedef unsigned __int64    uint_least64_t;

/* Fastest minimum-width integer types */

typedef signed char         int_fast8_t;
typedef signed short        int_fast16_t;
typedef signed int          int_fast32_t;
typedef signed __int64      int_fast64_t;
typedef unsigned char       uint_fast8_t;
typedef unsigned short      uint_fast16_t;
typedef unsigned int        uint_fast32_t;
typedef unsigned __int64    uint_fast64_t;

/* Integer types capable of holding object pointers */

#ifndef _INTPTR_T_DEFINED
#ifdef  _NI_mswin64_
typedef __int64             intptr_t;
#else
typedef int                 intptr_t;
#endif
#define _INTPTR_T_DEFINED
#endif

#ifndef _UINTPTR_T_DEFINED
#ifdef  _NI_mswin64_
typedef unsigned __int64    uintptr_t;
#else
typedef unsigned int        uintptr_t;
#endif
#define _UINTPTR_T_DEFINED
#endif

/* Greatest-width integer types */

typedef signed __int64      intmax_t;
typedef unsigned __int64    uintmax_t;

/* Limits of exact-width integer types */

#define INT8_MIN          (-128)
#define INT8_MAX            127
#define UINT8_MAX           255

#define INT16_MIN         (-32768)
#define INT16_MAX           32767
#define UINT16_MAX          65535

#define INT32_MIN         (-2147483648)
#define INT32_MAX           2147483647
#define UINT32_MAX          4294967295

#define INT64_MIN         (-9223372036854775808LL)
#define INT64_MAX           9223372036854775807LL
#define UINT64_MAX          18446744073709551615ULL

/* Limits of minimum-width integer types */

#define INT_LEAST8_MIN      INT8_MIN
#define INT_LEAST8_MAX      INT8_MAX
#define UINT_LEAST8_MAX     UINT8_MAX

#define INT_LEAST16_MIN     INT16_MIN
#define INT_LEAST16_MAX     INT16_MAX
#define UINT_LEAST16_MAX    UINT16_MAX

#define INT_LEAST32_MIN     INT32_MIN
#define INT_LEAST32_MAX     INT32_MAX
#define UINT_LEAST32_MAX    UINT32_MAX

#define INT_LEAST64_MIN     INT64_MIN
#define INT_LEAST64_MAX     INT64_MAX
#define UINT_LEAST64_MAX    UINT64_MAX

/* Limits of fastest minimum-width integer types */

#define INT_FAST8_MIN       INT8_MIN
#define INT_FAST8_MAX       INT8_MAX
#define UINT_FAST8_MAX      UINT8_MAX

#define INT_FAST16_MIN      INT16_MIN
#define INT_FAST16_MAX      INT16_MAX
#define UINT_FAST16_MAX     UINT16_MAX

#define INT_FAST32_MIN      INT32_MIN
#define INT_FAST32_MAX      INT32_MAX
#define UINT_FAST32_MAX     UINT32_MAX

#define INT_FAST64_MIN      INT64_MIN
#define INT_FAST64_MAX      INT64_MAX
#define UINT_FAST64_MAX     UINT64_MAX

/* Limits of integer types capable of holding object pointers */

#ifdef  _NI_mswin64_
#define INTPTR_MIN          INT64_MIN
#define INTPTR_MAX          INT64_MAX
#define UINTPTR_MAX         UINT64_MAX
#else
#define INTPTR_MIN          INT32_MIN
#define INTPTR_MAX          INT32_MAX
#define UINTPTR_MAX         UINT32_MAX
#endif

/* Limits of greatest-width integer types */

#define INTMAX_MIN          INT64_MIN
#define INTMAX_MAX          INT64_MAX
#define UINTMAX_MAX         UINT64_MAX

/* Limits of integer types defined in other headers */

     /* ptrdiff_t defined in stddef.h */
#define PTRDIFF_MIN         INTPTR_MIN
#define PTRDIFF_MAX         INTPTR_MAX

     /* size_t defined in stddef.h */
#define SIZE_MAX            UINTPTR_MAX

     /* ssize_t defined in stddef.h  (non-standard) */
#define SSIZE_MIN           INTPTR_MIN
#define SSIZE_MAX           INTPTR_MAX

     /* sig_atomic_t defined in signal.h */
#define SIG_ATOMIC_MIN      INT32_MIN
#define SIG_ATOMIC_MAX      INT32_MAX

     /* wchar_t defined in stddef.h */
#define WCHAR_MIN           0
#define WCHAR_MAX           UINT16_MAX

     /* wint_t defined in stddef.h */
#define WINT_MIN            0
#define WINT_MAX            UINT16_MAX

/* Macros for minimum-width integer constants */

#define INT8_C(val)         (val)
#define INT16_C(val)        (val)
#define INT32_C(val)        (val ## L)
#define INT64_C(val)        (val ## LL)

#define UINT8_C(val)        (val)
#define UINT16_C(val)       (val)
#define UINT32_C(val)       (val ## UL)
#define UINT64_C(val)       (val ## ULL)

/* Macros for greatest-width integer constants */

#define INTMAX_C(val)       (val ## LL)
#define UINTMAX_C(val)      (val ## ULL)

#ifdef __cplusplus
    }
#endif
    
#endif /* !defined(_STDINT_H_) */
