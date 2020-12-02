/*
 *  Copyright (C) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_ICOMPARITOR_H
#define OPENXDS_CORE_ADT_ICOMPARITOR_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif



struct _IComparitor
{
	IObject super;
	void*        (*free)( IKey* k );
	int   (*compareKeys)( const IKey* k, const IKey* k2 );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
