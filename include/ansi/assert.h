/*============================================================================*/
/*                        L a b W i n d o w s / C V I                         */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 1987-2009.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       assert.h                                                      */
/* Purpose:     Include file for ANSI Standard C assertion handler            */
/*                                                                            */
/*============================================================================*/

#include "cvidef.h"
#include "cvirte.h"

#ifndef _ASSERT_H_
#define _ASSERT_H_

#ifdef __cplusplus
    extern "C" {
#endif

#undef assert

#ifdef NDEBUG
#define assert(exp) ((void)  0)

#else
void CVIANSI _assert(char *, char *, int);
void CVIANSI _assert_func(const char *, const char *, const char *, int);

#if defined (_CVI_C99_EXTENSIONS_) && _CVI_C99_EXTENSIONS_
#define assert(exp) ((exp) ? (void) 0 : _assert_func(#exp, __FILE__, __func__, __LINE__))
#else
#define assert(exp) ((exp) ? (void) 0 : _assert(#exp, __FILE__, __LINE__))
#endif
#endif

#ifdef __cplusplus
    }
#endif

#endif /* _ASSERT_H_ */
