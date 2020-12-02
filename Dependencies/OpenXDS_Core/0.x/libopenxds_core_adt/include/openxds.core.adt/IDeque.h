/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IDEQUE_H
#define OPENXDS_CORE_ADT_IDEQUE_H

#include "openxds.core.adt.h"
#include "openxds.core.adt/IPosition.h"

#include <openxds.core/types.h>
#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IDeque
{
	IDeque*      (*free)(       IDeque* self );

	void     (*addFirst)(       IDeque* self, E* e );
	void      (*addLast)(       IDeque* self, E* e );
	E*    (*removeFirst)(       IDeque* self );
	E*     (*removeLast)(       IDeque* self );
	const E*    (*first)( const IDeque* self );
	const E*     (*last)( const IDeque* self );
	int          (*size)( const IDeque* self );
	bool      (*isEmpty)( const IDeque* self );

};


	#ifdef __cplusplus
};};};
	#endif
#endif
