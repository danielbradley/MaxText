/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_THREADS_THREAD_H
#define OPENXDS_CORE_THREADS_THREAD_H

#include <openxds.core/export.h>
#include <openxds.core.base.h>
#include <openxds.core.threads.h>

#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace threads {
	extern "C" {
#endif

struct _IThread
{
	IThread*               (*free)( IThread* self );
	bool                    (*run)( IThread* self );
	bool                   (*wait)( IThread* self );
};

EXPORT	IThread* new_Thread( void*(*callback)(void*), void* aRunnable );

#ifdef __cplusplus
}
};};};
#endif

#endif
