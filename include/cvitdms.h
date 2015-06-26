/*============================================================================*/
/*                           TDM Streaming Library                            */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 2006-2009.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       cvitdms.h                                                     */
/* Purpose:     Include file for TDM Streaming Library                        */
/*                                                                            */
/*============================================================================*/

#ifndef _CVITDMS_H
#define _CVITDMS_H

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

typedef struct _TDMSFile                TDMSFile;
typedef struct _TDMSChannelGroup        TDMSChannelGroup;
typedef struct _TDMSChannel             TDMSChannel;

typedef TDMSFile*                       TDMSFileHandle;
typedef TDMSChannelGroup*               TDMSChannelGroupHandle;
typedef TDMSChannel*                    TDMSChannelHandle;

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
    TDMS_Int8       = 1,    // char
    TDMS_UInt8      = 5,    // unsigned char
    TDMS_Int16      = 2,    // short
    TDMS_UInt16     = 6,    // unsigned short
    TDMS_Int32      = 3,    // int
    TDMS_UInt32     = 7,    // unsigned int
    TDMS_Int64      = 4,    // __int64
    TDMS_UInt64     = 8,    // unsigned __int64
    TDMS_Float      = 9,    // float
    TDMS_Double     = 10,   // double
    TDMS_String     = 32,   // string (char *)
    TDMS_Boolean    = 33,   // boolean (unsigned char)
    TDMS_Timestamp  = 68,   // timestamp (CVIAbsoluteTime or Year/Month/Day/Hour/Minute/Second/Millisecond components)
} TDMSDataType;

typedef enum {
    TDMS_Streaming2_0               = 2,            // TDM Streaming format (.tdms), version 2.0
    TDMS_Streaming1_0               = 1,            // TDM Streaming format (.tdms), version 1.0
    TDMS_Streaming                  = 0,            // Legacy constant, same as TDMS_Streaming1_0
} TDMSFileFormat;

typedef enum {
    TDMS_ByteOrderBigEndian     = 0,    // Big-endian - also called network order
    TDMS_ByteOrderNative        = 1,    // Native - the endian format of the host computer
    TDMS_ByteOrderLittleEndian  = 2,    // Little-endian
} TDMSByteOrder;

typedef enum {
    TDMS_CreateFileDisableBuffering     = 0x00000001,   // Disable system file buffering- Windows only.
} TDMSCreateFileOptions;

typedef enum {
    TDMS_OpenFileDisableBuffering       = 0x00000001,   // Disable system file buffering- Windows only.
} TDMSOpenFileOptions;

typedef enum {
    TDMS_DataLayoutNonInterleaved   = 0,    // Values for a single channel are not interleaved (values are continguous)
    TDMS_DataLayoutInterleaved      = 1,    // Values for a single channel are interleaved with values for other channels
} TDMSDataLayout;

// File property constants
#define TDMS_FILE_NAME                  "name"              // Name
#define TDMS_FILE_DESCRIPTION           "description"       // Description
#define TDMS_FILE_TITLE                 "title"             // Title
#define TDMS_FILE_AUTHOR                "author"            // Author

// ChannelGroup property constants
#define TDMS_CHANNELGROUP_NAME          "name"              // Name
#define TDMS_CHANNELGROUP_DESCRIPTION   "description"       // Description

// Channel property constants
#define TDMS_CHANNEL_NAME               "name"              // Name
#define TDMS_CHANNEL_DESCRIPTION        "description"       // Description
#define TDMS_CHANNEL_UNIT_STRING        "unit_string"       // Unit String

// Error codes
typedef enum {
    
    TDMS_NoError                                            = 0,        // No error
    TDMS_ErrorBegin                                         = -6601,    //
    
    TDMS_InvalidArgument                                    = -6601,    // Invalid argument.
    TDMS_OutOfMemory                                        = -6602,    // Out of memory.
    TDMS_FileAlreadyOpen                                    = -6603,    // The file is already open.
    TDMS_FileCouldNotBeOpened                               = -6604,    // The file could not be opened.
    TDMS_FileNotFound                                       = -6605,    // The file could not be found.
    TDMS_FileAccessDenied                                   = -6606,    // File access denied.
    TDMS_DriveIsFull                                        = -6607,    // The drive is full.
    TDMS_TooManyOpenFiles                                   = -6608,    // The maximum number of open files has been reached. Close one or more files and try again.
    TDMS_PathNotFound                                       = -6609,    // The path could not be found.
    TDMS_NotAValidTDMSFile                                  = -6610,    // The file is not a valid TDMS file.
    TDMS_FileCouldNotBeClosed                               = -6611,    // The file could not be closed.
    TDMS_WriteToFileFailed                                  = -6612,    // Write to file failed.
    TDMS_ReadFromFileFailed                                 = -6613,    // Read from file failed.
    TDMS_FailedToLoadLibrary                                = -6614,    // The library failed to load.
    TDMS_TDMFilesAreNotSupported                            = -6615,    // TDM files are not supported. Only TDMS files are supported.
    TDMS_PropertyIsReadOnly                                 = -6616,    // The specified property is read only.
    TDMS_DuplicateName                                      = -6617,    // The file already contains an object with that name.
    TDMS_RequestCannotBeCompletedWithUnsavedData            = -6618,    // The request cannot be completed with unsaved data. Save the file and try again.
    TDMS_UnexpectedError                                    = -6619,    // An unexpected error occurred.
    TDMS_NullPointerPassed                                  = -6620,    // A null pointer was passed where a non-null pointer was expected.
    TDMS_InvalidFileHandle                                  = -6621,    // Invalid file handle.
    TDMS_InvalidChannelGroupHandle                          = -6622,    // Invalid channel group handle.
    TDMS_InvalidChannelHandle                               = -6623,    // Invalid channel handle.
    TDMS_InvalidFilePath                                    = -6624,    // Invalid file path.
    TDMS_InvalidDataType                                    = -6625,    // Invalid data type.
    TDMS_InvalidFileFormatValue                             = -6626,    // Invalid value for file format.
    TDMS_InvalidName                                        = -6627,    // Invalid name.
    TDMS_InvalidPropertyName                                = -6628,    // Invalid property name.
    TDMS_PropertyDoesNotExist                               = -6629,    // The property does not exist.
    TDMS_PropertyAlreadyExists                              = -6630,    // The property already exists.
    TDMS_PropertyTypeMismatch                               = -6631,    // The data type of the property does not match the expected data type.
    TDMS_RequestExceedsActualNumberOfValues                 = -6632,    // The request exceeds the actual number of available values.
    TDMS_BufferIsTooSmall                                   = -6633,    // The buffer is too small to hold all values.
    TDMS_StringContainsInvalidCharacters                    = -6634,    // String contains invalid characters.
    TDMS_CannotModifyFileOpenedForReadOnlyAccess            = -6635,    // A file opened for read-only access cannot be modified.
    TDMS_FileMustHaveTDMSExtension                          = -6636,    // The file must have a .tdms extension.
    TDMS_InvalidTimeValue                                   = -6637,    // The specified time value is invalid.
    TDMS_InvalidByteOrderValue                              = -6638,    // Invalid value for byte order.
    TDMS_InvalidOptionsValue                                = -6639,    // Invalid value for options.
    TDMS_ChannelGroupNotFound                               = -6640,    // The channel group could not be found.
    TDMS_ChannelNotFound                                    = -6641,    // The channel could not be found.
    TDMS_FeatureNotSupportedWithThisFileVersion             = -6642,    // A feature you have requested is not supported for this version of the TDMS file format.
    TDMS_HandleInvalidDueToNamePropertyChange               = -6643,    // The handle is invalid because the channel group or channel it referred to was renamed.
    TDMS_FileFormatNewerThanSupported                       = -6644,    // The file format is too new to be supported by this version of the library.
    TDMS_InvalidDataLayout                                  = -6645,    // Invalid value for data layout.
    TDMS_AllChannelsMustHaveSameDatatype                    = -6646,    // All channels passed to this function must have the same data type.
    TDMS_InterleavedDataLayoutNotSupportedForStringDataType = -6647,    // Interleaved data layout not supported for channels of string data type.
    TDMS_InterleavedDataLayoutRequiresMultipleChannels      = -6648,    // Interleaved data layout requires multiple channels.
    TDMS_NumValuesMustBeMultipleOfNumChannels               = -6649,    // The number of values must be an even multiple of the number of channels.

    TDMS_ErrorEnd                                           = -6649,        //
    TDMS_ErrorForceSizeTo32Bits                             = 0xffffffff    //

} TDMSError;

//*****************************************************************************
/// -> Object Management
//*****************************************************************************
int CVIFUNC TDMS_CreateFileEx (const char *filePath,
                               TDMSFileFormat fileFormat,
                               TDMSByteOrder byteOrder,
                               unsigned int options,
                               const char *name,
                               const char *description,
                               const char *title,
                               const char *author,
                               TDMSFileHandle *file);
                               
int CVIFUNC TDMS_AddChannelGroup (TDMSFileHandle file,
                                  const char *name,
                                  const char *description,
                                  TDMSChannelGroupHandle *channelGroup);

int CVIFUNC TDMS_AddChannel (TDMSChannelGroupHandle channelGroup,
                             TDMSDataType dataType,
                             const char *name,
                             const char *description,
                             const char *unitString,
                             TDMSChannelHandle *channel);

int CVIFUNC TDMS_SaveFile (TDMSFileHandle file);

int CVIFUNC TDMS_CloseFile (TDMSFileHandle file);

int CVIFUNC TDMS_OpenFileEx (const char *filePath,
                             int readOnly,
                             unsigned int options,
                             TDMSFileHandle *file);

int CVIFUNC TDMS_DefragmentFile (const char *filePath);

//*****************************************************************************
/// -> Advanced
//*****************************************************************************
int CVIFUNC TDMS_CloseChannelGroup (TDMSChannelGroupHandle channelGroup);

int CVIFUNC TDMS_CloseChannel (TDMSChannelHandle channel);

//*****************************************************************************
/// <- Advanced
//*****************************************************************************

//*****************************************************************************
/// -> Obsolete
//*****************************************************************************
int CVIFUNC TDMS_CreateFile (const char *filePath,
                             TDMSFileFormat fileFormat,
                             const char *name,
                             const char *description,
                             const char *title,
                             const char *author,
                             TDMSFileHandle *file);

int CVIFUNC TDMS_OpenFile (const char *filePath,
                           int readOnly,
                           TDMSFileHandle *file);

//*****************************************************************************
/// <- Obsolete
//*****************************************************************************

//*****************************************************************************
/// <- Object Management
//*****************************************************************************

//*****************************************************************************
/// -> Data Storage
//*****************************************************************************
int CVIFUNC TDMS_AppendDataValues (TDMSChannelHandle channel,
                                   void *values,
                                   size_t numValues,
                                   int saveFile);

int CVIFUNC TDMS_AppendDataValuesMultiChannel (TDMSChannelHandle channels[],
                                               size_t numChannels,
                                               void *values,
                                               size_t numValues,
                                               TDMSDataLayout dataLayout,
                                               int saveFile);

//*****************************************************************************
/// <- Data Storage
//*****************************************************************************

//*****************************************************************************
/// -> Data Retrieval
//*****************************************************************************

//*****************************************************************************
/// -> Enumeration
//*****************************************************************************
int CVIFUNC TDMS_GetChannelGroupByName (TDMSFileHandle file,
                                        const char *name,
                                        TDMSChannelGroupHandle *channelGroup);

int CVIFUNC TDMS_GetChannelByName (TDMSChannelGroupHandle channelGroup,
                                   const char *name,
                                   TDMSChannelHandle *channel);

int CVIFUNC TDMS_GetChannelGroupAndChannelByName (TDMSFileHandle file,
                                                  const char *channelGroupName,
                                                  const char *channelName,
                                                  TDMSChannelGroupHandle *channelGroup,
                                                  TDMSChannelHandle *channel);

int CVIFUNC TDMS_GetNumChannelGroups (TDMSFileHandle file,
                                      unsigned int *numChannelGroups);

int CVIFUNC TDMS_GetChannelGroups (TDMSFileHandle file,
                                   TDMSChannelGroupHandle channelGroupsBuf[],
                                   size_t numChannelGroups);

int CVIFUNC TDMS_GetNumChannels (TDMSChannelGroupHandle channelGroup,
                                 unsigned int *numChannels);

int CVIFUNC TDMS_GetChannels (TDMSChannelGroupHandle channelGroup,
                              TDMSChannelHandle channelsBuf[],
                              size_t numChannels);

//*****************************************************************************
/// <- Enumeration
//*****************************************************************************

int CVIFUNC TDMS_GetNumDataValues (TDMSChannelHandle channel,
                                   unsigned __int64 *numValues);

int CVIFUNC TDMS_GetDataValuesEx (TDMSChannelHandle channel,
                                  unsigned __int64 indexOfFirstValueToGet,
                                size_t numValuesToGet,
                                void *values);

int CVIFUNC TDMS_GetDataType (TDMSChannelHandle channel,
                              TDMSDataType *dataType);

//*****************************************************************************
/// -> Obsolete
//*****************************************************************************
int CVIFUNC TDMS_GetDataValues (TDMSChannelHandle channel,
                                unsigned int indexOfFirstValueToGet,
                                unsigned int numValuesToGet,
                                void *values);

//*****************************************************************************
/// <- Obsolete
//*****************************************************************************

//*****************************************************************************
/// <- Data Retrieval
//*****************************************************************************

//*****************************************************************************
/// -> Properties
//*****************************************************************************

//*****************************************************************************
/// -> File
//*****************************************************************************
int CVIFUNC_C TDMS_SetFileProperty (TDMSFileHandle file,
                                    const char *property,
                                    TDMSDataType dataType,
                                    ...);

int CVIFUNC TDMS_SetFilePropertyV (TDMSFileHandle file,
                                   const char *property,
                                   TDMSDataType dataType,
                                   va_list args);

int CVIFUNC TDMS_GetFileProperty (TDMSFileHandle file,
                                  const char *property,
                                  void *value,
                                  size_t valueSizeInBytes);

int CVIFUNC TDMS_GetFileStringPropertyLength (TDMSFileHandle file,
                                              const char *property,
                                              unsigned int *length);

int CVIFUNC TDMS_FilePropertyExists (TDMSFileHandle file,
                                     const char *property,
                                     int *exists);

int CVIFUNC TDMS_GetNumFileProperties (TDMSFileHandle file,
                                       unsigned int *numProperties);

int CVIFUNC TDMS_GetFilePropertyNames (TDMSFileHandle file,
                                       char** propertyNames,
                                       size_t numPropertyNames);

int CVIFUNC TDMS_GetFilePropertyType (TDMSFileHandle file,
                                      const char *property,
                                      TDMSDataType *dataType);

//*****************************************************************************
/// <- File
//*****************************************************************************

//*****************************************************************************
/// -> Channel Group
//*****************************************************************************
int CVIFUNC_C TDMS_SetChannelGroupProperty (TDMSChannelGroupHandle channelGroup,
                                            const char *property,
                                            TDMSDataType dataType,
                                            ...);

int CVIFUNC TDMS_SetChannelGroupPropertyV (TDMSChannelGroupHandle channelGroup,
                                           const char *property,
                                           TDMSDataType dataType,
                                           va_list args);

int CVIFUNC TDMS_GetChannelGroupProperty (TDMSChannelGroupHandle channelGroup,
                                          const char *property,
                                          void *value,
                                          size_t valueSizeInBytes);

int CVIFUNC TDMS_GetChannelGroupStringPropertyLength (TDMSChannelGroupHandle channelGroup,
                                                      const char *property,
                                                      unsigned int *length);

int CVIFUNC TDMS_ChannelGroupPropertyExists (TDMSChannelGroupHandle channelGroup,
                                             const char *property,
                                             int *exists);

int CVIFUNC TDMS_GetNumChannelGroupProperties (TDMSChannelGroupHandle channelGroup,
                                               unsigned int *numProperties);

int CVIFUNC TDMS_GetChannelGroupPropertyNames (TDMSChannelGroupHandle channelGroup,
                                               char** propertyNames,
                                               size_t numPropertyNames);

int CVIFUNC TDMS_GetChannelGroupPropertyType (TDMSChannelGroupHandle channelGroup,
                                              const char *property,
                                              TDMSDataType *dataType);

//*****************************************************************************
/// <- Channel Group
//*****************************************************************************

//*****************************************************************************
/// -> Channel
//*****************************************************************************
int CVIFUNC_C TDMS_SetChannelProperty (TDMSChannelHandle channel,
                                       const char *property,
                                       TDMSDataType dataType,
                                       ...);

int CVIFUNC TDMS_SetChannelPropertyV (TDMSChannelHandle channel,
                                      const char *property,
                                      TDMSDataType dataType,
                                      va_list args);

int CVIFUNC TDMS_GetChannelProperty (TDMSChannelHandle channel,
                                     const char *property,
                                     void *value,
                                     size_t valueSizeInBytes);

int CVIFUNC TDMS_GetChannelStringPropertyLength (TDMSChannelHandle channel,
                                                 const char *property,
                                                 unsigned int *length);

int CVIFUNC TDMS_ChannelPropertyExists (TDMSChannelHandle channel,
                                        const char *property,
                                        int *exists);

int CVIFUNC TDMS_GetNumChannelProperties (TDMSChannelHandle channel,
                                          unsigned int *numProperties);

int CVIFUNC TDMS_GetChannelPropertyNames (TDMSChannelHandle channel,
                                          char** propertyNames,
                                          size_t numPropertyNames);

int CVIFUNC TDMS_GetChannelPropertyType (TDMSChannelHandle channel,
                                         const char *property,
                                         TDMSDataType *dataType);

//*****************************************************************************
/// <- Channel
//*****************************************************************************

//*****************************************************************************
/// <- Properties
//*****************************************************************************

//*****************************************************************************
/// -> Miscellaneous
//*****************************************************************************
const char * CVIFUNC TDMS_GetLibraryErrorDescription (int errorCode);

void CVIFUNC TDMS_FreeMemory (void *memoryPointer);

int CVIFUNC TDMS_ConvertFileFormat (const char *filePath, TDMSFileFormat newFileFormat);

int CVIFUNC TDMS_GetFileFormat (const char *filePath, TDMSFileFormat *fileFormat);

//*****************************************************************************
/// <- Miscellaneous
//*****************************************************************************

//*****************************************************************************
/// -> Separate timestamp functions for non-C users
//*****************************************************************************
int CVIFUNC TDMS_AppendDataValuesTimestampComponents (TDMSChannelHandle channel,
                                                      unsigned int year[], 
                                                      unsigned int month[], 
                                                      unsigned int day[],
                                                      unsigned int hour[], 
                                                      unsigned int minute[], 
                                                      unsigned int second[],
                                                      double milliSecond[],
                                                      size_t numValues,
                                                      int saveFile);

int CVIFUNC TDMS_AppendDataValuesMultiChannelTimestampComponents (TDMSChannelHandle channels[],
                                                                  size_t numChannels,
                                                                  unsigned int year[], 
                                                                  unsigned int month[], 
                                                                  unsigned int day[],
                                                                  unsigned int hour[], 
                                                                  unsigned int minute[], 
                                                                  unsigned int second[],
                                                                  double milliSecond[],
                                                                  size_t numValues,
                                                                  TDMSDataLayout dataLayout,
                                                                  int saveFile);

int CVIFUNC TDMS_GetDataValuesTimestampComponents (TDMSChannelHandle channel,
                                                   unsigned __int64 indexOfFirstValueToGet,
                                                   size_t numValuesToGet,
                                                   unsigned int year[], 
                                                   unsigned int month[], 
                                                   unsigned int day[],
                                                   unsigned int hour[], 
                                                   unsigned int minute[], 
                                                   unsigned int second[],
                                                   double milliSecond[],
                                                   unsigned int weekDay[]);

int CVIFUNC TDMS_SetFilePropertyTimestampComponents (TDMSFileHandle file,
                                                     const char *property,
                                                     unsigned int year, 
                                                     unsigned int month, 
                                                     unsigned int day,
                                                     unsigned int hour, 
                                                     unsigned int minute, 
                                                     unsigned int second, 
                                                     double milliSecond);

int CVIFUNC TDMS_GetFilePropertyTimestampComponents (TDMSFileHandle file,
                                                     const char *property,
                                                     unsigned int *year, 
                                                     unsigned int *month, 
                                                     unsigned int *day,
                                                     unsigned int *hour, 
                                                     unsigned int *minute, 
                                                     unsigned int *second, 
                                                     double *milliSecond,
                                                     unsigned int *weekDay);

int CVIFUNC TDMS_SetChannelGroupPropertyTimestampComponents (TDMSChannelGroupHandle channelGroup,
                                                             const char *property,
                                                             unsigned int year, 
                                                             unsigned int month, 
                                                             unsigned int day,
                                                             unsigned int hour, 
                                                             unsigned int minute, 
                                                             unsigned int second, 
                                                             double milliSecond);

int CVIFUNC TDMS_GetChannelGroupPropertyTimestampComponents (TDMSChannelGroupHandle channelGroup,
                                                             const char *property,
                                                             unsigned int *year, 
                                                             unsigned int *month, 
                                                             unsigned int *day,
                                                             unsigned int *hour, 
                                                             unsigned int *minute, 
                                                             unsigned int *second, 
                                                             double *milliSecond,
                                                             unsigned int *weekDay);

int CVIFUNC TDMS_SetChannelPropertyTimestampComponents (TDMSChannelHandle channel,
                                                        const char *property,
                                                        unsigned int year, 
                                                        unsigned int month, 
                                                        unsigned int day,
                                                        unsigned int hour, 
                                                        unsigned int minute, 
                                                        unsigned int second, 
                                                        double milliSecond);

int CVIFUNC TDMS_GetChannelPropertyTimestampComponents (TDMSChannelHandle channel,
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

#endif //!defined(_NILIBTDMS_H)
