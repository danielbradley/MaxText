/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_TIME_H
#define OPENXDS_CORE_BASE_TIME_H

#include "openxds.core/export.h"
#include "openxds.core.base.h"

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif

typedef struct _ITime ITime;

struct _ITime
{
	ITime*                             (*free)(       ITime* self );
	ITime*                             (*copy)( const ITime* self );
	ITime*                              (*now)();
	const char*                  (*getTextual)( const ITime* self );
	unsigned long long (*getSecondsSinceEpoch)( const ITime* self );
};

EXPORT	ITime* new_Time( unsigned long long );
EXPORT	ITime* Time_Now( void );

	#ifdef __cplusplus
		};};};};
	#endif
#endif
