/*
 * Graph.c
 *
 *  Created on: May 15, 2019
 *      Author: Ari
 */
#include "Graph.h"
#include "List.h"


Graph newGraph(int n){
	Graph G = malloc(
			((n+1)*(sizeof(List)))+
			((3*ARRSIZE)*(sizeof(int)))+
			(3*(sizeof(int))));
	for(int i=0; 0<=n; n++){
		G->L[i] = newList();
	}

	int order = n;
	int size = 0;
	int source = -2;

	return G;
}

void freeGraph(Graph* pG){
	//dont need to free int arrays I think
	for(int i=0; i< (*pG)->order;i++){
		freeList((*pG)->L[i]);
	}
	free(*pG);
	pG = NULL;
}

int getOrder(Graph G){
	return G->order;
}
int getSize(Graph G){

	return G->size;
}
int getSource(Graph G){
	return G->source;
}
int getParent(Graph G, int u){
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given.");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL) return NIL;

	return G->P[u];
}

int getDist(Graph G, int u){
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given in getDist().");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL) return INF;
	return G->D[u];

}
void getPath(List L, Graph G, int u){
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given in getPath().");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		fprintf(stderr, "error: BFS() must be called before getPath().");
		exit(EXIT_FAILURE);
	}

	if(G->D[u] == NIL){
		append(L, G->source);
		append(L, NIL);
		append(L, u);
	}
	else getPathR(L, G, u);

}
//recursively find the shortest path
void getPathR(List L, Graph G, int u){

	prepend(L, u);
	if(G->D[u] != 0){
		moveFront(G->L[u]);
		while((G->D[get(G->L[u])] != (G->D[u] - 1)) && (index(G->D[u]) != -1)){
			moveNext(G->L[u]);
		}
		getPathR(L, G, get(G->L[u]));
	}

}

/*** Manipulation procedures ***/
void makeNull(Graph G){
	for(int i=1; i <= getSize(G); i++){
		clear(G[i]);
	}
}

void addEdge(Graph G, int u, int v){
	//precond
	if(1 > u || getOrder(G) < u) {
		fprintf(stderr, "error: invalid vertex given in addEdge().");
		exit(EXIT_FAILURE);
	}
	if(1 > v || getOrder(G) < v) {
		fprintf(stderr, "error: invalid vertex given in addEdge().");
		exit(EXIT_FAILURE);
	}

	moveFront(G[u]);
	while(get(G[u]) < v && index(G[u]) < 0){
		moveNext(G[u]);
	}
	if(index(G[u]) > 0) insertBefore(G[u], v);
	else prepend(G[u], v);

	moveFront(G[v]);
	while(get(G[v]) < u && index(G[v]) < 0){
		moveNext(G[v]);
	}
	if(index(G[v]) > 0) insertBefore(G[v], u);
	else prepend(G[v], u);

	G->size++;
}

void addArc(Graph G, int u, int v){
	//precond
	if(1 > u || getOrder(G) < u) {
		fprintf(stderr, "error: invalid vertex given in addArc().");
		exit(EXIT_FAILURE);
	}
	if(1 > v || getOrder(G) < v) {
		fprintf(stderr, "error: invalid vertex given in addArc().");
		exit(EXIT_FAILURE);
	}

	moveFront(G[u]);
	while(get(G[u]) < v && index(G[u]) < 0){
		moveNext(G[u]);
	}
	if(index(G[u]) > 0) insertBefore(G[u], v);
	else prepend(G[u], v);

	G->size++;
}

void BFS(Graph G, int s){

	for(int i=1; i<getSize(G); i++){
		G->C[i] = 0; //0 is white
		G->D[i] = INF;
		G->P[i] = NIL;
	}
	G->C[s] = 1;
	G->D[s] = 0;
	G->P[s] = NIL;
	List Q = newList(); //the queue, fifo
	append(Q, s);
	moveFront(Q); //the cursor at the front will be used to retrieve elements

	int adj; //adjacent vertex holder, v in the algorithm in figure 22.3

	while(length(Q) != 0){
		int u = get(Q);
		deleteFront(Q); //dequeue

		movefront(G->L[u]);
		while(index(G->L[u]) != -1){
			adj = get(G->L[u]);

			if(G->C[adj] == 0){
				G->C[adj] = 1;
				G->D[adj] = G->D[u] + 1;
				G->P[adj] = u;
				append(Q, adj); //enqueue
			}

			moveNext(G->L[u]);
		}
		G->C[u] = 2; //set u to black
	}

	freeList(Q);

}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){

	for(int i=1; i <= getOrder(G); i++){
		moveFront(G->L[i]);

		fprintf(out, "\n%d: ", i);
		while(index(G->L[i]) != -1){
			fprintf(out, "%d ", get(G->L[i]));

			moveNext(G->L[i]);
		}
		//insert newline here if swap
	}
}
