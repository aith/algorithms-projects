//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa4: Breadth First Search and Shortest Paths in Graphs
// cmps101, spring 2019
//
// Graph.c
//-----------------------------------------------------------------------------
#include "Graph.h"

//constructor
Graph newGraph(int n){
	Graph G = malloc(
			((n+1)*(sizeof(List)))+
			((3*ARRSIZE)*(sizeof(int)))+
			(3*(sizeof(int))));
	for(int i=0; i<=n; i++){
		G->L[i] = newList();
	}

	G->order = n;
	G->size = 0;
	G->source = NIL;

	return G;
}

//destructor
void freeGraph(Graph* pG){
	//dont need to free int arrays I think
	for(int i=0; i<= (*pG)->order;i++){
		freeList(&((*pG)->L[i]));
	}

	free(*pG);
	*pG = NULL;
}
//Access functions-----------------------------------

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
	//precondition
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given.");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL)
		return NIL;

	return G->P[u];
}

int getDist(Graph G, int u){
	//precondition
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given in getDist().");
		exit(EXIT_FAILURE);
	}

	if(getSource(G) == NIL) return INF;
	return G->D[u];

}

//recursively obtain the shortest path from source to vertex u
void getPath(List L, Graph G, int u){
	//preconditions
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given in getPath().");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		fprintf(stderr, "error: BFS() must be called before getPath().");
		exit(EXIT_FAILURE);
	}

	if(u == G->source){ append(L, u); }
	else if(G->P[u] == NIL){
		append(L, NIL);
	}else {
		getPath(L, G, G->P[u]);
		append(L, u);
	}

	//else getPathR(L, G, u); the old method


//vestigial function, might be reused
}
//recursively find the shortest path
void getPathR(List L, Graph G, int u){

	prepend(L, u);
	if(G->D[u] != 0){
		moveFront(G->L[u]);
		while((G->D[get(G->L[u])] != (G->D[u] - 1)) && (index(G->L[u]) != -1)){
			moveNext(G->L[u]);
		}
		getPathR(L, G, get(G->L[u]));
	}

}

/*** Manipulation procedures ***/

//clears each vertex's adjacency
void makeNull(Graph G){
	for(int i=1; i <= getOrder(G); i++){
		clear(G->L[i]);
	}
	G->size = 0;
}

//adds adjacency to both vertices
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

	if(length(G->L[u]) > 0){
		moveFront(G->L[u]);
		while(index(G->L[u]) > -1 && get(G->L[u]) < v){
			moveNext(G->L[u]);
		}
		if(index(G->L[u]) != -1) insertBefore(G->L[u], v);
		else append(G->L[u], v);
	} else prepend(G->L[u], v);

	if(length(G->L[v]) > 0){
		moveFront(G->L[v]);
		while(index(G->L[v]) > -1 && get(G->L[v]) < u){
			moveNext(G->L[v]);
		}
		if(index(G->L[v]) != -1) insertBefore(G->L[v], u);
		else append(G->L[v], u);
	} else prepend(G->L[v], u);

	G->size++;
}

//adds adjacency to u only
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

	if(length(G->L[u]) > 0){
		moveFront(G->L[u]);
		while(index(G->L[u]) > -1 && get(G->L[u]) < v){
			moveNext(G->L[u]);
		}
		if(index(G->L[u]) != -1) insertBefore(G->L[u], v);
		else append(G->L[u], v);
	} else prepend(G->L[u], v);

	G->size++;
}

//runs breadth first search, traverses all discoverable vertices
void BFS(Graph G, int s){
	for(int i=1; i<=getOrder(G); i++){
		//if(i==s) continue;
		G->C[i] = 0; //0 is white
		G->D[i] = INF;
		G->P[i] = NIL;
	}
	G->C[s] = 1; //1 is grey
	G->D[s] = 0;
	G->P[s] = NIL;
	G->source = s;
	List Q = newList(); //the queue, fifo
	append(Q, s);
	moveFront(Q); //the cursor at the front will be used to retrieve elements

	int adj; //adjacent vertex holder, v in the algorithm in figure 22.3

	while(length(Q) != 0){
		moveFront(Q);
		int u = get(Q);
		deleteFront(Q); //dequeue

		if(length(G->L[u]) > 0){
			moveFront(G->L[u]);
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
		}
		G->C[u] = 2; //set u to black
	}

	freeList(&Q);

}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){

	for(int i=1; i <= getOrder(G); i++){

		fprintf(out, "%d:", i);
		if(length(G->L[i]) > 0){
			moveFront(G->L[i]);
			while(index(G->L[i]) != -1){
				fprintf(out, " %d", get(G->L[i]));

				moveNext(G->L[i]);
			}
		}
		fprintf(out, "\n");
	}
}
