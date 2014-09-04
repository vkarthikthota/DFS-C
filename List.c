

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//structs--------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
  int data;
  struct NodeObj* next;
  struct NodeObj* prev;
  struct NodeObj* cursor;
} NodeObj;

// private NodeObj type
typedef struct NodeObj* Node;

// private ListObj type
typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;
//typedef struct ListObj* List;
// Constructors-Destructors--------------------------------------------

// newNode()
// Returns reference to a new Node object. Initialzes next, prev,
// and data fields
// Private
Node newNode(int data) {
  Node N = malloc(sizeof(NodeObj));
  N->next = NULL;
  N->prev = NULL;
  N->data = data;
  return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private
void freeNode(Node* pN) {
  if( pN!=NULL && *pN!=NULL ) {
     free(*pN);
     *pN = NULL;
  }
}

// newList() 
// Retunrs reference to new empty List Object.
List newList(void) {
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return(L);
}

// freeList() 
// Fress all the heap memory associated with List *pL, and sets
// *pL to NULL.S
void freeList(List* pL) {
  if(pL==NULL || *pL==NULL) { return; }
  while( length(*pL) != 0) {
     deleteFront(*pL);
  }
  free(*pL);
  *pL = NULL;
}

// Access Fucntions----------------------------------------------------

// Returns number of elements in this List.
int length(List L) {
  if(L == NULL) {
     printf("List Error: calling length() on NULL List reference\n");
     exit(1);
  }
  return(L->length);
}

// Returns the index of the cursor elemtn in this list, or
// returns -1 if the cursor eleent is undefined.
int getIndex(List L) {
  if(L->cursor == NULL) {
     L->index = -1;
  }
  return L->index;
}

// Returns front element in this List. Pre: length() > 0.
int front(List L) {
  if(L == NULL) {
     printf("List Error: calling front() on NULL List reference\n");
     exit(1);
  }
  if(L->length == 0) {
     printf("List Error: calling front() on an empty list");
     exit(1);
  }
  return(L->front->data);
}

// Returns back element in this list. Pre: length() > 0.
int back(List L) {
  if(L == NULL) {
     printf("List Error: calling front() on NULL list reference\n");
     exit(1);
  }
  if(L->length == 0) {
     printf("List Error: calling back() on an empty list");
     exit(1);
  }
  return(L->back->data);
}

// Returns cursor element in this list. Pre: legnth()>0,
//  getIndext()>=0.
int getElement(List L) {
  if(L == NULL) {
     printf("List Error: calling getElement() on NULL list reference");
     exit(1);
  }
  if(L->length == 0) {
     printf("List Error: calling getElement() on an empty list");
     exit(1);
  }
  if(L->cursor == NULL) {
     printf("List Error:  getElement() when cursor is undefined.");  
     exit(1);
  }
  return (L->cursor->data);
}
//given in example by the professor
// Returns true if this List and L are the same integer 
// sequence. The cursor is ignored in both lists.  
int equals(List A, List B) {
  int flag = 1;
  Node N = NULL;
  Node M = NULL;
 
  if( A==NULL || B==NULL) { 
     printf("List Error: calling equals() on NULL List referece\n");
  }
  N = A->front;
  M = B->front;
  if( A->length != B->length ) { return 0; }
  while(flag && N!=NULL) {
     flag = (N->data==M->data);
     N = N->next;
     M = M->next;
  }
  return flag;
}

// Manipulation Procedures---------------------------------------------
// Re-sets this List to the empty state. 
void clear(List L) {
  while(L->length != 0) {
     deleteFront(L);
  }
  L->front = L->back = L->cursor = NULL;
}

// If 0<=i<=length()-1, moves the cursor to the element 
// // at index i, otherwise the cursor becomes undefined.
void moveTo(List L, int i) {
  if(i >= 0 && i <= length(L) -1 ) {
     L->index = i;
     L->cursor = L->front;
     int j; 
     for(j = 0; j < i; j++) {
        L->cursor = L->cursor->next;
     }
  }
     else {
       L->cursor = NULL;
     }
}

// If 0<getIndex()<=length()-1, moves the cursor one step toward the 
// front of the list. If getIndex()==0, cursor becomes undefined.
//  If getIndex()==-1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1). 
void movePrev(List L) {
  if(L == NULL) {
     printf("List Error: calling movePrev() on empty List");
     exit(1);
  }
  if(L->length == 0) {
     printf("List Error: calling movePrev() ...\n");
     exit(1);
  }
  L->cursor = L->cursor->prev;
  L->index--;
}

// If 0<=getIndex()<length()-1, moves the cursor one step toward the 
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L) {
   if(L == NULL) {
     printf("List Error: calling moveNext() on empty List");
     exit(1);
  }
  if(L->length == 0) {
     printf("List Error: calling moveNext() ...\n");
     exit(1);
  }  
  L->cursor = L->cursor->next;
  L->index++;
}

// Inserts new element before front element in this List.
void prepend(List L, int data) {
  Node tmp = newNode(data); 
  if(L->length == 0 ) {   
     L->front = L->back = tmp;
  }
  else {
     L->front->prev = tmp;
     tmp->next = L->front;
     L->front = tmp;
  }
  L->length++;
  L->index++;
}

//Inserts new element after back element in this List.
void append(List L, int data) {
  Node tmp = newNode(data);
  if(L->length == 0) {
     L->front = L->back = tmp;
  }
  else {
     L->back->next = tmp;
     tmp->prev = L->back;
     L->back = tmp;
  }
  L->length++;
}

// Inserts new element before cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data) {
  if(L->length == 0) {
     printf("List Error: cannot insertBefore on empty List");
     exit(1);
  }
  if(L->cursor == NULL) {
     printf("List Error: cursor undefined in insertbefore");
     exit(1);
  }
  Node tmp = newNode(data);
  if(L->cursor !=  L->front) {
     L->cursor->prev->next = tmp;
     tmp->prev = L->cursor->prev;
  }
  tmp->next = L->cursor;
  L->cursor->prev = tmp;
  if(L->cursor == L->front) {L->front = tmp; }
  L->index++;
  L->length++;
}

// Inserts new element after cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertAfter(List L, int data) {
  if(L->length == 0) {
     printf("List Error: cannot insertBefore on empty List");
     exit(1);
  }
  if(L->cursor == NULL) {
     printf("List Error: cursor undefined in insertafter");
     exit(1);
  }
  Node tmp = newNode(data);
  if(L->cursor !=  L->back) {
     L->cursor->next->prev = tmp;
     tmp->next = L->cursor->next;
  }
  tmp->prev = L->cursor;
  L->cursor->next = tmp;
  if(L->cursor == L->back) {L->back = tmp; }
  L->length++;
}

// Deletes the front element in this List. Pre: length()>0
void deleteFront(List L) {
  
  if(L == NULL) {
     printf("List Error: null");
     exit(1);
  }
  Node tmp = NULL;
  tmp = L->front;
  if(length(L) > 1) {
     L->front = L->front->next;
     L->front->prev = NULL;
  }
  else {
     L->front = L->back = NULL;
  }
  L->length--;
  freeNode(&tmp);
}

// Deletes the back element in this List. Pre: length()>0
void deleteBack(List L) {
  if(L == NULL) {
     printf("List Error");
     exit(1);
  }
  
  Node tmp = NULL;
  tmp = L->back;
  if(length(L) > 1) {
     L->back = L->back->prev;
     L->back->next = NULL;
  }
  else {
     L->front = L->back = NULL;
  }
  L->length--;
  freeNode(&tmp);
}

// Deletes cursor element in this List. Cursor is undefined after this 
// operation. Pre: length()>0, getIndex()>=0
void delete(List L) {
  if(L->length == 0) {
     printf("List Error: calling delete() on empty List");
     exit(1);
  }
  if(L->cursor == NULL) {
     printf("List Error: curosr undefined");
     exit(1);
  }
 
  if(L->cursor == L->front) {
     deleteFront(L);
  }
  else if(L->cursor == L->back) {
     deleteBack(L);
  }
  else {
    Node tmpPrev, tmpNext;
    tmpPrev = L->cursor->prev;
    tmpNext = L->cursor->next;
    tmpPrev->next = tmpNext;
    tmpNext->prev = tmpPrev;
    L->cursor = NULL;
    L->length--;
    freeNode(&(L->cursor));
  }
}


//Other Methods--------------------------------------------------------
// Prints the list
//PrintList () was provided in the examples folder by Professor Tantalo
void printList(FILE* out, List L) {
  Node N = NULL;
  if(L == NULL) {
     printf("List Error: calling printList() on NULL reference\n");
     exit(1);
  }
  for(N = L->front; N != NULL; N = N->next) {
     if(N->next == NULL) {
        fprintf(out, "%d", N->data);
     } 
     else if (N->prev == NULL) {
        fprintf(out, "%d ", N->data);
     }
     else {
     fprintf(out, "%d ", N->data);
     }
  }
}

// copyList () was provdied in the examples by Professor Tantalo
// Returns a new list representing the same integer sequence as this 
// list. The cursor in the new list is undefined, regardless of the 
// state of the cursor in this List. This List is unchanged. 
List copyList(List L) {
  List X  = newList();
  Node N = L->front;
  while(N != NULL) {
     append(X,N->data);
     N = N->next;
  }
  return X;
}

