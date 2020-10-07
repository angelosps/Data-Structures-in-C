#include <stdio.h>
#include <stdlib.h>
#include "QueueInterface.h"

void LevelOrderTraversal(TreeNode *T){
   Queue Q;
   TreeNode *N;

     InitializeQueue(&Q);
     Insert(T, &Q);
     while (!Empty(&Q)){
          Remove(&Q, &N);
          if (N!=NULL){
              printf("%c\n", N->Symbol);
              Insert(N->LLink, &Q);
              Insert(N->RLink, &Q);
          }
       }
}

int main(void){
   TreeNode *T, *M, *N;

   /* constructing a tree with three nodes */
   printf("Constructing a tree with three nodes..\n");
   T=(TreeNode *)malloc(sizeof(TreeNode));

   T->Symbol='+';
   printf("Symbol '+' added to Tree as the root\n");
   M=(TreeNode *)malloc(sizeof(TreeNode));
   T->LLink=M;
   M->Symbol='a';
   M->LLink=NULL;
   M->RLink=NULL;
   printf("Symbol 'a' added to Tree as the left child of root\n");

   N=(TreeNode *)malloc(sizeof(TreeNode));
   T->RLink=N;
   N->Symbol='b';
   N->LLink=NULL;
   N->RLink=NULL;
   printf("Symbol 'b' added to Tree as the right child of root\n");
   printf("Level Order Traversal of Tree:\n");
   
   //TREE TRAVERSAL WITH QUEUE
   LevelOrderTraversal(T);
}
