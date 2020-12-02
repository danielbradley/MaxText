/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_EXPORT_H
#define OPENXDS_CORE_EXPORT_H

#include "openxds.core/debug.h"

#ifdef _WIN32
	#ifdef __cplusplus
	#define EXPORT extern "C" __declspec(dllexport)
	#else
	#define EXPORT __declspec(dllexport)
	#endif
#else
	#ifdef __cplusplus
		#define EXPORT extern "C"
	#else	
	#define EXPORT
	#endif
#endif

/*
 *	CRuntime.h in this file so that its functions are defined
 *	for all source files that include "openxds/debug.h"
 *	via this file.
 *
 *	However, it needs to be included after the definition of
 *	EXPORT as it itself is exported.
 */ 
#include "openxds.core.base/CRuntime.h"

#endif
