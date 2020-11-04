//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa5: Depth First Search and SSCs
// cmps101, spring 2019
//
// Graph.h
//-----------------------------------------------------------------------------
#ifndef GRAPH_H_
#define GRAPH_H_
#include "List.h"

#define INF -1
#define NIL 0
#define UNDEF -3
#define ARRSIZE 2001

typedef struct GraphObj {
	int *C; //color
	int *P; //parents
	int *D; //discover from source to vertex i
	int *F; //finish time
	int order; //vertex count
	int size; // edge count
	int time;
	List L[];

} GraphObj;

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif /* GRAPH_H_ */
