#define MAXCOUNT 10

typedef struct{
      int first;
      int second;
} pair;

typedef pair PQItem;
typedef PQItem PQArray[MAXCOUNT+1];

typedef struct {
      int Count;
      PQArray ItemArray;
} PriorityQueue;

void PQInitialize (PriorityQueue *);
int PQEmpty (PriorityQueue *);
int PQFull (PriorityQueue *);
void PQInsert (PQItem, PriorityQueue *);
PQItem PQRemove (PriorityQueue *);
