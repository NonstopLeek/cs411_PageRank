#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <omp.h>
#include <string.h>

typedef struct node {
    int vertex;
    struct node *next;
} Node;

typedef struct graph {
    int numVertices;
    Node **adjacencyList;
} Graph;

Node *createNode(int newVertex)
{
    // printf("Creating Node\n");
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = newVertex;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int newVerticesCount)
{
    Graph *newGraph = (Graph *)malloc(sizeof(Graph));
    newGraph->numVertices = newVerticesCount;
    newGraph->adjacencyList = (Node **)malloc(newVerticesCount * sizeof(Node *));

    for (int i = 0; i < newVerticesCount; i++)
    {
        newGraph->adjacencyList[i] = NULL;
    }

    return newGraph;
}

void createEdge(Graph *graph, int src, int dest)
{
    // Create edge from source node to destination node
    struct node *newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

void printGraph(Graph *graph)
{
    printf("Printing Graph...\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        // printf("Vertex: %d\n", i);
        Node *temp = graph->adjacencyList[i];
        // printf("Node temp: graph->adjacencyList[i]=%d\n", graph->adjacencyList[i]);
        printf("\nVertex: %d\n[", i);
        while(temp)
        {
            printf("%d", temp->vertex);
            temp = temp->next;
            if (temp)
                printf(", ");
        }
        printf("]");
        printf("\n");
    }
}

