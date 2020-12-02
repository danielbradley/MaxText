/*
 *  Copyright (C) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IDICTIONARY_H
#define OPENXDS_CORE_ADT_IDICTIONARY_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IDictionary
{
	IDictionary*              (*free)( IDictionary* self );

	const IEntry*           (*insert)( IDictionary* self, const IKey* key, E* value );
	const IEntry*        (*insertRef)( IDictionary* self, const IKey* key, const E* value );
	const IEntry*     (*insertObject)( IDictionary* self, const IKey* key, IObject* anObject );
	const IEntry*  (*insertObjectRef)( IDictionary* self, const IKey* key, const IObject* anObject );
	const IEntry*      (*insertValue)( IDictionary* self, const IKey* key, IValue* anObject );

	E*                      (*remove)( IDictionary* self, const IEntry* entry );

	const IEntry*             (*find)( const IDictionary* self, const IKey* key );
	const IEntry*       (*startsWith)( const IDictionary* self, const IKey* key );
	
	IEIterator*            (*findAll)( const IDictionary* self, const IKey* key );
	IEIterator*            (*entries)( const IDictionary* self );
	IIterator*              (*values)( const IDictionary* self );

	bool               (*containsKey)( const IDictionary* self, const IKey* key );
	bool         (*containsKeyPrefix)( const IDictionary* self, const IKey* key );

	int                       (*size)( const IDictionary* self );
	bool                   (*isEmpty)( const IDictionary* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
