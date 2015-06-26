/*============================================================================*/
/*                       L a b W i n d o w s / C V I                          */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 1987-2009.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:   utility.h                                                         */
/* Purpose: Include file for LabWindows/CVI Utility Library.                  */
/*                                                                            */
/*============================================================================*/

#ifndef UTILITY_HEADER
#define UTILITY_HEADER

/* This header must be included after any Windows SDK header or any header */
/* that directly or indirectly includes a Windows SDK header.              */
/* Some of the function names conflict with Windows SDK functions.         */
#ifndef INCLUDE_AFTER_WINDOWS_H
#define INCLUDE_AFTER_WINDOWS_H
#endif /* INCLUDE_AFTER_WINDOWS_H */

#include "cvidef.h"
#include "stdlib.h"
#include "cvirte.h"

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif

#define VAL_AUTO_CENTER (-2147483647L - 1)    /* for SetStdioWindowPosition() */

#if defined(_NI_mswin16_)
#define MAX_PATHNAME_LEN   80    /* includes nul byte */
#define MAX_DRIVENAME_LEN   3    /* includes nul byte */
#define MAX_DIRNAME_LEN    66    /* includes nul byte */
#define MAX_FILENAME_LEN   13    /* includes nul byte */

#elif defined(_NI_mswin32_) || defined(_NI_mswin64_)
#define MAX_PATHNAME_LEN  260    /* includes nul byte */
#define MAX_DRIVENAME_LEN   3    /* includes nul byte */
#define MAX_DIRNAME_LEN   256    /* includes nul byte */
#define MAX_FILENAME_LEN  256    /* includes nul byte */

#elif defined(_NI_linux_)
#define MAX_PATHNAME_LEN 1024    /* recommended buffer size for paths */
#define MAX_DRIVENAME_LEN   1    /* includes nul byte */
#define MAX_DIRNAME_LEN   256    /* includes nul byte */
#define MAX_FILENAME_LEN  256    /* recommended buffer size for file names */

#elif defined(_NI_unix_)
#define MAX_PATHNAME_LEN  256    /* recommended buffer size for paths */
#define MAX_DRIVENAME_LEN   1    /* includes nul byte */
#define MAX_DIRNAME_LEN   256    /* includes nul byte */
#define MAX_FILENAME_LEN  256    /* recommended buffer size for file names */

#else
#error Undefined Platform. You need to add one of the
#error following to your compiler defines:
#error     Platform                      Preprocessor directive
#error Microsoft Windows 3.1           #define _NI_mswin16_
#error Windows 95/NT                   #define _NI_mswin32_
#error Solaris 1                       #define _NI_sparc_       1
#error Solaris 2                       #define _NI_sparc_       2
#error HP-UX                           #define _NI_hpux_
#error Linux x86                       #define _NI_linux_
#error
#error _NI_i386_ has been replaced with _NI_mswin16_.
#error See Programmers Reference Manual for more information.


#endif

/* GetExternalModuleAddrEx (undocumented) options parameter */
#define GETEXTMODADDR_OPTIONS_LIST_UNDEFINED    1


/* SystemHelp commands */
#if !defined(HELP_CONTEXT)     /* prevent warnings when SDK files are used */
#define HELP_CONTEXT        0x0001
#define HELP_QUIT           0x0002
#define HELP_CONTENTS       0x0003
#define HELP_HELPONHELP     0x0004
#define HELP_SETCONTENTS    0x0005
#define HELP_CONTEXTPOPUP   0x0008
#define HELP_KEY            0x0101
#define HELP_COMMAND        0x0102
#define HELP_PARTIALKEY     0x0105
#if defined(_NI_mswin32_)
#define HELP_FINDER         0x000b
#endif /* defined(_NI_mswin32_) */
#endif /* !defined(HELP_CONTEXT) */
#define HELP_POPUPID        0x0104  /* not supported on Windows 95 */

#if defined(_NI_mswin_) || defined(_NI_mswin16_) || defined(_NI_mswin32_)
/* LaunchExecutableEx window display options */
#define LE_HIDE         0
#define LE_SHOWNORMAL       1
#define LE_SHOWMINIMIZED    2
#define LE_SHOWMAXIMIZED    3
#define LE_SHOWMINNOACTIVE  7
#define LE_SHOWNA           8
#endif /* defined(_NI_mswin_) */

#if defined (_NI_unix_) || defined(_NI_linux_)
/* LaunchExecutableEx window display options */
#define LE_SHOWNORMAL       1
#endif

#define CVI_STDIO_WINDOW    0
#define HOST_SYSTEM_STDIO   1

/* for the GetWindowDisplaySetting zoomState argument */
#define VAL_NO_ZOOM         0L
#define VAL_MINIMIZE            1L
#define VAL_MAXIMIZE            2L


/* for the GetCurrentPlatform() function */
enum _GetCurrentPlatformEnum
{
    kPlatformWin16 = 1,
    kPlatformWin95,
    kPlatformWinnt,
    kPlatformSunos4,
    kPlatformSunos5,
    kPlatformHPUX9,
    kPlatformHPUX10,
    kPlatformMac,
    kPlatformLinuxX86
};


/* for the CheckForDuplicateAppInstance() function */
#define ACTIVATE_OTHER_INSTANCE         1
#define DO_NOT_ACTIVATE_OTHER_INSTANCE  0

#if defined(_NI_mswin_) || defined(_NI_mswin32_) || defined(_NI_linux_)
/* Thread-Safe Queue */

typedef intptr_t CmtTSQHandle;
typedef intptr_t CmtTSQCallbackID;

typedef void (CVICALLBACK *CmtTSQCallbackPtr) (CmtTSQHandle queueHandle, unsigned int event, int value, void *callbackData);
#define TSQCallbackPtr CmtTSQCallbackPtr

/* Events */
#define     EVENT_TSQ_QUEUE_SIZE            (1 << 0)    /* value = size in number of items */
#define     EVENT_TSQ_ITEMS_IN_QUEUE        (1 << 1)    /* value = number of items in queue */
#define     EVENT_TSQ_QUEUE_SPACE_FREE      (1 << 2)    /* value = free space in number of items */

/* Attributes */
#define     ATTR_TSQ_READER_ACTIVE          1           /* int (boolean) (not settable) */
#define     ATTR_TSQ_WRITER_ACTIVE          2           /* int (boolean) (not settable) */
#define     ATTR_TSQ_QUEUE_SIZE             3           /* size_t (number of items) */
#define     ATTR_TSQ_ITEM_SIZE              4           /* size_t (number of bytes) (not settable) */
#define     ATTR_TSQ_ITEMS_IN_QUEUE         5           /* size_t (number of items) (not settable) */
#define     ATTR_TSQ_QUEUE_FREE_SPACE       7           /* size_t (free space in number of items) (not settable) */
#define     ATTR_TSQ_QUEUE_OPTIONS          8           /* unsigned int (not settable) */
#define     ATTR_TSQ_GROWTH_INCREMENT       9           /* size_t (block size, in number of items, to use when growing the queue) */
#define     ATTR_TSQ_ACCESS_DENY            10          /* unsigned int (VAL_TSQ_ACCESSS_DENY_READ, ...) */

/* Constants */
/* CmtNewTSQ options */
#define     OPT_TSQ_DYNAMIC_SIZE            (1 << 0)    /* queue grows when full  */
#define     OPT_TSQ_AUTO_FLUSH_ALL          (1 << 1)    /* queue flushes all unread data when full */
#define     OPT_TSQ_AUTO_FLUSH_EXACT        (1 << 2)    /* queue flushes needed data when full */

/* CmtReadTSQData options */
#define     OPT_TSQ_READ_PEEK               (1 << 0)    /* leave the data in the queue after the read */

/* ATTR_TSQ_ACCESS_DENY values */
#define     VAL_TSQ_ACCESS_DENY_NONE        0                                                       /* allow all access */
#define     VAL_TSQ_ACCESS_DENY_READ        (1 << 0)                                                /* read access */
#define     VAL_TSQ_ACCESS_DENY_WRITE       (1 << 1)                                                /* write access */
#define     VAL_TSQ_ACCESS_DENY_FLUSH       (1 << 2)                                                /* flush access */
#define     VAL_TSQ_ACCESS_DENY_READWRITE   (VAL_TSQ_ACCESS_DENY_READ | VAL_TSQ_ACCESS_DENY_WRITE)  /* read/write access */
#define     VAL_TSQ_ACCESS_DENY_ALL         0xFFFFFFFF                                              /* all access */

/* Miscellaneous constants */
#define     TSQ_INFINITE_TIMEOUT            -1
#define     TSQ_FLUSH_ALL                   -1

/* Thread Pool */
typedef intptr_t CmtThreadPoolHandle;
typedef intptr_t CmtThreadPoolCallbackID;
typedef int CmtThreadFunctionID;

typedef void (CVICALLBACK *CmtThreadFunctionCallbackPtr) (CmtThreadPoolHandle poolHandle, CmtThreadFunctionID functionID, unsigned int event, int value, void *callbackData);
typedef void (CVICALLBACK *CmtThreadPoolCallbackPtr) (CmtThreadPoolHandle poolHandle, unsigned int event, int value, void *callbackData);
typedef int (CVICALLBACK *CmtThreadFunctionPtr) (void *functionData);
#define ThreadFunctionCallbackPtr CmtThreadFunctionCallbackPtr
#define ThreadPoolCallbackPtr CmtThreadPoolCallbackPtr
#define ThreadFunctionPtr CmtThreadFunctionPtr

/* Thread Pool Events */
#define     EVENT_TP_THREAD_BEGIN               (1 << 0)    /* value = threadID */
#define     EVENT_TP_THREAD_END                 (1 << 1)    /* value = threadID */

/* Thread Function Events */
#define     EVENT_TP_THREAD_FUNCTION_BEGIN      (1 << 0)    /* value = 0 */
#define     EVENT_TP_THREAD_FUNCTION_END        (1 << 1)    /* value = function return value */

/* Attributes */
#define     ATTR_TP_THREAD_STACK_SIZE               1   /* size_t (number of bytes) */
#define     ATTR_TP_THREAD_SECURITY                 2   /* SECURITY_ATTRIBUTES*  */
#define     ATTR_TP_PROCESS_EVENTS_WHILE_WAITING    3   /* int (boolean) */
#define     ATTR_TP_THREAD_PRIORITY                 4   /* int (THREAD_PRIORITY_NORMAL, ...) */
#define     ATTR_TP_MAX_NUM_THREADS                 5   /* int (number of threads) */
#define     ATTR_TP_NUM_THREADS                     6   /* int (number of threads) (not settable) */
#define     ATTR_TP_NUM_ACTIVE_THREADS              7   /* int (number of threads) (not settable) */

#define     ATTR_TP_FUNCTION_RETURN_VALUE           1   /* int (return value from thread function) (not settable) */
#define     ATTR_TP_FUNCTION_THREAD_ID              2   /* unsigned int (threadID) (not settable) */
#define     ATTR_TP_FUNCTION_THREAD_HANDLE          3   /* void * (HANDLE) (not settable) */
#define     ATTR_TP_FUNCTION_EXECUTION_STATUS       4   /* int (ThreadPoolThreadFnExecutionStatus) (not settable) */

/* CmtWaitForThreadPoolFunctionCompletion options */
#define     OPT_TP_PROCESS_EVENTS_WHILE_WAITING     1   /* int (boolean) */

/* Values */
typedef enum {
    kCmtThreadFunctionWaitingToExecute,
    kCmtThreadFunctionPreExecution,
    kCmtThreadFunctionExecuting,
    kCmtThreadFunctionPostExecution,
    kCmtThreadFunctionComplete,
    kCmtThreadFunctionThreadTerminated,
    kCmtThreadFunctionStatus_ForceSizeToFourBytes = 0xFFFFFFFF
} CmtThreadFunctionExecutionStatus;

/* Constants */
#define     DEFAULT_THREAD_POOL_HANDLE          ((CmtThreadPoolHandle)-1)
#define     DEFAULT_THREAD_PRIORITY             0XFFFFFF9D
#define     UNLIMITED_THREAD_POOL_THREADS       0XFFFFFFFF
#define     RUN_IN_SCHEDULED_THREAD             0
#ifdef _NI_linux_
#define     THREAD_PRIORITY_NORMAL              0
#endif

/* Thread Local Variable */
typedef int CmtTLVHandle;

typedef void (CVICALLBACK *CmtTLVCallbackPtr) (void *threadLocalPtr, int event, void *callbackData, unsigned int threadID);
#define TLVCallbackPtr CmtTLVCallbackPtr

/* Thread Local Variable Events */
#define     EVENT_TLV_DISCARD_THREAD_DETACH     (1 << 0)    /* thread exiting */
#define     EVENT_TLV_DISCARD_FUNCTION_CALLED   (1 << 1)    /* CmtDiscardThreadLocalVar called */

/* Thread Safe Variable */
typedef intptr_t CmtTSVHandle;

/* Thread Safe Variable Macros */
#define DeclareThreadSafeScalarVar(datatype, name)                  \
DeclareThreadSafeVarCommonFunctions(datatype, name)                 \
DeclareThreadSafeVarGetSetFunctions(datatype, name)

#define DeclareThreadSafeArrayVar(datatype, name)                   \
DeclareThreadSafeVarCommonFunctions(datatype, name)                 \

#define DeclareThreadSafeVar(datatype, name)                        \
DeclareThreadSafeScalarVar(datatype, name)


#define DeclareThreadSafeVarCommonFunctions(datatype, name)         \
int Initialize ## name (void);                                      \
void Uninitialize ## name (void);                                   \
datatype *GetPointerTo ## name(void);                               \
void ReleasePointerTo ## name (void);


#define DeclareThreadSafeVarGetSetFunctions(datatype, name)         \
void Set ## name (datatype val);                                    \
datatype Get ## name (void);


#define TSV_ALLOW_UNLIMITED_NESTING     -1

#define DefineThreadSafeScalarVar(datatype, name, maxGetPointerNesting)             \
DefineThreadSafeVarCommonDataAndFunctions(datatype, name, 1, maxGetPointerNesting)  \
DefineThreadSafeVarScalarGetSetFunctions(datatype, name)

#define DefineThreadSafeArrayVar(datatype, name, numElements, maxGetPointerNesting) \
DefineThreadSafeVarCommonDataAndFunctions(datatype, name, numElements, maxGetPointerNesting)

#define DefineThreadSafeVar(datatype, name)     \
    DefineThreadSafeScalarVar(datatype, name, TSV_ALLOW_UNLIMITED_NESTING)


#define DefineThreadSafeVarCommonDataAndFunctions(datatype, name, numElements, maxGetPointerNesting) \
static CmtTSVHandle _locked ## name;                                            \
DeclareTSVNestedLockCount(datatype, name);                              \
int Initialize ## name (void)                                           \
{                                                                       \
    return CmtNewTSV (sizeof (datatype) * numElements, &_locked ## name);\
}                                                                       \
void Uninitialize ## name (void)                                        \
{                                                                       \
    CmtDiscardTSV (_locked ## name);                                    \
}                                                                       \
datatype *GetPointerTo ## name(void)                                    \
{                                                                       \
    void *_locked ## name ## Ptr = NULL;                                \
    CmtGetTSVPtr (_locked ## name, &_locked ## name ## Ptr);            \
    CheckThreadSafeVarNestedLockCount(datatype, name, maxGetPointerNesting);\
    return (datatype *)_locked ## name ## Ptr;                          \
}                                                                       \
void ReleasePointerTo ## name (void)                                    \
{                                                                       \
    RecordThreadSafeVarNestedLockExit(datatype, name, maxGetPointerNesting);\
    CmtReleaseTSVPtr (_locked ## name);                                 \
}                                                                       \


#define DefineThreadSafeVarScalarGetSetFunctions(datatype, name)        \
void Set ## name (datatype val)                                         \
{                                                                       \
    CmtSetTSV (_locked ## name, &val);                                  \
}                                                                       \
datatype Get ## name (void)                                             \
{                                                                       \
    datatype retval;                                                    \
    void *_locked ## name ## Ptr = NULL;                                \
    CmtGetTSVPtr (_locked ## name, &_locked ## name ## Ptr);            \
    retval = *(datatype *)_locked ## name ## Ptr;                       \
    CmtReleaseTSVPtr (_locked ## name);                                 \
    return retval;                                                      \
}

#ifndef DEBUG_THREAD_SAFE_VAR
#if (defined(_CVI_DEBUG_) || (!defined(_CVI_) && !defined(NDEBUG)))
#define DEBUG_THREAD_SAFE_VAR   1
#else
#define DEBUG_THREAD_SAFE_VAR   0
#endif
#endif


#define __Stringify(name)   #name

#if ( DEBUG_THREAD_SAFE_VAR )
#define DeclareTSVNestedLockCount(datatype, name)   \
static int _locked ## name ## count

#if _NI_linux_
#define CheckThreadSafeVarNestedLockCount(datatype, name, maxGetPointerNesting) \
    if (maxGetPointerNesting >= 0 && (_locked ## name ## count > maxGetPointerNesting)) {\
        fprintf (stderr,                                                \
                     "The maximum (%d) nested Thread Safe Variable "    \
                     "lock count, you specified, has been exceeded. "   \
                     "You have probably not matched a call to %s "      \
                     "with a call to %s.  Use the \"Up Call Stack\" "   \
                     "Run menu item to find the current call to %s\n",  \
                     (int)maxGetPointerNesting,                             \
                     __Stringify( GetPointerTo ## name ),               \
                     __Stringify( ReleasePointerTo ## name ),           \
                     __Stringify( GetPointerTo ## name ));              \
        fflush (stderr);                                                \
    }                                                                   \
    _locked ## name ## count++;


#define RecordThreadSafeVarNestedLockExit(datatype, name, maxGetPointerNesting) \
    _locked ## name ## count--;                                         \
    if (_locked ## name ## count < 0) {                                 \
        fprintf (stderr,                                                \
                     "Call to %s without a preceeding call to %s."      \
                     "Use the \"Up Call Stack\" Run menu item to find " \
                     "the current call to %s.\n",                       \
                     __Stringify( ReleasePointerTo ## name ),           \
                     __Stringify( GetPointerTo ## name ),               \
                     __Stringify( ReleasePointerTo ## name ));          \
        fflush (stderr);                                                \
    }
#else
#define CheckThreadSafeVarNestedLockCount(datatype, name, maxGetPointerNesting) \
    if (maxGetPointerNesting >= 0 && (_locked ## name ## count > maxGetPointerNesting)) {\
        ErrorPrintf ("The maximum (%d) nested Thread Safe Variable "    \
                     "lock count, you specified, has been exceeded. "   \
                     "You have probably not matched a call to %s "      \
                     "with a call to %s.  Use the \"Up Call Stack\" "   \
                     "Run menu item to find the current call to %s",    \
                     (int)maxGetPointerNesting,                         \
                     __Stringify( GetPointerTo ## name ),               \
                     __Stringify( ReleasePointerTo ## name ),           \
                     __Stringify( GetPointerTo ## name ));              \
        Breakpoint();                                                   \
    }                                                                   \
    _locked ## name ## count++;


#define RecordThreadSafeVarNestedLockExit(datatype, name, maxGetPointerNesting) \
    _locked ## name ## count--;                                         \
    if (_locked ## name ## count < 0) {                                 \
        ErrorPrintf ("Call to %s without a preceeding call to %s."      \
                     "Use the \"Up Call Stack\" Run menu item to find " \
                     "the current call to %s.",                         \
                     __Stringify( ReleasePointerTo ## name ),           \
                     __Stringify( GetPointerTo ## name ),               \
                     __Stringify( ReleasePointerTo ## name ));          \
        Breakpoint();                                                   \
    }
#endif

#else /* ! (DEBUG_THREAD_SAFE_VAR) */
#define DeclareTSVNestedLockCount(datatype, name)

#define CheckThreadSafeVarNestedLockCount(datatype, name, maxGetPointerNesting)

#define RecordThreadSafeVarNestedLockExit(datatype, name, maxGetPointerNesting)
#endif


/* User Lock */
typedef intptr_t CmtThreadLockHandle;

/* Constants */
/* CmtNewLock options */
#define     OPT_TL_PROCESS_EVENTS_WHILE_WAITING     (1 << 0)    /* Process events while waiting for lock. */

/* Attributes */
#define     ATTR_LOCK_OWNER_THREAD          1           /* unsigned int (ID of thread owning lock) (not settable) */


/* General Multithreading */

/* Constants */
#define     CMT_MAX_MESSAGE_BUF_SIZE            256

/* Error codes */
typedef enum
{
    kCmtInvalidHandle                       = -14901,
    kCmtInvalidParameter                    = -14902,
    kCmtInvalidAttribute                    = -14903,
    kCmtInvalidEvent                        = -14904,
    kCmtOutOfMemory                         = -14905,
    kCmtTimeOut                             = -14906,
    kCmtEventCallbackAlreadyRegistered      = -14907,
    kCmtInvalidCallbackID                   = -14908,
    kCmtInvalidThreadID                     = -14909,
    kCmtSystemError                         = -14910,
    kCmtTSQAnotherReaderActive              = -14911,
    kCmtTSQAnotherWriterActive              = -14912,
    kCmtTSQQueueFull                        = -14913,
    kCmtTSQQueueEmpty                       = -14914,
    kCmtTSQUserReadTooMuch                  = -14915,
    kCmtTSQUserWroteTooMuch                 = -14916,
    kCmtTSQTooManyItemsForAutoFlush         = -14917,
    kCmtTSQAccessDenied                     = -14918,
    kCmtTSQCannotResizeFromThread           = -14919,
    kCmtTSQReleaseFromWrongThread           = -14920,
    kCmtTPAttrNotSetableWhenThreadsExist    = -14921,
    kCmtTPThreadPriorityInvalid             = -14922,
    kCmtTPInvalidFnID                       = -14923,
    kCmtTPFnIDOwnedByPool                   = -14924,
    kCmtTPFnAttrUnavailable                 = -14925,
    kCmtTPNotAThreadPoolThread              = -14926,
    kCmtTPDefaultPoolNotAllowed             = -14927,
    kCmtTPCantReduceNumThrds                = -14928,
    kCmtTSVReleaseFromWrongThread           = -14929,
    kCmtTLReleaseFromWrongThread            = -14930,
    kCmtTLDiscardOwnedLock                  = -14931,
    kCmtTLReleaseWhenNotAcquired            = -14932
} CmtError;

#endif /* defined(_NI_mswin_) || defined(_NI_mswin32_) || defined(_NI_linux_) */

/* Dynamic Memory Information */
#define DYNAMIC_MEMORY_SHOW_ALLOCATED_MEMORY            0x80000000
#define DYNAMIC_MEMORY_SHOW_ALLOCATED_MEMORY_SUMMARY    0x80000001

int CVIFUNC    GetFileAttrs (const char fileName[], int *readOnly, int *system,
                             int *hidden, int *archive);
#if defined(_NI_mswin_) || defined(_NI_mswin16_) || defined(_NI_mswin32_)
int CVIFUNC    GetDrive (int *currentDriveNum, int *numDrives);
void CVIFUNC   DisableTaskSwitching (void);
void CVIFUNC   EnableTaskSwitching (void);
int CVIFUNC    GetInterruptState (void);
#ifdef _NI_mswin32_
int CVIFUNC    GetModuleDir (const void *hInstance, char dirName[]);
#endif
void CVIFUNC   GetWindowDisplaySetting (int *visible, int *zoomState);

int CVIFUNC    CheckForDuplicateAppInstance(int options, int *thereWasAnotherInstance);


#if !defined(SDK_CONFLICT_PRIORITY) || !(defined(_WINDEF_) || defined(_WINDOWS_))
#if defined(_NI_mswin32_) || defined(_NI_mswin64_)
int CVIFUNC    cviprefix(GetSystemTime) (int *hours, int *minutes, int *seconds);
char CVIFUNC   cviprefix(inp) (short port);
short CVIFUNC  cviprefix(inpw) (short port);
long CVIFUNC  cviprefix(inpd) (short port);
char CVIFUNC   cviprefix(outp) (short port, char value);
short CVIFUNC  cviprefix(outpw) (short port, short value);
long CVIFUNC  cviprefix(outpd) (short port, long value);
#define GetSystemTime cviprefix(GetSystemTime)
#define inp     cviprefix(inp)
#define inpw    cviprefix(inpw)
#define inpd    cviprefix(inpd)
#define outp    cviprefix(outp)
#define outpw   cviprefix(outpw)
#define outpd   cviprefix(outpd)
#else
int CVIFUNC    GetSystemTime (int *hours, int *minutes, int *seconds);
char CVIFUNC   inp (short port);
short CVIFUNC  inpw (short port);
char CVIFUNC   outp (short port, char value);
short CVIFUNC  outpw (short port, short value);
#endif
#endif

int CVIFUNC    GetSystemDate (int *month, int *day, int *year);
int CVIFUNC    SetDrive (int driveNum);
int CVIFUNC    SetFileAttrs (const char fileName[], int readOnly, int system,
                             int hidden, int archive);

#if !defined(SDK_CONFLICT_PRIORITY) || !(defined(_WINDEF_) || defined(_WINDOWS_))
#if defined(_NI_mswin32_) || defined(_NI_mswin64_)
int CVIFUNC    cviprefix(SetSystemTime) (int hours, int minutes, int seconds);
#define SetSystemTime cviprefix(SetSystemTime)
#else
int CVIFUNC    SetSystemTime (int hours, int minutes, int seconds);
#endif
#endif

int CVIFUNC    SetSystemDate (int month, int day, int year);
int CVIFUNC    ReadFromPhysicalMemory (unsigned physicalAddr, void *buffer, unsigned size);
int CVIFUNC    WriteToPhysicalMemory (unsigned physicalAddr, const void *buffer, unsigned size);
int CVIFUNC    ReadFromPhysicalMemoryEx (unsigned physicalAddr, void *buffer, unsigned size, int unitSize);
int CVIFUNC    WriteToPhysicalMemoryEx (unsigned physicalAddr, const void *buffer, unsigned size, int unitSize);
#if defined(_NI_mswin32_) || defined(_NI_mswin64_)
int CVIFUNC    MapPhysicalMemory (unsigned physicalAddr, unsigned size, void *mappedAddr, int *handle);
int CVIFUNC    UnMapPhysicalMemory (int handle);
#endif
int CVIFUNC    CVILowLevelSupportDriverLoaded(void);
#endif  /* defined(_NI_mswin_) */

int CVIFUNC    CVIRTEHasBeenDetached(void);

int CVIFUNC    SystemHelp (const char *helpFileName, unsigned command, unsigned long longData, const char *strData);

int CVIFUNC    CurrThreadId (void);   /* returns 1 on platforms that do not have threads */
int CVIFUNC    MainThreadId (void);   /* returns 1 on platforms that do not have threads */

int CVIFUNC    SetStdioPort (int stdioPort);
void CVIFUNC   GetStdioPort (int *stdioPort);

#if !defined(SDK_CONFLICT_PRIORITY) || !(defined(_WINDEF_) || defined(_WINDOWS_))
#if defined(_NI_mswin32_) || defined(_NI_mswin64_)
void CVIFUNC   cviprefix(Beep) (void);
#define Beep cviprefix(Beep)
#else
void CVIFUNC   Beep (void);
#endif
#endif

int  CVIFUNC   BeingDebuggedByCVI(void);
void CVIFUNC   Breakpoint (void);
void CVIFUNC   Cls (void);

#if !defined(SDK_CONFLICT_PRIORITY) || !(defined(_WINDEF_) || defined(_WINDOWS_))
#if defined(_NI_mswin32_) || defined(_NI_mswin64_)
int CVIFUNC    cviprefix(CopyFile) (const char sourceFile[], const char targetFile[]);
#ifdef CopyFile
#undef CopyFile
#endif
#define CopyFile cviprefix(CopyFile)
#else
int CVIFUNC    CopyFile (const char sourceFile[], const char targetFile[]);
#endif
#endif

char * CVIFUNC DateStr (void);
void CVIFUNC   Delay (double numSeconds);
int CVIFUNC    DeleteDir (const char dirName[]);

#if !defined(SDK_CONFLICT_PRIORITY) || !(defined(_WINDEF_) || defined(_WINDOWS_))
#if defined(_NI_mswin32_) || defined(_NI_mswin64_)
int CVIFUNC    cviprefix(DeleteFile) (const char fileName[]);
#ifdef DeleteFile
#undef DeleteFile
#endif
#define DeleteFile cviprefix(DeleteFile)
#else
int CVIFUNC    DeleteFile (const char fileName[]);
#endif
#endif

void CVIFUNC   DisableBreakOnLibraryErrors (void);
void CVIFUNC   DisableInterrupts (void);
void CVIFUNC   EnableBreakOnLibraryErrors (void);
void CVIFUNC   EnableInterrupts (void);
int CVIFUNC    ExecutableHasTerminated (int handle);
int CVIFUNC    GetBreakOnLibraryErrors (void);
int CVIFUNC    GetBreakOnProtectionErrors (void);
int CVIFUNC    GetBreakOnFirstChanceExceptions (void);
int CVIFUNC    GetCVIVersion (void);
void CVIFUNC   GetCVIVersionYear (char version[]);
int CVIFUNC    GetCurrentPlatform (void);
int CVIFUNC    GetDir (char currentDir[]);
int CVIFUNC    GetKey (void);
int CVIFUNC    GetPersistentVariable (void);
int CVIFUNC    GetProjectDir (char dirName[]);
int CVIFUNC    GetFullPathFromProject (const char fileName[], char fullPathName[]);
int CVIFUNC    GetFileDate (const char fileName[], int *month, int *day, int *year);

#if !defined(SDK_CONFLICT_PRIORITY) || !(defined(_WINDEF_) || defined(_WINDOWS_))
#if defined(_NI_mswin32_) || defined(_NI_mswin64_)
int CVIFUNC    cviprefix(GetFileSize) (const char fileName[], ssize_t *fileSize);
int CVIFUNC    cviprefix(GetFileTime) (const char fileName[], int *hours, int *minutes, int *seconds);
#define GetFileSize cviprefix(GetFileSize)
#define GetFileTime cviprefix(GetFileTime)
#else
int CVIFUNC    GetFileSize (const char fileName[], ssize_t *fileSize);
int CVIFUNC    GetFileTime (const char fileName[], int *hours, int *minutes, int *seconds);
#endif
#endif

int CVIFUNC    GetFirstFile (const char searchPath[], int normal, int readOnly, int system,
            int hidden, int archive, int directory, char fileName[]);
int CVIFUNC    GetNextFile (char fileName[]);
void CVIFUNC   GetStdioWindowOptions  (int *maxNumLines, int *bringToFrontWhenModified,
                  int *showLineNumbers);
void CVIFUNC   GetStdioWindowPosition  (int *top, int *left);
void CVIFUNC   GetStdioWindowSize  (int *height, int *width);
void CVIFUNC   GetStdioWindowVisibility  (int *visible);
int CVIFUNC    InStandaloneExecutable  (void);
int CVIFUNC    UsingInstrSupDll (void);
int CVIFUNC    WhichRuntimeSupportDll (void);
int CVIFUNC    KeyHit (void);
int CVIFUNC    LaunchExecutable (const char fileName[]);
int CVIFUNC    LaunchExecutableEx (const char fileName[], int nCmdShow, int *handle);
int CVIFUNC    MakeDir (const char newDirName[]);
int CVIFUNC    MakePathname (const char dirName[], const char fileName[], char pathName[]);
int CVIFUNC    RenameFile (const char existingName[], const char newName[]);
int CVIFUNC    RetireExecutableHandle (int handle);
long CVIFUNC   RoundRealToNearestInteger (double x);
void CVIFUNC   SplitPath (const char pathName[], char driveName[], char dirName[], char fileName[]);
int CVIFUNC    SetBreakOnLibraryErrors (int doBreak);
int CVIFUNC    SetBreakOnProtectionErrors (int doBreak);
int CVIFUNC    SetBreakOnFirstChanceExceptions (int doBreak);
int CVIFUNC    SetDir (const char dirName[]);
int CVIFUNC    SetFileDate (const char fileName[], int month, int day, int year);

#if !defined(SDK_CONFLICT_PRIORITY) || !(defined(_WINDEF_) || defined(_WINDOWS_))
#if defined(_NI_mswin32_) || defined(_NI_mswin64_)
int CVIFUNC    cviprefix(SetFileTime) (const char fileName[], int hours, int minutes, int seconds);
#define SetFileTime cviprefix(SetFileTime)
#else
int CVIFUNC    SetFileTime (const char fileName[], int hours, int minutes, int seconds);
#endif
#endif

void CVIFUNC   SetPersistentVariable (int value);
int CVIFUNC    SetStdioWindowOptions (int maxNumLines, int bringToFrontWhenModified,
                  int showLineNumbers);
int CVIFUNC    SetStdioWindowPosition (int top, int left);
int CVIFUNC    SetStdioWindowSize (int height, int width);
void CVIFUNC   SetStdioWindowVisibility (int visible);
void CVIFUNC   SyncWait (double beginTime, double interval);
int CVIFUNC    TerminateExecutable (int handle);
char * CVIFUNC TimeStr (void);

double CVIFUNC Timer (void);
double CVIFUNC TruncateRealNumber (double x);

extern void *__CVIUserHInst;

#if defined(_NI_mswin_) || defined(_NI_mswin32_) || defined(_NI_linux_)
/* Thread-Safe Queue */
int CVIFUNC     CmtNewTSQ (int numItems, size_t itemSize, unsigned int options, CmtTSQHandle *queueHandle);
int CVIFUNC     CmtDiscardTSQ (CmtTSQHandle queueHandle);
int CVIFUNC     CmtGetTSQAttribute (CmtTSQHandle queueHandle, int attribute, void *value);
int CVIFUNC_C   CmtSetTSQAttribute (CmtTSQHandle queueHandle, int attribute, ...);
int CVIFUNC     CmtWriteTSQData (CmtTSQHandle queueHandle, const void *buffer, size_t numItems, int timeout, int *numItemsFlushed);
int CVIFUNC     CmtGetTSQWritePtr (CmtTSQHandle queueHandle, void *writePointer, int *numEmptyItems);
int CVIFUNC     CmtReleaseTSQWritePtr (CmtTSQHandle queueHandle, int itemsWritten);
int CVIFUNC     CmtReadTSQData (CmtTSQHandle queueHandle, void *buffer, size_t numItems, int timeout, unsigned int options);
int CVIFUNC     CmtGetTSQReadPtr (CmtTSQHandle queueHandle, void *readPointer, int *numAvailableItems);
int CVIFUNC     CmtReleaseTSQReadPtr (CmtTSQHandle queueHandle, int itemsRead);
int CVIFUNC     CmtFlushTSQ (CmtTSQHandle queueHandle, int numItems, int *numItemsFlushed);
int CVIFUNC     CmtInstallTSQCallback (CmtTSQHandle queueHandle, unsigned int event, int thresholdValue,
                                       CmtTSQCallbackPtr callback, void *callbackData,
                                       unsigned int threadID, CmtTSQCallbackID *callbackID);
int CVIFUNC     CmtUninstallTSQCallback (CmtTSQHandle queueHandle, CmtTSQCallbackID callbackID);
#ifndef _NI_linux_
int CVIFUNC     CmtGetTSQAttributeEx (CmtTSQHandle queueHandle, int attribute, void *value, int timeout);
#endif /* _NI_linux_ */

#ifdef _CVI_DEBUG_
#pragma soft_reference(CmtGetTSQAttributeEx)
#pragma soft_reference(CmtGetTSQReadPtr)
#pragma soft_reference(CmtReleaseTSQReadPtr)
#endif

/* Thread Pool */
int CVIFUNC     CmtScheduleThreadPoolFunction (CmtThreadPoolHandle poolHandle, CmtThreadFunctionPtr threadFunction,
                                               void *threadFunctionData, CmtThreadFunctionID *threadFunctionID);
int CVIFUNC     CmtScheduleThreadPoolFunctionAdv (CmtThreadPoolHandle poolHandle, CmtThreadFunctionPtr threadFunction,
                                                  void *threadFunctionData, int threadFunctionPriority,
                                                  CmtThreadFunctionCallbackPtr callback, unsigned int callbackEventMask,
                                                  void *callbackData, unsigned int callbackThreadID, CmtThreadFunctionID *threadFunctionID);
int CVIFUNC     CmtReleaseThreadPoolFunctionID (CmtThreadPoolHandle poolHandle, CmtThreadFunctionID threadFunctionID);
int CVIFUNC     CmtGetThreadPoolFunctionAttribute (CmtThreadPoolHandle poolHandle, CmtThreadFunctionID threadFunctionID, int attribute, void *value);
int CVIFUNC     CmtWaitForThreadPoolFunctionCompletion (CmtThreadPoolHandle poolHandle, CmtThreadFunctionID threadFunctionID, unsigned int options);
int CVIFUNC     CmtExitThreadPoolThread (int returnValue);

int CVIFUNC     CmtNewThreadPool (int maxNumThreads, CmtThreadPoolHandle *poolHandle);
int CVIFUNC     CmtDiscardThreadPool (CmtThreadPoolHandle poolHandle);
int CVIFUNC     CmtPreAllocThreadPoolThreads (CmtThreadPoolHandle poolHandle, int numThreads, int *numAllocated);
int CVIFUNC     CmtTerminateThreadPoolThread (CmtThreadPoolHandle poolHandle, unsigned int threadID, int exitCode);
int CVIFUNC     CmtGetThreadPoolAttribute (CmtThreadPoolHandle poolHandle, int attribute, void *value);
int CVIFUNC_C   CmtSetThreadPoolAttribute (CmtThreadPoolHandle poolHandle, int attribute, ...);

int CVIFUNC     CmtInstallThreadPoolCallback (CmtThreadPoolHandle poolHandle, unsigned int event, CmtThreadPoolCallbackPtr callback, void *callbackData, CmtThreadPoolCallbackID *callbackID);
int CVIFUNC     CmtUninstallThreadPoolCallback (CmtThreadPoolHandle poolHandle, CmtThreadPoolCallbackID callbackID);


/* Thread Local Variable */
int CVIFUNC     CmtNewThreadLocalVar (size_t varSize, const void *initialValue, CmtTLVCallbackPtr callback, void *callbackData, CmtTLVHandle *tlvHandle);
int CVIFUNC     CmtDiscardThreadLocalVar (CmtTLVHandle tlvHandle);
int CVIFUNC     CmtGetThreadLocalVar (CmtTLVHandle tlvHandle, void *threadLocalPtr);


/* Thread Safe Variable */
int CVIFUNC     CmtNewTSV (size_t tsvSize, CmtTSVHandle *tsvHandle);
int CVIFUNC     CmtDiscardTSV (CmtTSVHandle tsvHandle);
int CVIFUNC     CmtGetTSVPtr (CmtTSVHandle tsvHandle, void *variablePtr);
int CVIFUNC     CmtReleaseTSVPtr (CmtTSVHandle tsvHandle);
int CVIFUNC     CmtSetTSV (CmtTSVHandle tsvHandle, const void *valuePtr);


/* User Lock */
int CVIFUNC CmtNewLock (const char lockName[], unsigned int options, CmtThreadLockHandle *lockHandle);
int CVIFUNC CmtDiscardLock (CmtThreadLockHandle lockHandle);
int CVIFUNC CmtGetLock (CmtThreadLockHandle lockHandle);
int CVIFUNC CmtTryToGetLock (CmtThreadLockHandle lockHandle, int *obtainedLock);
int CVIFUNC CmtReleaseLock (CmtThreadLockHandle lockHandle);
int CVIFUNC CmtGetLockAttribute (CmtThreadLockHandle lockHandle, int attribute, void *value);

#ifdef _CVI_DEBUG_
#pragma soft_reference(CmtGetLockAttribute)
#endif

/* General Multithreading */
int CVIFUNC             CmtGetErrorMessage (int statusCode, char statusMessage[]);
unsigned int CVIFUNC    CmtGetNumProcessors (void);
unsigned int CVIFUNC    CmtGetCurrentThreadID (void);
unsigned int CVIFUNC    CmtGetMainThreadID (void);
int CVIFUNC             CmtGetCurrentThreadPriority (int *priority);
int CVIFUNC             CmtSetCurrentThreadPriority (int priority);


#if defined(_NI_mswin_) || defined(_NI_mswin32_)
int CVIFUNC_C DebugPrintf(const char* format, ...);
int CVIFUNC_C ErrorPrintf(const char* format, ...);
#endif /* defined(_NI_mswin_) || defined(_NI_mswin32_) */

/* Dynamic Memory Information */
int CVIFUNC   CVIDynamicMemoryInfo(const char   message[],
                                   size_t *allocatedBlocks,
                                   size_t *allocatedBytes,
                                   unsigned int  options);

/* Resource tracking */
int CVIFUNC GetEnableResourceTracking (void);
int CVIFUNC SetEnableResourceTracking (int enable);

unsigned short CVIFUNC_C Get387CW(void);
void CVIFUNC_C Set387CW(unsigned short);
void CVIFUNC DisableLoadExternalModuleUndefSymPrompt(void);

#if defined(_CVI_) && !defined(__TPC__)
#pragma PassOrigPtrInfoForVoidPtrParam  CmtSetTSV
#pragma PassOrigPtrInfoForVoidPtrParam  CmtGetTSVPtr
#pragma PassOrigPtrInfoForVoidPtrParam  CmtGetTSQWritePtr
#pragma PassOrigPtrInfoForVoidPtrParam  CmtGetTSQReadPtr
#endif

/* Functions for managing Real-Time targets. OBSOLETE: Superseded by Real-Time Utility Library. */

#pragma pack (4)
typedef struct {
    unsigned long serialNumber;
    char ipAddress[16];     /* format: xxx.xxx.xxx.xxx */
    char status[32];
    char modelDescription[32];
    char hostName[32];
    char macAddress[6];     /* returned as hex data */
} RTControllerInfo;
#pragma pack ()

#ifndef RTISSHUTTINGDOWN_DECLARED
#define RTISSHUTTINGDOWN_DECLARED
int CVIFUNC RTIsShuttingDown (void);
#endif

int CVIFUNC RTControllerQuery (char *ipAddress, RTControllerInfo *info);
int CVIFUNC RTControllerReboot (char *ipAddress);

typedef enum {
    kRTTargetIsInInstallMode    =   -14981, // The real-time target is installing software.
    kRTTargetIsLocked           =   -14982, // The real-time target is locked.
    kRTTargetOtherError         =   -14983, // The real-time target could not be rebooted.
} RealTimeTargetErrors;

#endif /* defined(_NI_mswin_) || defined(_NI_mswin32_) || defined(_NI_linux_) */

/************************************************************************/
/* This class of functions is obsolete. National Instruments recommends */
/* that you instead use the Windows SDK functions LoadLibrary and       */
/* GetProcAddress to load external modules. These functions allow you   */
/* to load Windows DLLs, but not compiled object modules or libraries.  */
/************************************************************************/
int CVIFUNC    LoadExternalModule (const char pathName[]);
int CVIFUNC    LoadExternalModuleEx (const char pathName[], const void *hInstance);
void * CVIFUNC GetExternalModuleAddr (int moduleId, const char symbolName[], int *status);
void * CVIFUNC GetExternalModuleAddrEx (int moduleId, const char symbolName[], int *status,
                                        unsigned options, char buf[], unsigned bufSize);
int CVIFUNC    ReleaseExternalModule(int moduleId);
int CVIFUNC    RunExternalModule (int moduleId, const char buffer[]);
int CVIFUNC    UnloadExternalModule (int moduleId);

/****************/
/* CVI Time API */
/****************/
#pragma pack (4)
#ifndef CVITime_DECLARED
#define CVITime_DECLARED
typedef struct CVITime { unsigned __int64 lsb; __int64 msb; } CVITime;
#endif
#ifndef CVIAbsoluteTime_DECLARED
#define CVIAbsoluteTime_DECLARED
typedef union CVIAbsoluteTime { CVITime cviTime; unsigned int u32Data[4]; } CVIAbsoluteTime;
#endif
#ifndef CVITimeInterval_DECLARED
#define CVITimeInterval_DECLARED
typedef union CVITimeInterval { CVITime cviTime; unsigned int u32Data[4]; } CVITimeInterval;
#endif
#pragma pack ()

typedef enum
{
    CVITimeUnitBase             = 919263177UL - 48UL,
    CVITimeUnitAttoseconds      = CVITimeUnitBase + 30UL,
    CVITimeUnitFemtoseconds     = CVITimeUnitBase + 33UL,
    CVITimeUnitPicoseconds      = CVITimeUnitBase + 36UL,
    CVITimeUnitNanoseconds      = CVITimeUnitBase + 39UL,
    CVITimeUnit100Nanoseconds   = CVITimeUnitBase + 41UL,
    CVITimeUnitMicroseconds     = CVITimeUnitBase + 42UL,
    CVITimeUnitMilliseconds     = CVITimeUnitBase + 45UL,
    CVITimeUnitSeconds          = CVITimeUnitBase + 48UL,
    CVITimeUnitMinutes          = CVITimeUnitBase + 50UL,
    CVITimeUnitHours            = CVITimeUnitBase + 52UL,
    CVITimeUnitDays             = CVITimeUnitBase + 54UL,
} CVITimeUnit;

typedef enum
{
    CVITimeRoundMethodNear              = 1,
    CVITimeRoundMethodTruncate,
    CVITimeRoundMethodUp,
    CVITimeRoundMethodDown,
    CVITimeRoundForceSizeToFourBytes    = 0xFFFFFFFF
} CVITimeRoundMethod;

typedef enum
{
    kCVITimeInvalidArgumentError        = -1,
    kCVITimeNullPointerError            = -2,
    kCVITimeOverflowError               = -3,
    kCVITimeDateOutOfRangeError         = -4,
    kCVITimeOperationFailedError        = -5,
} CVITimeError;

int CVIFUNC GetCurrentCVIAbsoluteTime(CVIAbsoluteTime *absTime);

int CVIFUNC CVIAbsoluteTimeFromLocalCalendar(unsigned year, unsigned month, unsigned day, 
        unsigned hour, unsigned minute, unsigned second, double milliSecond, 
        CVIAbsoluteTime *absTime);
int CVIFUNC CVIAbsoluteTimeToLocalCalendar(CVIAbsoluteTime absTime, unsigned *year, 
        unsigned *month, unsigned *day, unsigned *hour, unsigned *minute, 
        unsigned *second, double *milliSecond, unsigned *weekDay);

int CVIFUNC AddToCVIAbsoluteTime(CVIAbsoluteTime absTime, CVITimeInterval interval, 
        CVIAbsoluteTime *result);
int CVIFUNC SubtractFromCVIAbsoluteTime(CVIAbsoluteTime absTime, CVITimeInterval interval, 
        CVIAbsoluteTime *result);
int CVIFUNC SubtractCVIAbsoluteTimes(CVIAbsoluteTime absTime1, CVIAbsoluteTime absTime2, 
        CVITimeInterval *result);
int CVIFUNC IncrementCVIAbsoluteTime(CVIAbsoluteTime *absTime, CVITimeInterval increment);
int CVIFUNC DecrementCVIAbsoluteTime(CVIAbsoluteTime *absTime, CVITimeInterval decrement);

int CVIFUNC CompareCVIAbsoluteTimes(CVIAbsoluteTime absTime1, CVIAbsoluteTime absTime2, int *result);
int CVIFUNC CompareCVIAbsoluteTimesWithTolerance(CVIAbsoluteTime absTime1, 
        CVIAbsoluteTime absTime2, CVITimeInterval tolerance, int *result);

int CVIFUNC CVITimeIntervalFromSeconds(double seconds, CVITimeInterval *interval);
int CVIFUNC CVITimeIntervalToSeconds(CVITimeInterval interval, double *seconds);
int CVIFUNC CVITimeIntervalFromTimeUnit(CVITimeUnit unit, __int64 value, CVITimeInterval *interval);
int CVIFUNC CVITimeIntervalToTimeUnit(CVITimeInterval interval, CVITimeUnit unit, 
        CVITimeRoundMethod roundMethod, __int64 *value);
int CVIFUNC CVITimeIntervalToFractionalUnitTime(CVITimeInterval interval, CVITimeUnit unit, 
        CVITimeInterval *fractionalTime);

int CVIFUNC AddCVITimeIntervals(CVITimeInterval interval1, CVITimeInterval interval2, 
        CVITimeInterval *result);
int CVIFUNC SubtractCVITimeIntervals(CVITimeInterval interval1, CVITimeInterval interval2, 
        CVITimeInterval *result);
int CVIFUNC MultiplyCVITimeInterval(CVITimeInterval interval, __int64 multiplier, 
        CVITimeInterval *result);
int CVIFUNC DivideCVITimeInterval(CVITimeInterval interval, __int64 divisor, CVITimeInterval *result);
int CVIFUNC IncrementCVITimeInterval(CVITimeInterval *interval, CVITimeInterval increment);
int CVIFUNC DecrementCVITimeInterval(CVITimeInterval *interval, CVITimeInterval decrement);

int CVIFUNC CompareCVITimeIntervals(CVITimeInterval interval1, CVITimeInterval interval2, int *result);
int CVIFUNC CompareCVITimeIntervalsWithTolerance(CVITimeInterval interval1, 
        CVITimeInterval interval2, CVITimeInterval tolerance, int *result);

/**********************/
/* Profiler Functions */
/**********************/
int CVIFUNC CVIProfSetCurrentThreadProfiling(int enable);
int CVIFUNC CVIProfGetCurrentThreadProfiling(int *enabled);

#ifdef __cplusplus
    }
#endif

#endif /* UTILITY_HEADER */

