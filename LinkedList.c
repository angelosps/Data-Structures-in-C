#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ItemType int

typedef struct NodeTag{
      ItemType item;
      struct NodeTag *Link;
}NodeType;
typedef NodeType *NodePointer;

void InsertNewSecondNode(ItemType , NodeType **);
void InsertNewLastNode(ItemType , NodeType **);
void DeleteLastNode(NodeType **);
NodeType *ListSearch(ItemType , NodeType *);
void PrintList(NodeType *);

int main(void){
      NodeType *L;
      L=NULL;
      printf("The list initially contains some integers.\n\n");

      InsertNewLastNode(1, &L);
      InsertNewLastNode(3, &L);
      InsertNewLastNode(4, &L);
      InsertNewLastNode(5, &L);

      PrintList(L);
    
      InsertNewSecondNode(2, &L);

      PrintList(L);

      DeleteLastNode(&L);
      PrintList(L);

      printf("Searching number '1' in the list..\n");
      if (ListSearch(1, L) != NULL)
        printf("'1' is in the list.\n");
      else 
        printf("'1' not found in the list.\n");

      printf("Searching number '5' in the list..\n");
      if (ListSearch(5, L) != NULL)
        printf("'5' is in the list.\n");
      else 
        printf("'5' not found in the list.\n");

      
   return 0;
}

void InsertNewLastNode(ItemType x, NodeType **L){
      NodeType *N, *P;
      printf("Pushing back the number '%d'\n", x);
      N=(NodeType *)malloc(sizeof(NodeType));
      N->item=x;
      N->Link=NULL;

      if (*L == NULL) {
         *L=N;
      } else {
         P=*L;
         while (P->Link != NULL) P=P->Link;
         P->Link=N;
      }
}

void PrintList(NodeType *L){
      NodeType *N;
      printf("Printing the list..\n");
      printf("(");
      N=L;
      while(N != NULL) {
         printf("%d", N->item);
         N=N->Link;
         if (N!=NULL) printf(",");
      }
      printf(")\n");
}

void DeleteLastNode(NodeType **L){
      NodeType *PreviousNode, *CurrentNode;
      printf("Deleting last item..\n");
      if (*L != NULL) {
         if ((*L)->Link == NULL){
            free(*L);
            *L=NULL;
         } else {
            PreviousNode=*L;
            CurrentNode=(*L)->Link;
            while (CurrentNode->Link != NULL){
               PreviousNode=CurrentNode;
               CurrentNode=CurrentNode->Link;
            }
            PreviousNode->Link=NULL;
            free(CurrentNode);
         }
      }
}

void InsertNewSecondNode (ItemType x, NodeType **L){
      printf("Pushing number '%d' after the first item of the list..\n", x);
      NodeType *N;
      N=(NodeType *)malloc(sizeof(NodeType));
      N->item = x;
      N->Link=(*L)->Link;
      (*L)->Link=N;
}

NodeType *ListSearch(ItemType x, NodeType *L){
      NodeType *N;

      N=L;
      while (N != NULL){
        if (N->item==x){
           return N;
        } else {
           N=N->Link;
        }
      }
      return N;
}