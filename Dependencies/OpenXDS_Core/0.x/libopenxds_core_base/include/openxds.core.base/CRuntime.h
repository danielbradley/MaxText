/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_CRUNTIME_H
#define OPENXDS_CORE_BASE_CRUNTIME_H

#include "openxds.core/export.h"
#include "openxds.core/types.h"
#include "openxds.core.base.h"
#include <stdlib.h>

	/*	These allow programs to include CRuntime for testing but reimplement their own
	 *  stubs for normal compilation.
	 */
	#ifndef OPENXDS_CORE_BASE_CRUNTIME_MALLOC
	#define OPENXDS_CORE_BASE_CRUNTIME_MALLOC
	#endif

	#ifndef OPENXDS_CORE_BASE_CRUNTIME_CALLOC
	#define OPENXDS_CORE_BASE_CRUNTIME_CALLOC
	#endif

	#ifndef OPENXDS_CORE_BASE_CRUNTIME_FREE
	#define OPENXDS_CORE_BASE_CRUNTIME_FREE
	#endif

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif
	
/*
 *	Conditionally defined in "openxds/debug.h"
 */
	#ifndef OPENXDS_CORE_BASE_DIRECT_MEMORY_ALLOCATION

EXPORT	void*		CRuntime_malloc( size_t size );
EXPORT	void*		CRuntime_calloc( size_t nmemb, size_t size );
EXPORT	void*		CRuntime_realloc( void* ptr, size_t size );
EXPORT	void*		CRuntime_recalloc( void* ptr, size_t old, size_t size );
EXPORT	void*		CRuntime_recalloc_type( void* ptr, size_t old, size_t size, size_t type );
EXPORT	void*		CRuntime_free( void* ptr );

EXPORT	long long	CRuntime_GetAllocationCount(void);
EXPORT	void		CRuntime_SleepForSeconds( unsigned int seconds );
EXPORT	void		CRuntime_SleepForMicroseconds( unsigned int microseconds );

	#endif

	#ifdef __cplusplus
		};};};};
	#endif
#endif
