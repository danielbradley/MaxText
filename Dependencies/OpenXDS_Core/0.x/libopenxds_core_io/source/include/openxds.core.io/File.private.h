/*
 *  Copyright (C) 2004-2005 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_IO_FILE_PRIVATE_H
#define OPENXDS_CORE_IO_FILE_PRIVATE_H

#include "openxds.core.io/File.h"
#include "openxds.core.io/Path.h"
#include <openxds.core.base/Time.h>
#include <stdio.h>

typedef struct _FileTimes FileTimes;

struct _FileTimes
{
	ITime* lastAccess;
	ITime* lastModification;
	ITime* lastChange;
};

typedef struct _File File;

struct _File
{
	IFile     super;
	IPath*    path;
	FILE*     stream;
	bool      eof;
	bool      closeOnFree;
	FileTimes times;
};

EXPORT	void            free_File( File* self );
EXPORT	int             File_open( File* self, const char* access );
EXPORT	int             File_flush( File* self );
EXPORT	int             File_close( File* self );

/*
 *	Returns nr of bytes read, or 0 if error.
 */
EXPORT	char*           File_readCharacters(       File* self );
EXPORT	long                     File_write(       File* self, const byte* buffer, long bufferSize );
EXPORT	long                      File_read( const File* self,       byte* buffer, long bufferSize );

EXPORT	const IPath*           File_getPath( const File* self );

EXPORT	int                     File_create( const File* self );
EXPORT	int                     File_delete( const File* self );
EXPORT	int                     File_remove( const File* self );

EXPORT	bool            File_copyTo( const File* self, const IPath* target, bool force );
EXPORT	bool            File_exists( const File* self );
EXPORT	bool            File_isNewerThan( const File* self, const File* other );
EXPORT	bool            File_isOpen( const File* self );
EXPORT	bool            File_isEOF( const File* self );

EXPORT	const ITime*    File_getLastAccess( const File* self );
EXPORT	const ITime*    File_getLastModification( const File* self );
EXPORT	const ITime*    File_getLastChange( const File* self );

//static const char* NameForDescriptor( int fd );
//static void        File_retrieveTimes( File* self );

#endif
