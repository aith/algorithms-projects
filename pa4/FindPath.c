//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa4: Breadth First Search and Shortest Paths in Graphs
// cmps101, spring 2019
//
// FindPath.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char * argv[]){
	FILE* in = fopen (argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	int a = 0; //input 1
	int b = 0; //input 2
	int d = 0; //distance
	int size = 0;
	Graph G = NULL;
	List L = newList();

	if( argc != 3 ){
	  printf("Usage: %s <input file> <output file>\n", argv[0]);
	  exit(1);
	}

   if(in==NULL){
	  printf("err: Unable to open file %s for reading\n", argv[1]);
	  exit(1);
   }

   if(out==NULL){
	  printf("err: Unable to open file %s for writing\n", argv[2]);
	  exit(1);
   }

	//get size
	fscanf (in, "%d", &size);

	//create Graph w size
	G = newGraph(size);

	//take vertex inputs and add edges
	fscanf(in, "%d %d\n", &a, &b);
	while (a != 0 && !feof (in)){
		addEdge(G, a, b);
		fscanf(in, "%d %d\n", &a, &b);
	}

	//error checking #1
	if(b != 0){
		printf("err: Two zeroes must be stated to initialize path finding.\n");
		exit(1);
	}

	//print Graph onto output file
	printGraph(out, G);

	//get paths and print
	int i=0; //for the newline, ensures that the first iteration doesn't add a newline
	fscanf (in, "%d %d\n", &a, &b);
	while (a != 0 && b!= 0 && !feof (in)){
		BFS(G, a);

		d = getDist(G, b);

		if(i > 0) fprintf(out, "\n");
		i = 1;
		fprintf(out, "\nThe distance from %d to %d is ", a, b);
		if(d != INF){
			fprintf(out, "%d", d);
			fprintf(out, "\nA shortest %d-%d path is: ", a, b);
			getPath(L, G, b);
			printList(out, L);
			clear(L);

		}else {
			fprintf(out, "infinity");
			fprintf(out, "\nNo %d-%d path exists", a, b);
		}
		fscanf (in, "%d %d\n", &a, &b);

	}
	fprintf(out, "\n");
	//error checking #2
	if(b != 0){
		printf("err: Two zeroes must be stated to end path finding.\n");
		exit(1);
	}

	freeGraph(&G);
	freeList(&L);
	fclose(in);
	fclose(out);
}
