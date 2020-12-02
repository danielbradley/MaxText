/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_INTEGER_PRIVATE_H
#define OPENXDS_CORE_BASE_INTEGER_PRIVATE_H

#include "openxds.core.base/Integer.h"
#include "openxds.core/export.h"

#include <stdarg.h>

	#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace base {
	extern "C"
	{
	#endif

typedef struct _Integer Integer;

EXPORT  Integer*     free_Integer( Integer* self );
EXPORT  void     Integer_setValue( Integer* self, int aValue );
EXPORT  int      Integer_getValue( const Integer* self );

	#ifdef __cplusplus
	}
	};};};
	#endif
#endif
