/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_DEBUG_H
#define OPENXDS_CORE_DEBUG_H

/*
 *	Do not include this file!
 *
 *	This file should only be included by "openxds/base/psa/export.h" in
 *	the OpenXDS_Core libraries, and "openxds/types.h" in the OpenXDS
 *	libraries.
 *
 *	Thus Core objects get this via "openxds/base/psa/export.h" and
 *	OpenXDS objects get this via "openxds/base/Object.h" via
 *	"openxds/types.h"
 *
 *	Do NOT include this file!
 */

/*
#ifdef OPENXDS_DEBUG
#ifndef _WIN32
#define OPENXDS_USE_DEBUG_NEW_AND_DELETE
#endif
#endif

#ifndef OPENXDS_DEBUG
#define CRuntime_malloc	malloc
#define CRuntime_calloc	calloc
#define CRuntime_realloc	realloc
#define CRuntime_free		free
#define CRuntime_GetAllocationCount() 0
#define OPENXDS_BASE_PSA_DIRECT_MEMORY_ALLOCATION
#endif
*/

#endif
