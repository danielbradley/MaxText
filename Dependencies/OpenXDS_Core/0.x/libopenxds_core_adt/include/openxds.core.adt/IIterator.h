/*
 *  Copyright (c) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IITERATOR_H
#define OPENXDS_CORE_ADT_IITERATOR_H

#include "openxds.core.adt.h"
#include <openxds.core/types.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IIterator
{
	IIterator*     (*free)( IIterator* self );
	void          (*reset)( IIterator* self );
	const E*       (*next)( IIterator* self );

	bool        (*hasNext)( const IIterator* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
