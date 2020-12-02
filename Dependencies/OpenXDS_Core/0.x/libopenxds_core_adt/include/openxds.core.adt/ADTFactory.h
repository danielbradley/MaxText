/*
 *  Copyright (C) 2007-2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_ADTFACTORY_H
#define OPENXDS_CORE_ADT_ADTFACTORY_H

#include "openxds.core.adt.h"

#include <openxds.core/export.h>
#include <openxds.core/types.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif

struct _ADTFactory
{
	ADTFactory*                    (*free)( ADTFactory* self );

	IKey*                     (*createKey)( const char* key );
	IValue*                 (*createValue)( E* value );
	IEntry*                 (*createEntry)( const IKey* key, IValue* value );

	IStack*                 (*createStack)();
	IString*               (*createString)( const char* str );
	IList*                   (*createList)();
	IMap*                     (*createMap)();
	IDictionary*       (*createDictionary)();
	IVector*               (*createVector)();
	ISequence*           (*createSequence)();
	ITree*                   (*createTree)();


/*	IQueue*                 (*createQueue)( ADTFactory* self ); */
/*	IVector*               (*createVector)( ADTFactory* self ); */
/*	ISequence*           (*createSequence)( ADTFactory* self ); */
/*	IPriorityQueue* (*createPriorityQueue)( ADTFactory* self ); */
/*	IGraph*                 (*createGraph)( ADTFactory* self ); */
/*	ISearch*               (*createSearch)( ADTFactory* self ); */

/*	ISort*                   (*createSort)( ADTFactory* self ); */
/*	IHashFunction*   (*createHashFunction)( ADTFactory* self ); */
/*	IValue*                 (*createValue)( ADTFactory* self ); */
};

/* EXPORT	ADTFactory* new_ADTFactory( const char* module_location ); */
/* EXPORT	void*       free_ADTFactory( ADTFactory* factory ); */

	#ifdef __cplusplus
};};};
	#endif

#endif
