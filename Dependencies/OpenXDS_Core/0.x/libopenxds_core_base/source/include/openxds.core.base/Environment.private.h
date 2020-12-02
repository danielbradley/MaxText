/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_ENVIRONMENT_PRIVATE_H
#define OPENXDS_CORE_BASE_ENVIRONMENT_PRIVATE_H

#include "openxds.core.base/Environment.h"
#include "openxds.core/export.h"

#include <stdarg.h>

#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace base {
extern "C"
{
#else
#ifndef BOOLEAN
#define BOOLEAN
	typedef int bool;
#endif
#endif

typedef struct _Environment Environment;

EXPORT	Environment* free_Environment( Environment* self );

EXPORT  void        Environment_initialise( Environment* self, const char* argv_0, char fileSeparator );

EXPORT  char*       Environment_searchPathFor( const Environment* self, const char* file );

EXPORT	const char* Environment_getExecutableName( const Environment* self );
EXPORT	const char* Environment_getExecutableLocation( const Environment* self );
EXPORT	const char* Environment_getDirectoryContainingExecutable( const Environment* self );

EXPORT	const char* Environment_getPath( const Environment* self );

EXPORT	const char* Environment_getEnvironmentVariable( const char* variable );
EXPORT	void        Environment_setEnvironmentVariable( const char* key, const char* value, int overwrite );

EXPORT  bool Environment_isLink( const char* path );
EXPORT  char* Environment_readLink( const char* path );
EXPORT	char Environment_getFileSeparator();

		bool Environment_private_CheckExistance( const char* path, const char* filename );

#ifdef __cplusplus
}
};};};
#endif
#endif
