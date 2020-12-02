#include "openxds.core.adt.std/StdADTFactory.h"
#include "openxds.core.adt.std/StdVector.h"

#include <openxds.core.adt/IValue.h>
#include <openxds.core.base/CRuntime.h>

static const int DEFAULT_CAPACITY = 1;

struct _StdVector
{
	IVector   super;
	IValue**  V;
	int       f;
	int       b;
	int       N;
};

static void enlarge( StdVector* self )
{
	IValue** V = self->V;
	int      f = self->f;
	int      N = self->N;
	int      n = StdVector_size( self );

	int N2 = N * 2;
	
	IValue** V2 = CRuntime_calloc( N2, sizeof( IValue* ) );
	
	int r;
	for ( r=0; r < n; r++ )
	{
		int i = (f + r) % N;
		V2[r] = V[i];
	}
	
	self->f = 0;
	self->b = n;
	self->N = N2;
	self->V = CRuntime_free( self->V );
	self->V = V2;
}

StdVector* new_StdVector()
{
	StdVector* self = CRuntime_calloc( 1, sizeof( StdVector ) );
	
	self->super.free       = (      IVector* (*)(       IVector*                      )) free_StdVector;

	self->super.add        = (      void     (*)(       IVector*, int,       E*       )) StdVector_add;
	self->super.addRef     = (      void     (*)(       IVector*, int, const E*       )) StdVector_add_ref;
	self->super.addObject  = (      void     (*)(       IVector*, int,       IObject* )) StdVector_add_IObject;

	self->super.set        = (      E*       (*)(       IVector*, int, const E*       )) StdVector_set;
	self->super.removeFrom = (      E*       (*)(       IVector*, int                 )) StdVector_removeFrom;

	self->super.get        = (const E*       (*)( const IVector*, int                 )) StdVector_get;
	self->super.size       = (      int      (*)( const IVector*                      )) StdVector_size;
	self->super.isEmpty    = (      bool     (*)( const IVector*                      )) StdVector_isEmpty;

	self->N = DEFAULT_CAPACITY;
	self->V = CRuntime_calloc( self->N, sizeof( IValue* ) );
	self->f = 0;
	self->b = 0;
	
	return self;
}

StdVector* free_StdVector( StdVector* self )
{
	int      N = self->N;
	IValue** V = self->V;
	
	int      i;
	for ( i=0; i < N; i++ )
	{
		if ( NULL != V[i] ) V[i]->free( V[i] );
	}
	CRuntime_free( self->V );
	return CRuntime_free( self );
}

bool StdVector_isEmpty( const StdVector* self )
{
	return (self->f == self->b);
}

int StdVector_size( const StdVector* self )
{
	return (self->N - self->f + self->b) % self->N;
}

static bool isFull( const StdVector* self )
{
	return ( StdVector_size( self ) == (self->N - 1) );
}

E* StdVector_set( StdVector* self, int r, const E* element )
{
	E* ret = NULL;

	int      f = self->f;
	int      N = self->N;
	IValue** V = self->V;
	
	if ( (r < 0) || (StdVector_size( self ) <= r) ) abort();
	
	int     i   = (f + r) % N;
	IValue* v   = V[i];
	        ret = v->replaceValue( v, (E*) element );
	
	return ret;
}

const E* StdVector_get( const StdVector* self, int r )
{
	int      f = self->f;
	int      N = self->N;
	IValue** V = self->V;
	
	if ( (r < 0) || (StdVector_size( self ) <= r) ) abort();

	int i = (f + r) % N;
	return V[i]->getValue( V[i] );
}

static void addValue( StdVector* self, int r, IValue* v )
{
	int n = StdVector_size( self );
	
	if ( (r < 0) || (n < r) ) abort();

	if ( isFull( self ) ) enlarge( self );

	int      f = self->f;
    int      b = self->b;
	int      N = self->N;
	IValue** V = self->V;

	if ( 0 == r )
	{
		f = self->f = (N + f - 1) % N;
		V[f] = v;
	}
	else
	{
		E* e = v->replaceValue( v, NULL );
		int i;
		for ( i=r; i < n; i++ )
		{
			e = StdVector_set( self, r, e );
		}
		v->replaceValue( v, e );
		V[b] = v;
		self->b = (b + 1) % N;
	}
}

void StdVector_add( StdVector* self, int r, E* e )
{
	addValue( self, r, StdADTFactory_createValue( e ) );
}

void StdVector_add_ref( StdVector* self, int r, const E* e )
{
	addValue( self, r, StdADTFactory_createValue_ref( e ) );
}

void StdVector_add_IObject( StdVector* self, int r, IObject* e )
{
	addValue( self, r, StdADTFactory_createValue_IObject( e ) );
}

E* StdVector_removeFrom( StdVector* self, int r )
{
	E* e = NULL;

	IValue** V = self->V;
	int      f = self->f;
    int      b = self->b;
	int      N = self->N;
	int      n = StdVector_size( self );

	if ( (r < 0) || (n <= r) ) abort();
	
	if ( 0 == r )
	{
		IValue* v = V[f];
		e = v->replaceValue( v, NULL );
		V[f] = v = v->free( v );
		
		self->f = f = (f + 1) % N;
	}
	else
	{
		int i;
		for ( i = n-1; i >= r; i-- )
		{
			e = StdVector_set( self, i, e );
		}
		self->b = b = (N + b - 1) % N;
		V[b] = V[b]->free( V[b] );
	}
	return e;
} 
