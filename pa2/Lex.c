//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa2: Lex, List ADT in C
// cmps101, spring 2019
//
// Lex.c
//-----------------------------------------------------------------------------
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_LEN 1000

int main(int argc, char * argv[]){

   //L is the array that stores each row's spot in lexographic order
	List L = newList();

   int n=0, count=0, outi = 0; //outi is for printing the array
   FILE *in, *out; //input and output files
   char line[MAX_LEN]; //used in the creation of token
   char tokenlist[MAX_LEN]; //a row in the input file
   char* token; //makes up tokenlist

   //String array that'll be printed into output file
   char S[MAX_LEN][MAX_LEN]; //number of Strings then String length


   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("err: Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("err: Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // read each line of input file, then count and print tokens
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
      token = strtok(line, " \n"); // \n is the delimiter
      tokenlist[0] = '\0';
      while( token!=NULL ){
         strcat(tokenlist, token);
         strcat(tokenlist, " ");
         token = strtok(NULL, " \n"); //what does this do?
      }

      strcpy(S[n], tokenlist);
      n++;

   }

   //prepare for the sorting
   append(L, 0);
   moveFront(L);

	 for(int i = 1; i < n; i++){
		for(int j = 0; j < length(L); j++){
			if(strcmp(S[i],S[j]) > 0)
			moveNext(L);
		}
		if(index(L) != -1){
		   insertBefore(L, i);
		   moveFront(L);
		}
		else{
		   append(L, i);
		   moveFront(L);
		}
	 }

	 //reset cursor for printing
	 moveFront(L);

	 //print to output file, printing S[] based on the L[]'s values
	 while(outi < length(L)) {
		fprintf(out, "%s\n", S[get(L)]);
		moveNext(L);
		outi++;
	 }

	 //free the String
	 freeList(&L);
	 fclose(out);
     fclose(in);

     //exit
     return(0);
}
