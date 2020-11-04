//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa4: Breadth First Search and Shortest Paths in Graphs
// cmps101, spring 2019
//
// List.h
//-----------------------------------------------------------------------------
#ifndef LIST_H_
#define LIST_H_

#include<stdio.h>
#include<stdlib.h>

typedef struct NodeObj {
	struct NodeObj *next;
	struct NodeObj *prev;
	int data;
} NodeObj;

typedef struct NodeObj *Node;

// Structures
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int index;
	int length;

} ListObj;

typedef struct ListObj *List;


// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List* pL);
// Access functions -----------------------------------------------------------
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);
// Manipulation procedures ----------------------------------------------------
void deleteNode(Node N);
void clear(List L);
void clearNode(Node N);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);



#endif /* LIST_H_ */
