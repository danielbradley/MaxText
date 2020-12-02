/*
 *  Copyright (C) 2009 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_STDSTACK_H
#define OPENXDS_CORE_ADT_STD_STDSTACK_H

#include "openxds.core.adt.std.h"

#include <openxds.core.adt/IStack.h>
#include <openxds.core/types.h>
#include <openxds.core/export.h>
#include <openxds.core/IObject.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif


EXPORT	StdStack*             new_StdStack(void);
EXPORT	StdStack*            free_StdStack(       StdStack* self );

/*	Implements openxds/core/adt/Stack */
EXPORT	void                 StdStack_push(       StdStack* self, E* anElement );
EXPORT	void           StdStack_pushObject(       StdStack* self, IObject* anElement );
EXPORT	E*                    StdStack_pop(       StdStack* self );

EXPORT	const E*              StdStack_top( const StdStack* self );
EXPORT	int                  StdStack_size( const StdStack* self );
EXPORT	bool              StdStack_isEmpty( const StdStack* self );


	#ifdef __cplusplus
		};};};};};
	#endif
#endif
