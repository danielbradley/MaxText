/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#include <openxds.core/types.h>
#include "openxds.core.adt.std/StdListNode.h"

typedef struct _LinkedList LinkedList;

LinkedList*   new_StdLinkedList(void);
void*        free_StdLinkedList( LinkedList* self );
const ListNode*  StdLinkedList_addFirst( LinkedList* self, ListNode* aListNode );
const ListNode*   StdLinkedList_addLast( LinkedList* self, ListNode* aListNode );
const ListNode* StdLinkedList_addBefore( LinkedList* self, const ListNode* next, ListNode* aListNode );
const ListNode*  StdLinkedList_addAfter( LinkedList* self, const ListNode* prev, ListNode* aListNode );
ListNode*          StdLinkedList_remove( LinkedList* self, const ListNode* aListNode );
const ListNode*  StdLinkedList_getFirst( LinkedList* self );
const ListNode*   StdLinkedList_getLast( LinkedList* self );
const ListNode* StdLinkedList_getBefore( LinkedList* self, const ListNode* aListNode );
const ListNode*  StdLinkedList_getAfter( LinkedList* self, const ListNode* aListNode );
int               StdLinkedList_getSize( LinkedList* self );
bool              StdLinkedList_isEmpty( LinkedList* self );
