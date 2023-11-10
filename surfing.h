#include "graph.h"

// TODO finish implementing serial version of this code then parallelize it

void calculatePageRank(Graph* graph, int walkLength, double damping) {
    // damping: [0.0, 1.0]
    int vertexCount = graph->numVertices;
    int vertexVisits[vertexCount] = {0};
    // TODO will probably need to make an array of locks for vertexVisits when we parallelize this
    
    for (int startingVertexIndex = 0; startingVertexIndex < vertexCount; startingVertexIndex++) {
        
        Node* currentVertex = graph->adjacencyList[startingVertexIndex];

        for (int step = 0; step < walkLength; step++) {
            vertexVisits[currentVertex->vertex]++;

             // TODO change to (omp_get_thread_num() + 1) * (startingVertexIndex + 1) * (step + 1)
            uint seed = (startingVertexIndex + 1) * (step + 1);
            double coinFlip = (double)rand_r(&seed) / RAND_MAX;
            seed *= (step + 1);
            if (coinFlip > damping) { // && neighbors count > 0
                // go to a random neighbor
            }
            else {
                // go to any random vertex
                int randomVertexIndex = rand_r(&seed) % vertexCount;
                currentVertex = graph->adjacencyList[randomVertexIndex];
            }
        }
    }
}