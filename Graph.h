
#define _GRAPH_H_INCLUDE
#ifndef _GRAPH_H_INCLUDE_

#define NIL 0

#define UNDEF -1

#define WHITE 0
#define GRAY 1
#define BLACK 2


#include "List.h"

typedef struct GraphObj* Graph;

Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/ 
int getOrder(Graph G); 
int getSize(Graph G); 
int getSource(Graph G); 
int getParent(Graph G, int u); 
int getDiscover(Graph G, int u); 
int getFinish(Graph G, int u); 
 
/*** Manipulation procedures ***/  
void addEdge(Graph G, int u, int v); 
void addArc(Graph G, int u, int v); 
void DFS(Graph G, List S); 

 
 
/*** Other operations ***/ 
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G); 

#endif
