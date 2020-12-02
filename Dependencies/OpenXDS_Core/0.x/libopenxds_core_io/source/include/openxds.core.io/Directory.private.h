/*
 *  Copyright (C) 2004-2005 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_IO_DIRECTORY_PRIVATE_H
#define OPENXDS_CORE_IO_DIRECTORY_PRIVATE_H

#include "openxds.core.io/Directory.h"

typedef struct _Directory Directory;

//  lifecycle functions
EXPORT	Directory*          free_Directory(       Directory* self );
EXPORT	Directory*  Directory_subdirectory( const Directory* self, const char* name );

//  filesystem actions
EXPORT	bool             Directory_refresh(       Directory* self );
EXPORT	bool           Directory_createAll( const Directory* self );
EXPORT	bool              Directory_create( const Directory* self );
EXPORT	bool              Directory_delete( const Directory* self );


EXPORT	bool         Directory_isDirectory( const Directory* self );
EXPORT	bool              Directory_exists( const Directory* self );
EXPORT	bool   Directory_containsDirectory( const Directory* self, const char* dirname );
 
EXPORT	const     IPath* Directory_getPath( const Directory* self );
EXPORT	const IPath* Directory_getRealPath( const Directory* self );

#ifdef __cplusplus
EXPORT	const openxds::core::adt::ISequence* Directory_getFiles( const Directory* self );
#else
EXPORT	const ISequence*                     Directory_getFiles( const Directory* self );
#endif


struct _Directory
{
	IDirectory               super;
	IPath*                   path;
#ifdef __cplusplus
	openxds::adt::ISequence* fileList;
#else
	ISequence*               fileList;
#endif

};


#endif
