#include "openxds.core.adt.std/StdADTFactory.h"

#include "openxds.core.adt.std/StdDictionary.h"
#include "openxds.core.adt.std/StdEntry.h"
#include "openxds.core.adt.std/StdKey.h"
#include "openxds.core.adt.std/StdList.h"
#include "openxds.core.adt.std/StdMap.h"
#include "openxds.core.adt.std/StdStack.h"
#include "openxds.core.adt.std/StdString.h"
#include "openxds.core.adt.std/StdValue.h"
#include "openxds.core.adt.std/StdVector.h"
#include "openxds.core.adt.std/StdSequence.h"
#include "openxds.core.adt.std/StdTree.h"

ADTFactory* new_StdADTFactory()
{
	StdADTFactory* self = CRuntime_calloc( 1, sizeof( StdADTFactory ) );
	self->super.free             = (ADTFactory*  (*)(ADTFactory*          )) free_StdADTFactory;
	self->super.createKey        = (IKey*        (*)(const char*          )) StdADTFactory_createKey;
	self->super.createValue      = (IValue*      (*)(E*                   )) StdADTFactory_createValue;
	self->super.createEntry      = (IEntry*      (*)(const IKey*, IValue* )) StdADTFactory_createValue;

	self->super.createStack      = (IStack*      (*)(                     )) StdADTFactory_createStack;
	self->super.createString     = (IString*     (*)(const char*          )) StdADTFactory_createString;
	self->super.createList       = (IList*       (*)(                     )) StdADTFactory_createList;
	self->super.createMap        = (IMap*        (*)(                     )) StdADTFactory_createMap;
	self->super.createDictionary = (IDictionary* (*)(                     )) StdADTFactory_createDictionary;
	self->super.createVector     = (IVector*     (*)(                     )) StdADTFactory_createVector;
	self->super.createSequence   = (ISequence*   (*)(                     )) StdADTFactory_createSequence;
	self->super.createTree       = (ITree*       (*)(                     )) StdADTFactory_createTree;
	
	return (ADTFactory*) self;
}

StdADTFactory* free_StdADTFactory( StdADTFactory* self )
{
	return CRuntime_free( self );
}

IKey* StdADTFactory_createKey( const char* key )
{
	return (IKey*) new_StdKey( key );
}

IValue* StdADTFactory_createValue( void* value )
{
	return (IValue*) new_StdValue( value );
}

IValue* StdADTFactory_createValue_ref( const void* value )
{
	return (IValue*) new_StdValue_ref( value );
}

IValue* StdADTFactory_createValue_IObject( IObject* value )
{
	return (IValue*) new_StdValue_IObject( value );
}

IEntry* StdADTFactory_createEntry( const IKey* key, IValue* value )
{
	StdEntry* entry = new_StdEntry( key, value );
	return (IEntry*) entry;
}

IStack* StdADTFactory_createStack()
{
	return (IStack*) new_StdStack();
}

IString* StdADTFactory_createString( const char* str )
{
	return (IString*) new_StdString( str );
}

IList* StdADTFactory_createList()
{
	return (IList*) new_StdList();
}

IMap* StdADTFactory_createMap()
{
	return (IMap*) new_StdMap();
}

IDictionary* StdADTFactory_createDictionary()
{
	return (IDictionary*) new_StdDictionary();
}

IDictionary* StdADTFactory_createSortedDictionary()
{
	return (IDictionary*) new_StdSortedDictionary();
}

IVector* StdADTFactory_createVector()
{
	return (IVector*) new_StdVector();
}

ISequence* StdADTFactory_createSequence()
{
	return (ISequence*) new_StdSequence();
}

ITree* StdADTFactory_createTree()
{
	return (ITree*) new_StdTree();
}
