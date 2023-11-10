#include "graph.h"

#define PAGE_RANK_COUNT 5

// TODO finish implementing serial version of this code then parallelize it

int* calculatePageRank(Graph* graph, int walkLength, double damping) {
    // damping: [0.0, 1.0]
    int vertexCount = graph->numVertices;
    int vertexVisits[vertexCount];
    memset(vertexVisits, 0, vertexCount * sizeof(int));
    // TODO will probably need to make an array of locks for vertexVisits when we parallelize this
    
    for (int startingVertexIndex = 0; startingVertexIndex < vertexCount; startingVertexIndex++) {
        
        int currentVertexIndex = startingVertexIndex;

        for (int step = 0; step < walkLength; step++) {
            // TODO change to (omp_get_thread_num() + 1) * (startingVertexIndex + 1) * (step + 1)
            uint seed = (startingVertexIndex + 1) * (step + 1);
            double coinFlip = (double)rand_r(&seed) / RAND_MAX;
            seed *= (step + 1);

            int neighborCount = 0;
            Node* neighbor = graph->adjacencyList[currentVertexIndex];
            while(neighbor) {
                neighborCount++;
                neighbor = neighbor->next;
            }

            if (coinFlip > damping && neighborCount > 0) {
                int randomNeighborIndex = rand_r(&seed) % neighborCount;
                neighbor = graph->adjacencyList[currentVertexIndex];
                for (int i = 0; i < randomNeighborIndex; i++) {
                    neighbor = neighbor->next;
                }
                currentVertexIndex = neighbor->vertex;
            }
            else {
                int randomVertexIndex = rand_r(&seed) % vertexCount;
                currentVertexIndex = randomVertexIndex;
            }

            vertexVisits[currentVertexIndex]++;
        }
    }

    int* highestRankVertexIndices = (int *)malloc(sizeof(int) * PAGE_RANK_COUNT);
    memset(highestRankVertexIndices, 0, PAGE_RANK_COUNT * sizeof(int));

    for (int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++) {
        int currentVertexIndex = vertexIndex;
        int currentVertexVisits = vertexVisits[currentVertexIndex];
        for (int vertexRank = 0; vertexRank < PAGE_RANK_COUNT; vertexRank++) {
            int rankedVertexIndex = highestRankVertexIndices[vertexRank];
            int rankedVertexVisits = vertexVisits[rankedVertexIndex];
            if (currentVertexVisits > rankedVertexVisits) {
                highestRankVertexIndices[vertexRank] = currentVertexIndex;
                currentVertexIndex = rankedVertexIndex;
                currentVertexVisits = rankedVertexVisits;
            }
        }
    }

    //for(int i = 0; i < PAGE_RANK_COUNT; i++) {
    //    printf("Rank %d: Vertex %d with visits = %d\n", (i + 1),
    //        highestRankVertexIndices[i], vertexVisits[highestRankVertexIndices[i]]);
    //}

    return highestRankVertexIndices;
}