// AVL Tree implementation ( Balanced BST )
// and the histogram problem
// Histogram problem: showing the frequency of keys inserted in the tree.

#include <stdio.h>
#include <stdlib.h>
typedef int Item;
typedef int Key;
#define NULLitem -1 
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (!less(A, B) && !less(B, A))
typedef struct STnode* link;
struct STnode { Item item; link l, r; int height; int freq; };

link head, z;

int ITEMrand(void) { return rand(); }

int ITEMscan(int *x) { return scanf("%d", x); }

void ITEMshow(int x) { printf(" %d\t", x); }

link NEW(Item item, link l, link r, int N, int freq){ 
link x = malloc(sizeof *x);
    x->item = item; x->l = l; x->r = r; x->height = N; x->freq=1;
    return x;
}

int max(int a, int b){
    if ( a >= b )  return a;
    return b;
}

void AVLinit() { head = (z = NEW(NULLitem, NULL, NULL, 0, 0)); }

int AVLcount() { return head->height; }

Item searchR(link h, Key v, int f_update){ 
Key t = key(h->item);
    if (h == z) return NULLitem;
    if eq(v, t) {
        if(f_update) h->freq++;
        return h->item;
    }
    if less(v, t) return searchR(h->l, v, f_update);
    else return searchR(h->r, v, f_update);
}
  
Item AVLsearch(Key v, int f_update) { return searchR(head, v, f_update); }

int balancefactor(link h){
    if(h == z) return 0;
    return ( h->l->height - h->r->height );
}

link rotR(link h){ 
link x = h->l; h->l = x->r; x->r = h;
h->height = max(h->l->height, h->r->height) + 1;
x->height = max(x->l->height, x->r->height) + 1;
    return x; 
}

link rotL(link h){ 
link x = h->r; h->r = x->l; x->l = h;
h->height = max(h->l->height, h->r->height) + 1;
x->height = max(x->l->height, x->r->height) + 1;
    return x; 
}

void sortR(link h, void (*visit)(Item)) {
    if (h == z) return;
    sortR(h->l, visit);
    visit(h->item); printf("   %d\n", h->freq);
    sortR(h->r, visit);
}
  
void AVLsort(void (*visit)(Item)) { sortR(head, visit); }

Item selectR(link h, int k){ 
    int t;
    if (h == z) return NULLitem;
    t = (h->l == z) ? 0 : h->l->height;
    if (t > k) return selectR(h->l, k);
    if (t < k) return selectR(h->r, k-t-1);
    return h->item;
}

Item AVLselect(int k) { return selectR(head, k); }

link partR(link h, int k) { 
int t = h->l->height;
    if (t > k )      
      { h->l = partR(h->l, k); h = rotR(h); }
    if (t < k )
      { h->r = partR(h->r, k-t-1); h = rotL(h); }
    return h;
}

link joinLR(link a, link b){
    if (b == z) return a;
    b = partR(b, 0); b->l = a;
    return b;
}
  
link deleteR(link h, Key v){ 
link x; Key t = key(h->item);
    if (h == z) return z;
    if (less(v, t)) h->l = deleteR(h->l, v);
    if (less(t, v)) h->r = deleteR(h->r, v);
    if (eq(v, t))      
    { x = h; h = joinLR(h->l, h->r); free(x); }
    return h;
}
  
void AVLdelete(Key v) { head = deleteR(head, v); }

// to convert a BST to AVL just take care of the rotations when inserting an item
link insertR(link h, Item item){ 
Key v = key(item), t = key(h->item);
    //if reached the correct (empty) place to insert the new node
    if (h == z) return NEW(item, z, z, 1, 1); //make a new leaf node with the inserted item
    
    //the item to be inserted is smaller than the curr node
    if less(v, t) h->l = insertR(h->l, item); //so go to search in left subtree the correct place 
    
    //the item to be inserted is bigger than the curr node
    else h->r = insertR(h->r, item); //so go in the right subtree to find the correct place for the new node(item)
    
    h->height = 1 + max(h->l->height, h->r->height); //after inserting the new node, update the height in previous nodes 
    
    int b = balancefactor(h); //check the balance factor of each previous nodes to see if rotations needed

    // case where the current node is '//' (left left unbalanced)
    if( b > 1 && item < h->l->item ) // left subtree height - right subtree height > 1 
        return rotR(h); //perform a right rotation

    // case where node is '\\' (right right unbalanced)
    if( b < -1 && item > h->r->item ) // right subtree height - left subtree height > 1 
        return rotL(h); //perform a left rotate 

    // left right case
    // the left subtree is bigger than right subtree such as follows: 
    /*
    i.e. the node '4' is left-right unbalanced
        4
       / 
      2
       \
        3
    
    1. make a left rotation at '2'
    2. make a right rotation at '4'
    */ 
    if( b > 1 && item > h->l->item ){
        h->l = rotL(h->l); // first, perform a left rotation at the h's left child
        return rotR(h); // then, perform a right rotation at h 
    }
    
    // right left case 
    // the right subtree is bigger than left subtree such as follows: 
    /*
    i.e. the node '2' is right-left unbalanced
        2
         \
          4
         / 
        3
    
    1. make a right rotation at '4'
    2. make a left rotation at '2'
    */ 
    if( b < -1 && item < h->r->item ){
        h->r = rotR(h->r); // first, perform a right rotation at the h's right child
        return rotL(h); // then, perform a left rotation at h
    }

    return h; 
}
  
void AVLinsert(Item item) { 

    if(item == AVLsearch(item, 1)) {
        printf("Attempted to insert key '%d' but it already exists in the Tree\n", item);
        return;
    }

head = insertR(head, item); 
printf("Key '%d' successfully inserted in the Tree.\n", item);

}

int main(void){ 

    AVLinit();
    printf("Inserting keys {2, 4, 2, 2, 3, 4, 2, 6, 4, 2} in the tree.\n");
    AVLinsert(2); AVLinsert(4); AVLinsert(2); AVLinsert(2); AVLinsert(3); 
    AVLinsert(4); AVLinsert(2); AVLinsert(6); AVLinsert(4); AVLinsert(2);
    
    printf("KEY\t FREQUENCY\n");
    AVLsort(ITEMshow); 

}
