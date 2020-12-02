/*
 *  Copyright (C) 2004-2009 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_THREADS_SEMAPHORE_H
#define OPENXDS_CORE_THREADS_SEMAPHORE_H

#include <openxds.core/export.h>
#include <openxds.core.base.h>
#include <openxds.core.threads.h>

#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace threads {
	extern "C" {
#endif

EXPORT	Semaphore* new_Semaphore();
EXPORT	Semaphore* new_Semaphore_value( int start );
EXPORT	void free_Semaphore( Semaphore* self );

EXPORT	void Semaphore_wait( Semaphore* self );
EXPORT	void Semaphore_signal( Semaphore* self );

#ifdef __cplusplus
}
};};};
#endif

#endif
