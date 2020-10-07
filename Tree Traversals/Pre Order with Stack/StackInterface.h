#define MAXSTACKSIZE 100

typedef struct NodeTag{
        char Symbol;
        struct NodeTag *LLink;
        struct NodeTag *RLink;
} TreeNode;

typedef TreeNode *ItemType;

typedef struct{
        int Count;
        ItemType Items[MAXSTACKSIZE];
} Stack;

void InitializeStack(Stack *);

int Empty(Stack *);

int Full(Stack *);

void Pop(Stack *, ItemType *);

void Push(ItemType , Stack *);