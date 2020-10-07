#include "StackInterface.h"
#include <stdio.h>
void InitializeStack(Stack *S){ S->Count=0; }

int Empty(Stack *S) { return (S->Count == 0); }

int Full(Stack *S){ return(S->Count == MAXSTACKSIZE); }

void Pop(Stack *S, ItemType *X){  
   if (S->Count ==0){
      printf("attempt to pop from an empty stack");
   } else {
      --(S->Count);
      *X=S->Items[S->Count];
   }
}

void Push(ItemType X, Stack *S){
   if (S->Count == MAXSTACKSIZE){
      printf("attempt to push new item on a full stack");
   } else {
      S->Items[S->Count]=X;
      ++(S->Count);
   }
}