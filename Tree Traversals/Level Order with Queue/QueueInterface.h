#include <stdio.h>
#include <stdlib.h>
#define MAXQUEUESIZE 100

typedef struct NodeTag{
      char Symbol;
      struct NodeTag *LLink;
      struct NodeTag *RLink;
} TreeNode;

typedef TreeNode *ItemType;

typedef struct {
      int Count;
      int Front;
      int Rear;
      ItemType Items[MAXQUEUESIZE];
} Queue;

void InitializeQueue(Queue *);
int Empty(Queue *);
int Full(Queue *);
void Insert(ItemType, Queue *);
void Remove(Queue *, ItemType *);
