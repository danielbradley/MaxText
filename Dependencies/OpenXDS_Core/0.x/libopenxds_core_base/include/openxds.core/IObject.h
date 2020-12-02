/*
 *  Copyright (c) 2008-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_IOBJECT_H
#define OPENXDS_CORE_IOBJECT_H

#include "openxds.core.h"

	#ifdef __cplusplus
namespace openxds {
	namespace core {
	#endif


struct _IObject
{
	void* (*free)( IObject* o );
};


	#ifdef __cplusplus
};};
	#endif
#endif
