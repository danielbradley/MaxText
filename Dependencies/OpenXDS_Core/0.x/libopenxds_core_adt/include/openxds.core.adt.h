/*
 *  Copyright (c) 2008-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_H
#define OPENXDS_CORE_ADT_H

#include <openxds.core/types.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif

typedef struct _ADTFactory  ADTFactory;

/* typedef struct _IArray               IArray; */
typedef struct _IComparitor          IComparitor;
typedef struct _IIterator            IIterator;
typedef struct _IEIterator           IEIterator;
typedef struct _IPIterator           IPIterator;
typedef struct _IKey                 IKey;
typedef struct _IList                IList;
typedef struct _IPosition            IPosition;
typedef struct _IStack               IStack;
typedef struct _IString              IString;
typedef struct _IValue               IValue;
typedef struct _IEntry               IEntry;
typedef struct _IMap                 IMap;
typedef struct _IDictionary          IDictionary;
typedef struct _IVector              IVector;
typedef struct _IDeque               IDeque;
typedef struct _ISequence            ISequence;
typedef struct _ITree                ITree;

/* typedef struct _ICompressionFunction ICompressionFunction; */
/* typedef struct _IEdge                IEdge; */
/* typedef struct _IGraph               IGraph; */
/* typedef struct _IHashCode            IHashCode; */
/* typedef struct _IHashFunction        IHashFunction; */
/* typedef struct _IPriorityQueue       IPriorityQueue; */
/* typedef struct _IQueue               IQueue; */
/* typedef struct _ISearch              ISearch; */
/* typedef struct _ISort                ISort; */
/* typedef struct _IVertex              IVertex; */

	#ifdef __cplusplus
};};};
	#endif

#endif
