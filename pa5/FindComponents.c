//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa5: Depth First Search and SSCs
// cmps101, spring 2019
//
// FindComponents.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char * argv[]){
	FILE* in = fopen (argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	int a = 0; //input 1
	int b = 0; //input 2
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
		addArc(G, a, b);
		fscanf(in, "%d %d\n", &a, &b);
	}

	//error checking #1
	if(b != 0){
		printf("err: Two zeroes must be stated to initialize path finding.\n");
		exit(1);
	}

	//populate the List
	for(int i=1;i<=getOrder(G);i++){
		append(L, i);
	}

	//run DFS
	DFS(G, L);

	//print Graph onto output file
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

	//obtain strongly connected components
	Graph Gt = transpose(G);

	DFS(Gt, L);

	//to count connected components, count how many nil parents there are
	int nilcount = 0;
	int list_vertex; //hold

	if(length(L) > 0){
		moveFront(L);
	}
	while(index(L) != -1){
		list_vertex = get(L);
		if(getParent(Gt,list_vertex) == NIL) nilcount++;
		moveNext(L);
	}

	//print out scc count
	fprintf(out, "\nG contains %d strongly connected component", nilcount);
	if(nilcount == 1) fprintf(out, ":\n");
	else fprintf(out, "s:\n");

	//to obtain scc's, separate trees by the nil parents
	//alternatively, we can concatenate them onto strings to save runtime
	if(length(L) > 0){
		moveBack(L);

		for(int i=1; i<=nilcount;i++){
			fprintf(out, "Component %d:", i);

			int count = 0;
			while(getParent(Gt, get(L)) != NIL){
				//fprintf(out, " %d", get(L));
				count++;
				movePrev(L);
			}
			for(int i=0; i<count; i++){
				fprintf(out, " %d", get(L));
				moveNext(L);
			}
			fprintf(out, " %d", get(L));

			for(int i=0; i<count; i++){
				movePrev(L);
			}

			fprintf(out, "\n");
			movePrev(L);
		}
	}
	freeGraph(&G);
	freeGraph(&Gt);
	freeList(&L);
	fclose(in);
	fclose(out);
}


