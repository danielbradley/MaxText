/*
 *  Copyright (C) 2009 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_STDVECTOR_H
#define OPENXDS_CORE_ADT_STD_STDVECTOR_H

#include "openxds.core.adt.std.h"

#include <openxds.core.adt/IVector.h>
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


StdVector*       new_StdVector(void);
StdVector*      free_StdVector( StdVector* self );

void	         StdVector_add(       StdVector* self, int rank,       E*       anElement );
void	     StdVector_add_ref(       StdVector* self, int rank, const E*       anElement );
void	 StdVector_add_IObject(       StdVector* self, int rank,       IObject* anObject );

E*	             StdVector_set(       StdVector* self, int rank, const E*       anElement );
E*	      StdVector_removeFrom(       StdVector* self, int rank );

const E*         StdVector_get( const StdVector* self, int rank );
int             StdVector_size( const StdVector* self );
bool         StdVector_isEmpty( const StdVector* self );


	#ifdef __cplusplus
		};};};};};
	#endif
#endif
