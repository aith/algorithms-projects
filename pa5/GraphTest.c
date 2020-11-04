//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa5: Depth First Search and SSCs
// cmps101, spring 2019
//
// GraphTest.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  A = newList(); // test 1
  Graph G = NULL;
  Graph Gt = NULL;

   // Build graph G
   G = newGraph(n);
   addArc(G, 2, 7);

printGraph(stdout, G);

for(i=1; i<n; i++){
      if( i%7!=0 ) addArc(G, i, i+1);
      if( i<=28  ) addArc(G, i, i+7);
   }
DFS(G, A);
//obtain strongly connected components
Graph Gt = transpose(G);

DFS(Gt, A);


printf("\n Distances: ");
	for(int i=1; i<=n; i++){
		   printf("%d ", G->D[i]);
	}
printf("\n Parents: ");
	for(int i=1; i<=n; i++){
		   printf("%d ", G->P[i]);
	}
printList(stdout, A);

makeNull(G);
freeGraph(&G);
freeGraph(&Gt);
freeList(&A);
}
