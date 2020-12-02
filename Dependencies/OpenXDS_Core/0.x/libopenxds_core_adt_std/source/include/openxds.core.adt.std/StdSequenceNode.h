/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_STDSEQUENCENODE_H
#define OPENXDS_CORE_ADT_STD_STDSEQUENCENODE_H

#include <openxds.core.adt/IPosition.h>

	#ifdef __cplusplus
		using namespace openxds::core;

		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif

typedef struct _Node StdSequenceNode;

StdSequenceNode*            new_StdSequenceNode(       E*               anElement, long index );
StdSequenceNode*           free_StdSequenceNode(       StdSequenceNode* self      );
E*               StdSequenceNode_replaceElement(       StdSequenceNode* self, E* anElement );

const E*             StdSequenceNode_getElement( const StdSequenceNode* self      );
long                   StdSequenceNode_getIndex( const StdSequenceNode* self      );

typedef struct _Node Node;

struct _Node
{
	IPosition super;
	E*        e;
	long      i;
};

	#ifdef __cplusplus
		};};};};};
	#endif

#endif
