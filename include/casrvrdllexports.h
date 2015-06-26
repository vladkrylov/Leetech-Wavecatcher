/*============================================================================*/
/*                        L a b W i n d o w s / C V I                         */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 2000-2009.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       casrvrdllexports.h                                            */
/* Purpose:     This file should be used to export the following functions    */
/*              from COM DLLS that are built in CVI.                          */
/*                                                                            */
/*============================================================================*/

#include <windows.h>

STDAPI DllCanUnloadNow (void);

STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);

STDAPI DllRegisterServer (void);

STDAPI DllUnregisterServer (void);
