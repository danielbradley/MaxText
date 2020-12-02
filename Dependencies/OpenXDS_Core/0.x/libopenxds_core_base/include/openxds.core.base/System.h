/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_SYSTEM_H
#define OPENXDS_CORE_BASE_SYSTEM_H

#include "openxds.core/export.h"
#include "openxds.core.base/Environment.h"
#include <stdarg.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif

EXPORT void System_Initialize( int argc, char** argv );

/*
 *  System allocating functions
 */
EXPORT	char*              System_CurrentDirectory( void );
EXPORT	char*                 System_CurrentVolume( void );
EXPORT	char*                      System_Hostname( void );

EXPORT	IEnvironment* System_GetInitialEnvironment( void );

	#ifdef __cplusplus
		};};};};
	#endif
#endif
