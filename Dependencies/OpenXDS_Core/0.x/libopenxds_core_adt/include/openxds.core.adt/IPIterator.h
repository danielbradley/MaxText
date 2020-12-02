/*
 *  Copyright (c) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IPITERATOR_H
#define OPENXDS_CORE_ADT_IPITERATOR_H

#include "openxds.core.adt.h"
#include "openxds.core.adt/IPosition.h"
#include <openxds.core/types.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IPIterator
{
	IPIterator*      (*free)( IPIterator* self );
	void            (*reset)( IPIterator* self );
	const IPosition* (*next)( IPIterator* self );

	bool          (*hasNext)( const IPIterator* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
