/*
 *  Copyright (C) 2004-2005 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_IO_DIRECTORY_H
#define OPENXDS_CORE_IO_DIRECTORY_H

#include "openxds.core.io.h"
#include "openxds.core.io/Path.h"

#include <openxds.core.adt.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace io {
		extern "C"
		{ 
	#endif


struct _IDirectory
{
	IDirectory*                        (*free)(       IDirectory* self );
	IDirectory*                     (*refresh)(       IDirectory* self );
	IDirectory*                (*subdirectory)( const IDirectory* self, const char* name );
	bool                          (*createAll)( const IDirectory* self );
	bool                          (*createDir)( const IDirectory* self );
	bool                          (*deleteDir)( const IDirectory* self );
	bool                        (*isDirectory)( const IDirectory* self );
	bool                             (*exists)( const IDirectory* self );
	bool                  (*containsDirectory)( const IDirectory* self, const char* dirname );
	const IPath*                    (*getPath)( const IDirectory* self );

#ifdef __cplusplus
	const openxds::core::adt::ISequence* (*getFiles)( const IDirectory* self );
#else
	const ISequence*                     (*getFiles)( const IDirectory* self );
#endif
};

//  lifecycle functions
EXPORT	IDirectory*   new_Directory( const char* location );
EXPORT	IDirectory*   new_Directory_path( const IPath* location );


	#ifdef __cplusplus
		}
		};};};
	#endif

#endif
