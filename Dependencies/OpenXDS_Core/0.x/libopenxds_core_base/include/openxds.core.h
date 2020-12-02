/*
 *  Copyright (c) 2008-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_H
#define OPENXDS_CORE_H

#include "openxds.core/export.h"
#include "openxds.core/types.h"

	#ifdef __cplusplus
namespace openxds {
	namespace core {
	#else
		#ifndef BOOLEAN
		#define BOOLEAN
			typedef int bool;
		#endif
	#endif

	typedef struct _IObject IObject;
	
	#ifdef __cplusplus
};};
	#endif
#endif
