/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_ENVIRONMENT_H
#define OPENXDS_CORE_BASE_ENVIRONMENT_H

#include "openxds.core/export.h"
#include "openxds.core.base.h"
#include <stdarg.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif

struct _IEnvironment
{
	IEnvironment*                                (*free)(       IEnvironment* self );
	        char*                       (*searchPathFor)( const IEnvironment* self, const char* file );
	  const char*                   (*getExecutableName)( const IEnvironment* self );
	  const char*               (*getExecutableLocation)( const IEnvironment* self );
	  const char*    (*getDirectoryContainingExecutable)( const IEnvironment* self );

	  const char*                             (*getPath)( const IEnvironment* self );
	  const char*              (*getEnvironmentVariable)( const char* variable );
	  void                     (*setEnvironmentVariable)( const char* key, const char* value, bool overwrite );
	  
	  char                           (*getFileSeparator)();
};

EXPORT	IEnvironment*                    new_Environment( const char* argv_0 );
EXPORT	IEnvironment*              new_Environment_using( const char* argv_0, char fileSeparator );

EXPORT	char                Environment_getFileSeparator(void);
EXPORT	const char*   Environment_getEnvironmentVariable( const char* variable );

	#ifdef __cplusplus
		};};};};
	#endif
#endif
