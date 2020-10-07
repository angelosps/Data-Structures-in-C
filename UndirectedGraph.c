// Implementation of Undirected Graph ADT
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    
    new = malloc(sizeof(Edge));  
    new->endpoint = src;
    new->nextedge = G->firstedge[dest];
    G->firstedge[dest] = new;
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

bool visited[MAXVERTEX];

void DFS(Graph * G, int x){
    visited[x] = 1;

    Edge *curr = G->firstedge[x];
    while(curr){
        Vertex v = curr->endpoint; 
        if (visited[v] == 0) 
            DFS(G, v);
        curr = curr->nextedge;
    }
}

int main ( void ) {

Graph G;
int n, e;

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

DFS(&G, 0);
      
printf("\nVisited array\n");

for(int i = 0; i<n; i++)
    printf("%d ", visited[i]);
      
printf("\n");

return 0;
}
