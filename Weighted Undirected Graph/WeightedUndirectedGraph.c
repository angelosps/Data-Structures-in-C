// Weighted Undirected Graph ADT with
// Prim's algorithm for Minimum Spanning Tree

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "PQInterface.h"
#define MAXVERTEX 5

typedef enum {FALSE, TRUE} Boolean;

typedef struct{
      int first; //destination
      int second; //weight
} Vertex;

typedef struct edge {
      Vertex endpoint;
      struct edge *nextedge;
} Edge;

typedef struct DirectedGraph {
      int n;         
      Edge *firstedge[MAXVERTEX];
} Graph;


PriorityQueue pq;

void Initialize(Graph *G, int n) {
    G->n = n;
    for(int i = 0; i < MAXVERTEX; i++)
        G->firstedge[i] = NULL;
}

void InsertEdge(Graph *G, int src, int dest, int weight){
    Edge *new = malloc(sizeof(Edge));  
    new->endpoint.first = dest;
    new->endpoint.second = weight;
    new->nextedge = G->firstedge[src];
    G->firstedge[src] = new;
    
    new = malloc(sizeof(Edge));  
    new->endpoint.first = src;
    new->endpoint.second = weight;
    new->nextedge = G->firstedge[dest];
    G->firstedge[dest] = new;
}

void ShowGraph(Graph *G){
    printf("Graph in form of Adjacency List is printed..\n");
    printf("x: y(w) where the edge x-y has cost w.\n\n");

    for(int i = 0; i < MAXVERTEX; i++){
        printf("%d: ", i);
        Edge *ptr = G->firstedge[i];
        while( ptr != NULL ) {
            (ptr->nextedge == NULL) ? printf("%d(%d)", ptr->endpoint.first, ptr->endpoint.second) : printf("%d(%d), ", ptr->endpoint.first, ptr->endpoint.second);
            
            ptr = ptr->nextedge;
        }
        printf("\n");    
    }
}

bool taken[MAXVERTEX];

void process(Graph *G, int edge){
    taken[edge]=1;

    Edge *ptr = G->firstedge[edge];
    while( ptr != NULL ) {
        Vertex v = ptr->endpoint;
        if(taken[v.first] == 0){
            PQItem p;
            p.first = v.second;
            p.second = v.first;
            PQInsert(p, &pq);  
        }  
        ptr = ptr->nextedge;
    }
    
}

int Prim(Graph *G){
    process(G, 0);
    int cost = 0;
    
    while( !PQEmpty(&pq) ){
        PQItem front = PQRemove(&pq);
        int u = front.second;
        int w = front.first;
        
        if(!taken[u]) cost += w;
        process(G, u);
    }

return cost;
}

int main ( void ) {
Graph G;
int n;

scanf("%d", &n);
    
Initialize(&G, n);
PQInitialize(&pq);

char line[6];

while( fgets(line, 6, stdin) != NULL ){
    if ( strcmp(line, "\n") == 0 ) continue;
    int x, y, w;
    x = atoi(&line[0]);
    y = atoi(&line[2]);
    w = atoi(&line[4]);
    InsertEdge(&G, x, y, w);
}

printf("\nGraph:\n");
ShowGraph(&G);

PQInitialize(&pq);

printf("\nMST cost = %d\n", Prim(&G));

return 0;
}