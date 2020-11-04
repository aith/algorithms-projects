/*
 * List.c
 *
 *  Created on: Apr 17, 2019
 *      Author: Ari
 */
#include "List.h"
#include<stdio.h>
#include<stdlib.h>

List newList(void){ //look over the ptr usage
	List new_list = malloc(sizeof(List));
	(new_list)->back = NULL;
	(new_list)->front = NULL;
	(new_list)->cursor = NULL;
	(new_list)->index = -1;
	new_list->length = 0;
	//note: not defining the ints
	return new_list; //pass the address of the place malloced
}

Node newNode(int data){
	Node new_node = malloc(sizeof(Node));
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->data = data;
	return new_node;
}

void freeList(List* pL){ //given pointer to List
	Node itr = (*pL)->front; //set item pointed by iterator to front(which is also a pointer, so it gives the address of front)
	while(itr != NULL){ //if causes error, do ->next, and also hard code the final deletion
		Node to_be_del = itr;
		itr = itr->next;
		deleteNode(to_be_del);
	}
	free(pL);
	pL = NULL;
}

// Access functions -----------------------------------------------------------

int isEmpty(List L){
	//return 0 if empty, return 1 if not
	if(L->length < 1 || L->front == NULL || L->back == NULL) return 0;
	return 1;
}

int length(List L){
	if(L == NULL) {
			fprintf(stderr, "err: List is undefined.\n");
				exit(EXIT_FAILURE);
		}
	if(L->length < 1){
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}
	return L->length;
}

int index(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
			exit(EXIT_FAILURE);
	}
	if(L->length < 1){
			fprintf(stderr, "err: List is empty or undefined.\n");
			exit(EXIT_FAILURE);
		}
	if(L->cursor == NULL || L->index < 0) return -1;
	return L->index;
}

int front(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
			exit(EXIT_FAILURE);
	}
	if(L->front == NULL) {
		fprintf(stderr, "err: Front is undefined.\n");
	}
	return L->front->data;
}

int back(List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
			exit(EXIT_FAILURE);
	}
	if(L->back == NULL) {
		fprintf(stderr, "err: Front is undefined.\n");
	}
	return (L->back)->data;
}

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

int equals(List A, List B){
	if(A == NULL || B == NULL) {
		fprintf(stderr, "err: List(s) is undefined.\n");
			exit(EXIT_FAILURE);
	}
	if(A->length != B->length) return 0;
	Node A_itr = A->front;
	Node B_itr = B->front;
	for(int i=0; i<(A->length); i++){ //might need to do ->next here too to avoid error, or use length index
		if(A_itr->data != B_itr->data) return 0;
		A_itr = A_itr->next;
		B_itr = B_itr->next;
	}
	return 1;
}

// Manipulation procedures ----------------------------------------------------


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

void clear(List L){
	//reset cursor
	L->cursor = NULL;
	L->index = -1;
	if(L == NULL || L->length <= 0) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}
	Node itr = L->front;
	Node to_be_del = malloc(sizeof(Node));
	for(int i=0; i<L->length-1; i++){ //get rid of -1 later
		to_be_del = itr;
		itr = itr->next;
		deleteNode(to_be_del);
	}
}

void moveFront(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}
	L->cursor = L->front;
	L->index = 0;
}

void moveBack(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}
	L->cursor = L->back;
	L->index = (L->length)-1;
}

void movePrev(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor != L->front){
		if(L->cursor != L->front){
			L->cursor = L->cursor->prev;
			L->index--;
		} else {
			L->index = -1;
			L->cursor = NULL;
		}
	}
}

void moveNext(List L){
	if(L == NULL || L->length < 1) {
			fprintf(stderr, "err: List is undefined.\n");
			exit(EXIT_FAILURE);
	}
	if(L->cursor != L->back) {
		if(L->cursor != L->back) {
		   L->cursor = L->cursor->next;
		   L->index++;
		}
		else
		    L->index = -1;
			L->cursor = NULL;
	 }
}

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

void append(List L, int data){
	if(L == NULL) {
		fprintf(stderr, "err: List is undefined.\n");
		exit(EXIT_FAILURE);
	}

	Node N = newNode(data);

	if(L->length <= 0){
		L->front = N;
		L->back = N;

	} else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
	L->length++;
}

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

void deleteFront(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}
	Node N = L->front->next;
	deleteNode(L->front);
	L->front = N;
	N->prev = NULL;
	L->length--;
}

void deleteBack(List L){
	if(L == NULL || L->length < 1) {
			fprintf(stderr, "err: List is empty or undefined.\n");
			exit(EXIT_FAILURE);
	}

	if(L->cursor == L->back) {
		L->index = -1;
	}
	Node N = L->back->prev;
	deleteNode(L->back);
	L->back = N;
	N->next = NULL;
	L->length--;
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
	} else if (L->cursor == L->front){
		deleteFront(L);
	} else {
		//Node to_be_del = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		deleteNode(L->cursor);
		L->length--;
		L->index = -1;
		L->cursor = NULL; //for safety
	}
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
	if(L == NULL) {
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}

	Node itr = L->front;
	for(int i=0; i<L->length; i++){
		fprintf(out, "%d ", itr->data);
		itr = itr->next;
	}
}

List copyList(List L){
	if(L == NULL || L->length < 1) {
		fprintf(stderr, "err: List is empty or undefined.\n");
		exit(EXIT_FAILURE);
	}

	List nL = newList();

	append(nL, L->front->data);

	if(L->length > 1){
		Node itr = L->front->next;


		for(int i=0; i<L->length-2;i++){
			append(nL, itr->data);

			itr = itr->next;
		}

		append(nL, itr->data);

		nL->back = itr;
	}

	return nL;
}







