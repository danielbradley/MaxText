/*
 *  Copyright (c) 2008-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_H
#define OPENXDS_CORE_ADT_STD_H

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif

typedef struct _StdADTFactory          StdADTFactory;

typedef struct _StdIterator            StdIterator;
typedef struct _StdEIterator           StdEIterator;
typedef struct _StdPIterator           StdPIterator;
typedef struct _Key                    Key;
typedef struct _StdValue               StdValue;
typedef struct _StdList                StdList;
typedef struct _StdStack               StdStack;
typedef struct _StdString              StdString;
typedef struct _StdEntry               StdEntry;
typedef struct _StdMap                 StdMap;
typedef struct _StdDictionary          StdDictionary;
typedef struct _StdVector              StdVector;
typedef struct _StdSequence            StdSequence;
typedef struct _StdTree                StdTree;

/* typedef struct _StdHashCode            StdHashCode; */
/* typedef struct _StdHashFunction        StdHashFunction; */
/* typedef struct _StdHashTable           StdHashTable; */
/* typedef struct _StdCompressionFunction StdCompressionFunction; */


	#ifdef __cplusplus
		};};};};};
	#endif
#endif
