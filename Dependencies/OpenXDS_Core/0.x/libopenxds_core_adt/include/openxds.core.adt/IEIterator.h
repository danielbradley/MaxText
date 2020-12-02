/*
 *  Copyright (c) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IEITERATOR_H
#define OPENXDS_CORE_ADT_IEITERATOR_H

#include "openxds.core.adt.h"
#include "openxds.core.adt/IEntry.h"
#include <openxds.core/types.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IEIterator
{
	IEIterator*   (*free)( IEIterator* self );
	void         (*reset)( IEIterator* self );
	const IEntry* (*next)( IEIterator* self );

	bool       (*hasNext)( const IEIterator* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
