#include <stdio.h>
#include <stdlib.h>
#include "StackInterface.h"

void InitializeStack(Stack *S) { S->ItemList=NULL; }

int SEmpty(Stack *S) { return (S->ItemList==NULL); }

int SFull(Stack *S) { return 0; }

void SPush(ItemType X, Stack *S){
   StackNode *Temp;

   Temp=(StackNode *) malloc(sizeof(StackNode));

   if (Temp==NULL){
      printf("system storage is exhausted");
   } else {
      Temp->Link=S->ItemList;
      Temp->Item=X;
      S->ItemList=Temp;
   }
}


void SPop(Stack *S, ItemType *X) {
   StackNode *Temp;

   if (S->ItemList==NULL){
     printf("attempt to pop the empty stack");
   } else {
      Temp=S->ItemList;
      *X=Temp->Item;
      S->ItemList=Temp->Link;
      free(Temp);
   }
}
