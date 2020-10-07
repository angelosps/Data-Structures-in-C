#include "PQInterface.h"
#define less(A, B) ( (A.first < B.first) || ( (A.first == B.first) && (A.second < B.second) ) )
//#define greater(A, B) (A.first > B.first && A.second )
void PQInitialize(PriorityQueue *PQ) { PQ->Count=0; }

int PQEmpty(PriorityQueue *PQ) { return(PQ->Count==0); }

int PQFull(PriorityQueue *PQ) { return(PQ->Count==MAXCOUNT); }

void PQInsert(PQItem Item, PriorityQueue *PQ) {
    int ChildLoc;
    int ParentLoc;

    (PQ->Count)++;
    ChildLoc=PQ->Count;
    ParentLoc=ChildLoc/2;

    while (ParentLoc != 0){
       if (!less(Item, PQ->ItemArray[ParentLoc])){
            PQ->ItemArray[ChildLoc]=Item;
            return;
       } else {
            PQ->ItemArray[ChildLoc]=PQ->ItemArray[ParentLoc];
            ChildLoc=ParentLoc;
            ParentLoc=ParentLoc/2;
       }
    }

    PQ->ItemArray[ChildLoc]=Item;
}

PQItem PQRemove(PriorityQueue *PQ) {
   int CurrentLoc;
   int ChildLoc;
   PQItem ItemToPlace;
   PQItem ItemToReturn;
   PQItem NULLitem;
   NULLitem.first = NULLitem.second = -1;

   if(PQEmpty(PQ)) return NULLitem;

   ItemToReturn=PQ->ItemArray[1];
   ItemToPlace=PQ->ItemArray[PQ->Count];
   (PQ->Count)--;
   CurrentLoc=1;
   ChildLoc=2*CurrentLoc;

   while (ChildLoc <= PQ->Count){
       if (ChildLoc < PQ->Count){
          if (less(PQ->ItemArray[ChildLoc+1], PQ->ItemArray[ChildLoc])){
             ChildLoc++;
          }
       }
       if (!less(PQ->ItemArray[ChildLoc], ItemToPlace)){
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