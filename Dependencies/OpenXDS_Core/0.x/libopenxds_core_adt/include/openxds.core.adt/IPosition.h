/*
 *  Copyright (c) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IPOSITION_H
#define OPENXDS_CORE_ADT_IPOSITION_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IPosition
{
	IObject super;
	void*       (*free)( IPosition* self );
	const E* (*getElement)( const IPosition* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
