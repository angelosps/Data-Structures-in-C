typedef int ItemType;

typedef struct StackNodeTag {
           ItemType Item;
           struct StackNodeTag *Link;
        } StackNode;

typedef struct {
           StackNode *ItemList;
        } Stack;

extern void InitializeStack(Stack *S);
extern int SEmpty(Stack *S);
extern int SFull(Stack *S);
extern void SPush(ItemType X, Stack *S);
extern void SPop(Stack *S, ItemType *X);
