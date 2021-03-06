/*
 * Graph.h
 *
 *  Created on: May 15, 2019
 *      Author: Ari
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#define INF -1
#define NIL -2
#define ARRSIZE 99

typedef struct GraphObj {
	List L[];
	int C[ARRSIZE]; //color
	int P[ARRSIZE]; //parents
	int D[ARRSIZE]; //distance from source to vertex i
	int order; //vertice count
	int size; // edge count
	int source;

} GraphObj;

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif /* GRAPH_H_ */
