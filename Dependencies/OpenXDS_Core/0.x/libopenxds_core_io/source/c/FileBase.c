/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.io/File.private.h"

#include <openxds.core.base/CharString.h>
#include <openxds.core.base/Time.h>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

static void        File_retrieveTimes( File* self );
static const char* File_NameForDescriptor( int fd );


static void initialise( File* self )
{
	self->super.free                = (       IFile* (*)(       IFile* ))                     free_File;
	self->super.open                = (         int  (*)(       IFile*, const char* access )) File_open;
	self->super.flush               = (         int  (*)(       IFile* )) File_flush;
	self->super.close               = (         int  (*)(       IFile* )) File_close;

	self->super.readCharacters      = (        char* (*)(       IFile* ))                                              File_readCharacters; 
	self->super.write               = (        long  (*)(       IFile*, const byte* buffer, long bufferSize )) File_write;
	self->super.read                = (        long  (*)( const IFile*,       byte* buffer, long bufferSize )) File_read;

	self->super.getPath             = ( const IPath* (*)( const IFile* ))                     File_getPath;

	self->super.createFile          = (         int  (*)( const IFile* ))                     File_create;
	self->super.deleteFile          = (         int  (*)( const IFile* ))                     File_delete;
	self->super.removeFile          = (         int  (*)( const IFile* ))                     File_remove;

	self->super.copyTo              = (        bool  (*)( const IFile* ))                     File_copyTo;
	self->super.exists              = (        bool  (*)( const IFile* ))                     File_exists;
	self->super.isNewerThan         = (        bool  (*)( const IFile*, const IFile* other )) File_isNewerThan;
	self->super.isOpen              = (        bool  (*)( const IFile* ))                     File_isOpen;
	self->super.isEOF               = (        bool  (*)( const IFile* ))                     File_isEOF;
}


IFile*
new_File( const char* location )
{
	File* self = CRuntime_calloc( 1, sizeof( File ) );
	initialise( self );
	
	self->path = new_Path( location );
	self->closeOnFree = 1;
	return (IFile*) self;
}

IFile*
new_File_path( const IPath* path )
{
	File* self = CRuntime_calloc( 1, sizeof( File ) );
	initialise( self );

	self->path = path->copy( path );
	self->closeOnFree = 1;
	return (IFile*) self;
}

void
free_File( File* self )
{
	if ( self->path ) self->path->free( self->path );
	if ( self->stream && self->closeOnFree ) File_close( self );
	if ( self->times.lastAccess )       self->times.lastAccess->free( self->times.lastAccess );
	if ( self->times.lastModification ) self->times.lastModification->free( self->times.lastModification );
	if ( self->times.lastChange )       self->times.lastChange->free( self->times.lastChange );
	CRuntime_free( self );
}

int
File_open( File* self, const char* access )
{
	int status = 0;

	const char* filepath = 0;

	if ( File_isOpen( self ) )
	{
		status = 1;
	} else {
		filepath = self->path->getNativeFormat( self->path );
		self->stream = fopen( filepath, access );
		if ( self->stream )
		{
			status = 1;
		}
	}
	return status;
}

int
File_flush( File* self )
{
	int status = 0;
	if ( 0 == fflush( self->stream ) )
	{
		status = 1;
	}
	return status;
}

int
File_close( File* self )
{
	int status = 0;
	if ( 0 == fclose( self->stream ) )
	{
		self->stream = NULL;
		self->eof = 0;
		status = 1;
	}
	return status;
}

char*
File_readCharacters( File* self )
{
	/*
	 *	At most read one less than buffer size so that buffer is
	 *	null terminated.
	 */
	void* buffer = CRuntime_calloc( 1024, sizeof( char ) );
	const unsigned char* buf = (unsigned char*) buffer;

	/*
	 *	fread( buffer, 1023, 1, self->stream );
	 */
	File_read( self, buffer, 1023 );

	/*
	 *	If file is not ASCII, i.e., negative char values, return 0.
	 */
	{
		unsigned int i;
		for ( i=0; i < 1024; i++ )
		{
			if ('\0' == buf[i])
			{
				break;
			}
			else if ( 127 < buf[i] )
			{
				CRuntime_free( buffer );
				buffer = NULL;
				break;
			}
		}
	}
	return buffer;
}

long
File_read( const File* self, byte* buffer, long bufferSize )
{
	unsigned long read = fread( buffer, 1, bufferSize, self->stream );
	if ( feof( self->stream ) )
	{
		((File*)self)->eof = 1;
	}
	return read;
}

long
File_write( File* self, const byte* buffer, long bufferSize )
{
	return fwrite( buffer, bufferSize, 1, self->stream );
}

const IPath*
File_getPath( const File* self )
{
	return self->path;
}

bool File_exists( const File* self )
{
	bool exists = 0;
	FILE* f = fopen( self->path->getNativeFormat( self->path ), "r" );
	if ( f )
	{
		fclose( f );
		exists = 1;
	}
	//else if ( EACCES == errno )
	//{
	//	exists = 1;
	//}
	return exists;
}

bool File_isNewerThan( const File* self, const File* other )
{
	const ITime* self_modification_time  = File_getLastModification( self );
	const ITime* other_modification_time = File_getLastModification( other );
	
	unsigned long long self_seconds  =  self_modification_time->getSecondsSinceEpoch( self_modification_time );
	unsigned long long other_seconds = other_modification_time->getSecondsSinceEpoch( other_modification_time );

	//const char* self_name = Path_getBasename( File_getPath( self ) );
	//const char* self_text = Time_getTextual( self_modification_time );
	//const char* other_name = Path_getBasename( File_getPath( other ) );
	//const char* other_text = Time_getTextual( other_modification_time );
	//fprintf( stderr, "File_isNewerThan: %s@%s compared to %s@%s\n", self_name, self_text, other_name, other_text );
	
	return ( self_seconds > other_seconds );
}

bool File_isOpen( const File* self )
{
	if ( self->stream )
	{
		return 1;
	} else {
		return 0;
	}
}

bool File_isEOF( const File* self )
{
	return self->eof;
}

const ITime*
File_getLastAccess( const File* self )
{
	if ( !self->times.lastAccess )
	{
		File_retrieveTimes( (File*) self );
	}
	return self->times.lastAccess;
}

const ITime*
File_getLastModification( const File* self )
{
	if ( !self->times.lastModification )
	{
		File_retrieveTimes( (File*) self );
	}
	return self->times.lastModification;
}

const ITime*
File_getLastChange( const File* self )
{
	if ( !self->times.lastChange )
	{
		File_retrieveTimes( (File*) self );
	}
	return self->times.lastChange;
}

IFile* File_GetFileForStandardDescriptor( flags stream )
{
	File* self = CRuntime_calloc( 1, sizeof( File ) );
	initialise( self );

	self->path = new_Path( File_NameForDescriptor( (int) stream ) );
	self->closeOnFree = 0;
	
	switch( stream )
	{
	case OPENXDS_CORE_IO_FILE_STDIN:
		self->stream = stdin;
		break;
	case OPENXDS_CORE_IO_FILE_STDOUT:
		self->stream = stdout;
		break;
	case OPENXDS_CORE_IO_FILE_STDERR:
		self->stream = stderr;
		break;
	default:
		free_File( self );
		self = NULL;
	}
	
	return (IFile*) self; 
}

IFile* File_GetFileForStandardStream( void* stream )
{
	int fd1 = 4; // Unknown fileno( (FILE*) stream );

	File* self = CRuntime_calloc( 1, sizeof( File ) );
	initialise( self );

	self->path = new_Path( File_NameForDescriptor( fd1 ) );
	self->closeOnFree = 1;

	switch( fd1 )
	{
	case OPENXDS_CORE_IO_FILE_STDIN:
		self->stream = freopen( NULL, "rb", stream );
		break;
	case OPENXDS_CORE_IO_FILE_STDOUT:
		self->stream = freopen( NULL, "wb", stream );
		break;
	case OPENXDS_CORE_IO_FILE_STDERR:
		self->stream = freopen( NULL, "wb", stream );
		break;
	default:
		self->stream = stream;
		break;
	}
	
	return (IFile*) self; 
}

IFile* File_GetFileForStream( void* stream )
{
	File* self = NULL;
	if ( stream )
	{
		self = CRuntime_calloc( 1, sizeof( File ) );
		initialise( self );
		
		self->path = new_Path( "UNKNOWN" );
		self->stream = stream;
		self->closeOnFree = 0;
	}
	return (IFile*) self;
}	

static const char* File_NameForDescriptor( int fd )
{
	const char* name;
	switch ( fd )
	{
	case OPENXDS_CORE_IO_FILE_STDIN:
		name = "STDIN";
		break;
	case OPENXDS_CORE_IO_FILE_STDOUT:
		name = "STDOUT";
		break;
	case OPENXDS_CORE_IO_FILE_STDERR:
		name = "STDERR";
		break;
	default:
		name = "UNKNOWN";
	}
	return name;
}

static void
File_retrieveTimes( File* self )
{
	struct stat buf;
	const IPath* path = File_getPath( self );
	
	stat( path->getCondensed( path ), &buf );
	
	self->times.lastAccess = new_Time( buf.st_atime );
	self->times.lastModification = new_Time( buf.st_mtime );
	self->times.lastChange = new_Time( buf.st_ctime );
}

