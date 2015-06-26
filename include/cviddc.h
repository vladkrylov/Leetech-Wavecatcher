/*============================================================================*/
/*                        DIAdem Connectivity Library                         */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 2004-2009.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       cviddc.h                                                      */
/* Purpose:     Include file for DIAdem Connectivity Library                  */
/*                                                                            */
/*============================================================================*/

#ifndef _CVIDDC_H
#define _CVIDDC_H

#include <cvidef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_CVI_) && !defined(__TPC__)
#pragma EnableLibraryRuntimeChecking
#endif

//*****************************************************************************
// Typedefs, enums, constants, etc.
//*****************************************************************************

#ifdef WIN32
    #pragma pack(push)
    #pragma pack(4)
#endif

typedef struct _DDCFile             DDCFile;
typedef struct _DDCChannelGroup     DDCChannelGroup;
typedef struct _DDCChannel          DDCChannel;

typedef DDCFile*                    DDCFileHandle;
typedef DDCChannelGroup*            DDCChannelGroupHandle;
typedef DDCChannel*                 DDCChannelHandle;

#ifndef CVITime_DECLARED
#define CVITime_DECLARED
typedef struct CVITime { unsigned __int64 lsb; __int64 msb; } CVITime;
#endif

#ifndef CVIAbsoluteTime_DECLARED
#define CVIAbsoluteTime_DECLARED
typedef union CVIAbsoluteTime { CVITime cviTime; unsigned int u32Data[4]; } CVIAbsoluteTime;
#endif

#ifdef WIN32
    #pragma pack(pop)
#endif

typedef enum {
    DDC_UInt8       = 5,    // unsigned char
    DDC_Int16       = 2,    // short
    DDC_Int32       = 3,    // int
    DDC_Float       = 9,    // float
    DDC_Double      = 10,   // double
    DDC_String      = 23,   // string
    DDC_Timestamp   = 30,   // timestamp (CVIAbsoluteTime or Year/Month/Day/Hour/Minute/Second/Millisecond components)
} DDCDataType;

// File type constants
#define DDC_FILE_TYPE_TDM               "TDM"
#define DDC_FILE_TYPE_TDM_STREAMING     "TDMS"
#define DDC_FILE_TYPE_TDM_STREAMING1_0  "TDMS1_0"

// File property constants
#define DDC_FILE_NAME                   "name"              // Name
#define DDC_FILE_DESCRIPTION            "description"       // Description
#define DDC_FILE_TITLE                  "title"             // Title
#define DDC_FILE_AUTHOR                 "author"            // Author
#define DDC_FILE_DATETIME               "datetime"          // Date/Time

// ChannelGroup property constants
#define DDC_CHANNELGROUP_NAME           "name"              // Name
#define DDC_CHANNELGROUP_DESCRIPTION    "description"       // Description

// Channel property constants
#define DDC_CHANNEL_NAME                "name"              // Name
#define DDC_CHANNEL_DESCRIPTION         "description"       // Description
#define DDC_CHANNEL_UNIT_STRING         "unit_string"       // Unit String
#define DDC_CHANNEL_MINIMUM             "minimum"           // Minimum
#define DDC_CHANNEL_MAXIMUM             "maximum"           // Maximum

// Error codes
typedef enum {

    DDC_NoError                                 = 0,            // No error
    DDC_ErrorBegin                              = -6201,        //

    DDC_OutOfMemory                             = -6201,        // The library could not allocate memory.
    DDC_InvalidArgument                         = -6202,        // An invalid argument was passed to the library.
    DDC_InvalidDataType                         = -6203,        // An invalid data type was passed to the library.
    DDC_UnexpectedError                         = -6204,        // An unexpected error occurred in the library.
    DDC_UsiCouldNotBeLoaded                     = -6205,        // The USI engine could not be loaded.
    DDC_InvalidFileHandle                       = -6206,        // An invalid file handle was passed to the library.
    DDC_InvalidChannelGroupHandle               = -6207,        // An invalid channel group handle was passed to the library.
    DDC_InvalidChannelHandle                    = -6208,        // An invalid channel handle was passed to the library.
    DDC_FileDoesNotExist                        = -6209,        // The file passed to the library does not exist.
    DDC_CannotWriteToReadOnlyFile               = -6210,        // The file passed to the library is read only and cannot be modified.
    DDC_StorageCouldNotBeOpened                 = -6211,        // The storage could not be opened.
    DDC_FileAlreadyExists                       = -6212,        // The file passed to the library already exists and cannot be created.
    DDC_PropertyDoesNotExist                    = -6213,        // The property passed to the library does not exist.
    DDC_PropertyDoesNotContainData              = -6214,        // The property passed to the library does not have a value.
    DDC_PropertyIsNotAScalar                    = -6215,        // The value of the property passed to the library is an array and not a scalar.
    DDC_DataObjectTypeNotFound                  = -6216,        // The object type passed to the library does not exist.
    DDC_NotImplemented                          = -6217,        // The current implementation does not support this operation.
    DDC_CouldNotSaveFile                        = -6218,        // The file could not be saved.
    DDC_MaximumNumberOfDataValuesExceeded       = -6219,        // The request would exceed the maximum number of data values for a channel.
    DDC_InvalidChannelName                      = -6220,        // An invalid channel name was passed to the library.
    DDC_DuplicateChannelName                    = -6221,        // The channel group already contains a channel with this name.
    DDC_DataTypeNotSupported                    = -6222,        // The current implementation does not support this data type.
    DDC_TDMStreamingPluginMustBeInstalled       = -6223,        // The TDM Streaming plug-in must be installed for this operation.
    DDC_FileAccessDenied                        = -6224,        // File access denied.
    DDC_InvalidTimeValue                        = -6225,        // The specified time value is invalid.
    DDC_ReplaceNotSupportedForSavedTDMSData     = -6226,        // The replace operation is not supported on data that has already been saved to a TDM Streaming file.

    DDC_ErrorEnd                                = -6226,        //
    DDC_ErrorForceSizeTo32Bits                  = 0xffffffff    //

} DDCError;

//*****************************************************************************
/// -> Object Management
//*****************************************************************************
int CVIFUNC DDC_CreateFile (const char *filePath,
                            const char *fileType,
                            const char *name,
                            const char *description,
                            const char *title,
                            const char *author,
                            DDCFileHandle *file);

int CVIFUNC DDC_AddChannelGroup (DDCFileHandle file,
                                 const char *name,
                                 const char *description,
                                 DDCChannelGroupHandle *channelGroup);

int CVIFUNC DDC_AddChannel (DDCChannelGroupHandle channelGroup,
                            DDCDataType dataType,
                            const char *name,
                            const char *description,
                            const char *unitString,
                            DDCChannelHandle *channel);

int CVIFUNC DDC_SaveFile (DDCFileHandle file);

int CVIFUNC DDC_CloseFile (DDCFileHandle file);

int CVIFUNC DDC_OpenFileEx(const char *filePath, 
                           const char *fileType, 
                           int readOnly, 
                           DDCFileHandle *file);

//*****************************************************************************
/// -> Advanced
//*****************************************************************************
int CVIFUNC DDC_RemoveChannelGroup (DDCChannelGroupHandle channelGroup);

int CVIFUNC DDC_RemoveChannel (DDCChannelHandle channel);

int CVIFUNC DDC_CloseChannelGroup (DDCChannelGroupHandle channelGroup);

int CVIFUNC DDC_CloseChannel (DDCChannelHandle channel);

//*****************************************************************************
/// <- Advanced
//*****************************************************************************
//*****************************************************************************
/// -> Obsolete
//*****************************************************************************
int CVIFUNC DDC_OpenFile (const char *filePath,
                          const char *fileType,
                          DDCFileHandle *file);

//*****************************************************************************
/// <- Obsolete
//*****************************************************************************
//*****************************************************************************
/// <- Object Management
//*****************************************************************************

//*****************************************************************************
/// -> Data Storage
//*****************************************************************************
int CVIFUNC DDC_SetDataValues (DDCChannelHandle channel,
                               void *values,
                               size_t numValues);

int CVIFUNC DDC_AppendDataValues (DDCChannelHandle channel,
                                  void *values,
                                  size_t numValues);

int CVIFUNC DDC_ReplaceDataValues (DDCChannelHandle channel,
                                   size_t indexOfFirstValueToReplace,
                                   void *values,
                                   size_t numValues);

//*****************************************************************************
/// <- Data Storage
//*****************************************************************************

//*****************************************************************************
/// -> Data Retrieval
//*****************************************************************************

//*****************************************************************************
/// -> Enumeration
//*****************************************************************************
int CVIFUNC DDC_GetNumChannelGroups (DDCFileHandle file,
                                     unsigned int *numChannelGroups);

int CVIFUNC DDC_GetChannelGroups (DDCFileHandle file,
                                  DDCChannelGroupHandle channelGroupsBuf[],
                                  size_t numChannelGroups);

int CVIFUNC DDC_GetNumChannels (DDCChannelGroupHandle channelGroup,
                                unsigned int *numChannels);

int CVIFUNC DDC_GetChannels (DDCChannelGroupHandle channelGroup,
                             DDCChannelHandle channelsBuf[],
                             size_t numChannels);

//*****************************************************************************
/// <- Enumeration
//*****************************************************************************

int CVIFUNC DDC_GetNumDataValues (DDCChannelHandle channel,
                                  unsigned __int64 *numValues);

int CVIFUNC DDC_GetDataValues (DDCChannelHandle channel,
                               size_t indexOfFirstValueToGet,
                               size_t numValuesToGet,
                               void *values);

int CVIFUNC DDC_GetDataType (DDCChannelHandle channel,
                             DDCDataType *dataType);

//*****************************************************************************
/// <- Data Retrieval
//*****************************************************************************

//*****************************************************************************
/// -> Properties
//*****************************************************************************

//*****************************************************************************
/// -> File
//*****************************************************************************
int CVIFUNC_C DDC_SetFileProperty (DDCFileHandle file,
                                   const char *property,
                                   ...);

int CVIFUNC DDC_SetFilePropertyV (DDCFileHandle file,
                                  const char *property,
                                  va_list args);

int CVIFUNC DDC_GetFileProperty (DDCFileHandle file,
                                 const char *property,
                                 void *value,
                                 size_t valueSizeInBytes);

int CVIFUNC DDC_GetFileStringPropertyLength (DDCFileHandle file,
                                             const char *property,
                                             unsigned int *length);

int CVIFUNC_C DDC_CreateFileProperty (DDCFileHandle file,
                                      const char *property,
                                      DDCDataType dataType,
                                      ...);

int CVIFUNC DDC_CreateFilePropertyV (DDCFileHandle file,
                                     const char *property,
                                     DDCDataType dataType,
                                     va_list args);

int CVIFUNC DDC_FilePropertyExists (DDCFileHandle file,
                                    const char *property,
                                    int *exists);

int CVIFUNC DDC_GetNumFileProperties (DDCFileHandle file, 
                                      unsigned int *numProperties);

int CVIFUNC DDC_GetFilePropertyNames (DDCFileHandle file, 
                                      char** propertyNames, 
                                      size_t numPropertyNames);

int CVIFUNC DDC_GetFilePropertyType (DDCFileHandle file, 
                                     const char *property, 
                                     DDCDataType *dataType);

//*****************************************************************************
/// <- File
//*****************************************************************************

//*****************************************************************************
/// -> Channel Group
//*****************************************************************************
int CVIFUNC_C DDC_SetChannelGroupProperty (DDCChannelGroupHandle channelGroup,
                                           const char *property,
                                           ...);

int CVIFUNC DDC_SetChannelGroupPropertyV (DDCChannelGroupHandle channelGroup,
                                          const char *property,
                                          va_list args);

int CVIFUNC DDC_GetChannelGroupProperty (DDCChannelGroupHandle channelGroup,
                                         const char *property,
                                         void *value,
                                         size_t valueSizeInBytes);

int CVIFUNC DDC_GetChannelGroupStringPropertyLength (DDCChannelGroupHandle channelGroup,
                                                     const char *property,
                                                     unsigned int *length);

int CVIFUNC_C DDC_CreateChannelGroupProperty (DDCChannelGroupHandle channelGroup,
                                              const char *property,
                                              DDCDataType dataType,
                                              ...);

int CVIFUNC DDC_CreateChannelGroupPropertyV (DDCChannelGroupHandle channelGroup,
                                             const char *property,
                                             DDCDataType dataType,
                                             va_list args);

int CVIFUNC DDC_ChannelGroupPropertyExists (DDCChannelGroupHandle channelGroup,
                                            const char *property,
                                            int *exists);

int CVIFUNC DDC_GetNumChannelGroupProperties (DDCChannelGroupHandle channelGroup, 
                                              unsigned int *numProperties);

int CVIFUNC DDC_GetChannelGroupPropertyNames (DDCChannelGroupHandle channelGroup, 
                                              char** propertyNames, 
                                              size_t numPropertyNames);

int CVIFUNC DDC_GetChannelGroupPropertyType (DDCChannelGroupHandle channelGroup, 
                                             const char *property, 
                                             DDCDataType *dataType);

//*****************************************************************************
/// <- Channel Group
//*****************************************************************************

//*****************************************************************************
/// -> Channel
//*****************************************************************************
int CVIFUNC_C DDC_SetChannelProperty (DDCChannelHandle channel,
                                      const char *property,
                                      ...);

int CVIFUNC DDC_SetChannelPropertyV (DDCChannelHandle channel,
                                     const char *property,
                                     va_list args);

int CVIFUNC DDC_GetChannelProperty (DDCChannelHandle channel,
                                    const char *property,
                                    void *value,
                                    size_t valueSizeInBytes);

int CVIFUNC DDC_GetChannelStringPropertyLength (DDCChannelHandle channel,
                                                const char *property,
                                                unsigned int *length);

int CVIFUNC_C DDC_CreateChannelProperty (DDCChannelHandle channel,
                                         const char *property,
                                         DDCDataType dataType,
                                         ...);

int CVIFUNC DDC_CreateChannelPropertyV (DDCChannelHandle channel,
                                        const char *property,
                                        DDCDataType dataType,
                                        va_list args);

int CVIFUNC DDC_ChannelPropertyExists (DDCChannelHandle channel,
                                       const char *property,
                                       int *exists);

int CVIFUNC DDC_GetNumChannelProperties (DDCChannelHandle channel, 
                                         unsigned int *numProperties);

int CVIFUNC DDC_GetChannelPropertyNames (DDCChannelHandle channel, 
                                         char** propertyNames, 
                                         size_t numPropertyNames);

int CVIFUNC DDC_GetChannelPropertyType (DDCChannelHandle channel, 
                                        const char *property, 
                                        DDCDataType *dataType);

//*****************************************************************************
/// <- Channel
//*****************************************************************************

//*****************************************************************************
/// <- Properties
//*****************************************************************************

//*****************************************************************************
/// -> Miscellaneous
//*****************************************************************************
const char * CVIFUNC DDC_GetLibraryErrorDescription (int errorCode);

void CVIFUNC DDC_FreeMemory (void *memoryPointer);

//*****************************************************************************
/// <- Miscellaneous
//*****************************************************************************

//*****************************************************************************
/// -> Separate timestamp functions for non-C users
//*****************************************************************************
int CVIFUNC DDC_SetDataValuesTimestampComponents (DDCChannelHandle channel,
                                                  unsigned int year[], 
                                                  unsigned int month[], 
                                                  unsigned int day[],
                                                  unsigned int hour[], 
                                                  unsigned int minute[], 
                                                  unsigned int second[],
                                                  double milliSecond[],
                                                  size_t numValues);

int CVIFUNC DDC_AppendDataValuesTimestampComponents (DDCChannelHandle channel,
                                                     unsigned int year[], 
                                                     unsigned int month[], 
                                                     unsigned int day[],
                                                     unsigned int hour[], 
                                                     unsigned int minute[], 
                                                     unsigned int second[],
                                                     double milliSecond[],
                                                     size_t numValues);

int CVIFUNC DDC_ReplaceDataValuesTimestampComponents (DDCChannelHandle channel,
                                                      size_t indexOfFirstValueToReplace,
                                                      unsigned int year[], 
                                                      unsigned int month[], 
                                                      unsigned int day[],
                                                      unsigned int hour[], 
                                                      unsigned int minute[], 
                                                      unsigned int second[],
                                                      double milliSecond[],
                                                      size_t numValues);

int CVIFUNC DDC_GetDataValuesTimestampComponents (DDCChannelHandle channel,
                                                  size_t indexOfFirstValueToGet,
                                                  size_t numValuesToGet,
                                                  unsigned int year[], 
                                                  unsigned int month[], 
                                                  unsigned int day[],
                                                  unsigned int hour[], 
                                                  unsigned int minute[], 
                                                  unsigned int second[],
                                                  double milliSecond[],
                                                  unsigned int weekDay[]);

int CVIFUNC DDC_CreateFilePropertyTimestampComponents (DDCFileHandle file,
                                                       const char *property,
                                                       unsigned int year, 
                                                       unsigned int month, 
                                                       unsigned int day,
                                                       unsigned int hour, 
                                                       unsigned int minute, 
                                                       unsigned int second, 
                                                       double milliSecond);

int CVIFUNC DDC_SetFilePropertyTimestampComponents (DDCFileHandle file,
                                                    const char *property,
                                                    unsigned int year, 
                                                    unsigned int month, 
                                                    unsigned int day,
                                                    unsigned int hour, 
                                                    unsigned int minute, 
                                                    unsigned int second, 
                                                    double milliSecond);

int CVIFUNC DDC_GetFilePropertyTimestampComponents (DDCFileHandle file,
                                                    const char *property,
                                                    unsigned int *year, 
                                                    unsigned int *month, 
                                                    unsigned int *day,
                                                    unsigned int *hour, 
                                                    unsigned int *minute, 
                                                    unsigned int *second, 
                                                    double *milliSecond,
                                                    unsigned int *weekDay);

int CVIFUNC DDC_CreateChannelGroupPropertyTimestampComponents (DDCChannelGroupHandle channelGroup,
                                                               const char *property,
                                                               unsigned int year, 
                                                               unsigned int month, 
                                                               unsigned int day,
                                                               unsigned int hour, 
                                                               unsigned int minute, 
                                                               unsigned int second, 
                                                               double milliSecond);

int CVIFUNC DDC_SetChannelGroupPropertyTimestampComponents (DDCChannelGroupHandle channelGroup,
                                                            const char *property,
                                                            unsigned int year, 
                                                            unsigned int month, 
                                                            unsigned int day,
                                                            unsigned int hour, 
                                                            unsigned int minute, 
                                                            unsigned int second, 
                                                            double milliSecond);

int CVIFUNC DDC_GetChannelGroupPropertyTimestampComponents (DDCChannelGroupHandle channelGroup,
                                                            const char *property,
                                                            unsigned int *year, 
                                                            unsigned int *month, 
                                                            unsigned int *day,
                                                            unsigned int *hour, 
                                                            unsigned int *minute, 
                                                            unsigned int *second, 
                                                            double *milliSecond,
                                                            unsigned int *weekDay);

int CVIFUNC DDC_CreateChannelPropertyTimestampComponents (DDCChannelHandle channel,
                                                          const char *property,
                                                          unsigned int year, 
                                                          unsigned int month, 
                                                          unsigned int day,
                                                          unsigned int hour, 
                                                          unsigned int minute, 
                                                          unsigned int second, 
                                                          double milliSecond);

int CVIFUNC DDC_SetChannelPropertyTimestampComponents (DDCChannelHandle channel,
                                                       const char *property,
                                                       unsigned int year, 
                                                       unsigned int month, 
                                                       unsigned int day,
                                                       unsigned int hour, 
                                                       unsigned int minute, 
                                                       unsigned int second, 
                                                       double milliSecond);

int CVIFUNC DDC_GetChannelPropertyTimestampComponents (DDCChannelHandle channel,
                                                       const char *property,
                                                       unsigned int *year, 
                                                       unsigned int *month, 
                                                       unsigned int *day,
                                                       unsigned int *hour, 
                                                       unsigned int *minute, 
                                                       unsigned int *second, 
                                                       double *milliSecond,
                                                       unsigned int *weekDay);

//*****************************************************************************
/// <- Separate timestamp functions for non-C users
//*****************************************************************************

#ifdef __cplusplus
    }
#endif

#endif //!defined(_CVIDDC_H)
