/*
* Copyright (c) 2012 Gracenote.
*
* This software may not be used in any way or distributed without
* permission. All rights reserved.
*
* Some code herein may be covered by US and international patents.
*/

/*
* gcsl_error_codes.h - Package code definitions and string access.
*/

/*
 * Note: all values are expressed in hexadecimal form.
 */

#ifndef	_GCSL_ERROR_CODES_H_
#define _GCSL_ERROR_CODES_H_

/*
* Dependencies
*/


#ifdef __cplusplus
extern "C" {
#endif


/*
* Constants
*/

/* Package/library identifiers. */
#define GCSLERR_BASE_PKG_ID				(0x00)
#define GCSLERR_MAX_PKG_ID				(GCSLERR_BASE_PKG_ID+0x7D)

#define GNSDKERR_BASE_PKG_ID			(0x80)
#define GNSDKERR_RSV_PKG_IDS			(GNSDKERR_BASE_PKG_ID+0x3f)
#define GNSDKERR_APP_PKG_IDS			(GNSDKERR_BASE_PKG_ID+0x5f)
#define GNSDKERR_MAX_PKG_ID				(GNSDKERR_BASE_PKG_ID+0x7D)

#define GCSLPKG_Memory					(GCSLERR_BASE_PKG_ID+0x01)
#define GCSLPKG_Thread					(GCSLERR_BASE_PKG_ID+0x02)
#define GCSLPKG_FileSystem				(GCSLERR_BASE_PKG_ID+0x03)
#define GCSLPKG_Socket					(GCSLERR_BASE_PKG_ID+0x04)
#define GCSLPKG_String					(GCSLERR_BASE_PKG_ID+0x05)
#define GCSLPKG_MD5						(GCSLERR_BASE_PKG_ID+0x06)
#define GCSLPKG_Compression				(GCSLERR_BASE_PKG_ID+0x07)
#define GCSLPKG_Log						(GCSLERR_BASE_PKG_ID+0x08)
#define GCSLPKG_Paths					(GCSLERR_BASE_PKG_ID+0x09)
#define GCSLPKG_Random					(GCSLERR_BASE_PKG_ID+0x0A)
#define GCSLPKG_TextCorr				(GCSLERR_BASE_PKG_ID+0x0B)
#define GCSLPKG_XML						(GCSLERR_BASE_PKG_ID+0x0C)
#define GCSLPKG_DataTypes				(GCSLERR_BASE_PKG_ID+0x0D)
#define GCSLPKG_Crypto					(GCSLERR_BASE_PKG_ID+0x0E)
#define GCSLPKG_Utils					(GCSLERR_BASE_PKG_ID+0x0F)
#define GCSLPKG_DataEncode				(GCSLERR_BASE_PKG_ID+0x10)
#define GCSLPKG_HDO						(GCSLERR_BASE_PKG_ID+0x11)
#define GCSLPKG_FPX						(GCSLERR_BASE_PKG_ID+0x12)
#define GCSLPKG_HTTP					(GCSLERR_BASE_PKG_ID+0x14)
#define GCSLPKG_CDS						(GCSLERR_BASE_PKG_ID+0x15)
#define GCSLPKG_GCSP					(GCSLERR_BASE_PKG_ID+0x16)
#define GCSLPKG_Lists					(GCSLERR_BASE_PKG_ID+0x17)
#define GCSLPKG_Fingerprint				(GCSLERR_BASE_PKG_ID+0x18)
#define GCSLPKG_DSP						(GCSLERR_BASE_PKG_ID+0x19)	/* part of FPX */
#define GCSLPKG_Cantametrix				(GCSLERR_BASE_PKG_ID+0x1A)	/* part of FPX */
#define GCSLPKG_FAPI					(GCSLERR_BASE_PKG_ID+0x1B)	/* part of FPX */
#define GCSLPKG_Time					(GCSLERR_BASE_PKG_ID+0x1C)
#define GCSLPKG_License					(GCSLERR_BASE_PKG_ID+0x1D)
#define GCSLPKG_Process					(GCSLERR_BASE_PKG_ID+0x1E)
#define GCSLPKG_Atomic					(GCSLERR_BASE_PKG_ID+0x1F)
#define GCSLPKG_DBEngine				(GCSLERR_BASE_PKG_ID+0x20)
#define GCSLPKG_ProtoBuffers			(GCSLERR_BASE_PKG_ID+0x21)
#define GCSLPKG_IOStream				(GCSLERR_BASE_PKG_ID+0x22)
/* be sure to add new packages to gcsl_log's package description list. */
#define GCSLERR_RSV_PKG_IDS				(GCSLERR_BASE_PKG_ID+0x30)
/* purpose related packages (not module related) */
#define GCSLPKG_Validation				(GCSLERR_RSV_PKG_IDS+0x01) /* for GNSDK Validation Log */
#define GCSLPKG_SubmitTest				(GCSLERR_RSV_PKG_IDS+0x02) /* for GNSDK Submit Testing Log */
#define GCSLPKG_HTTPLogging				(GCSLERR_RSV_PKG_IDS+0x03) /* for GCSP XML logging */
#define GCSLPKG_GCSPLogging				(GCSLERR_RSV_PKG_IDS+0x04) /* for HTTP traffic logging */
#define GCSLPKG_Timings					(GCSLERR_RSV_PKG_IDS+0x05) /* for Timings output */
#define GCSLPKG_Metrics					(GCSLERR_RSV_PKG_IDS+0x06) /* for Metrics gathering */
/*** NB: ensure the GCSL packages don't collide with the GNSDK package IDs which
	start at GCSLERR_BASE_PKG_ID+0x80 ****/

/* Error Codes */
/*
 * Codes are grouped by the package that usually (if not exclusively)
 * returns the code.
 * Values for each group of error codes begin with a multiple of 0x40.
 * This allows for numbering consistency when defining new codes within
 * a group. Note that this scheme is motivated by aesthetic (not functional)
 * reasons; error code origination is determined by the package id field
 * of the error value, not by the value of the error code field.
 */

#define GCSLERR_BASE_CODE						(0x0)

/* General Errors */
#define GCSLERR_NoError							(GCSLERR_BASE_CODE)
#define GCSLERR_InvalidArg						(GCSLERR_BASE_CODE+0x0001)	/* Invalid argument */
#define GCSLERR_NoMemory						(GCSLERR_BASE_CODE+0x0002)	/* Memory allocation failure */
#define GCSLERR_NotFound						(GCSLERR_BASE_CODE+0x0003)	/* Item not found */
#define GCSLERR_IOError							(GCSLERR_BASE_CODE+0x0004)	/* Error reading or writing */
#define GCSLERR_ReadOnly						(GCSLERR_BASE_CODE+0x0005)	/* Error reading or writing */
#define GCSLERR_Busy							(GCSLERR_BASE_CODE+0x0006)	/* System is busy */
#define GCSLERR_NotInited						(GCSLERR_BASE_CODE+0x0007)	/* System not initialized */
#define GCSLERR_BufferTooSmall					(GCSLERR_BASE_CODE+0x0008)	/* Input buffer is too small for available data */
#define GCSLERR_InvalidFormat					(GCSLERR_BASE_CODE+0x0009)	/* Invalid format in file or data structure */
#define GCSLERR_InitFailed						(GCSLERR_BASE_CODE+0x000A)
#define GCSLERR_Unsupported						(GCSLERR_BASE_CODE+0x000B)
#define GCSLERR_InvalidData						(GCSLERR_BASE_CODE+0x000C)
#define GCSLERR_InvalidCall						(GCSLERR_BASE_CODE+0x000D)
#define GCSLERR_HashingError					(GCSLERR_BASE_CODE+0x000E)
#define GCSLERR_Unexpected						(GCSLERR_BASE_CODE+0x003C)
#define GCSLERR_IckyError						(GCSLERR_BASE_CODE+0x003D)	/* Really, really bad error which can't be fathomed */
#define GCSLERR_Unknown							(GCSLERR_BASE_CODE+0x003E)	/* Unknown error */
#define GCSLERR_LibraryNotLoaded				(GCSLERR_BASE_CODE+0x003F)

/* File System Subsystem */
#define GCSLERR_FileInvalidAccess				(GCSLERR_BASE_CODE+0x0040)
#define GCSLERR_FileNotFound					(GCSLERR_BASE_CODE+0x0041)
#define GCSLERR_FileExists						(GCSLERR_BASE_CODE+0x0042)
#define GCSLERR_FileNoSpace						(GCSLERR_BASE_CODE+0x0043)
#define GCSLERR_FileTooManyOpen					(GCSLERR_BASE_CODE+0x0044)
#define GCSLERR_FileInvalidHandle				(GCSLERR_BASE_CODE+0x0045)
#define GCSLERR_FileInvalidName					(GCSLERR_BASE_CODE+0x0046)
#define GCSLERR_FileInvalidFolder				(GCSLERR_BASE_CODE+0x0047)
#define GCSLERR_FileTooLarge					(GCSLERR_BASE_CODE+0x0048)
#define GCSLERR_EndOfFile						(GCSLERR_BASE_CODE+0x0049)
#define GCSLERR_DirNotEmpty						(GCSLERR_BASE_CODE+0x0050)
#define GCSLERR_FileInvalidOffset				(GCSLERR_BASE_CODE+0x0051)
#define GCSLERR_WriteOnly						(GCSLERR_BASE_CODE+0x0052)

/* Remote Communications Management */
#define GCSLERR_NoMoreConnections				(GCSLERR_BASE_CODE+0x0080)
#define GCSLERR_CommInvalidAddress				(GCSLERR_BASE_CODE+0x0081)
#define GCSLERR_CommInvalidHandle				(GCSLERR_BASE_CODE+0x0082)
#define GCSLERR_CommHostDown					(GCSLERR_BASE_CODE+0x0083)
#define GCSLERR_Timeout							(GCSLERR_BASE_CODE+0x0084)
#define GCSLERR_HTTPClientError					(GCSLERR_BASE_CODE+0x0085)
#define GCSLERR_HTTPServerError					(GCSLERR_BASE_CODE+0x0086)
#define GCSLERR_HTTPInvalidURL					(GCSLERR_BASE_CODE+0x0087)
#define GCSLERR_ConnectionRefused				(GCSLERR_BASE_CODE+0x0088)
#define GCSLERR_HTTPInvalidHeaderFormat			(GCSLERR_BASE_CODE+0x0089)
#define GCSLERR_HTTPMovedError					(GCSLERR_BASE_CODE+0x008A)
#define GCSLERR_Disconnected					(GCSLERR_BASE_CODE+0x008B)
#define GCSLERR_HTTPCancelled					(GCSLERR_BASE_CODE+0x008C)
#define GCSLERR_ConnectionReset					(GCSLERR_BASE_CODE+0x008D)
#define GCSLERR_CommNotAvailable 				(GCSLERR_BASE_CODE+0x008E)

/* Crytographic Subsystem */
#define GCSLERR_UnsupportedAlg					(GCSLERR_BASE_CODE+0x00C0)

#define GCSLERR_BadXMLFormat					(GCSLERR_BASE_CODE+0x00C1)
#define GCSLERR_UnknownVersion					(GCSLERR_BASE_CODE+0x00C2)
#define GCSLERR_DataError						(GCSLERR_BASE_CODE+0x00C3)
#define	GCSLERR_InvalidTOC						(GCSLERR_BASE_CODE+0x00C4)

/* Micro XML Package */
#define GCSLERR_SyntaxError						(GCSLERR_BASE_CODE+0x0120)
#define GCSLERR_IllegalCharacter				(GCSLERR_BASE_CODE+0x0121)
#define GCSLERR_UnexpectedEndOfInput			(GCSLERR_BASE_CODE+0x0122)
#define GCSLERR_NothingAtPath					(GCSLERR_BASE_CODE+0x0123)
#define GCSLERR_DisallowedStructure				(GCSLERR_BASE_CODE+0x0124)

/* Online Protocol */
#define GCSLERR_WrongServerPublicKey			(GCSLERR_BASE_CODE+0x0160)
#define GCSLERR_WrongClientPublicKey			(GCSLERR_BASE_CODE+0x0161)
#define GCSLERR_ServerError						(GCSLERR_BASE_CODE+0x0162)
#define GCSLERR_ServerEncryptionError			(GCSLERR_BASE_CODE+0x0163)
#define GCSLERR_MaxRedirects					(GCSLERR_BASE_CODE+0x0164)
#define GCSLERR_InvalidClientID					(GCSLERR_BASE_CODE+0x0165)
#define GCSLERR_InvalidUserID					(GCSLERR_BASE_CODE+0x0166)
#define GCSLERR_QuotaExceeded					(GCSLERR_BASE_CODE+0x0167)

#define GCSLERR_Aborted							(GCSLERR_BASE_CODE+0x01A0)
#define GCSLERR_NotReady						(GCSLERR_BASE_CODE+0x01A1)
#define GCSLERR_NothingToDo						(GCSLERR_BASE_CODE+0x01A2)
#define GCSLERR_InvalidInputObject				(GCSLERR_BASE_CODE+0x01A3)
#define GCSLERR_InsufficientInputData			(GCSLERR_BASE_CODE+0x01A4)

/* GCSP Transport */
#define GCSLERR_CorruptEncryptData				(GCSLERR_BASE_CODE+0x0200)
#define GCSLERR_CorruptCompressData				(GCSLERR_BASE_CODE+0x0201)
#define GCSLERR_CommandError					(GCSLERR_BASE_CODE+0x0202)
#define GCSLERR_ClientCompression				(GCSLERR_BASE_CODE+0x0203)
#define GCSLERR_ClientEncryption				(GCSLERR_BASE_CODE+0x0204)
#define GCSLERR_GEMPError						(GCSLERR_BASE_CODE+0x0205)

#define GCSLERR_UnknownResponseCode				(GCSLERR_BASE_CODE+0x0206)
#define GCSLERR_ClientError						(GCSLERR_BASE_CODE+0x0207)
#define GCSLERR_GeneralError					(GCSLERR_BASE_CODE+0x0208)
#define GCSLERR_IncorrectUsage					(GCSLERR_BASE_CODE+0x0209)

/* Compression */
#define GCSLERR_UnknownCompressionType			(GCSLERR_BASE_CODE+0x0240)

/* Thread */
#define GCSLERR_TooMany							(GCSLERR_BASE_CODE+0x0280)
#define GCSLERR_Deadlock						(GCSLERR_BASE_CODE+0x0281)
#define GCSLERR_NoResources						(GCSLERR_BASE_CODE+0x0282)
#define GCSLERR_Interrupted						(GCSLERR_BASE_CODE+0x0283)
#define GCSLERR_PermissionError					(GCSLERR_BASE_CODE+0x0284)
#define GCSLERR_ThreadTerminated				(GCSLERR_BASE_CODE+0x0285)

/* Lists */
#define GCSLERR_ListInvalidFile					(GCSLERR_BASE_CODE+0x02D0)
#define GCSLERR_ListUnavailable					(GCSLERR_BASE_CODE+0x02D1)
#define GCSLERR_ListInvalidLevel				(GCSLERR_BASE_CODE+0x02D2)
#define GCSLERR_LocaleNotSet					(GCSLERR_BASE_CODE+0x02D3)
#define GCSLERR_ListUpdateNeeded				(GCSLERR_BASE_CODE+0x02D4)

/* Handle Errors */
#define GCSLERR_HandleObjectInvalid				(GCSLERR_BASE_CODE+0x0320)	/* handle reference invalid */
#define GCSLERR_HandleObjectWrongType			(GCSLERR_BASE_CODE+0x0321)	/* handle passed to incorrect API for object */
#define GCSLERR_HandleObjectMismatch			(GCSLERR_BASE_CODE+0x0322)	/* handle can't perform operation with parameter */

/* Submit Errors */
#define GCSLERR_MissingField					(GCSLERR_BASE_CODE+0x0340)
#define GCSLERR_InvalidContents					(GCSLERR_BASE_CODE+0x0341)
#define GCSLERR_NotEditable						(GCSLERR_BASE_CODE+0x0342)

/* DataType Errors */
#define GCSLERR_DataCorruption					(GCSLERR_BASE_CODE+0x0360)
#define GCSLERR_IndexOutOfRange					(GCSLERR_BASE_CODE+0x0361)
#define GCSLERR_WrongValueType					(GCSLERR_BASE_CODE+0x0362)
#define GCSLERR_BadKeyValue						(GCSLERR_BASE_CODE+0x0363)
#define GCSLERR_LateDataUpdate					(GCSLERR_BASE_CODE+0x0364)
#define GCSLERR_DoDefaultProcessing				(GCSLERR_BASE_CODE+0x0365)
#define GCSLERR_InvalidPath						(GCSLERR_BASE_CODE+0x0366)
#define GCSLERR_SetsIncompatible				(GCSLERR_BASE_CODE+0x0367)
#define GCSLERR_DuplicateValue					(GCSLERR_BASE_CODE+0x0368)

/* String Errors */
#define GCSLERR_InvalidUTF8						(GCSLERR_BASE_CODE+0x03A0)
#define GCSLERR_InvalidUCS2						(GCSLERR_BASE_CODE+0x03A1)

/* General low level subsystem errors */
#define GCSLERR_CommunicationsError				(GCSLERR_BASE_CODE+0x0400)
#define GCSLERR_QueryError						(GCSLERR_BASE_CODE+0x0401)
#define GCSLERR_CDSError						(GCSLERR_BASE_CODE+0x0402)
#define GCSLERR_DataEncodeError					(GCSLERR_BASE_CODE+0x0403)
#define GCSLERR_CompressionError				(GCSLERR_BASE_CODE+0x0404)
#define GCSLERR_EncryptionError					(GCSLERR_BASE_CODE+0x0405)

/* Crypto errors */
#define GCSLERR_InvalidKey						(GCSLERR_BASE_CODE+0x0410)
#define GCSLERR_InvalidSignature				(GCSLERR_BASE_CODE+0x0411)

/* License Errors */
#define GCSLERR_LicenseInvalid					(GCSLERR_BASE_CODE+0x0420)
#define GCSLERR_LicenseDisallowed				(GCSLERR_BASE_CODE+0x0421)
#define GCSLERR_LicenseExpired					(GCSLERR_BASE_CODE+0x0422)
#define GCSLERR_LicenseTrialExpired				(GCSLERR_BASE_CODE+0x0423)

/* Fingerprint Errors */
#define GCSLERR_TemporalDiscontinuity			(GCSLERR_BASE_CODE+0x0440)
#define GCSLERR_SilentAudio						(GCSLERR_BASE_CODE+0x0441)

/* Local Storage Errors */
#define GCSLERR_InvalidSchema					(GCSLERR_BASE_CODE+0x0500)
#define GCSLERR_SchemaMismatch					(GCSLERR_BASE_CODE+0x0501)
#define GCSLERR_EndOfRecords					(GCSLERR_BASE_CODE+0x0502)
#define GCSLERR_DuplicateRecord					(GCSLERR_BASE_CODE+0x0503)
#define GCSLERR_InvalidRecord					(GCSLERR_BASE_CODE+0x0504)
#define GCSLERR_InvalidStorage					(GCSLERR_BASE_CODE+0x0505)
#define GCSLERR_InvalidIterator					(GCSLERR_BASE_CODE+0x0506)

/* GNServer errors - these may not exist in any SDKs but they are used in the JNIs */
#define GCSLERR_Ambiguous						(GCSLERR_BASE_CODE+0x0510)

/* DB errors */
#define GCSLERR_NestedCall						(GCSLERR_BASE_CODE+0x0521)
/*#define	GCSLSERR_PermissionError			(GCSLERR_BASE_CODE+0x0522)*/
#define GCSLERR_ReadErr							(GCSLERR_BASE_CODE+0x0523)
#define GCSLERR_WriteErr						(GCSLERR_BASE_CODE+0x0524)
/*#define	GCSLERR_UnknownVersion				(GCSLERR_BASE_CODE+0x0525)*/
#define GCSLERR_InvalidFile						(GCSLERR_BASE_CODE+0x0526)
#define GCSLERR_AlreadyAdded					(GCSLERR_BASE_CODE+0x0527)
#define GCSLERR_InvalidBlock					(GCSLERR_BASE_CODE+0x0528)
/*#define	GCSLERR_Aborted						(GCSLERR_BASE_CODE+0x0529)*/
#define GCSLERR_NoSpace							(GCSLERR_BASE_CODE+0x052A)
#define	GCSLERR_BadIndex						(GCSLERR_BASE_CODE+0x052B)
#define GCSLERR_BadFreeList						(GCSLERR_BASE_CODE+0x052C)
#define	GCSLERR_BadRecord						(GCSLERR_BASE_CODE+0x052D)
/*#define	GCSLERR_BadBlock					(GCSLERR_BASE_CODE+0x052E)*/
#define	GCSLERR_IndexPastEOF					(GCSLERR_BASE_CODE+0x052F)
#define	GCSLERR_RecordPastEOF					(GCSLERR_BASE_CODE+0x0530)
#define	GCSLERR_IndexInFreeList					(GCSLERR_BASE_CODE+0x0531)
#define	GCSLERR_RecordInFreeList				(GCSLERR_BASE_CODE+0x0532)
#define	GCSLERR_BlockInFreeList					(GCSLERR_BASE_CODE+0x0533)
#define GCSLERR_IncompatibleDBs					(GCSLERR_BASE_CODE+0x0534)
#define GCSLERR_KeyNotRead						(GCSLERR_BASE_CODE+0x0535)
#define GCSLERR_InvalidByteOrder				(GCSLERR_BASE_CODE+0x0536)
/*#define GCSLERR_UnknownFSError				(GCSLERR_BASE_CODE+0x0537)*/
#define GCSLERR_BadHeader						(GCSLERR_BASE_CODE+0x0539)
/*#define	GCSLERR_CriticalSection				(GCSLERR_BASE_CODE+0x053A)*/
#define	GCSLERR_ThreadError						(GCSLERR_BASE_CODE+0x053B)
#define	GCSLERR_ReadLocked						(GCSLERR_BASE_CODE+0x053C)
#define	GCSLERR_WriteLocked						(GCSLERR_BASE_CODE+0x053D)
#define	GCSLERR_CorruptDB						(GCSLERR_BASE_CODE+0x053F)

/* Protocol Buffers */
#define	GCSLERR_DataTooShort					(GCSLERR_BASE_CODE+0x0580)
#define	GCSLERR_InvalidWireType					(GCSLERR_BASE_CODE+0x0581)
#define	GCSLERR_ParsingError					(GCSLERR_BASE_CODE+0x0582)
#define	GCSLERR_UnterminatedVarInt				(GCSLERR_BASE_CODE+0x0583)

/* Playlist Errors */
#define GCSLERR_SeedRequired					(GCSLERR_BASE_CODE+0x0600)
#define GCSLERR_StatementError					(GCSLERR_BASE_CODE+0x0601)

/* Local Lookup Errors */
#define GCSLERR_LocalDatabaseNotFound			(GCSLERR_BASE_CODE+0x0700)

/* ACR errors */
#define GCSLERR_MissingListingData				(GCSLERR_BASE_CODE+0x0720)

/* FP Local errors */
#define GCSLERR_InvalidDate						(GCSLERR_BASE_CODE+0x0740)

#define GCSLERR_MAX_ERROR_CODE					(GCSLERR_BASE_CODE+0x0750)	/* make sure you up this when codes are extended */

/* Make sure gnsdk_error_codes.h and gcsl_error_codes.h define the same codes with the same hex values */

/***************/
/* ERROR VALUES*/
/***************/

/* Atomic errors */
#define ATOMICERR_NoError						GCSLERR_NoError
#define ATOMICERR_InvalidArg					GCSLERR_MAKE_ERROR(GCSLPKG_Atomic, GCSLERR_InvalidArg)
#define ATOMICERR_Unexpected					GCSLERR_MAKE_ERROR(GCSLPKG_Atomic, GCSLERR_Unexpected)

/* Log errors */
#define LOGERR_NoError							GCSLERR_NoError
#define LOGERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_Log, GCSLERR_NoMemory)
#define LOGERR_IOError							GCSLERR_MAKE_ERROR(GCSLPKG_Log, GCSLERR_IOError)
#define LOGERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Log, GCSLERR_InvalidArg)
#define LOGERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Log, GCSLERR_NotInited)
#define LOGERR_HandleObjectWrongType			GCSLERR_MAKE_ERROR(GCSLPKG_Log, GCSLERR_HandleObjectWrongType)

/* Errors returned from the memory management subsystem */
#define MEMERR_NoError							GCSLERR_NoError
#define MEMERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_Memory, GCSLERR_NoMemory)
#define MEMERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Memory, GCSLERR_InvalidArg)
#define MEMERR_InvalidCall						GCSLERR_MAKE_ERROR(GCSLPKG_Memory, GCSLERR_InvalidCall)
#define MEMERR_InvalidFormat					GCSLERR_MAKE_ERROR(GCSLPKG_Memory, GCSLERR_InvalidFormat)

/* Errors returned from the file subsystem */
#define FSERR_NoError							GCSLERR_NoError
#define FSERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_NoMemory)
#define FSERR_InvalidAccess						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileInvalidAccess)
#define FSERR_SharingError						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_Busy)
#define FSERR_DirNotEmpty						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_DirNotEmpty)
#define FSWARN_DirNotEmpty						GCSLERR_MAKE_WARNING(GCSLPKG_FileSystem, GCSLERR_DirNotEmpty)
#define FSERR_NotFound 							GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileNotFound)
#define FSWARN_FileExists						GCSLERR_MAKE_WARNING(GCSLPKG_FileSystem, GCSLERR_FileExists)
#define FSERR_FileExists						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileExists)
#define FSERR_NoSpace							GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileNoSpace)
#define FSERR_TooManyOpen						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileTooManyOpen)
#define FSERR_InvalidHandle						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileInvalidHandle)
#define FSERR_InvalidFilename					GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileInvalidName)
#define FSERR_FileTooLarge						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileTooLarge)
#define FSERR_NotInited							GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_NotInited)
#define FSERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_InvalidArg)
#define FSERR_EndOfFile							GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_EndOfFile)
#define FSWARN_EndOfStream						GCSLERR_MAKE_WARNING(GCSLPKG_FileSystem, GCSLERR_EndOfFile)
#define FSERR_Unknown							GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_Unknown)
#define FSERR_Unsupported						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_Unsupported)
#define FSERR_InvalidOffset						GCSLERR_MAKE_ERROR(GCSLPKG_FileSystem, GCSLERR_FileInvalidOffset)

/* Errors returned from DataTypes subsystem */
#define DATATYPEERR_NoError						GCSLERR_NoError
#define DATATYPEERR_NoMemory					GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_NoMemory)
#define DATATYPEERR_InvalidArg					GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_InvalidArg)
#define DATATYPEERR_NotInited					GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_NotInited)
#define DATATYPEERR_NotFound					GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_NotFound)
#define DATATYPEWARN_NotFound					GCSLERR_MAKE_WARNING(GCSLPKG_DataTypes, GCSLERR_NotFound)
#define DATATYPEERR_HandleObjectInvalid			GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_HandleObjectInvalid)
#define DATATYPEERR_HandleObjectWrongType		GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_HandleObjectWrongType)
#define DATATYPEERR_HandleObjectMismatch		GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_HandleObjectMismatch)
#define DATATYPEERR_SetsIncompatible			GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_SetsIncompatible)
#define DATATYPEERR_DataCorruption				GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_DataCorruption)
#define DATATYPEERR_Unsupported					GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_Unsupported)
#define DATATYPEERR_IndexOutOfRange				GCSLERR_MAKE_WARNING(GCSLPKG_DataTypes, GCSLERR_IndexOutOfRange)
#define DATATYPEERR_BadKeyValue					GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_BadKeyValue)
#define DATATYPEERR_BufferTooSmall				GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_BufferTooSmall)
#define DATATYPEERR_InvalidCall					GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_InvalidCall)
#define DATATYPEERR_IncorrectUsage				GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_IncorrectUsage)
#define DATATYPEERR_DuplicateValue				GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_DuplicateValue)
#define DATATYPEERR_Aborted						GCSLERR_MAKE_ERROR(GCSLPKG_DataTypes, GCSLERR_Aborted)

/* Errors returned from HDO subsystem */
#define HDOERR_NoError							GCSLERR_NoError
#define HDOERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_NoMemory)
#define HDOERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_InvalidArg)
#define HDOERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_NotInited)
#define HDOERR_NotFound							GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_NotFound)
#define HDOWARN_NotFound						GCSLERR_MAKE_WARNING(GCSLPKG_HDO, GCSLERR_NotFound)
#define HDOERR_ReadOnly							GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_ReadOnly)
#define HDOERR_HandleObjectWrongType			GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_HandleObjectWrongType)
#define HDOERR_WrongValueType					GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_WrongValueType)
#define HDOERR_LateDataUpdate					GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_LateDataUpdate)
#define HDOERR_DataCorruption					GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_DataCorruption)
#define HDOERR_InvalidGPath						GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_InvalidPath)
#define HDOERR_InvalidPath						GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_InvalidPath)
#define HDOERR_BufferTooSmall					GCSLERR_MAKE_ERROR(GCSLPKG_HDO, GCSLERR_BufferTooSmall)

/* Errors returned from string subsystem */
#define STRINGERR_NoError						GCSLERR_NoError
#define STRINGERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_String, GCSLERR_NoMemory)
#define STRINGERR_InvalidArg					GCSLERR_MAKE_ERROR(GCSLPKG_String, GCSLERR_InvalidArg)
#define STRINGERR_InvalidUTF8					GCSLERR_MAKE_ERROR(GCSLPKG_String, GCSLERR_InvalidUTF8)
#define STRINGERR_InvalidUCS2					GCSLERR_MAKE_ERROR(GCSLPKG_String, GCSLERR_InvalidUCS2)
#define STRINGERR_InvalidFormat					GCSLERR_MAKE_ERROR(GCSLPKG_String, GCSLERR_InvalidFormat)
#define STRINGERR_BufferTooSmall				GCSLERR_MAKE_ERROR(GCSLPKG_String, GCSLERR_BufferTooSmall)

/* Errors returned from the micro XML subsystem */
#define XMLERR_NoError							GCSLERR_NoError
#define XMLERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_NoMemory)
#define XMLERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_InvalidArg)
#define XMLERR_SyntaxError						GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_SyntaxError)
#define XMLERR_IllegalXMLCharacterError			GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_IllegalCharacter)
#define XMLERR_UnexpectedEndOfInputError		GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_UnexpectedEndOfInput)
#define XMLERR_NotFound							GCSLERR_MAKE_WARNING(GCSLPKG_XML, GCSLERR_NotFound)
#define XMLERR_NothingAtPath					GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_NothingAtPath)
#define XMLERR_DisallowedStructure				GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_DisallowedStructure)
#define XMLERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_NotInited)
#define XMLERR_Unsupported						GCSLERR_MAKE_ERROR(GCSLPKG_XML, GCSLERR_Unsupported)
#define XMLERR_EndOfInput						GCSLERR_MAKE_WARNING(GCSLPKG_XML, GCSLERR_EndOfFile)

/* Errors returned from Cryptographic subsystem */
#define CRYPTERR_NoError						GCSLERR_NoError
#define CRYPTERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_NotInited)
#define CRYPTERR_InvalidArg 					GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_InvalidArg)
#define CRYPTERR_MemoryError					GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_NoMemory)
#define CRYPTERR_UnsupportedAlg					GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_UnsupportedAlg)
#define CRYPTERR_BufferTooSmall					GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_BufferTooSmall)
#define CRYPTERR_InvalidFormat					GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_InvalidFormat)
#define CRYPTERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_NoMemory)
#define CRYPTERR_IckyError						GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_IckyError)
#define CRYPTERR_IOError						GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_IOError)
#define CRYPTERR_OutOfRange						GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_IndexOutOfRange)
#define CRYPTERR_InvalidKey						GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_InvalidKey)
#define CRYPTERR_InvalidSignature				GCSLERR_MAKE_ERROR(GCSLPKG_Crypto, GCSLERR_InvalidSignature)

/* Errors returned from the Communication subsystem */
#define SOCKERR_NoError 						GCSLERR_NoError
#define SOCKERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_NotInited)
#define SOCKERR_Busy							GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_Busy)
#define SOCKERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_InvalidArg)
#define SOCKERR_HandleObjectWrongType			GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_HandleObjectWrongType)
#define SOCKERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_NoMemory)
#define SOCKERR_IOError 						GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_IOError)
#define SOCKERR_NoMoreConnections				GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_NoMoreConnections)
#define SOCKERR_InvalidAddress					GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_CommInvalidAddress)
#define SOCKERR_InvalidHandle					GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_CommInvalidHandle)
#define SOCKERR_Unsupported						GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_Unsupported)
#define SOCKERR_Timeout							GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_Timeout)
#define SOCKWARN_Timeout						GCSLERR_MAKE_WARNING(GCSLPKG_Socket, GCSLERR_Timeout)
#define SOCKERR_ConnectionRefused				GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_ConnectionRefused)
#define SOCKERR_ConnectionReset					GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_ConnectionReset)
#define SOCKERR_ConnectionHostDown				GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_CommHostDown)
#define SOCKERR_Disconnected					GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_Disconnected)
#define SOCKERR_NotAvailable					GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_CommNotAvailable)
#define SOCKERR_Unknown							GCSLERR_MAKE_ERROR(GCSLPKG_Socket, GCSLERR_Unknown)

/* Errors returned from the Communication subsystem */
#define HTTPERR_NoError 						GCSLERR_NoError
#define HTTPERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_InvalidArg)
#define HTTPERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_NotInited)
#define HTTPERR_NotFound						GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_NotFound)
#define HTTPERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_NoMemory)
#define HTTPERR_NotReady						GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_NotReady)
#define HTTPERR_InvalidHandle					GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_CommInvalidHandle)
#define HTTPERR_InvalidHeaderFormat				GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_HTTPInvalidHeaderFormat)
#define HTTPERR_InvalidURL						GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_HTTPInvalidURL)
#define HTTPERR_Disconnected					GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_Disconnected)
#define HTTPERR_Aborted							GCSLERR_MAKE_ERROR(GCSLPKG_HTTP, GCSLERR_Aborted)

/* Errors returned from the utilities package */
#define UTILERR_NoError							GCSLERR_NoError
#define UTILERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Utils, GCSLERR_InvalidArg)
#define UTILERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_Utils, GCSLERR_NoMemory)
#define UTILERR_Unsupported						GCSLERR_MAKE_ERROR(GCSLPKG_Utils, GCSLERR_Unsupported)
#define UTILERR_InvalidFormat					GCSLERR_MAKE_ERROR(GCSLPKG_Utils, GCSLERR_InvalidFormat)
#define UTILERR_IncorrectUsage					GCSLERR_MAKE_ERROR(GCSLPKG_Utils, GCSLERR_IncorrectUsage)
#define UTILERR_BufferTooSmall					GCSLERR_MAKE_ERROR(GCSLPKG_Utils, GCSLERR_BufferTooSmall)
#define UTILERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Utils, GCSLERR_NotInited)

/* Errors returned from the GCSP MIME extensions library */
#define GCSPERR_NoError							GCSLERR_NoError
#define GCSPERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_NotInited)
#define GCSPERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_InvalidArg)
#define GCSPERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_NoMemory)
#define GCSPERR_InvalidHeaderFormat				GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_HTTPInvalidHeaderFormat)
#define GCSPERR_WrongServerPublicKey			GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_WrongServerPublicKey)
#define GCSPERR_WrongClientPublicKey			GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_WrongClientPublicKey)
#define GCSPERR_ServerEncryptionError			GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_ServerEncryptionError)
#define GCSPERR_CorruptEncryptData				GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_CorruptEncryptData)
#define GCSPERR_CorruptCompressData				GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_CorruptCompressData)
#define GCSPERR_BadXMLFormat					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_BadXMLFormat)
#define GCSPERR_NotFound						GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_NotFound)
#define GCSPWARN_NotFound						GCSLERR_MAKE_WARNING(GCSLPKG_GCSP, GCSLERR_NotFound)
#define GCSPERR_CommandError					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_CommandError)
#define GCSPERR_InvalidInput					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_InvalidInput)
#define GCSPERR_NoValidation					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_NoValidation)
#define GCSPERR_ClientCompression				GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_ClientCompression)
#define GCSPERR_ClientEncryption				GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_ClientEncryption)
#define GCSPERR_GEMPError						GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_GEMPError)
#define GCSPERR_EmptyResponse					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_EmptyResponse)
#define GCSPERR_HandleObjectWrongType			GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_HandleObjectWrongType)
#define GCSPERR_HTTPClientError					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_HTTPClientError)
#define GCSPERR_HTTPServerError					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_HTTPServerError)
#define GCSPERR_HTTPMovedError					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_HTTPMovedError)
#define GCSPERR_Aborted							GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_Aborted)
#define GCSPWARN_Aborted						GCSLERR_MAKE_WARNING(GCSLPKG_GCSP, GCSLERR_Aborted)
#define GCSPERR_MaxRedirects					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_MaxRedirects)
#define GCSPERR_UnknownResponseCode				GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_UnknownResponseCode)
#define GCSPERR_ServerError						GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_ServerError)
#define GCSPERR_ClientError						GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_ClientError)
#define GCSPERR_GeneralError					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_GeneralError)
#define GCSPERR_InvalidClientID					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_InvalidClientID)
#define GCSPERR_InvalidUserID					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_InvalidUserID)
#define GCSPERR_QuotaExceeded					GCSLERR_MAKE_ERROR(GCSLPKG_GCSP, GCSLERR_QuotaExceeded)
#define GCSPWARN_EndOfStream					GCSLERR_MAKE_WARNING(GCSLPKG_GCSP, GCSLERR_EndOfFile)

/* Errors returned from the compression library */
#define COMPERR_NoError							GCSLERR_NoError
#define COMPERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Compression, GCSLERR_InvalidArg)
#define COMPERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_Compression, GCSLERR_NoMemory)
#define COMPERR_UnknownCompressionType			GCSLERR_MAKE_ERROR(GCSLPKG_Compression, GCSLERR_UnknownCompressionType)
#define COMPERR_BufferTooSmall					GCSLERR_MAKE_ERROR(GCSLPKG_Compression, GCSLERR_BufferTooSmall)
#define COMPERR_DataError						GCSLERR_MAKE_ERROR(GCSLPKG_Compression, GCSLERR_DataError)
#define COMPERR_BadVersion						GCSLERR_MAKE_ERROR(GCSLPKG_Compression, GCSLERR_UnknownVersion)
#define COMPERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Compression, GCSLERR_NotInited)
#define COMPWARN_EndOfStream					GCSLERR_MAKE_WARNING(GCSLPKG_Compression, GCSLERR_EndOfFile)

/* Errors returned from Random subsystem */
#define MD5ERR_NoError							GCSLERR_NoError
#define MD5ERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_MD5, GCSLERR_InvalidArg)
#define MD5ERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_MD5, GCSLERR_NoMemory)
#define MD5ERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_MD5, GCSLERR_NotInited)

/* Errors returned from Random subsystem */
#define RANDERR_NoError							GCSLERR_NoError
#define RANDERR_InitFailed						GCSLERR_MAKE_ERROR(GCSLPKG_Random, GCSLERR_InitFailed)
#define RANDERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Random, GCSLERR_InvalidArg)
#define RANDERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Random, GCSLERR_NotInited)
#define RANDERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_Random, GCSLERR_NoMemory)
#define RANDERR_Unknown							GCSLERR_MAKE_ERROR(GCSLPKG_Random, GCSLERR_Unknown)

/* Errors returned from Text Correlation subsystem */
#define TEXTCORRERR_NoError						GCSLERR_NoError
#define TEXTCORRERR_InvalidArg					GCSLERR_MAKE_ERROR(GCSLPKG_TextCorr, GCSLERR_InvalidArg)
#define TEXTCORRERR_NoMemory					GCSLERR_MAKE_ERROR(GCSLPKG_TextCorr, GCSLERR_NoMemory)
#define TEXTCORRERR_NotInited					GCSLERR_MAKE_ERROR(GCSLPKG_TextCorr, GCSLERR_NotInited)
#define TEXTCORRERR_BufferTooSmall				GCSLERR_MAKE_ERROR(GCSLPKG_TextCorr, GCSLERR_BufferTooSmall)
#define TEXTCORRERR_NothingToDo					GCSLERR_MAKE_WARNING(GCSLPKG_TextCorr, GCSLERR_NothingToDo) /* TODO: error, warning, info? */
#define TEXTCORRERR_IOError						GCSLERR_MAKE_ERROR(GCSLPKG_TextCorr, GCSLERR_IOError)
#define TEXTCORRERR_Unknown						GCSLERR_MAKE_ERROR(GCSLPKG_TextCorr, GCSLERR_Unknown)

/* Errors returned from the thread utility library */
#define THREADERR_NoError						GCSLERR_NoError
#define THREADERR_InvalidArg					GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_InvalidArg)
#define THREADERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_NoMemory)
#define THREADERR_TooMany						GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_TooMany)
#define THREADERR_NotFound						GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_NotFound)
#define THREADERR_PermissionError				GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_PermissionError)
#define THREADERR_Deadlock						GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_Deadlock)
#define THREADERR_NoResources					GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_NoResources)
#define THREADERR_Busy							GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_Busy)
#define THREADERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_NotInited)
#define THREADERR_Unknown						GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_Unknown)
#define THREADERR_Interrupted					GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_Interrupted)
#define THREADWARN_Timeout						GCSLERR_MAKE_WARNING(GCSLPKG_Thread, GCSLERR_Timeout)
#define THREADERR_Unsupported					GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_Unsupported)
#define THREADERR_HandleObjectWrongType			GCSLERR_MAKE_ERROR(GCSLPKG_Thread, GCSLERR_HandleObjectWrongType)

/* Errors returned from the Lists subsystem */
#define LISTSERR_NoError						GCSLERR_NoError
#define LISTSERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_InvalidArg)
#define LISTSERR_Unsupported					GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_Unsupported)
#define LISTSWARN_Unsupported					GCSLERR_MAKE_WARNING(GCSLPKG_Lists, GCSLERR_Unsupported)
#define LISTSERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_NoMemory)
#define LISTSERR_InvalidListFile				GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_ListInvalidFile)
#define LISTSERR_IOError						GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_IOError)
#define LISTSERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_NotInited)
#define LISTSERR_NotFound						GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_NotFound)
#define LISTSWARN_NotFound						GCSLERR_MAKE_WARNING(GCSLPKG_Lists, GCSLERR_NotFound)
#define LISTSWARN_NoMemory						GCSLERR_MAKE_WARNING(GCSLPKG_Lists, GCSLERR_NoMemory)
#define LISTSERR_InvalidFormat					GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_InvalidFormat)
#define LISTSERR_ListUnavailable				GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_ListUnavailable)
#define LISTSERR_HandleObjectWrongType			GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_HandleObjectWrongType)
#define LISTSERR_InvalidLevel					GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_ListInvalidLevel)
#define LISTSERR_IckyError						GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_IckyError)
#define LISTSERR_IndexOutOfRange				GCSLERR_MAKE_ERROR(GCSLPKG_Lists, GCSLERR_IndexOutOfRange)

/* Errors returned from DataEncode subsystem */
#define DATAENCODEERR_NoError					GCSLERR_NoError
#define DATAENCODEERR_InvalidArg 				GCSLERR_MAKE_ERROR(GCSLPKG_DataEncode, GCSLERR_InvalidArg)
#define DATAENCODEERR_NoMemory					GCSLERR_MAKE_ERROR(GCSLPKG_DataEncode, GCSLERR_NoMemory)
#define DATAENCODEERR_InvalidFormat				GCSLERR_MAKE_ERROR(GCSLPKG_DataEncode, GCSLERR_InvalidFormat)
#define DATAENCODEERR_NotInited					GCSLERR_MAKE_ERROR(GCSLPKG_DataEncode, GCSLERR_NotInited)

/* Errors returned from the Content subsystem. */
#define CDSERR_NoError							GCSLERR_NoError
#define CDSERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_InvalidArg)
#define CDSERR_NotFound							GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_NotFound)
#define CDSWARN_NotFound						GCSLERR_MAKE_WARNING(GCSLPKG_CDS, GCSLERR_NotFound)
#define CDSERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_NoMemory)
#define CDSERR_HandleObjectWrongType			GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_HandleObjectWrongType)
#define CDSERR_Aborted							GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_Aborted)
#define CDSERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_NotInited)
#define CDSERR_InvalidData						GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_InvalidData)
#define CDSERR_InvalidHeaderFormat				GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_HTTPInvalidHeaderFormat)
#define CDSERR_MaxRedirects						GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_MaxRedirects)
#define CDSERR_HTTPServerError					GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_HTTPServerError)
#define CDSERR_HTTPMovedError					GCSLERR_MAKE_ERROR(GCSLPKG_CDS, GCSLERR_HTTPMovedError)


/* Errors returned from the FPX subsystem */
#define FPXERR_NoError							GCSLERR_NoError
#define FPXERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_FPX, GCSLERR_InvalidArg)
#define FPXERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_FPX, GCSLERR_NoMemory)
#define FPXERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_FPX, GCSLERR_NotInited)
#define FPXERR_UnsupportedAlg					GCSLERR_MAKE_ERROR(GCSLPKG_FPX, GCSLERR_UnsupportedAlg)
#define FPXERR_NotReady							GCSLERR_MAKE_ERROR(GCSLPKG_FPX, GCSLERR_NotReady)
#define FPXERR_IckyError						GCSLERR_MAKE_ERROR(GCSLPKG_FPX, GCSLERR_IckyError)
#define FPXERR_MemoryError						GCSLERR_MAKE_ERROR(GCSLPKG_FPX, GCSLERR_NoMemory)

/* Errors returned from the Paths subsystem */
#define PATHSERR_NoError						GCSLERR_NoError
#define PATHSERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Paths, GCSLERR_InvalidArg)
#define PATHSERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Paths, GCSLERR_NotInited)
#define PATHSERR_NotFound						GCSLERR_MAKE_ERROR(GCSLPKG_Paths, GCSLERR_NotFound)
#define PATHSWARN_NotFound						GCSLERR_MAKE_WARNING(GCSLPKG_Paths, GCSLERR_NotFound)
#define PATHSERR_InvalidFileName				GCSLERR_MAKE_ERROR(GCSLPKG_Paths, GCSLERR_FileInvalidName)

/* Errors returned from the Fingerprint subsystem */
#define FINGERPRINTERR_NoError					GCSLERR_NoError
#define FINGERPRINTERR_InvalidArg				GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_InvalidArg)
#define FINGERPRINTERR_NoMemory					GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_NoMemory)
#define FINGERPRINTERR_NotInited				GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_NotInited)
#define FINGERPRINTERR_UnsupportedAlg			GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_UnsupportedAlg)
#define FINGERPRINTERR_NotReady					GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_NotReady)
#define FINGERPRINTERR_Unsupported				GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_Unsupported)
#define FINGERPRINTERR_IckyError				GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_IckyError)
#define FINGERPRINTERR_MemoryError				GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_NoMemory)
#define FINGERPRINTERR_InvalidData				GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_InvalidData)
#define FINGERPRINTWARN_TemporalDiscontinuity	GCSLERR_MAKE_WARNING(GCSLPKG_Fingerprint, GCSLERR_TemporalDiscontinuity)
#define FINGERPRINTERR_HandleObjectWrongType	GCSLERR_MAKE_ERROR(GCSLPKG_Fingerprint, GCSLERR_HandleObjectWrongType)
#define FINGERPRINTWARN_IndexOutOfRange			GCSLERR_MAKE_WARNING(GCSLPKG_Fingerprint, GCSLERR_IndexOutOfRange)

/* Errors returned from the Time subsystem */
#define TIMEERR_NoError							GCSLERR_NoError
#define TIMEERR_NotInited						GCSLERR_MAKE_ERROR(GCSLPKG_Time, GCSLERR_NotInited)
#define TIMEERR_NotFound						GCSLERR_MAKE_ERROR(GCSLPKG_Time, GCSLERR_NotFound)
#define TIMEERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_Time, GCSLERR_InvalidArg)
#define TIMEERR_InvalidFormat					GCSLERR_MAKE_ERROR(GCSLPKG_Time, GCSLERR_InvalidFormat)

/* Errors returned from the License subsystem */
#define LICENSEERR_NoError						GCSLERR_NoError
#define LICENSEERR_InvalidArg					GCSLERR_MAKE_ERROR(GCSLPKG_License, GCSLERR_InvalidArg)
#define LICENSEERR_NotInited					GCSLERR_MAKE_ERROR(GCSLPKG_License, GCSLERR_NotInited)
#define LICENSEERR_InvalidFormat				GCSLERR_MAKE_ERROR(GCSLPKG_License, GCSLERR_InvalidFormat)
#define LICENSEERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_License, GCSLERR_NoMemory)
#define LICENSEERR_LicenseInvalid				GCSLERR_MAKE_ERROR(GCSLPKG_License, GCSLERR_LicenseInvalid)
#define LICENSEERR_NotLicensed					GCSLERR_MAKE_ERROR(GCSLPKG_License, GCSLERR_NotLicensed)

/* Errors returned from the Process subsystem */
#define PROCESSERR_NoError						GCSLERR_NoError
#define PROCESSERR_InvalidArg					GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_InvalidArg)
#define PROCESSERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_NoMemory)
#define PROCESSERR_NotInited					GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_NotInited)
#define PROCESSWARN_NotFound					GCSLERR_MAKE_WARNING(GCSLPKG_Process, GCSLERR_NotFound)
#define PROCESSERR_NotFound						GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_NotFound)
#define PROCESSERR_Unknown						GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_Unknown)
#define PROCESSERR_HandleObjectWrongType		GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_HandleObjectWrongType)
#define PROCESSERR_Timeout						GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_Timeout)
#define PROCESSWARN_Timeout						GCSLERR_MAKE_WARNING(GCSLPKG_Process, GCSLERR_Timeout)
#define PROCESSERR_Disconnected					GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_Disconnected)
#define PROCESSERR_IOError						GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_IOError)
#define PROCESSERR_Busy							GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_Busy)
#define	PROCESSERR_Unsupported					GCSLERR_MAKE_ERROR(GCSLPKG_Process, GCSLERR_Unsupported)


#define DBERR_NoError							GCSLERR_NoError
#define DBERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_InvalidArg)
#define DBERR_NotFound							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_NotFound)
#define DBERR_NoMemory							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_NoMemory)
#define DBERR_IOErr								GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_IOError)
#define DBERR_NestedCall						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_NestedCall)
#define DBERR_PermissionError					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_PermissionError)
#define DBERR_ReadErr							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_ReadErr)
#define DBERR_WriteErr							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_WriteErr)
#define DBERR_UnknownVersion					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_UnknownVersion)
#define DBERR_InvalidFile						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_InvalidFile)
#define DBERR_AlreadyAdded						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_AlreadyAdded)
#define DBERR_InvalidBlock						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_InvalidBlock)
#define DBERR_Aborted							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_Aborted)
#define DBERR_FileExists						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_FileExists)
#define DBERR_NoSpace							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_NoSpace)
#define	DBERR_BadIndex							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_BadIndex)
#define	DBERR_BadFreeList						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_BadFreeList)
#define	DBERR_BadRecord							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_BadRecord)
#define	DBERR_BadBlock							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_BadBlock)
#define	DBERR_IndexPastEOF						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_IndexPastEOF)
#define	DBERR_RecordPastEOF						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_RecordPastEOF)
#define	DBERR_IndexInFreeList					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_IndexInFreeList)
#define	DBERR_RecordInFreeList					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_RecordInFreeList)
#define	DBERR_BlockInFreeList					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_BlockInFreeList)
#define	DBERR_IncompatibleDBs					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_IncompatibleDBs)
#define	DBERR_KeyNotRead						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_KeyNotRead)
#define	DBERR_InvalidByteOrder					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_InvalidByteOrder)
/*#define	DBERR_UnknownFSError					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_UnknownFSError)*/
#define	DBERR_InvalidIterator					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_InvalidIterator)
#define	DBERR_Unsupported						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_Unsupported)
#define	DBERR_BadHeader							GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_BadHeader)
#define	DBERR_CriticalSection					GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_CriticalSection)
#define	DBERR_ThreadError						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_ThreadError)
#define	DBERR_ReadLocked						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_ReadLocked)
#define	DBERR_WriteLocked						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_WriteLocked)
#define	DBERR_HandleObjectWrongType				GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_HandleObjectWrongType)
#define	DBERR_FileTooLarge						GCSLERR_MAKE_ERROR(GCSLPKG_DBEngine, GCSLERR_FileTooLarge)

#define GNPBERR_NoError							GCSLERR_NoError
#define GNPBERR_InvalidArg						GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_InvalidArg)
#define GNPBERR_InvalidType						GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_WrongValueType)
#define GNPBWARN_NotFound						GCSLERR_MAKE_WARNING(GCSLPKG_ProtoBuffers, GCSLERR_NotFound)
#define GNPBERR_NotFound						GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_NotFound)
#define GNPBERR_BadHeader						GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_BadHeader)
#define GNPBERR_ParsingError					GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_ParsingError)
#define GNPBERR_DataTooShort					GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_DataTooShort)
#define GNPBERR_InvalidWireType					GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_InvalidWireType)
#define GNPBERR_NoMemory						GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_NoMemory)
#define GNPBERR_UnterminatedVarInt				GCSLERR_MAKE_ERROR(GCSLPKG_ProtoBuffers, GCSLERR_UnterminatedVarInt)

#define IOSTREAMERR_NoError						GCSLERR_NoError
#define IOSTREAMERR_NotInited					GCSLERR_MAKE_ERROR(GCSLPKG_IOStream, GCSLERR_NotInited)
#define IOSTREAMERR_InvalidArg					GCSLERR_MAKE_ERROR(GCSLPKG_IOStream, GCSLERR_InvalidArg)
#define IOSTREAMERR_NoMemory					GCSLERR_MAKE_ERROR(GCSLPKG_IOStream, GCSLERR_NoMemory)
#define IOSTREAMERR_HandleObjectWrongType		GCSLERR_MAKE_ERROR(GCSLPKG_IOStream, GCSLERR_HandleObjectWrongType)
#define IOSTREAMERR_ReadOnly					GCSLERR_MAKE_ERROR(GCSLPKG_IOStream, GCSLERR_ReadOnly)
#define IOSTREAMERR_WriteOnly					GCSLERR_MAKE_ERROR(GCSLPKG_IOStream, GCSLERR_WriteOnly)
#define IOSTREAMWARN_EndOfStream				GCSLERR_MAKE_WARNING(GCSLPKG_IOStream, GCSLERR_EndOfFile)
#define IOSTREAMERR_Unsupported					GCSLERR_MAKE_ERROR(GCSLPKG_IOStream, GCSLERR_Unsupported)


#ifdef __cplusplus
}
#endif

#endif /* _GCSL_ERROR_CODES_H_ */

