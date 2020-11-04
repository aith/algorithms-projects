//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa5: Depth First Search and SSCs
// cmps101, spring 2019
//
// Graph.c
//-----------------------------------------------------------------------------
#include "Graph.h"

void Visit(Graph G, List S, List N, int u);

//constructor
Graph newGraph(int n){
	Graph G = malloc(
			((n+1)*(sizeof(List)))+
			(3*(sizeof(int)))
			+(4*(n+1)*(sizeof(int)))
			);
	for(int i=0; i<=n; i++){
		G->L[i] = newList();
	}

	G->P = (int *)malloc((n+1)*sizeof(int));
	G->F = (int *)malloc((n+1)*sizeof(int));
	G->D = (int *)malloc((n+1)*sizeof(int));
	G->C = (int *)malloc((n+1)*sizeof(int));

	G->order = n;
	G->size = 0;

	G->P[0] = UNDEF; //P[0] is UNDEF is DFS hasn't been run
	return G;
}

//destructor
void freeGraph(Graph* pG){
	//dont need to free int arrays I think
	for(int i=0; i<= (*pG)->order;i++){
		freeList(&((*pG)->L[i]));
	}
	free(((*pG)->P));
	free(((*pG)->C));
	free(((*pG)->D));
	free(((*pG)->F));

	(*pG)->P= NULL;
	(*pG)->C = NULL;
	(*pG)->D = NULL;
	(*pG)->F = NULL;

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
int getParent(Graph G, int u){
	//precondition
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given.");
		exit(EXIT_FAILURE);
	}
	if(G->P[0] == UNDEF)
		return NIL;
	return G->P[u];
}

/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given.");
		exit(EXIT_FAILURE);
	}
	if(G->P[0] != 1) return UNDEF;
	return G->D[u];
}

/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
	if(u < 1 || getOrder(G) < u){
		fprintf(stderr, "error: invalid vertex given.");
		exit(EXIT_FAILURE);
	}
	if(G->P[0] != 1) return UNDEF;
	return G->F[u];
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
void DFS(Graph G, List S){
	//precondition: S contains some
	//permutation of the integers {1, 2, … , 𝑛} where 𝑛 = getOrder(𝐺)
	if(getOrder(G) != length(S)){
		fprintf(stderr, "error: S is of invalid length, must be equal to G's vertex count.");
		exit(EXIT_FAILURE);
	}
	G->P[0] = 1; //to let functions know DFS has been called

	for(int i=1; i<=getOrder(G); i++){
		//if(i==s) continue;
		G->C[i] = 0; //0 is white
		G->P[i] = NIL;
	}

	G->time = 0;
	int len = length(S);
	int vertex;
	List N = newList();

	if(len > 0){
		moveFront(S);
		for(int i=1; i<=len && length(S) != 0; i++){
			vertex = get(S);
			if(G->C[vertex] == 0){
				Visit(G, S, N, vertex);
			}
			if(length(S) != 0) { //deleteFront(S);
			moveFront(S); }
		}

		//transfer from n to s
		if(length(N) > 0) moveFront(N);
		for(int i=1; i<=length(N);i++){
			append(S, get(N));
			moveNext(N);
		}
	}

	freeList(&N);
}

void Visit(Graph G, List S, List N, int u){

	G->D[u] = ++(G->time);
	G->C[u] = 1; //1 is grey

	if(length(G->L[u]) != 0) moveFront(G->L[u]);
	int y;
	while(index(G->L[u]) != -1){
		y = get(G->L[u]);
		if(G->C[y] == 0){
			G->P[y] = u;
			Visit(G, S, N, y);
		}
		moveNext(G->L[u]);
	}
	G->C[u] = 2; //2 is black
	G->F[u] = ++(G->time);
	prepend(N, u);
	//delete that specific node from S
	moveFront(S);
	while(index(S) != -1 && get(S) != u){
		moveNext(S);
	}
	delete(S);
}

Graph transpose(Graph G){
	Graph N = newGraph(getOrder(G));
	int temp; //new u in addArc

	for(int i=1; i<=getOrder(G); i++){

		if(length(G->L[i]) != 0) moveFront(G->L[i]);
		while(index(G->L[i]) != -1){
			temp = get(G->L[i]);
			addArc(N, temp, i);
			moveNext(G->L[i]);
		}
	}
	return N;
}

Graph copyGraph(Graph G){
	Graph N = newGraph(getOrder(G));

	for(int i=1; i<=getOrder(G); i++){
		if(length(G->L[i]) != 0) moveFront(G->L[i]);
		while(index(G->L[i]) != -1){
			addArc(N, i, get(G->L[i]));
			moveNext(G->L[i]);
		}
	}

	return N;
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
