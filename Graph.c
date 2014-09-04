

#include<stdio.h>
#include<stdlib.h>

// Header files: List.h and Graph.h

#include "List.h"
#include "Graph.h"

// typedef struct GraphObj is similar to the 
// ListObj in List.c ( I used that as an example to
// create GraphObj). 

// minor changes were made to this. new variables 
  typedef struct GraphObj 
  {

     List * adjacency;

     int * color;   // white, gray, or black 
     int * d;       // discover time
     int * p;       // parent 
     int * f;       // finish time
  
     int order;     // order stores the number of vertices
     int time;      // time
     int size;      // source represents the recently used vertex
     
  } GraphObj;
  
  
  
  // an example of this was covered in class on 2-18-14
  // same as BFS from PA4 with minor changes
  
  Graph newGraph(int n) 
  {
     // create a new Graph G of malloc/calloc
     
     Graph G = malloc(sizeof(GraphObj));
     G->adjacency = calloc(n+1, sizeof(List));
     G->color = calloc(n+1, sizeof(int));
     G->d = calloc(n+1, sizeof(int));
     G->p = calloc(n+1, sizeof(int));
     G->f = calloc(n+1, sizeof(int));
     
     G->order = n;
     G->size = 0;
     G->time = UNDEF;
    
    // loop i from 1 to n
    
     int i;
     for (i = 1; i <= n; i++) 
     {  
        G->adjacency[i] = newList();
        G->color[i] = WHITE;
        G->d[i] = UNDEF;
        G->p[i] = NIL;
        G->f[i] = UNDEF;
     }
   
     return (G);
 
  }
  
  
  
  // free the graph and its elements
  // I used listFree from List.c as an 
  // example to create freeGraph
  // same as PS4 with minor changes
  
  void freeGraph( Graph* pG) 
  {
  
  // pre-condition: 
     if(pG == NULL || *pG == NULL) { return; }
     
     int i;
     for(i = 1; i <= getOrder(*pG); i++)
     {
        freeList(&((*pG)->adjacency[i])); // free every element in adjacency
        ((*pG)->adjacency[i]) = NULL;
     }
     
    // frees all heap memory associated with *pG
    // received help on this part from a class mate. 
    // used freeList as reference 
    
    free((*pG)->adjacency);
    ((*pG)->adjacency) = NULL;
    free((*pG)->color);
    ((*pG)->color) = NULL;
    free((*pG)->d);
    ((*pG)->d) = NULL;
    free((*pG)->p);
    ((*pG)->p) = NULL;
    free((*pG)->f);
    ((*pG)->f) = NULL;
    free(*pG);
    *pG = NULL;

  }
  
  

// --------------------------------------------------------------------
//  
// ********************** Access Functions ********************* //
//
// --------------------------------------------------------------------
 
 
 
  // getOrder(Graph G) returns the number of vertices(called the 
  // order of the graph).
  // same as PA4
 
  int getOrder(Graph G)
  {
     if ( G == NULL ) 
     {
        printf( "Graph Error: getOrder() on NULL graph\n" );
        exit(1);
     }
  
     return G->order;

  }
 
 
 
  // getSize(Graph G) returns the number of the edges(called the 
  // size of the graph).
  // same as PA4
  int getSize ( Graph G ) 
  {
     // pre-condtion:
     if( G == NULL ) 
     {
        printf ( "Graph Error: getSize() on NULL graph\n" );
        exit(1);
     }

     return G->size;

  }

  
  // Function getParent() will return the parent 
  // same as PA4 
  int getParent ( Graph G, int u ) 
  {
     
     // pre-condtion: 
     if ( G == NULL ) 
     {
        printf ( "Graph Error: getParent() on NULL graph\n" );    
        exit(1);
     }
    
     // pre condtion for u:
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined\n" );
        exit(1);
     }
 
     // return the parent of the vertex u
    return G->p[u];
 
  } 


  
  // Function  getDiscover() returns the discover time
   
 
  int getDiscover ( Graph G, int u ) 
  {
  
     // pre-condition:
     if ( G == NULL ) 
     {
        printf( "Graph Error: getDiscover() on NULL graph\n" );
        exit(1);
     }
  
     // pre-condtion for u:
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined\n" );  
        exit(1);
     }
  
     // return the distance of the vertex
     return G->d[u];
  
  }


  
  // Function getFinish() returns finish time. 
  
  
  int getFinish ( Graph G, int u ) 
  {
     // pre-condition:
     if ( G == NULL ) 
     {
        printf( "Graph Error: getParent() on NULL graph\n" );
        exit(1);
     }
  
     // pre-condtion for u:
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined\n" );  
        exit(1);
     }
  
     // return the distance of the vertex
     return G->f[u];
  }
  
 

// -------------------------------------------------------------------
//
// ****************** Manipulation Procedures ***************** //
//
// -------------------------------------------------------------------
  
  

  // addArc() inserts a new directed edge from u to v, 
  // i.e. v is added to the adjacency List of u (but not
  //  u to the adjacency List of v). 
  // same as PA4
  void addArc ( Graph G, int u, int v ) 
  {
  
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: addArc() on NULL graph" );
        exit(1);
     }
     // pre-condition
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined" );
        exit(1);
     }
     // pre-condition
     if ( v < 1 || v > getOrder(G) )
     {
        printf ( "Graph Error:  addarc v undefined" );
        exit(1);
     }
    
    // add u to v 
     if(length(G->adjacency[u]) == 0) { 
        append (G->adjacency[u], v );
     }
     
     else 
     {
       moveTo(G->adjacency[u], 0);
       while(getIndex(G->adjacency[u]) != -1 ) 
       {
           if(v < getElement(G->adjacency[u])) {
              insertBefore(G->adjacency[u], v);
              break;
            }
            else {
            moveNext(G->adjacency[u]);
            }
        }
        
         if(getIndex(G->adjacency[u]) == -1) {
           append ( G->adjacency[u], v );
        }
     }
    
     G->size++;
     
  }
 
 
 
 
   // addEdge() inserts a new edge joining u to v, 
  // i.e. u is added to the adjacency List of v, 
  // and v to the adjacency List of u. Your program
  // is required to maintain these lists in sorted 
  // order by increasing labels. 
  // same as PA4
  void addEdge ( Graph G, int u, int v )
  {
  
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: addEdge() on NULL graph" );
        exit(1);
     }
     // pre-condition
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined" );
        exit(1);
     }
     // pre-condition
     if ( v < 1 || v > getOrder(G) ) 
     {
        printf ( "Graph Error: v undefined" );
        exit(1);
     }
     // add u to v 
     if(length(G->adjacency[u]) == 0) { 
        append (G->adjacency[u], v );
     }
     
     else 
     {
       moveTo(G->adjacency[u], 0);
       while(getIndex(G->adjacency[u]) != -1 ) 
       {
           if(v < getElement(G->adjacency[u])) {
              insertBefore(G->adjacency[u], v);
              break;
            }
            else {
            moveNext(G->adjacency[u]);
            }
        }
        
         if(getIndex(G->adjacency[u]) == -1) {
           append ( G->adjacency[u], v );
        }
     }
           
        // add v to u 
         if(length(G->adjacency[v]) == 0) { 
        append ( G->adjacency[v], u );
     }
     else 
     {
       moveTo(G->adjacency[v], 0);
       while(getIndex(G->adjacency[v]) != -1 ) {
           if(u < getElement(G->adjacency[v])) {
              insertBefore(G->adjacency[v], u);
              break;
            }
            else {
            moveNext(G->adjacency[v]);
            }
        }
        
        if(getIndex(G->adjacency[v]) == -1) {
           append ( G->adjacency[v], u );
        }
     }
        
     
     G->size++;
     G->size++;
  }


  // Translated the pseudo code given
  // in the textbook from page 604
  // received help from a student 

 // Functions DFSVISIT()
  void DFSVISIT ( Graph G, List S, int u) 
  {
     
        // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: DFSVISIT() on NULL graph" );
        exit(1);
     }
     
        // pre-condition
     if ( S == NULL ) 
     {
        printf ( "List Error: BFS() on NULL graph" );
        exit(1);
     }
     
    
     G->time++;
     G->d[u] = G->time;
     G->color[u] = GRAY;
     // move to the beginning of the list 
     moveTo(G->adjacency[u], 0);
   
     int adj;
     while(getIndex(G->adjacency[u]) != -1)
     {
        adj = getElement(G->adjacency[u]);
        if(G->color[adj] == WHITE) 
        {
           G->p[adj] = u;
           DFSVISIT(G, S, adj);
        }
        // move to the next thing in the list
        moveNext(G->adjacency[u]);
       
       }
      
      G->color[adj] = BLACK;
      G->time++;
      G->f[u] = G->time;
      // add to the front of the list after the visit operation
      prepend(S, u);

 }



  // Translated the pseudo code given
  // in the textbook from page 604
  // received help from a student 

  // Function DFS()
  

  void DFS ( Graph G, List S ) 
  {
  
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: DFS() on NULL graph" );
        exit(1);
     }
    
       // pre-condition
     if ( S == NULL ) 
     {
        printf ( "List Error: DFS() on NULL graph" );
        exit(1);
     }
     
     // copy the list to tmplist to perform DFS on
     // empty the list. 
     List tmpList = copyList(S);
     clear(S);
     int u;
     
     // used DFS algorithm from the book on page 604
     for ( u = 1; u <= getOrder(G); u++ )
     {
        G->color[u] = WHITE;
        G->p[u] = NIL;
        
      }
      // set time to 0, move to the start of the list
      G->time = 0;
      moveTo(tmpList, 0);
      
      int v;
      while(getIndex(tmpList) != -1)
      {
         v = getElement(tmpList);
         if( G->color[v] == WHITE) 
         {
         DFSVISIT (G, S, v);
         }
         // move to the next thing in the list.
         moveNext(tmpList);
      }
      
      freeList(&tmpList);
  }

     

 

// -------------------------------------------------------------------
// 
// *********************** Other Procedures ************************ //
//
// -------------------------------------------------------------------

  Graph transpose(Graph G) 
  {
  
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: transpose() on NULL graph" );
        exit(1);
     }
  
    List L;
    int i;
    Graph tmpGraph = newGraph(getOrder(G));
     
     for ( i = 1; i <= getOrder(G); i++ ) 
     {
     
       L = G->adjacency[i];
       
       moveTo(L,0);
       while ( getIndex(L) != -1 )
        {
          
           addArc(tmpGraph, getElement(L), i);
           moveNext(L);
        }
        
     }
     return tmpGraph;
     
  
  }
  

  // Function copyGraph   
  // based of the copyList from List.c

  Graph copyGraph(Graph G) 
  {
     
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: copyGraph() on NULL graph" );
        exit(1);
     }
     
     Graph tmpGraph = newGraph(getOrder(G));

     int i;
     for ( i = 1; i <= getOrder(G); i++ )
     {
        // call copyList from 
        // List.c
        
        tmpGraph->adjacency[i] = copyList(G->adjacency[i]);
     }
    
     return tmpGraph;
     
  
  }


  // Finally, function printGraph() prints the
  // adjacency list representation of G to
  // the file pointed to by out.
  // Based off the example form professor Tantalo
  // Received TA's help and Professor's help for this 
  // function 
  
  void printGraph ( FILE* out, Graph G ) 
  {
   
     if ( G == NULL ) 
     {
        printf ( "Graph Error: printGraph() on NULL graph" );
        exit(1);
     }
     
     int x;
     for(  x = 1; x <= getOrder(G); x++) 
     {
        fprintf(out, "%d: ", x);  
        printList ( out, G->adjacency[x] );
        fprintf(out, "\n");
     }
    
  }
     
     
     
  // END OF PROGRAM.





