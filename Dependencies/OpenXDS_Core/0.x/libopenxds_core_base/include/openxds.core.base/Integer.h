/*
 *  Copyright (c) 2008-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_INTEGER_H
#define OPENXDS_CORE_BASE_INTEGER_H

#include "openxds.core/export.h"
#include "openxds.core/types.h"
#include "openxds.core.base.h"

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif

struct _IInteger
{
	IInteger*     (*free)(       IInteger* self );
	    void  (*setValue)(       IInteger* self, int aValue );
	     int  (*getValue)( const IInteger* self );
};

EXPORT	IInteger* new_Integer( int aValue );

	#ifdef __cplusplus
		};};};};
	#endif
#endif
