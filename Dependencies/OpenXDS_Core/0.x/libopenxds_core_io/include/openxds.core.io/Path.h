/*
 *  Copyright (C) 2004-2009 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_IO_PATH_H
#define OPENXDS_CORE_IO_PATH_H

#include "openxds.core.io.h"

#include <openxds.core/export.h>
#include <openxds.core.adt.h>

#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace io {
extern "C"
{
#endif

#define OPENXDS_CORE_IO_TYPE_NONE                   0x0000
#define OPENXDS_CORE_IO_TYPE_UNKNOWN                0x0001
#define OPENXDS_CORE_IO_TYPE_FS                     0x0011
#define OPENXDS_CORE_IO_TYPE_FS_DEVICE              0x0111
#define OPENXDS_CORE_IO_TYPE_FS_DEVICE_BLOCK        0x1111
#define OPENXDS_CORE_IO_TYPE_FS_DEVICE_CHARACTER    0x2111
#define OPENXDS_CORE_IO_TYPE_FS_DIRECTORY           0x0211
#define OPENXDS_CORE_IO_TYPE_FS_DIRECTORY_SUPER     0x1211
#define OPENXDS_CORE_IO_TYPE_FS_FILE                0x0411
#define OPENXDS_CORE_IO_TYPE_FS_LINK                0x0811
#define OPENXDS_CORE_IO_TYPE_FS_SYMLINK             0x0811
#define OPENXDS_CORE_IO_TYPE_IO                     0x0020
#define OPENXDS_CORE_IO_TYPE_IO_FIFO                0x0120
#define OPENXDS_CORE_IO_TYPE_IO_SOCKET              0x0220
#define OPENXDS_CORE_IO_TYPE_NET                    0x0040

struct _IPath
{
	     IPath*      (*currentDirectory)();
	     IPath*                  (*free)(       IPath* self );
	     IPath*                  (*copy)( const IPath* self );

	const char*             (*getCommon)( const IPath* self );
	const char*          (*getCondensed)( const IPath* self );
	const char*           (*getProtocol)( const IPath* self );
	const char*           (*getHostname)( const IPath* self );
	const char*             (*getVolume)( const IPath* self );
	const char*            (*getDirname)( const IPath* self );
	const char*           (*getBasename)( const IPath* self );
	const char*          (*getExtension)( const IPath* self );
	const char*           (*getAbsolute)( const IPath* self );
	const char*                (*getURL)( const IPath* self );
	const char*       (*getNativeFormat)( const IPath* self );
	      int                 (*getType)( const IPath* self );

	      bool           (*hasExtension)( const IPath* self, const char* ext );
	      bool             (*isAbsolute)( const IPath* self );

	      char       (*getFileSeparator)();
		  char*          (*condensePath)( const char* path );
		  char*       (*convertToNative)( const char* path );
};

EXPORT	IPath* new_Path( const char* location );
EXPORT	IPath* Path_GetCurrentDirectory(void);
EXPORT	char   Path_GetFileSeparator(void);

#ifdef __cplusplus
};
};};};
#endif

#endif
