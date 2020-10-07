#include <stdio.h>
#include <stdlib.h>
#include "StackInterface.h"

void PreOrderTraversal(TreeNode *T){
     Stack S;
     TreeNode *N;

     InitializeStack(&S);
     Push(T,&S);

     while (!Empty(&S)){
           Pop(&S, &N);

            if (N!=NULL){
                 printf("%c\n", N->Symbol);
                 Push(N->RLink, &S);
                 Push(N->LLink, &S);
            }
      }
}

int main(void){
   TreeNode *T, *M, *N;

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

   printf("Pre Order Traversal of Tree (Root Left Right)\n");
   PreOrderTraversal(T);
return 0;   
}