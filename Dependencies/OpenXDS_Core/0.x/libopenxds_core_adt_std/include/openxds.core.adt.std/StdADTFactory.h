/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_STDADTFACTORY_H
#define OPENXDS_CORE_ADT_STD_STDADTFACTORY_H

#include "openxds.core.adt.std.h"

#include <openxds.core/export.h>
#include <openxds.core/types.h>

#include <openxds.core.adt/ADTFactory.h>
#include <openxds.core.adt.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif

struct _StdADTFactory
{
	ADTFactory super;
};

ADTFactory*      new_StdADTFactory(void);
StdADTFactory*  free_StdADTFactory( StdADTFactory* self );

IKey*               StdADTFactory_createKey( const char* key );

IValue*               StdADTFactory_createValue( E* value );
IValue*           StdADTFactory_createValue_ref( const E* value );
IValue*       StdADTFactory_createValue_IObject( IObject* value );

IEntry*               StdADTFactory_createEntry( const IKey* key, IValue* value );

IStack*               StdADTFactory_createStack(void);
IString*             StdADTFactory_createString( const char* str );
IList*                 StdADTFactory_createList(void);
IMap*                   StdADTFactory_createMap(void);
IDictionary*     StdADTFactory_createDictionary(void);
IDictionary*     StdADTFactory_createSortedDictionary(void);
IVector*             StdADTFactory_createVector(void);
ISequence*         StdADTFactory_createSequence(void);
ITree*                 StdADTFactory_createTree(void);

	#ifdef __cplusplus
		};};};};};
	#endif
#endif
