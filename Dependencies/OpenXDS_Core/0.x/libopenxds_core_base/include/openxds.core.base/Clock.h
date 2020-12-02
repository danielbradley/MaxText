/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_CLOCK_H
#define OPENXDS_CORE_BASE_CLOCK_H

#include "openxds.core/export.h"
#include "openxds.core.base.h"

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif


struct _IClock
{
	            IClock*                       (*free)(       IClock* self );
	              void                       (*start)(       IClock* self );
	              void                        (*stop)(       IClock* self );
	unsigned long long                 (*getInterval)( const IClock* self );
	              long                (*getTimeAsInt)();
	     unsigned long                 (*getUserTime)();
	     unsigned long               (*getSystemTime)();
	     unsigned long                   (*getUptime)();
	unsigned long long   (*getMicroSecondsSinceEpoch)();
	unsigned long long        (*getSecondsSinceEpoch)();
	     unsigned long          (*getClockCyclesUsed)();
};

EXPORT	IClock*                                  new_Clock( void );

EXPORT	long                            Clock_GetTimeAsInt( void );
EXPORT	unsigned long                    Clock_GetUserTime( void );
EXPORT	unsigned long                  Clock_GetSystemTime( void );
EXPORT	unsigned long                      Clock_GetUptime( void );

EXPORT	unsigned long long Clock_GetMicroSecondsSinceEpoch( void );
EXPORT	unsigned long long      Clock_GetSecondsSinceEpoch( void );

EXPORT	unsigned long             Clock_GetClockCyclesUsed( void ); 

	#ifdef __cplusplus
		};};};};
	#endif
#endif
