//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa4: Breadth First Search and Shortest Paths in Graphs
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
   List  B = newList(); //
   List  C = newList(); //
  Graph G = NULL;

   // Build graph G
   G = newGraph(n);
   addEdge(G, 2, 7);

printGraph(stdout, G);

for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
BFS(G, 1);


printf("\n Distances: ");
	for(int i=1; i<=n; i++){
		   printf("%d ", G->D[i]);
	}
printf("\n Parents: ");
	for(int i=1; i<=n; i++){
		   printf("%d ", G->P[i]);
	}
printf("\n Path from 4 to s:");
getPath(A, G, 14);
printList(stdout, A);

makeNull(G);
freeGraph(&G);
}
