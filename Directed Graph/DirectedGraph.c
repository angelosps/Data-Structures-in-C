// Implementation of Directed Graph ADT
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "QueueInterface.h"
#include "StackInterface.h"

#define MAXVERTEX 5

typedef enum {FALSE, TRUE} Boolean;

typedef int Vertex;

typedef struct edge {
      Vertex endpoint;
      struct edge *nextedge;
} Edge;

typedef struct DirectedGraph {
      int n;         
      Edge *firstedge[MAXVERTEX];
} Graph;

void Initialize(Graph *G, int n) {
    G->n = n;
    for(int i = 0; i < MAXVERTEX; i++)
        G->firstedge[i] = NULL;
}

void InsertEdge(Graph *G, int src, int dest){
    Edge *new = malloc(sizeof(Edge));  
    new->endpoint = dest;
    new->nextedge = G->firstedge[src];
    G->firstedge[src] = new;
}

void ShowGraph(Graph *G){
    for(int i = 0; i < MAXVERTEX; i++){
        printf("%d: ", i);
        Edge *ptr = G->firstedge[i];
        while( ptr != NULL ) {
            (ptr->nextedge == NULL) ? printf("%d", ptr->endpoint) : printf("%d, ", ptr->endpoint);
            ptr = ptr->nextedge;
        }
        printf("\n");    
    }
}

Graph GraphReverse(Graph *G){
    Graph GRev; 
    Initialize(&GRev, G->n);

        for(int i = 0; i < MAXVERTEX ; i++){
            Edge *ptr = G->firstedge[i];
            while ( ptr != NULL) {
                InsertEdge(&GRev, ptr->endpoint, i);
                ptr = ptr->nextedge;
            }  
        }    
    return GRev;
}

void BreadthTopSort(Graph *G) {
    int predecessorcount[MAXVERTEX];    
    int T[MAXVERTEX];

    Queue Q;
    Vertex v, succ;
    Edge *curedge;
    int place;

    for (v=0; v < G->n; v++)
        predecessorcount[v]=0;
        
    for (v=0; v < G->n; v++)
        for (curedge=G->firstedge[v]; curedge; curedge=curedge->nextedge)
        predecessorcount[curedge->endpoint]++;
    
    InitializeQueue(&Q);

    for (v=0; v < G->n; v++)
        if (predecessorcount[v]==0)
            Insert(v, &Q);
    

    place=-1;
    while (!Empty(&Q)) {
        Remove(&Q, &v);
        place++;
        T[place]=v;
            
        for (curedge=G->firstedge[v]; curedge; curedge=curedge->nextedge){
            succ=curedge->endpoint;
            predecessorcount[succ]--;
            if (predecessorcount[succ]==0)
                Insert(succ, &Q);
        }
    }
    
    bool flag = true;
    for(int i=0; i < G->n; i++) {
        if(T[i] < 0 || T[i] > G->n)
        {flag = false; continue;}
    }

    if(flag == false) 
        printf("\nNo Topological Sort can be formed for all the vertices of the graph.\nMay the graph contains cycle(s)!");
    else {
        for(int i=0; i < G->n; i++)
            printf("%d ", T[i]);
    }
    
    printf("\n");
}

Boolean visited[MAXVERTEX];
int start[MAXVERTEX], end[MAXVERTEX], parent[MAXVERTEX], time=0;

void Traverse(Graph *G, Vertex v, void (*Visit)(Vertex x), int par) {
    Vertex w;
    Edge *curedge;

    visited[v]=TRUE;
    parent[v]=par; 
    start[v] = time++;
    Visit(v);

    curedge=G->firstedge[v];      
    while (curedge) {
        w=curedge->endpoint;        
        if (!visited[w]) Traverse(G, w, Visit, v);
        curedge=curedge->nextedge;  
    }
    end[v] = time++;
}

void classify_edges(Graph *G){

    for(Vertex v = 0; v < MAXVERTEX; v++){
    
        Edge *curedge;
        curedge=G->firstedge[v];      
        while (curedge){
            Vertex w=curedge->endpoint;        
            if ( parent[w] == v )
                printf("Tree Edge (%d->%d)\n", v, w);
            else if (start[v] > start[w] && end[v] < end[w] && parent[v] != w) 
                printf("Back Edge (%d->%d)\n", v, w);
            else if (start[v] < start[w])
                printf("Forward Edge (%d->%d)\n", v, w); 
            else if(start[v] > start[w] && end[v] > end[w])
                printf("Cross Edge (%d->%d)\n", v, w); 

            curedge=curedge->nextedge;  
        }

    }

}

void reset_values(int n){

    for (Vertex v=0; v < n; v++){ 
        visited[v]=FALSE;
        start[v] = end[v] = 0;
    }

}

void DepthFirst(Graph *G, void (*Visit)(Vertex x)) {
    
    for (Vertex v=0; v < G->n; v++)
        if (!visited[v]) {
            printf("DFS(%d):\n", v);
            reset_values(G->n);
            Traverse(G, v, Visit, v);
            printf("\n");
            classify_edges(G);
        }
}

void PrintElement(Vertex x) { printf("%d ", x); }

// Ordering the vertices according to their visit time from DFS.
// A DFS traversal function which after each vertex is processed, adds the vertiex to the Stack
void order(Graph *G, Stack *S, int v) {
    Vertex w;
    Edge *curedge;

    visited[v]=TRUE;

    curedge=G->firstedge[v];      

    while (curedge){
        w=curedge->endpoint;       
        if(visited[w] == 0) order(G, S, w);
        curedge=curedge->nextedge; 
    }

    SPush(v, S);
}

//Implementing the Kosaraju's Algorithm with the use of a Stack
void StrongComponents(Graph *G){
// I am going to use a Stack to keep the time each vertex is visited during DFS

    // reseting the visited matrix
    for(int i = 0; i < G->n; i++) 
        visited[i] = 0;

    Stack S;
    InitializeStack(&S);

    for(int i=0; i<G->n; i++)
        if(visited[i] == 0)
            order(G, &S, i);

    //making the reversed Graph
    Graph Grev = GraphReverse(G);

    for(int i = 0; i < G->n; i++) visited[i] = 0;

    while( !SEmpty(&S) ){
        int v;
        SPop(&S, &v);
        if(visited[v] == 0) {
            Traverse(&Grev, v, PrintElement, 0);
            printf("\n");
        }
    }
}

int main ( void ) {
    Graph G;
    int n;
 
    scanf("%d", &n);
    
    Initialize(&G, n);
    
    char line[4];

    while( fgets(line, 4, stdin) != NULL ){
        if ( strcmp(line, "\n") == 0 ) continue;
        int x, y;
        x = atoi(&line[0]);
        y = atoi(&line[2]);
        InsertEdge(&G, x, y);
    }

    printf("\nGraph:\n");
    ShowGraph(&G);

    Graph GRev = GraphReverse(&G);
    printf("\nReversed Graph:\n");
    ShowGraph(&GRev);

    printf("\nTopological Sort: ");
    BreadthTopSort(&G);
    printf("\n");

    DepthFirst(&G, PrintElement);

    printf("\nStrongly Connected Components:\n");
    StrongComponents(&G);

return 0;
}