//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa2: Lex, List ADT in C
// cmps101, spring 2019
//
// List.c
//-----------------------------------------------------------------------------
#include "List.h"
#include<stdio.h>
#include<stdlib.h>

List newList(void){ //look over the ptr usage
	List new_list = malloc(sizeof(Node)*3+sizeof(int)*2); //fixed mem leak
	(new_list)->back = NULL;
	(new_list)->front = NULL;
	(new_list)->cursor = NULL;
	(new_list)->index = -1;
	new_list->length = 0;
	//note: not defining the ints
	return new_list; //pass the address of the place malloced
}

Node newNode(int data){
	Node new_node = malloc(sizeof(Node)*2+sizeof(int));
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->data = data;
	return new_node;
}

//frees nodes and list struct
void freeList(List* pL){ //given pointer to List
	clear(*pL);
	free(*pL);
	pL = NULL;
}

// Access functions -----------------------------------------------------------

// checks if list is empty
int isEmpty(List L){
	//return 0 if empty, return 1 if not
	if(L->length < 1 || L->front == NULL || L->back == NULL) return 0;
	return 1;
}

//returns list length
int length(List L){
	if(L == NULL) {
			fprintf(stderr, "err: List is undefined.\n");
				exit(EXIT_FAILURE);
	}
	return L->length;
}

//returns cursor index
int index(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
			exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL || L->index < 0) return -1;
	return L->index;
}

//returns front node's data
int front(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(L->front == NULL) {
		fprintf(stderr, "err: Front is undefined.\n");
		exit(EXIT_FAILURE);
	}
	return L->front->data;
}

//returns back node's data
int back(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
			exit(EXIT_FAILURE);
	}
	if(L->back == NULL) {
		fprintf(stderr, "err: Front is undefined.\n");
		exit(EXIT_FAILURE);
	}
	return (L->back)->data;
}

//returns cursor's data
int get(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(L->index < 0 || L->cursor == NULL){
		fprintf(stderr, "err: Cursor is undefined.\n");
		exit(EXIT_FAILURE);
	}
	return (L->cursor)->data;
}

//returns boolean, depending on if input lists are equal
int equals(List A, List B){
	if(A == NULL || B == NULL) {
		fprintf(stderr, "err: List(s) is undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(A->length != B->length) return 0;
	Node A_itr = A->front;
	Node B_itr = B->front;
	for(int i=0; i<(A->length); i++){
		if(A_itr->data != B_itr->data) return 0;
		A_itr = A_itr->next;
		B_itr = B_itr->next;
	}
	return 1;
}

// Manipulation procedures ----------------------------------------------------

//free a node
void deleteNode(Node N){
	if(N == NULL){
		fprintf(stderr, "err: Node is undefined.\n");
		exit(EXIT_FAILURE);
	}
	(N)->next = NULL;
	(N)->prev = NULL;
	free(N);
	N = NULL;
}

//free nodes from a list
void clear(List L){
	//reset cursor
	L->cursor = NULL;
	L->index = -1;
	clearNode(L->front);
	L->length = 0;
	L->back = NULL;
	L->front = NULL;
	L->cursor = NULL;
}

//recursive subroutine to clear()
// progress to each node and delete backwards
void clearNode(Node N){
	if(N == NULL) return;
	clearNode(N->next);
	deleteNode(N);
}

//move cursor to front
void moveFront(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: aList is undefined.\n");
		exit(EXIT_FAILURE);
	}
	L->cursor = L->front;
	L->index = 0;
}

//move cursor to back
void moveBack(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: bList is undefined.\n");
		exit(EXIT_FAILURE);
	}
	L->cursor = L->back;
	L->index = (L->length)-1;
}

//move cursor to previous node
void movePrev(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(L->index != -1){
		if(L->cursor != L->front){
			L->cursor = L->cursor->prev;
			L->index--;
		} else {
			L->index = -1;
			//L->cursor = NULL;
		}
	}
}

//move cursor to next node
void moveNext(List L){
	if(L == NULL || L->length < 1) {
			fprintf(stderr, "err: List is undefined.\n");
			exit(EXIT_FAILURE);
	}
	if(L->index != -1) {
		if(L->cursor != L->back) {
		   L->cursor = L->cursor->next;
		   L->index++;
		}
		else
		    L->index = -1;
			//L->cursor = NULL;
	 }
}

//add a node to the front of the list
void prepend(List L, int data){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}

	Node N = newNode(data);

	if(L->length <= 0){
		L->front = N;
		L->back = N;

	} else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
     }
	L->length++;
	if(L->index > -1) L->index++;
}

//add a node to end of the list
void append(List L, int data){ //if this still produces mem errors try to not have the mallocs of newnode and front n back overlap
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}

	Node N = newNode(data);

	if(L->length <= 0){
		L->front = N;
		L->back = N;

	} else {
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
    }
	L->length++;
}

//add a node before the cursor
void insertBefore(List L, int data){
	//case: list length is 0 or below
	 if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	 }
	 if(L->index < 0){
		fprintf(stderr, "err: Cursor is undefined.\n");
		exit(EXIT_FAILURE);
	 }

	 Node N = newNode(data);

	 //case: cursor is at front
	 if(L->index == 0) {
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		L->length++;
		L->index++;
	 }

	 //case: cursor is in middle/end
	 else {
		N->next = L->cursor;
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		L->cursor->prev = N;
		L->length++;
		L->index++;
	 }
}

//add a node after the cursor
void insertAfter(List L, int data){
	//case: list length is 0 or below
	 if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	 }
	 if(L->index < 0){
		fprintf(stderr, "err: Cursor is undefined.\n");
		exit(EXIT_FAILURE);
	 }

    Node N = newNode(data);

    //case: cursor is at back
    if(L->cursor == L->back) {
       N->prev = L->back;
       L->back->next = N;
       L->back = N;
       L->length++;
    }

    //case: cursor is in middle/front
    else {
       N->next = L->cursor->next;
       N->prev = L->cursor->next->prev;
       L->cursor->next->prev = N;
       L->cursor->next = N;
       L->length++;
    }
}

//delete the front node
void deleteFront(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(L->length > 1){
		if(L->cursor == L->front){
			L->cursor = NULL;
			L->index = -1;
		}
			Node N = L->front->next;
			deleteNode(L->front);
			L->front = N;
			N->prev = NULL;
			L->index--;
	} else {
		deleteNode(L->front);
		L->back = NULL;
		L->front = NULL;
		L->index = -1;
	}
	L->length--;
}

// delete the back node
void deleteBack(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(L->length > 1){
		if(L->cursor == L->back) {
			L->cursor = NULL;
			L->index = -1;
		}
			Node N = L->back->prev;
			deleteNode(L->back);
			L->back = N;
			N->next = NULL;

	} else {
		deleteNode(L->back);
		L->back = NULL;
		L->front = NULL;
	} L->length--;
}

//need to free all deleted nodes
void delete(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL){
		fprintf(stderr, "err: Cursor is undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == L->back) {
		deleteBack(L);
		L->index = -1;
	} else if (L->cursor == L->front){
		deleteFront(L);
		L->index = -1;
	} else {
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		deleteNode(L->cursor);
		L->length--;
		L->index = -1;
		L->cursor = NULL; //for safety
	}
}

// Other operations -----------------------------------------------------------

//print each node's element
void printList(FILE* out, List L){
	if(L == NULL || L->length <= 0) {
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}
	Node itr = L->front;
	for(int i=0; i<L->length; i++){
		fprintf(out, "%d ", itr->data);
		itr = itr->next;
	}
}

//create a new copy of a list
List copyList(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}

	List nL = newList();

	if(L->length == 0) return nL;

	append(nL, L->front->data);

	Node itr = L->front->next;

	if(L->length > 1){

		for(int i=0; i<L->length-2;i++){
			append(nL, itr->data);

			itr = itr->next;
		}
	}
	//add back
	if(L->length != 1) append(nL, itr->data);

	//for safety
	nL->back = itr;

	return nL;
}
