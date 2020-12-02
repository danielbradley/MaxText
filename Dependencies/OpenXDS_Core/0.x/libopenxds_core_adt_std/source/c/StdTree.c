#include "openxds.core.adt.std/StdTree.h"

#include "openxds.core.adt.std/StdTreeNode.h"

#include <openxds.core.h>
#include <openxds.core.adt.h>
#include <openxds.core.adt/ITree.h>
#include <openxds.core.base/CRuntime.h>

struct _StdTree
{
	ITree     super;
	TreeNode* root;
	int       size;
};

StdTree* new_StdTree()
{
	StdTree* self = CRuntime_calloc( 1, sizeof( StdTree ) );
	self->super.free          = (       ITree*      (*)(       ITree*                                                  )) free_StdTree;
	self->super.freeAll       = (       ITree*      (*)(       ITree*                                                  )) freeAll_StdTree;
	self->super.addRoot       = ( const IPosition*  (*)(       ITree*,       E*                                        )) StdTree_addRoot;
	self->super.addChild      = ( const IPosition*  (*)(       ITree*, const IPosition* p, E*                          )) StdTree_addChild;
	self->super.insertChildAt = ( const IPosition*  (*)(       ITree*, const IPosition* p, E*, long i                  )) StdTree_insertChildAt;
	self->super.addSubtree    = ( const IPosition*  (*)(       ITree*, const IPosition* p, ITree* t                    )) StdTree_addSubtree;
	self->super.replace       = (       E*          (*)(       ITree*, const IPosition* p, E*                          )) StdTree_replace;
	self->super.remove        = (       E*          (*)(       ITree*, const IPosition* p                              )) StdTree_remove;
	self->super.removeAsTree  = (       ITree*      (*)(       ITree*, const IPosition* p                              )) StdTree_removeAsTree;
	self->super.swapSubtrees  = (       void        (*)(       ITree*, const IPosition* p, ITree*, const IPosition* p2 )) StdTree_swapSubtrees;
	self->super.root          = ( const IPosition*  (*)( const ITree*                                                  )) StdTree_root;
	self->super.parent        = ( const IPosition*  (*)( const ITree*, const IPosition* p                              )) StdTree_parent;
	self->super.child         = ( const IPosition*  (*)( const ITree*, const IPosition* p, long i                      )) StdTree_child;
	self->super.isRoot        = (       bool        (*)( const ITree*, const IPosition* p                              )) StdTree_isRoot;
	self->super.isInternal    = (       bool        (*)( const ITree*, const IPosition* p                              )) StdTree_isInternal;
	self->super.isExternal    = (       bool        (*)( const ITree*, const IPosition* p                              )) StdTree_isExternal;
	self->super.hasParent     = (       bool        (*)( const ITree*, const IPosition* p                              )) StdTree_hasParent;
	self->super.hasChild      = (       bool        (*)( const ITree*, const IPosition* p, long i                      )) StdTree_hasChild;
	self->super.children      = (       IPIterator* (*)( const ITree*, const IPosition* p                              )) StdTree_children;

	self->super.nrChildren    = (       long        (*)( const ITree*, const IPosition* p                              )) StdTree_nrChildren;
	self->super.nrOfChild     = (       long        (*)( const ITree*, const IPosition* p                              )) StdTree_nrOfChild;
	self->super.size          = (       long        (*)( const ITree*                                                  )) StdTree_size;
	self->super.isEmpty       = (       bool        (*)( const ITree*                                                  )) StdTree_isEmpty;

	self->root = NULL;
	self->size = 0;
	
	return self;
}

StdTree* free_StdTree( StdTree* self )
{
	if ( self->root ) free_StdTreeNode( self->root );

	return CRuntime_free( self );
}

StdTree* freeAll_StdTree( StdTree* self )
{
	if ( self->root ) freeAll_StdTreeNode( self->root );

	return CRuntime_free( self );
}

const IPosition* StdTree_addRoot( StdTree* self, E* value )
{
	IPosition* p = NULL;
	if ( !self->root )
	{
		self->size = 1;
		self->root = new_StdTreeNode( NULL, value );
		p = (IPosition*) self->root;
	}
	return p;
}

const IPosition* StdTree_addChild( StdTree* self, const IPosition* p, E* value )
{
	IPosition* child = NULL;
	if ( p )
	{
		self->size++;
		TreeNode* node = (TreeNode*) p;
		child = (IPosition*) StdTreeNode_addChild( node, value );
	}
	return child;
}

const IPosition* StdTree_insertChildAt( StdTree* self, const IPosition* p, E* value, long i )
{
	IPosition* child = NULL;
	if ( p )
	{
		TreeNode* node = (TreeNode*) p;
		child = (IPosition*) StdTreeNode_addChildAt( node, value, i );

		if ( child ) self->size++;
	}
	return child;
}

const IPosition* StdTree_addSubtree( StdTree* self, const IPosition* p, ITree* t )
{
	IPosition* child = NULL;
	if ( p )
	{
		StdTree* tree = (StdTree*) t;
		self->size += tree->size;

		if ( tree->root )
		{
			TreeNode* node = (TreeNode*) p;
			child = (IPosition*) StdTreeNode_addNode( node, tree->root );
			tree->root = NULL;
			tree->size = 0;
		}
		t->free( t );
	}
	return child;
}

E* StdTree_replace( StdTree* self, const IPosition* p, E* e )
{
	TreeNode* node = (TreeNode*) p;
	return StdTreeNode_replace( node, e );
}

E* StdTree_remove( StdTree* self, const IPosition* p )
{
	E* e = StdTreeNode_extract( (TreeNode*) p );
	if ( self->root == (TreeNode*) p ) self->root = NULL;
	
	if ( e )
	{
		self->size--;
	}
	return e;
}

StdTree*
StdTree_removeAsTree( StdTree* self, const IPosition* p )
{
	StdTree* tree = new_StdTree();
	tree->root = StdTreeNode_extractWithChildren( (TreeNode*) p );
	
	self->size = StdTreeNode_countDescendents( self->root );
	tree->size = StdTreeNode_countDescendents( tree->root );
	
	return tree;
}

void
StdTree_swapSubtrees( StdTree* self, const IPosition* p1, StdTree* tree, const IPosition* p2 )
{
	TreeNode* a = (TreeNode*) p1;
	TreeNode* b = (TreeNode*) p2;
	
	StdTreeNode_swap( a, b );
	
	self->size = StdTreeNode_countDescendents( self->root );
	tree->size = StdTreeNode_countDescendents( tree->root );
}

const IPosition* StdTree_root( const StdTree* self )
{
	return (const IPosition*) self->root;
}

const IPosition* StdTree_parent( const StdTree* self, const IPosition* p )
{
	TreeNode* node = (TreeNode*) p;
	return (IPosition*) StdTreeNode_getParent( node );
}

const IPosition* StdTree_child( const StdTree* self, const IPosition* p, long i )
{
	TreeNode* node = (TreeNode*) p;
	return (IPosition*) StdTreeNode_getChild( node, i );
}

bool StdTree_isRoot( const StdTree* self, const IPosition* p )
{
	return (((TreeNode*)p) == self->root);
}

bool StdTree_isInternal( const StdTree* self, const IPosition* p )
{
	return !StdTreeNode_isExternal( (TreeNode*) p );
}

bool StdTree_isExternal( const StdTree* self, const IPosition* p )
{
	return StdTreeNode_isExternal( (TreeNode*) p );
}

bool StdTree_hasParent( const StdTree* self, const IPosition* p )
{
	return StdTreeNode_hasParent( (TreeNode*) p );
}

bool StdTree_hasChild( const StdTree* self, const IPosition* p, long i )
{
	return StdTreeNode_hasChild( (TreeNode*) p, i );
}

IPIterator* StdTree_children( const StdTree* self, const IPosition* p )
{
	return StdTreeNode_children( (TreeNode*) p );
}

long StdTree_nrChildren( const StdTree* self, const IPosition* p )
{
	TreeNode* node = (TreeNode*) p;
	return StdTreeNode_nrChildren( node );
}

long StdTree_nrOfChild( const StdTree* self, const IPosition* p )
{
	return StdTreeNode_nrOfChild( (TreeNode*) p );
}

long StdTree_size( const StdTree* self )
{
	return self->size;
}

bool StdTree_isEmpty( const StdTree* self )
{
	return (NULL == self->root);
}
