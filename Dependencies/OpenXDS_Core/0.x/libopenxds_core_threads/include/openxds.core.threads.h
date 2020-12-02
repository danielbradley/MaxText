/*
 *  Copyright (C) 2008-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_THREADS_H
#define OPENXDS_CORE_THREADS_H

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace threads {
	#endif

	typedef struct _IConditionVariable IConditionVariable;
	typedef struct _IMutex             IMutex;
	typedef struct _ISemaphore         ISemaphore;
	typedef struct _IThread            IThread;
	
	#ifdef __cplusplus
};};};
	#endif
#endif
