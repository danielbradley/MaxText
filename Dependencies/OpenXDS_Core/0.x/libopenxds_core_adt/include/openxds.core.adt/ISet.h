/*
 *  Copyright (C) 2007-2009 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_ISET_H
#define OPENXDS_CORE_ADT_ISET_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _ISet
{
	ISet*              (*free)( ISet* s );
	void                (*add)( ISet* self, const E* anElement );
	const E*            (*get)( ISet* self, unsigned int index );
	void          (*unionWith)( ISet* self, const ISet* aSet );

	IObject*       (*contains)( const IStack* s, const E* anElement );
	int                (*size)( const IStack* s );
	bool            (*isEmpty)( const IStack* s );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
