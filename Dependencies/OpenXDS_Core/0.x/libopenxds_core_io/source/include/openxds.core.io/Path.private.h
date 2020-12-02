/*
 *  Copyright (C) 2004 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include <openxds.core.io/Path.h>

#ifndef OPENXDS_CORE_IO_PATH_PRIVATE_H
#define OPENXDS_CORE_IO_PATH_PRIVATE_H

#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace io {
	extern C
	{
#endif

typedef struct _Path Path;

/*
//  Lifecycle functions
*/
EXPORT	Path* free_Path( Path* self );
EXPORT	Path* Path_copy( const Path* self );

/*
//  Accessors
*/
EXPORT	const char* Path_getCommon( const Path* self );
EXPORT	const char* Path_getCondensed( const Path* self );
EXPORT	const char* Path_getProtocol( const Path* self );
EXPORT	const char* Path_getHostname( const Path* self );
EXPORT	const char* Path_getVolume( const Path* self );
EXPORT	const char* Path_getDirname( const Path* self );
EXPORT	const char* Path_getBasename( const Path* self );
EXPORT	const char* Path_getExtension( const Path* self );
EXPORT	const char* Path_getAbsolute( const Path* self );
EXPORT	const char* Path_getURL( const Path* self );
EXPORT	const char* Path_getNativeFormat( const Path* self );
EXPORT	int         Path_getType( const Path* self );

EXPORT	bool        Path_hasExtension( const Path* self, const char* extension );
EXPORT	bool        Path_isAbsolute( const Path* self );

EXPORT	char*       Path_condensePath( const char* location );
EXPORT	char*       Path_convertToNative( const char* location );

#ifdef __cplusplus
EXPORT	openxds::core::adt::IList*      Path_convertListToNative( const openxds::core::adt::IList* list );
#else
EXPORT	IList*      Path_convertListToNative( const IList* list );
#endif

#ifdef __cplusplus
};
};};};
#endif

#endif