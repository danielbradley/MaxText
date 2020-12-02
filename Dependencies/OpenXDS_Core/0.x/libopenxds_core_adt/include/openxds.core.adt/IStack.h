/*
 *  Copyright (C) 2007-2009 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_ISTACK_H
#define OPENXDS_CORE_ADT_ISTACK_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IStack
{
	IStack*       (*free)( IStack* s );
	void          (*push)( IStack* s, E* element );
	void    (*pushObject)( IStack* s, IObject* element );

	E*             (*pop)( IStack* s );

	const E*       (*top)( const IStack* s );
	int           (*size)( const IStack* s );
	bool       (*isEmpty)( const IStack* s );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
