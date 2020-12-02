/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_THREADS_MUTEX_H
#define OPENXDS_CORE_THREADS_MUTEX_H

#include <openxds.core.base.h>
#include <openxds.core/export.h>
#include <openxds.core.threads.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace threads {
		extern "C" {
	#endif

struct _IMutex
{
	IMutex*                (*free)( IMutex* self );
	bool                   (*lock)( IMutex* self );
	bool                (*tryLock)( IMutex* self );
	bool                 (*unlock)( IMutex* self );
	bool                (*isValid)( IMutex* self );
};

EXPORT	IMutex* new_Mutex(void);

	#ifdef __cplusplus
		}
		};};};
	#endif
#endif
