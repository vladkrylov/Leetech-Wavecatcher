/*============================================================================*/
/*                        L a b W i n d o w s / C V I                         */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 2005-2009.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       cvinetv.h                                                     */
/* Purpose:     Header file for LabWindows/CVI Network Variables Library      */
/*                                                                            */
/*============================================================================*/

#ifndef __CVINETV_H__
#define __CVINETV_H__

#include "cvidef.h"

#if defined(_CVI_) && !defined(__TPC__)
#pragma EnableLibraryRuntimeChecking
#endif

#ifdef __cplusplus
    extern "C" {
#endif

//-----------------------------------------------------------------------------
// Data types
//-----------------------------------------------------------------------------
typedef struct  __CNVData                   _CNVData;
typedef struct  __CNVSubscriber             _CNVSubscriber;
typedef struct  __CNVBufferedSubscriber     _CNVBufferedSubscriber;
typedef struct  __CNVReader                 _CNVReader;
typedef struct  __CNVAsyncReader            _CNVAsyncReader;
typedef struct  __CNVBufferedWriter         _CNVBufferedWriter;
typedef struct  __CNVWriter                 _CNVWriter;
typedef struct  __CNVBrowser                _CNVBrowser;
typedef _CNVData *                          CNVData;
typedef _CNVSubscriber *                    CNVSubscriber;
typedef _CNVBufferedSubscriber *            CNVBufferedSubscriber;
typedef _CNVReader *                        CNVReader;
typedef _CNVAsyncReader *                   CNVAsyncReader;
typedef _CNVBufferedWriter *                CNVBufferedWriter;
typedef _CNVWriter *                        CNVWriter;
typedef _CNVBrowser *                       CNVBrowser;

#define CNVWaitForever      ((int)-1)
#define CNVDoNotWait        ((int)-2)

typedef enum
{   
    CNVErrorBegin                               = -6399,
    
    CNVLibCouldNotBeLoadedError                 = CNVErrorBegin,
    CNVInvalidLibVersionError,
    CNVCouldNotCreateMutexError,

    CNVUnexpectedError,
    CNVNotImplementedError,
    CNVOutOfMemoryError,
    CNVInvalidArgumentError,
    CNVOperationAbortedError,
    CNVAccessDeniedError,
    CNVPendingError,
    
    CNVInvalidPacketError,
    CNVDuplicateError,
    CNVContextError,
    CNVNotFoundError,
    CNVInvalidObjectError,
    CNVConnectedError,
    CNVNoSuchNameError,
    CNVDisconnectedError,
    CNVNoSuchServiceError,
    CNVConnectingError,
    CNVLogosStartupError,
    CNVWriterExistsError,
    CNVNetworkError,
    CNVCacheOverflowError,
    CNVNoMoreEntriesError,
    CNVNetworkDataError,
    CNVAlreadySubscribedError,
    CNVBufferFullError,
    CNVNoWriteAccessError,
    CNVInvalidNetworkVariableNameError,
    CNVInvalidMachineNameError,
    CNVInvalidProcessNameError,
    CNVInvalidPointNameError,
    CNVProcessManagerDownError,
    CNVThreadInitFailedError,
    CNVItemDoesNotExistError,
    CNVProcessServerDownError,
    CNVReadAccessDeniedError,
    CNVWriteAccessDeniedError,
    CNVAlarmDisabledError,
    CNVHostResolveError,
    CNVIPResolveError,
    CNVUnknownAttributeNameError,
    CNVInvalidAttributeValueError,
    CNVAttributeAccessError,
    
    CNVInvalidDataTypeError,
    CNVInvalidConnectionHandleError,
    CNVInvalidDataHandleError,
    CNVInvalidBrowserHandleError,
    CNVInvalidNumberOfDimensionsError,
    CNVNotAnArrayError,
    CNVInvalidArraySizeError,
    CNVMissingDataAttributeError,
    CNVInvalidConnectionAttributeError,
    CNVWaitTimeElapsedError,
    CNVEmptyDataError,
    CNVNotSupportedOnRealTimeError,
    CNVNotSupportedInCallbackError,
    CNVCouldNotRegisterMachineError,

    CNVDNSFailureError,
    CNVHostUnreachableError,
    CNVServiceLookupFailureError,
    CNVProcessFailureError,
    CNVResolveURLFailureError,
    CNVSubscribeFailedError,

    CNVNotAScalarError,
    CNVNotAStructError,

    CNVErrorEnd,
    CNVErrorForceSizeTo32Bits                   = 0xffffffff

} CNVError;

typedef enum
{
    CNVEmpty = 0,

    CNVInt8 = 1,
    CNVInt16,
    CNVInt32,
    CNVInt64,

    CNVUInt8,
    CNVUInt16,
    CNVUInt32,
    CNVUInt64,

    CNVBool,
    CNVSingle,
    CNVDouble,

    CNVString,

    CNVStruct,

    CNVDataType4Bytes = 0xffffffff
} CNVDataType;

typedef enum
{
    CNVConnecting               = 1,
    CNVConnected                = 2,
    CNVDisconnected             = 3,

    CNVConnectionStatus4Bytes   = 0xffffffff
} CNVConnectionStatus;

typedef enum
{
    CNVConnectionStatusAttribute,           // CNVConnectionStatus  [readonly]  
    CNVConnectionErrorAttribute,            // int                  [readonly]  
    CNVMostRecentDataAttribute,             // CNVData              [readonly]
    CNVClientBufferMaximumItemsAttribute,   // int                  [read-write]
    CNVClientBufferNumberOfItemsAttribute,  // int                  [read]
    CNVFlushOnWriteAttribute,               // int                  [read-write]

    CNVConnectionAttribute4Bytes = 0xffffffff
} CNVConnectionAttribute;

typedef enum
{
    CNVNewData          = 1,
    CNVNoData,
    CNVStaleData,
    CNVDataWasLost,

    CNVBufferDataStatus4Bytes = 0xffffffff
} CNVBufferDataStatus;

typedef enum
{   
    CNVBrowseTypeUndefined          = 0,
    CNVBrowseTypeMachine            = 1,
    CNVBrowseTypeProcess            = 2,
    CNVBrowseTypeFolder             = 4,
    CNVBrowseTypeItem               = 7,
    CNVBrowseTypeItemRange          = 8,
    CNVBrowseTypeImplicitItem       = 17,   // Item whose path name is the same as it's parent

    CNVBrowseType4Bytes             = 0xffffffff
} CNVBrowseType;

typedef enum
{
    CNVVariableServerBufferMaxItemsAttribute    = 1,    // unsiged int [read-write]
    CNVVariableSingleWriterAttribute,                   // int [read-write]
    CNVVariablePrototypeAttribute,                      // CNVData [read-write]
    CNVVariableDescriptionAttribute,                    // char * [read-write]

    CNVVariableAttribute4Bytes      = 0xffffffff
} CNVVariableAttribute;

typedef unsigned __int64 CNVDataQuality; 

#define CNVDataQualityGood                              ((CNVDataQuality) (0))
#define CNVDataQualityStale                             ((CNVDataQuality) (1 << 0))
#define CNVDataQualitySensorFailure                     ((CNVDataQuality) (1 << 1))
#define CNVDataQualityDeviceFailure                     ((CNVDataQuality) (1 << 2))
#define CNVDataQualityServerFailure                     ((CNVDataQuality) (1 << 3))
#define CNVDataQualityNetworkFailure                    ((CNVDataQuality) (1 << 4))
#define CNVDataQualityNonexistent                       ((CNVDataQuality) (1 << 5))
#define CNVDataQualityNoKnownValue                      ((CNVDataQuality) (1 << 6))
#define CNVDataQualityInactive                          ((CNVDataQuality) (1 << 7))
#define CNVDataQualityForced                            ((CNVDataQuality) (1 << 8))
#define CNVDataQualityLowLimited                        ((CNVDataQuality) (1 << 9))
#define CNVDataQualityHighLimited                       ((CNVDataQuality) (1 << 10))
#define CNVDataQualityConstant                          ((CNVDataQuality) (1 << 11))
#define CNVDataQualitySensorInaccurate                  ((CNVDataQuality) (1 << 12))
#define CNVDataQualityEULimitsExceeded                  ((CNVDataQuality) (1 << 13))
#define CNVDataQualitySubnormal                         ((CNVDataQuality) (1 << 14))
#define CNVDataQualityMathException                     ((CNVDataQuality) (1 << 15))
#define CNVDataQualityCommLinkFailure                   ((CNVDataQuality) (1 << 16))
#define CNVDataQualityConnecting                        ((CNVDataQuality) (1 << 17))
#define CNVDataQualityDNSFailure                        ((CNVDataQuality) (1 << 18))
#define CNVDataQualityHostUnreachable                   ((CNVDataQuality) (1 << 19))
#define CNVDataQualityServiceLookupFailure              ((CNVDataQuality) (1 << 20))
#define CNVDataQualityDisconnected                      ((CNVDataQuality) (1 << 21))
#define CNVDataQualityProcessFailure                    ((CNVDataQuality) (1 << 22))
#define CNVDataQualityResolveURLFailure                 ((CNVDataQuality) (1 << 23))
#define CNVDataQualityAccessDenied                      ((CNVDataQuality) (1 << 24))
#define CNVDataQualityInvalidURL                        ((CNVDataQuality) (1 << 25))
#define CNVDataQualityAppDefined1                       ((CNVDataQuality) (1 << 26))
#define CNVDataQualityAppDefined2                       ((CNVDataQuality) (1 << 27))
#define CNVDataQualityAppDefined3                       ((CNVDataQuality) (1 << 28))
#define CNVDataQualityInAlarm                           ((CNVDataQuality) (1 << 29))
#define CNVDataQualitySubscribeFailed                   ((CNVDataQuality) (1 << 30))
#define CNVDataQualityExtendedInfo                      ((CNVDataQuality) (1 << 31))
#define CNVDataQualityReadBufferFull                    (((CNVDataQuality) (1 << 0)) << 32)
#define CNVDataQualityReadBufferOverflow                (((CNVDataQuality) (1 << 1)) << 32)
#define CNVDataQualityServerWriteBufferFull             (((CNVDataQuality) (1 << 2)) << 32)
#define CNVDataQualityServerWriteBufferBufferOverflow   (((CNVDataQuality) (1 << 3)) << 32)

typedef void (CVICALLBACK * CNVStatusCallback)(void * handle, 
                                               CNVConnectionStatus status, 
                                               int error, void * callbackData);
typedef void (CVICALLBACK * CNVDataCallback)(void * handle, CNVData data, 
                                             void * callbackData);
typedef void (CVICALLBACK * CNVDataTransferredCallback)(void * handle, int error, 
                                                        void * callbackData);

//-----------------------------------------------------------------------------
// General functions
//-----------------------------------------------------------------------------

int CVIFUNC CNVCreateSubscriber(const char * networkVariablePathName, 
                CNVDataCallback dataCallback, CNVStatusCallback statusCallback, 
                void * callbackData, int waitTime, intptr_t reserved, 
                CNVSubscriber * subscriber); 

int CVIFUNC CNVCreateBufferedSubscriber(const char * networkVariablePathName, 
                CNVStatusCallback statusCallback, void * callbackData, 
                int clientBufferMaxItems, int waitTime, intptr_t reserved,
                CNVBufferedSubscriber * subscriber); 

int CVIFUNC CNVCreateReader(const char * networkVariablePathName, 
                CNVStatusCallback statusCallback, void * callbackData, 
                int waitTime, intptr_t reserved, CNVReader * reader);

int CVIFUNC CNVCreateAsyncReader(const char * networkVariablePathName, 
                CNVDataCallback dataCallback, CNVStatusCallback statusCallback, 
                void * callbackData, int waitTime, intptr_t reserved, 
                CNVAsyncReader * reader);

int CVIFUNC CNVCreateBufferedWriter(const char * networkVariablePathName, 
                CNVDataTransferredCallback dataTransferredCallback, 
                CNVStatusCallback statusCallback, void * callbackData, 
                int clientBufferMaxItems, int waitTime, intptr_t reserved,
                CNVBufferedWriter * bufferedWriter);

int CVIFUNC CNVCreateWriter(const char * networkVariablePathName, 
                CNVStatusCallback statusCallback, void * callbackData, 
                int waitTime, intptr_t reserved, CNVWriter * writer);

int CVIFUNC CNVGetDataFromBuffer(CNVBufferedSubscriber subscriber, 
                CNVData * data, CNVBufferDataStatus * status);

int CVIFUNC CNVRead(CNVReader reader, int waitTime, CNVData * data);

int CVIFUNC CNVReadAsync(CNVAsyncReader reader);

int CVIFUNC CNVPutDataInBuffer(CNVBufferedWriter bufferedWriter, CNVData data, 
                int bufferWaitTime);

int CVIFUNC CNVWrite(CNVWriter writer, CNVData data, int waitTime);

int CVIFUNC CNVGetConnectionAttribute(void * handle, 
                CNVConnectionAttribute attribute, void * value);

int CVIFUNC_C CNVSetConnectionAttribute(void * handle, 
                CNVConnectionAttribute attribute, ...);

int CVIFUNC CNVDispose(void * handle);

//-----------------------------------------------------------------------------
// Data functions
//-----------------------------------------------------------------------------
int CVIFUNC CNVGetDataType(CNVData data, CNVDataType * type, 
                unsigned long * numDimensions);
int CVIFUNC CNVGetArrayDataDimensions(CNVData data, 
                size_t numDimensions, size_t dimensions[]);
int CVIFUNC CNVGetScalarDataValue(CNVData data, CNVDataType type, void * value);
int CVIFUNC CNVGetArrayDataValue(CNVData data, CNVDataType type, void * buffer, 
                size_t numElements);
int CVIFUNC CNVGetNumberOfStructFields(CNVData data, unsigned short * numFields);
int CVIFUNC CNVGetStructFields(CNVData data, CNVData fields[], 
                size_t numFields);
int CVIFUNC_C CNVCreateScalarDataValue(CNVData * data, CNVDataType type, ...);
int CVIFUNC CNVCreateArrayDataValue(CNVData * data, CNVDataType type, 
                const void * array, size_t numDimensions, 
                size_t dimensions[]);
int CVIFUNC CNVCreateStructDataValue(CNVData * data, CNVData fields[], 
                size_t numFields);
int CVIFUNC_C CNVSetScalarDataValue(CNVData data, CNVDataType type, ...);
int CVIFUNC CNVSetArrayDataValue(CNVData data, CNVDataType type, 
                const void * array, size_t numDimensions, 
                size_t dimensions[]);
int CVIFUNC CNVSetStructDataValue(CNVData data, CNVData fields[], 
                size_t numFields);
int CVIFUNC CNVGetDataQuality(CNVData data, CNVDataQuality * quality);
int CVIFUNC CNVGetDataUTCTimestamp(CNVData data, unsigned __int64 * timestamp);
int CVIFUNC CNVGetDataServerError(CNVData data, unsigned int * serverError);
int CVIFUNC CNVGetTimestampInfo(unsigned __int64 timestamp, int * year,
                int * month, int * day, int * hour, int * minute, 
                double * second);
int CVIFUNC CNVCheckDataQuality(CNVDataQuality quality, int * good);
int CVIFUNC CNVGetDataQualityDescription(CNVDataQuality quality, 
                const char * delimiter, char ** description);
int CVIFUNC CNVDisposeData(CNVData data);

//-----------------------------------------------------------------------------
// Browser functions - not supported on CVI real-time platforms
//-----------------------------------------------------------------------------
int CVIFUNC CNVCreateBrowser(CNVBrowser * browser);
int CVIFUNC CNVBrowse(CNVBrowser browser, const char * location);
int CVIFUNC CNVBrowseNextItem(CNVBrowser browser, char ** item, int * leaf,
                              CNVBrowseType * browseType, CNVData * typeData);
int CVIFUNC CNVDisposeBrowser(CNVBrowser browser);
int CVIFUNC CNVRegisterMachine(const char * machine);
int CVIFUNC CNVUnregisterMachine(const char * machine);
int CVIFUNC CNVGetRegisteredMachines(char *** machines, unsigned int * numMachines);

//-----------------------------------------------------------------------------
// Configuration functions
//-----------------------------------------------------------------------------
int CVIFUNC CNVVariableEngineIsRunning(int * isRunning);

// Process functions
int CVIFUNC CNVGetProcesses(char *** processes, int * numProcesses);
int CVIFUNC CNVProcessExists(const char * processName, int * exists);
int CVIFUNC CNVNewProcess(const char * processName);
int CVIFUNC CNVDeleteProcess(const char * processName);
int CVIFUNC CNVStartProcess(const char * processName);
int CVIFUNC CNVStopProcess(const char * processName);
int CVIFUNC CNVProcessIsRunning(const char * processName, int * isRunning);

// Variable functions
int CVIFUNC CNVGetVariables(const char * processName, char *** variables, 
                            int * numVariables);
int CVIFUNC CNVVariableExists(const char * processName, const char * variableName, 
                              int * exists);
int CVIFUNC CNVNewVariable(const char * processName, const char * variableName);
int CVIFUNC CNVNewVariableCollection(const char * processName, size_t numVariables,
                                     const char * variableNames[], 
                                     unsigned int maxBufferItems, int singleWriter);
int CVIFUNC CNVDeleteVariable(const char * processName, const char * variableName);
int CVIFUNC CNVGetVariableAttribute(const char * processName, 
                                    const char * variableName, 
                                    CNVVariableAttribute attribute,
                                    void * value);
int CVIFUNC_C CNVSetVariableAttribute(const char * processName, 
                                      const char * variableName, 
                                      CNVVariableAttribute attribute, ...);

//-----------------------------------------------------------------------------
// Miscellaneous functions
//-----------------------------------------------------------------------------
void CVIFUNC CNVFreeMemory(void * pointer);
const char * CVIFUNC CNVGetErrorDescription(int errorCode);
void CVIFUNC CNVFinish(void);

//-----------------------------------------------------------------------------
// Advanced functions
//-----------------------------------------------------------------------------
int CVIFUNC CNVFlushAllConnections(int waitTime);

//-----------------------------------------------------------------------------

#if defined(_CVI_) && !defined(__TPC__)
#pragma PassOrigPtrInfoForVoidPtrParam  CNVGetScalarDataValue
#endif

#ifdef __cplusplus
}
#endif

#endif // ifndef __CVINETV_H__

//-----------------------------------------------------------------------------

