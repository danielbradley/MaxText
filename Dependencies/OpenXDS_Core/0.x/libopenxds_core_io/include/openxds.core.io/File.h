/*
 *  Copyright (C) 2004 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_IO_FILE_H
#define OPENXDS_CORE_IO_FILE_H

#include "openxds.core.io/Path.h"

#include <openxds.core/export.h>
#include <openxds.core.base.h>
#include <openxds.core.base/Time.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace io {
		extern "C"
		{
	#endif

#define OPENXDS_CORE_IO_FILE_STDIN  0
#define OPENXDS_CORE_IO_FILE_STDOUT 1
#define OPENXDS_CORE_IO_FILE_STDERR 2


struct _IFile
{
	IFile*                             (*free)(       IFile* self );
	void                            (*refresh)(       IFile* self );
	int                                (*open)(       IFile* self, const char* access );
	int                               (*flush)(       IFile* self );
	int                               (*close)(       IFile* self );
	char*                    (*readCharacters)(       IFile* self );
	long                              (*write)(       IFile* self, const byte* buffer, long bufferSize );
	long                               (*read)( const IFile* self,       byte* buffer, long bufferSize );
	const IPath*                    (*getPath)( const IFile* self );

	int                          (*createFile)( const IFile* self );
	int                          (*deleteFile)( const IFile* self );
	int                          (*removeFile)( const IFile* self );

	bool                             (*copyTo)( const IFile* self );
	bool                             (*exists)( const IFile* self );
	bool                        (*isNewerThan)( const IFile* self, const IFile* other );
	bool                             (*isOpen)( const IFile* self );
	bool                              (*isEOF)( const IFile* self );
//	bool                             (*isFile)( const IFile* self );
};

EXPORT	IFile*                          new_File( const char* location );
EXPORT	IFile*                     new_File_path( const IPath* path );
EXPORT	IFile* File_GetFileForStandardDescriptor( flags stream );
EXPORT	IFile*     File_GetFileForStandardStream( void* stream );
EXPORT	IFile*             File_GetFileForStream( void* stream );

	#ifdef __cplusplus
		};
		};};};
	#endif

#endif
