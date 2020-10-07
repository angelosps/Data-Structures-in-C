// Binary Search Tree non-recursive

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXN 5
typedef int Item;
typedef int Key;

#define NULLitem -1 
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (!less(A, B) && !less(B, A))

typedef struct STnode* link;
struct STnode { Item item; link l, r; int N; };

static link head, NULLNODE;

void STinit();
Item ITEMrand(void);
int ITEMscan(Item *);
void ITEMshow(Item);
int STcount();
bool STsearch(Key);
void STsort(void (*visit)(Item));
void STinsert1(Item);
Item SelectI(int); 
bool BSTdelete(Item);

void main( void ){ 
    STinit();
    for (int N = 1; N <= MAXN; N++) {
        printf("Inserting item %d\n", N);
        STinsert1(N);
    }
    
    printf("The keys in sorted order are: ");
    STsort(ITEMshow); printf("\n");
    printf("The 3rd smallest key in the tree is: %d\n", SelectI(3));
    printf("Searching for item '1'.. "); STsearch(1) ? printf("Found!\n") : printf("Not found!\n");
    printf("Deleting item '2'..\n"); BSTdelete(2);
    printf("The keys in sorted order are: ");
    STsort(ITEMshow); printf("\n");
    printf("Searching for item '2'.. "); STsearch(2) ? printf("Found!\n") : printf("Not found!\n");
    printf("The 3rd smallest key in the tree is: %d\n", SelectI(3));
}

int ITEMrand(void) { return rand(); }

int ITEMscan(int *x) { return scanf("%d", x); }

void ITEMshow(int x) { printf("%10d", x); }

link NEW(Item item, link l, link r, int N){ 
link x = malloc(sizeof *x);
    x->item = item; x->l = l; x->r = r; x->N = N;
    return x;
}

void STinit() { head = (NULLNODE = NEW(NULLitem, NULL, NULL, 0)); }

int STcount() { return head->N; }

bool STsearch(int k){ 
link curr = head; 

    while (curr!=NULLNODE){ 
        if(curr->item == k) 
            return true;
        else if( k < curr->item )  
            curr = curr->l; 
        else curr = curr->r; 
    }

return false; 
}

void STinsert1(Item item){
link curr=head, parent = NULLNODE;
Key v = key(item), t = key(curr->item);
link newnode = NEW(item, NULLNODE, NULLNODE, 1);

    if(head == NULLNODE) {
        head = newnode;
        return;
    }
    while ( curr != NULLNODE ){
        parent = curr;
        (curr->N)++; 
        if(less(v, t)) curr = curr->l;
        if(less(t, v)) curr = curr->r;
    }

    if(parent->item > item) parent->l = newnode;
    else parent->r = newnode;

}

void sortR(link h, void (*visit)(Item)){
    if (h == NULLNODE) return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
}
  
void STsort(void (*visit)(Item)) { sortR(head, visit); }

Item SelectI(int k){ 
link curr = head; 

    while (curr!=NULLNODE){ 
        if(curr->l->N == k-1) 
            return curr->item;
        else if( k > curr->l->N ) { 
            k = k - (curr->l->N) - 1; 
            curr = curr->r; 
        }
        else curr = curr->l; 
    }

return NULLitem; 
}

bool BSTdelete(Item x){
		link curr, parent;
		curr=head;
		parent=NULLNODE;
		while(curr->item != x){ 
			parent=curr;
			if(x < curr->item)
				curr=curr->l;
			else if(x > curr->item)
				curr=curr->r;
			if(curr == NULLNODE)
				return false;   
		}

		if(curr->l != NULLNODE && curr->r != NULLNODE){	
			link prev = curr; 
			link child = curr->r; 
			while(child->l != NULLNODE){ 
				prev = child;
				child = child->l;
			}
			curr->item = child->item; 
			if(child->r != NULL) 
				if(prev != curr) 
					prev->l = child->r; 
				else
					prev->r = child->r;
			else 
				if(prev != curr)
					prev->l = NULLNODE;
				else
					prev->r = NULLNODE;
			free( child ); 
		}
		else if(parent != NULLNODE){ 
			bool left=false;
			if(x < parent->item)
				left=true;
			if(curr->l == NULLNODE && curr->r == NULLNODE){	
				if(left==true)
					parent->l=NULLNODE;
				else
					parent->r=NULLNODE;
			}
			else if(curr->r == NULLNODE){					
			if(left==true)
				parent->l=curr->l;
			else
				parent->r = curr->l;
			}
			else if(curr->l == NULLNODE){					
			if(left==true)
				parent->l=curr->r;
			else
				parent->r = curr->r;
			}
			free( curr );
		}
		else if(parent == NULLNODE){ 				
			if(curr->l == NULLNODE && curr->r == NULLNODE) 
				head = NULLNODE; 
			else if(curr->l == NULLNODE)
				head = curr->r; 
			else if(curr->r == NULLNODE)
				head = curr->l; 
		}
}


