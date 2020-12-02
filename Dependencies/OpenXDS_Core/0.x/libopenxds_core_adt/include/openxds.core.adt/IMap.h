/*
 *  Copyright (C) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IMAP_H
#define OPENXDS_CORE_ADT_IMAP_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IMap
{
	IMap*                 (*free)( IMap* self );

	E*                     (*put)( IMap* self, const IKey* key, E*       value );
	E*               (*putObject)( IMap* self, const IKey* key, IObject* value );
	E*                  (*putRef)( IMap* self, const IKey* key, const E* value );
	E*                  (*remove)( IMap* self, const IKey* key );

	const E*               (*get)( const IMap* self, const IKey* key );
	IIterator*            (*keys)( const IMap* self );
	IIterator*          (*values)( const IMap* self );

	int                   (*size)( const IMap* self );
	bool               (*isEmpty)( const IMap* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
