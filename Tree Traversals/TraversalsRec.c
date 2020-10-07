/* Tree-Traversals using RECURSION. 
PRE-ORDER TRAVERSAL -> ROOT LEFT RIGHT 
IN-ORDER TRAVERSAL -> LEFT ROOT RIGHT
POST-ORDER TRAVERSAL -> LEFT RIGHT ROOT
Time Complexity: O(N) */
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeTag{
      char Symbol;
      struct NodeTag *LLink;
      struct NodeTag *RLink;
}TreeNode;

typedef enum {PreOrder, InOrder, PostOrder} OrderOfTraversal;

void Visit(TreeNode *T){
     printf("%c\n", T->Symbol);
}

void Traverse(TreeNode *T, OrderOfTraversal TraversalOrder){
     if (T!=NULL){
        if (TraversalOrder==PreOrder){
           Visit(T);
           Traverse(T->LLink, PreOrder);
           Traverse(T->RLink, PreOrder);
        } else if (TraversalOrder==InOrder){
           Traverse(T->LLink, InOrder);
            Visit(T);
           Traverse(T->RLink, InOrder);
       } else if (TraversalOrder==PostOrder){
           Traverse(T->LLink, PostOrder);
           Traverse(T->RLink, PostOrder);
           Visit(T);
      }
   }
}


int main(void){
   TreeNode *T, *M, *N;
   
   /* constructing a tree with three nodes */
   T=(TreeNode *)malloc(sizeof(TreeNode));

   T->Symbol='+';

   M=(TreeNode *)malloc(sizeof(TreeNode));
   T->LLink=M;
   M->Symbol='a';
   M->LLink=NULL;
   M->RLink=NULL;

   N=(TreeNode *)malloc(sizeof(TreeNode));
   T->RLink=N;
   N->Symbol='b';
   N->LLink=NULL;
   N->RLink=NULL;
   printf("Pre-Order Traversal\n");
   Traverse(T, PreOrder);
   printf("\nIn-Order Traversal\n");
   Traverse(T, InOrder);
   printf("\nPost-Order Traversal\n");
   Traverse(T, PostOrder);

}
