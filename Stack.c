#include <stdio.h>
#include <stdlib.h>
typedef int ItemType;

typedef struct StackNodeTag{
      ItemType Item;
      struct StackNodeTag *Link;
}StackNode;

typedef struct{
      StackNode *ItemList;
}Stack;

void InitializeStack(Stack *S);
int Empty(Stack *S);
void Push(ItemType X, Stack *S);
void Pop(ItemType *X, Stack *S);

int main(void){
   
Stack S; 
InitializeStack(&S);

for(int i=1; i<=3; i++) Push(i, &S);

while(!Empty(&S)){
   int x; Pop(&x, &S);
   printf("'%d' Popped from the stack\n", x);
}

printf("Stack is Empty.\n");

   return 0;
}

void InitializeStack(Stack *S) { S->ItemList=NULL; }

int Empty(Stack *S) { return (S->ItemList==NULL); }

void Push(ItemType X, Stack *S){
   StackNode *Temp;
   printf("Pushing '%d' in the Stack..\n", X);

   Temp=(StackNode *) malloc(sizeof(StackNode));

   if (Temp==NULL){
      printf("System storage is exhausted!");
   } else {
      Temp->Link=S->ItemList;
      Temp->Item=X;
      S->ItemList=Temp;
   }
}

void Pop(ItemType *X, Stack *S){
   StackNode *Temp;

   if (S->ItemList==NULL){
     printf("Attempting to pop from an empty stack!");
   } else {
      Temp=S->ItemList;
      *X=Temp->Item;
      S->ItemList=Temp->Link;
      free(Temp);
   }
}
