/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_STDEITERATOR_H
#define OPENXDS_CORE_ADT_STD_STDEITERATOR_H

#include <openxds.core/export.h>
#include <openxds.core/types.h>

#include <openxds.core.adt/IEIterator.h>
#include <openxds.core.adt.std.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif


StdEIterator*  new_StdEIterator(void);
StdEIterator* free_StdEIterator( StdEIterator* self );

/*	Implements openxds/core/adt/IPosition */
void         StdEIterator_reset( StdEIterator* self );
const IEntry* StdEIterator_next( StdEIterator* self );

bool       StdEIterator_hasNext( const StdEIterator* self );

/*	For population */
void      StdEIterator_addEntry( StdEIterator* self, const IEntry* e );


	#ifdef __cplusplus
		};};};};};
	#endif
#endif
