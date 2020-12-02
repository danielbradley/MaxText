/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_STDPITERATOR_H
#define OPENXDS_CORE_ADT_STD_STDPITERATOR_H

#include <openxds.core/export.h>
#include <openxds.core/types.h>

#include <openxds.core.adt/IPIterator.h>
#include <openxds.core.adt.std.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif


StdPIterator*       new_StdPIterator(void);
StdPIterator*      free_StdPIterator( StdPIterator* self );

/*	Implements openxds/core/adt/IPosition */
void              StdPIterator_reset( StdPIterator* self );
bool            StdPIterator_hasNext( const StdPIterator* self );
const IPosition*   StdPIterator_next( StdPIterator* self );

/*	For population */
void StdPIterator_addPosition( StdPIterator* self, const IPosition* p );


	#ifdef __cplusplus
		};};};};};
	#endif
#endif
