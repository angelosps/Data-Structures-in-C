#include <stdio.h>
#include <stdlib.h>
#define NULLitem -1 
#define less(A, B) ( A < B )
#define equal(A, B) ( A == B )
#define MAX_NUM 5
typedef int ItemType;
typedef int Key;
typedef struct STnode* link;
struct STnode { ItemType item; link l, r; int N; }; 
link head, NULLnode;

void ITEMshow(ItemType); 
void BSTinit(); 
int BSTcount(); 
void BSTinsert(ItemType); 
ItemType BSTsearch(Key); 
void BSTdelete(ItemType);
ItemType BSTselect(int); 
void BSTsort(void (*visit)(ItemType)); 

int main(void){ 

    BSTinit(MAX_NUM);

    for (ItemType item = 1; item <= MAX_NUM; item++){
        if (BSTsearch(item) != NULLitem) continue; //if item already exists in the Tree continue
        printf("Inserting item '%d'\n", item);
        BSTinsert(item); 
    }
    
    printf("The keys in sorted order are: ");
    BSTsort(ITEMshow); printf("\n\n");
    printf("Tree consists of:\n");
    printf("->%d keys\n", MAX_NUM);
    printf("->%d distinct keys\n\n", BSTcount());
    
    ItemType i=BSTselect(1);
    printf("Item with the second smallest key is '%d'\n\n", i);
    
    BSTdelete(1); printf("Item '1' has been deleted.\n");
    BSTdelete(2); printf("Item '2' has been deleted.\n");
    printf("After the two deletions the keys in sorted order are: ");
    BSTsort(ITEMshow); printf("\n");

  
    return 0;
}

void ITEMshow(int x){ printf("'%d' ", x); }

// make the node
link NEW(ItemType item, link l, link r, int N){ 
    link x = malloc(sizeof *x);
    x->item = item; x->l = l; x->r = r; x->N = N;
    return x;
}

// initialize the tree  
void BSTinit(){ head = (NULLnode = NEW(NULLitem, NULL, NULL, 0)); }

// tree-subtree size
int BSTcount() { return head->N; }

/* Recursive binary-search */
ItemType searchR(link h, Key v){ //binary logic
    Key t = h->item;
    if (h == NULLnode) return NULLitem; //if out of tree return null
    if equal(v, t) return h->item; //if key is the curr node then return it 
    if less(v, t) return searchR(h->l, v); //if key is smaller than curr node check left
    else return searchR(h->r, v); //if key exists it would be right so check this range
}
  
ItemType BSTsearch(Key v){ return searchR(head, v); }

/* Recursive insert operation */
link insertR(link h, ItemType item){ 
    Key v = item, t = (h->item);
    if (h == NULLnode) return NEW(item, NULLnode, NULLnode, 1); //if end of the tree put the new node
    if less(v, t) //if smaller than curr node go left
        h->l = insertR(h->l, item);
    else //else go right
        h->r = insertR(h->r, item);
    (h->N)++; //increase the size of subtree  
    return h;
}
  
void BSTinsert(ItemType item){ head = insertR(head, item); }

link rotateR(link h){ //right node rotation  
    link  x = h->l; h->l = x->r; x->r = h;
    return x; 
}

link rotateL(link h){ //left node rotation
    link x = h->r; h->r = x->l; x->l = h;
    return x; 
}

//shows recursively the tree in the correct sorted order
void sortR(link h, void (*visit)(ItemType)){
    if (h == NULLnode) return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
}
  
void BSTsort(void (*visit)(ItemType)){ sortR(head, visit); }

/* Recursive select operation */
//Returns the k-th smallest item in zero based indexing 
ItemType selectR(link h, int k){ 
    int t;
    if (h == NULLnode) return NULLitem; //if out of tree return null
    t = (h->l == NULLnode) ? 0 : h->l->N; //how many items are in the left subtree(?)
    if (t > k) return selectR(h->l, k); //the item is in left 
    if (t < k) return selectR(h->r, k-t-1); //the item is in right
    return h->item; //item we search for is the head item
}

ItemType BSTselect(int k){ return selectR(head, k); }

/* partition auxiliary function */
//moves the k-th item to the root (used in joining two subtrees)
link partR(link h, int k){ 
int t = h->l->N;
    if(t > k ) { h->l = partR(h->l, k); h = rotateR(h); }
    if(t < k ) { h->r = partR(h->r, k-t-1); h = rotateL(h); }
    return h;
}

/*joins two subtrees in one when we need to delete a node with two subtrees as child*/
//moves with partR function the most left item to root of the right subtree 
//after joins in the left leaf of right subtree the first subtree to make the link
link joinLR(link a, link b){
    if (b == NULLnode) return a;
    b = partR(b, 0); b->l = a;
    return b;
}

/* recursive deletion operation */ 
//case 1: the node has no children so just remove it
//case 2: the node has only one children so make the child the root and free the space
//case 3: the node has two subtrees so link them and them in one and their root will take its place on the tree
//then free the space of deleted node
link deleteR(link h, Key v){ 
link x; Key t = h->item;
    if (h == NULLnode) return NULLnode; //out of tree; return
    if (less(v, t)) h->l = deleteR(h->l, v);
    if (less(t, v)) h->r = deleteR(h->r, v);
    if (equal(v, t)) { x = h; h = joinLR(h->l, h->r); free(x); } //we found the node to delete and so do it
    return h;
}
  
void BSTdelete(Key v) { head = deleteR(head, v); }
