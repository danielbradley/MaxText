#include "openxds.core.adt.std/StdIterator.h"
#include "openxds.core.adt.std/StdSequence.h"
#include "openxds.core.adt.std/StdADTFactory.h"
#include "openxds.core.adt.std/StdPIterator.h"
#include "openxds.core.adt.std/StdSequenceNode.h"

#include <openxds.core/IObject.h>
#include <openxds.core.adt/IPosition.h>
#include <openxds.core.base/CRuntime.h>

#include <stdio.h>

static void    shuffleUp( StdSequence* self, long rank );
static void  shuffleDown( StdSequence* self, long rank );
static void       expand( StdSequence* self );
static bool    checkRank( const StdSequence* self, long index );
static bool checkRankAdd( const StdSequence* self, long index );
static bool       isFull( const StdSequence* self );

struct _StdSequence
{
	ISequence super;
	Node** V;
	long   N;
	long   f;
	long   b;
	bool   freeIObjects;
};

static long toIndex( const StdSequence* self, long rank )
{
	return (self->f + rank) % self->N;
}

static long toRank( const StdSequence* self, long index )
{
	return (self->N + index - self->f) % self->N;
}

static long increment( const StdSequence* self, long index )
{
	return (index + 1) % self->N;
}

static long decrement( const StdSequence* self, long index )
{
	return (self->N + index - 1) % self->N;
}

StdSequence* new_StdSequence()
{
	StdSequence* self = CRuntime_calloc( 1, sizeof( StdSequence ) );
	
	self->super.free        = (ISequence* (*)( ISequence*     )) free_StdSequence;
	self->super.freeAll     = (ISequence* (*)( ISequence*     )) freeAll_StdSequence;
	
	self->super.setFreeIObjects = (   void        (*)(       ISequence*, bool flag            )) StdSequence_setFreeIObjects;
	
	/* Deque */
	self->super.addFirst     = (      void        (*)(       ISequence*, E*                   )) StdSequence_addFirst;
	self->super.addLast      = (      void        (*)(       ISequence*, E*                   )) StdSequence_addLast;
	self->super.removeFirst  = (      E*          (*)(       ISequence*                       )) StdSequence_removeFirst;
	self->super.removeLast   = (      E*          (*)(       ISequence*                       )) StdSequence_removeLast;
	self->super.getFirst     = (const E*          (*)( const ISequence*                       )) StdSequence_getFirst;
	self->super.getLast      = (const E*          (*)( const ISequence*                       )) StdSequence_getLast;

	/* List */
	self->super.insertFirst  = (const IPosition*  (*)(       ISequence*, E*                   )) StdSequence_insertFirst;
	self->super.insertLast   = (const IPosition*  (*)(       ISequence*, E*                   )) StdSequence_insertLast;
	self->super.insertBefore = (const IPosition*  (*)(       ISequence*, const IPosition*, E* )) StdSequence_insertBefore;
	self->super.insertAfter  = (const IPosition*  (*)(       ISequence*, const IPosition*, E* )) StdSequence_insertAfter;
	self->super.replace      = (      E*          (*)(       ISequence*, const IPosition*, E* )) StdSequence_replace;
	self->super.remove       = (      E*          (*)(       ISequence*, const IPosition*     )) StdSequence_remove;
	self->super.first        = (const IPosition*  (*)( const ISequence*                       )) StdSequence_first;
	self->super.last         = (const IPosition*  (*)( const ISequence*                       )) StdSequence_last;
	self->super.prev         = (const IPosition*  (*)( const ISequence*, const IPosition*     )) StdSequence_previous;
	self->super.previous     = (const IPosition*  (*)( const ISequence*, const IPosition*     )) StdSequence_previous;
	self->super.next         = (const IPosition*  (*)( const ISequence*, const IPosition*     )) StdSequence_next;
	self->super.positions    = (      IPIterator* (*)( const ISequence*                       )) StdSequence_positions;
	self->super.elements     = (      IIterator*  (*)( const ISequence*                       )) StdSequence_elements;
	
	/* Vector */
	self->super.add          = (      void        (*)(       ISequence*, long, E*             )) StdSequence_add;
	self->super.set          = (      E*          (*)(       ISequence*, long, E*             )) StdSequence_set;
	self->super.removeFrom   = (      E*          (*)(       ISequence*, long                 )) StdSequence_removeFrom;
	self->super.get          = (const E*          (*)( const ISequence*, long                 )) StdSequence_get;
	
	/* Bridging */
	self->super.rankOf       = (      long        (*)( const ISequence*, const IPosition*     )) StdSequence_rankOf;
	self->super.atRank       = (const IPosition*  (*)( const ISequence*, long                 )) StdSequence_atRank;
	
	/* Common */
	self->super.size         = (      long        (*)( const ISequence*                       )) StdSequence_size;
	self->super.isEmpty      = (      bool        (*)( const ISequence*                       )) StdSequence_isEmpty;
	
	self->N = 1;
	self->V = CRuntime_calloc( self->N, sizeof( Node* ) );
	self->f = 0;
	self->b = 0;
	self->freeIObjects = 0;
	
	return self;
}

StdSequence* free_StdSequence( StdSequence* self )
{
	long i;
	long N = self->N;
	for ( i=0; i < N; i++ )
	{
		Node* v = self->V[i];
		if ( v )
		{
			if ( v->e )
			{
				if ( self->freeIObjects )
				{
					IObject* obj = (IObject*) v->e;
					v->e = obj->free( obj );
				}
				else
				{
					v->e = CRuntime_free( v->e );
				}
			}
			CRuntime_free( v );
		}
	}
	CRuntime_free( self->V );
	return CRuntime_free( self );
}

StdSequence* freeAll_StdSequence( StdSequence* self )
{
	long i;
	long N = self->N;
	for ( i=0; i < N; i++ )
	{
		Node* v = self->V[i];
		if ( v )
		{
			if ( v->e )
			{
				IObject* obj = (IObject*) v->e;
				v->e = obj->free( obj );
			}
			CRuntime_free( v );
		}
	}
	CRuntime_free( self->V );
	return CRuntime_free( self );
}

void StdSequence_setFreeIObjects( StdSequence* self, bool flag )
{
	self->freeIObjects = flag;
}

long StdSequence_size( const StdSequence* self )
{
	return (self->N - self->f + self->b) % self->N;
}

bool StdSequence_isEmpty( const StdSequence* self )
{
	return (self->f == self->b);
}

/*
static long toRank( StdSequence* self, long index )
{

}
*/

E* StdSequence_set( StdSequence* self, long r, E* e )
{
	E* ret = NULL;

	if ( checkRank( self, r ) )
	{
		long   i = toIndex( self, r ); /* (self->f + r) % self->N; */
		ret = self->V[i]->e;
		self->V[i]->e = e;
	}
	
	return ret;
}

IPosition* StdSequence_insertFirst( StdSequence* self, E* e )
{
	if ( isFull( self ) ) expand( self );
	
	self->f = decrement( self, self->f ); /* (self->N + self->f - 1) % self->N; */
	
	self->V[self->f] = new_StdSequenceNode( e, self->f );
	
	return (IPosition*) self->V[self->f];
}

IPosition* StdSequence_insertLast( StdSequence* self, E* e )
{
	IPosition* ret = NULL;
	
	if ( isFull( self ) ) expand( self );
	
	self->V[self->b] = new_StdSequenceNode( e, self->b );
	ret = (IPosition*) self->V[self->b];

	self->b = increment( self, self->b ); /* (self->b + 1) % self->N; */
	
	return ret;
}

E* StdSequence_removeFirst( StdSequence* self )
{
	E* e = self->V[self->f]->e;
	self->V[self->f] = CRuntime_free( self->V[self->f] );
	
	self->f = increment( self, self->f ); /* (self->f + 1) % self->N; */

	return e;
}

E* StdSequence_removeLast( StdSequence* self )
{
	E* e = NULL;
	long size = StdSequence_size( self );
	if ( 0 < size )
	{
		long r = size - 1;
		long i = toIndex( self, r );
		
		e          = StdSequenceNode_replaceElement( self->V[i], NULL );
		self->V[i] = free_StdSequenceNode( self->V[i] );
		self->b    = i;
	}
	return e;
}

void StdSequence_add( StdSequence* self, long r, E* e )
{
	checkRankAdd( self, r );
	
	if ( isFull( self ) ) expand( self );
	
	if ( 0 == r )
	{
		StdSequence_insertFirst( self, e );
	}
	else
	{
		long i = toIndex( self, r );
		shuffleUp( self, r );
		self->V[i] = new_StdSequenceNode( e, i );
		self->b    = increment( self, self->b );
	}
}

E* StdSequence_removeFrom( StdSequence* self, long r )
{
	E* ret = NULL;
	if ( checkRank( self, r ) )
	{
		if ( 0 == r )
		{
			ret = StdSequence_removeFirst( self );
		}
		else
		{
			long i = toIndex( self, r );
			ret   =  StdSequenceNode_replaceElement( self->V[i], NULL );
			self->V[i] = free_StdSequenceNode( self->V[i] );
			shuffleDown( self, r );
			self->b = decrement( self, self->b );
		}
	}
	return ret;
}

const E* StdSequence_get( const StdSequence* self, long r )
{
	const E* ret = NULL;
	if ( checkRank( self, r ) )
	{
		long i = toIndex( self, r );
		ret   = StdSequenceNode_getElement( self->V[i] );
	}
	return ret;
}

long StdSequence_rankOf( const StdSequence* self, const IPosition* p )
{
	StdSequenceNode* n = (StdSequenceNode*) p;
	long i   = StdSequenceNode_getIndex( n ); 
	return toRank( self, i ); /* (self->N + n->i - self->f) % self->N; */
}

const IPosition* StdSequence_atRank( const StdSequence* self, long r )
{
	const IPosition* p = NULL;
	if ( checkRank( self, r ) )
	{
		long i = toIndex( self, r );
		p = (const IPosition*) self->V[i];
	}
	return p;
}

const IPosition* StdSequence_insertBefore( StdSequence* self, const IPosition* p, E* e )
{
	long r = StdSequence_rankOf( self, p );
	StdSequence_add( self, r, e );
	return StdSequence_atRank( self, r );
}

const IPosition* StdSequence_insertAfter( StdSequence* self, const IPosition* p, E* e )
{
	long r = StdSequence_rankOf( self, p );
	StdSequence_add( self, r + 1, e );
	return StdSequence_atRank( self, r + 1 );
}

E* StdSequence_replace( StdSequence* self, const IPosition* p, E* e )
{
	long r = StdSequence_rankOf( self, p );
	return StdSequence_set( self, r, e );
}

E* StdSequence_remove( StdSequence* self, const IPosition* p )
{
	long r = StdSequence_rankOf( self, p );
	return StdSequence_removeFrom( self, r );
}

const IPosition* StdSequence_first( const StdSequence* self )
{
	return StdSequence_atRank( self, 0 );
}

const IPosition* StdSequence_last( const StdSequence* self )
{
	long n = StdSequence_size( self );
	return StdSequence_atRank( self, n - 1 );
}

const E* StdSequence_getFirst( const StdSequence* self )
{
	return StdSequence_get( self, 0 );
}

const E* StdSequence_getLast( const StdSequence* self )
{
	long n = StdSequence_size( self );
	return StdSequence_get( self, n - 1 );
}

const IPosition* StdSequence_previous( const StdSequence* self, const IPosition* p )
{
	long r = StdSequence_rankOf( self, p );
	return StdSequence_atRank( self, r - 1 );
}

const IPosition* StdSequence_next( const StdSequence* self, const IPosition* p )
{
	long r = -1;
	if ( p ) r = StdSequence_rankOf( self, p );
	return StdSequence_atRank( self, r + 1 );
}

void StdSequence_addFirst( StdSequence* self, E* e )
{
	StdSequence_insertFirst( self, e );
}

void StdSequence_addLast( StdSequence* self, E* e )
{
	StdSequence_insertLast( self, e );
}

IPIterator* StdSequence_positions( const StdSequence* self )
{
	StdPIterator* positions = new_StdPIterator();
	
	long n = StdSequence_size( self );
	long r;
	const IPosition* p = NULL;
	for ( r=0; r < n; r++ )
	{
		p = StdSequence_atRank( self, r );
		StdPIterator_addPosition( positions, p );
	}
	return (IPIterator*) positions;
}

IIterator* StdSequence_elements( const StdSequence* self )
{
	StdIterator* elements = new_StdIterator();

	long n = StdSequence_size( self );
	long r;
	const IPosition* p = NULL;
	for ( r=0; r < n; r++ )
	{
		p = StdSequence_atRank( self, r );
		const void* e = p->getElement( p );
		StdIterator_addElement( elements, e );
	}

	return (IIterator*) elements;
}

void shuffleUp( StdSequence* self, long rank )
{
	long n = StdSequence_size( self );
	
	long r;
	for ( r=n-1; r >= rank; r-- )
	{
		long src  = toIndex( self, r ); /* (f + r) % N; */
		long dest = toIndex( self, r+1 ); /*(f + r + 1) % N; */
		
		self->V[dest] = self->V[src];
		self->V[dest]->i = dest;
		self->V[src] = NULL;
	}
}

void shuffleDown( StdSequence* self, long rank )
{
	long n = StdSequence_size( self );

	long r;
	for ( r=rank; r < n-1; r++ )
	{
		long dest = toIndex( self, r );
		long src  = toIndex( self, r+1 );
		
		self->V[dest] = self->V[src];
		self->V[dest]->i = dest;

		self->V[src] = NULL;
	}
}

void expand( StdSequence* self )
{
	long N = self->N;
	long N2 = N * 2;
	Node** V2 = CRuntime_calloc( N2, sizeof( Node* ) );

	long n = StdSequence_size( self );
	long r;
	for ( r=0; r < n; r++ )
	{
		long i = toIndex( self, r );
		V2[r] = self->V[i];
		V2[r]->i = r;
		self->V[i] = NULL;
	}

	CRuntime_free( self->V );
	self->V = V2;
	self->N = N2;
	self->f = 0;
	self->b = n;
}

bool checkRank( const StdSequence* self, long r )
{
	long n = StdSequence_size( self );

	if ( (r < 0) || (n <= r ) )
	{
/*		fprintf( stderr, "StdSequence::checkRank: invalid rank." ); */
/*		abort(); */
		return 0;
	} else {
		return 1;
	}
}

bool checkRankAdd( const StdSequence* self, long r )
{
	long n = StdSequence_size( self );

	if ( (r < 0) || (n < r ) )
	{
/*		fprintf( stderr, "StdSequence::checkRankAdd: invalid rank." ); */
/*		abort(); */
		return 0;
	} else {
		return 1;
	}
}

bool isFull( const StdSequence* self )
{
	long n = StdSequence_size( self );

	return (n == (self->N - 1));
}
