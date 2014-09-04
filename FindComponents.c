

/* Include the header files */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 500



/* Main */

int main( int argc, char * argv[]) 
{

/* Variables */

  FILE *in, *out;
  int lineNum = 0;             // keeps track of number of lines 
  char line[MAX_LEN];          // line
  int strongC = 0;                     // keeps track of strongly connected components
  
  // Graph G1, G2 and List L 
  
  Graph G1, G2;
  List L = newList();
  
  
/* file reading and writing */

  //this part of the code was given in the example of FileIO.c
  // check command line for correct number of arguments
 
  if( argc != 3 )
  {
     printf("Usage: %s <input file> <output file>\n", argv[0]);
     exit(1);
  }
  
   // open files for reading and writing 
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if( in == NULL )
  {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }


  if( out == NULL )
  {
     printf("Unable to open file %s for writing\n", argv[2]);
     exit(1);
  }
  
  // used the example form FileIO provided by the profesor
  // reads the input from the input file and prints the 
  // adjacency vertices 
  // Same as the BFS code from FindPath in PA4 with minor 
  // changes. addArc 
  
  int source, src, dst;
   while(fgets(line, MAX_LEN, in) != NULL) 
   {
     lineNum++;
     if(lineNum == 1) 
     {
        source =  atoi(strtok(line, " \n"));
        G1 = newGraph(source);
     }
     else 
     {
        src = atoi(strtok(line, " \n"));
        dst = atoi(strtok(NULL, " \n"));
        if( src != 0)  { addArc(G1, src, dst); }
        else { break; }   
     }
     
   }
 fprintf(out, "Adjacency list representation of G: \n");
 printGraph(out, G1);
 fprintf(out, "\n");
 
 
 
 
 /* Run DFS */ 
 
// Transpose a tmpGraph
 G2 = transpose(G1);
 

 int i;
 for(i = 1; i<= getOrder(G1); i++ )
 {
    append(L, i);
 }
 
 
 // Run DFS on original Graph and then then tmpGraph
 DFS(G1,L);
 DFS(G2, L);
 
 
 // Get the Strongly Connected Components. 
 for (i = 1; i <= getOrder(G1); i++ ) 
 {  
     if(getParent(G2, i) == NIL)
     {
        strongC++;
     }
 }
 
 /* Print Statements */ 
 
 
 fprintf(out, "G contains %d strongly connected components:\n", strongC);
 
 List tmpList = newList();
 
 for(i = 1; i<= strongC; i++ ) 
 {
 
     fprintf(out, "Component %d: ", i);
     
     while(getParent(G2, back(L)) != NIL) 
     {
        prepend(tmpList, back(L));
       
        deleteBack(L);
        
     }
        prepend(tmpList, back(L));
        deleteBack(L);
        printList(out, tmpList);
        clear(tmpList);
        fprintf(out, "\n");
        
  }
  
 // free list, graph 
 
 clear(L);
 freeList(&tmpList);
 freeList(&L);
 freeGraph(&G1);
 freeGraph(&G2);
 
 // close the files
 
 fclose(in);
 fclose(out);
 
 return 0;
 
}
 
