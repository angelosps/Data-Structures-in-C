#include <stdio.h>
#include <stdlib.h>

typedef struct NodeTag{
      char Symbol;
      struct NodeTag *LLink;
      struct NodeTag *RLink;
}TreeNode;

int main(void){
   TreeNode *T, *M, *N;
   
   /* constructing a binary tree with three nodes */
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
   
printf("Printing the Tree..\n");
printf("%4c\n", T->Symbol);
printf("  / \\ \n");
printf("%2c%4c\n", T->LLink->Symbol, T->RLink->Symbol);

}
