// Priority Queue - Min Heap Implementation
#include <stdio.h>
#define MAX_SIZE 10
typedef int ItemType;
typedef ItemType PQArray[MAX_SIZE+1];

typedef struct {
        int Count;
        PQArray ItemArray;
}PriorityQueue;

void Initialize (PriorityQueue *);
int Empty (PriorityQueue *);
int Full (PriorityQueue *);
void Push (ItemType, PriorityQueue *);
ItemType Top (PriorityQueue *);
void SortArray(ItemType *);

int main(void){

ItemType A[MAX_SIZE];

printf("Array before sorting..\n");
for (int i=0; i<10; ++i){
    A[i]=(3*i-13)*(3*i-13);
    printf("%d ",A[i]);
}
printf("\n");

SortArray(A);

printf("Array after sorting with Priority Queue..\n");

for(int i=0; i<10; ++i) printf("%d ", A[i]);

printf("\n");

return 0;
}

/* Sorting a given array using the Priority Queue */
void SortArray(ItemType *A){
PriorityQueue PQ;

   Initialize(&PQ);
   for (int i=0; i<MAX_SIZE; ++i) Push(A[i], &PQ);
   for (int i=MAX_SIZE-1; i>=0; --i) A[i]=Top(&PQ);
}

void Initialize(PriorityQueue *PQ) { PQ->Count=0; }

int Empty(PriorityQueue *PQ) { return(PQ->Count==0); }

int Full(PriorityQueue *PQ) { return(PQ->Count==MAX_SIZE); }

/* Pushes an item to the Priority Queue */
void Push(ItemType Item, PriorityQueue *PQ){ 

    //keep track of the locations we compare
    int ChildLoc; 
    int ParentLoc;

    (PQ->Count)++;
    ChildLoc=PQ->Count; //new leaf is created
    ParentLoc=ChildLoc/2; //find the parent of new item
    while (ParentLoc != 0){ //find the correct position in the tree for the new item
        if (Item <= PQ->ItemArray[ParentLoc]){ //if this is, then place the item
            PQ->ItemArray[ChildLoc]=Item;
            return;
        }else{ //else make the swap between parent and child and go up
            PQ->ItemArray[ChildLoc]=PQ->ItemArray[ParentLoc];
            ChildLoc=ParentLoc;
            ParentLoc=ParentLoc/2;
       }
    }
    
    PQ->ItemArray[ChildLoc]=Item; //the new item placed in the root position

}

/* Returns the item with the highest priority */
ItemType Top(PriorityQueue *PQ){ 
   int CurrentLoc;
   int ChildLoc;
   ItemType ItemToPlace; // the most right of the bottom which is initially deleted
   ItemType ItemToReturn; // highest priority

   if(Empty(PQ)) { printf("Trying to pop from an Empty Queue!\n"); return -1; }

   ItemToReturn=PQ->ItemArray[1]; // return the root which has the highest priority
   ItemToPlace=PQ->ItemArray[PQ->Count];
   (PQ->Count)--; // item deleted
   CurrentLoc=1; // starting heapifying process from the root
   ChildLoc=2*CurrentLoc;

   while (ChildLoc <= PQ->Count){
       if (ChildLoc < PQ->Count){ // not the last item
          if (PQ->ItemArray[ChildLoc+1] > PQ->ItemArray[ChildLoc]){
             ChildLoc++; // switch to the next item which is larger
          }
       }
       if (PQ->ItemArray[ChildLoc] <= ItemToPlace){
           PQ->ItemArray[CurrentLoc]=ItemToPlace;
           return(ItemToReturn);
       } else {
           PQ->ItemArray[CurrentLoc]=PQ->ItemArray[ChildLoc];
           CurrentLoc=ChildLoc;
           ChildLoc=2*CurrentLoc;
       }
    }
    PQ->ItemArray[CurrentLoc]=ItemToPlace;

    return(ItemToReturn);
}
