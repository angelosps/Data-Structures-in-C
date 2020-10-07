#include <stdio.h>
#include <stdlib.h>
typedef int ItemType;

typedef struct QueueNodeTag{
      ItemType Item;
      struct QueueNodeTag *Link;
}QueueNode;

typedef struct{
      QueueNode *Front;
      QueueNode *Rear;
}Queue;

void InitializeQueue(Queue *Q);
int Empty(Queue *);
void Enqueue(ItemType R, Queue *Q);
void Dequeue(Queue *Q, ItemType *F);

int main(void){
   Queue Q;

   InitializeQueue(&Q);

   for(int i=1; i<=3; i++) Enqueue(i, &Q);

   while(!Empty(&Q)){
   int i;
      Dequeue(&Q, &i);
      printf("Item '%d' removed from the queue.\n", i);
   }

   printf("Queue is empty.\n");
}

void InitializeQueue(Queue *Q){
    Q->Front=NULL;
    Q->Rear=NULL; 
}

int Empty(Queue *Q) { return(Q->Front==NULL); }

/* Inserting an item in the Queue */
void Enqueue(ItemType R, Queue *Q){
   QueueNode *Temp;
   printf("Inserting '%d' in the queue..\n", R);
   Temp=(QueueNode *)malloc(sizeof(QueueNode));

   if (Temp==NULL){
      printf("System storage is exhausted!");
   } else {
      Temp->Item=R;
      Temp->Link=NULL;
      if (Q->Rear==NULL){
         Q->Front=Temp;
         Q->Rear=Temp;
      } else {
         Q->Rear->Link=Temp;
         Q->Rear=Temp;
      }
   }
}

/* Deleting from the Queue */
void Dequeue(Queue *Q, ItemType *F){
   QueueNode *Temp;

   if (Q->Front==NULL){
      printf("Attempting to remove from an empty queue!");
   } else {
      *F=Q->Front->Item;
      Temp=Q->Front;
      Q->Front=Temp->Link;
      free(Temp);
      if (Q->Front==NULL) Q->Rear=NULL;
   }
}
