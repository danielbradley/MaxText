/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_ITERATOR_H
#define OPENXDS_CORE_ADT_STD_ITERATOR_H

#include <openxds.core/export.h>
#include <openxds.core/types.h>

#include <openxds.core.adt/IIterator.h>
#include <openxds.core.adt.std.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif


StdIterator*  new_StdIterator(void);
StdIterator* free_StdIterator( StdIterator* self );

/*	Implements openxds/core/adt/IPosition */
void        StdIterator_reset( StdIterator* self );
bool      StdIterator_hasNext( const StdIterator* self );
const void*  StdIterator_next( StdIterator* self );

/*	For population */
void StdIterator_addElement( StdIterator* self, const void* element );


	#ifdef __cplusplus
		};};};};};
	#endif
#endif
