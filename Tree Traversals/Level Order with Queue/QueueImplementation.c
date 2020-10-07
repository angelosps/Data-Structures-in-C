#include <stdio.h>
#include "QueueInterface.h"

void InitializeQueue(Queue *Q){
   Q->Count=0;
   Q->Front=0;
   Q->Rear=0;
}

int Empty(Queue *Q){ return(Q->Count==0); }

int Full(Queue *Q){ return(Q->Count==MAXQUEUESIZE); }

void Insert(ItemType R, Queue *Q){
   if (Q->Count==MAXQUEUESIZE){
      printf("Attempting to insert in a full queue!");
   } else {
      Q->Items[Q->Rear]=R;
      Q->Rear=(Q->Rear+1)%MAXQUEUESIZE;
      ++(Q->Count);
   }
}

void Remove(Queue *Q, ItemType *F){
   if (Q->Count==0){
      printf("Attempting to remove from an empty queue!");
   } else {
      *F=Q->Items[Q->Front];
      Q->Front=(Q->Front+1)%MAXQUEUESIZE;
      --(Q->Count);
   }
}
