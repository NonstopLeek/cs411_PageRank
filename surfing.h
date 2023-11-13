#include "graph.h"

#define PAGE_RANK_COUNT 5

int* calculatePageRank(Graph* graph, int walkLength, double damping) {
    // damping: [0.0, 1.0]
    int vertexCount = graph->numVertices;
    int vertexVisits[vertexCount];
    memset(vertexVisits, 0, vertexCount * sizeof(int));

    omp_lock_t vertexLocks[vertexCount];
    for (int i = 0; i < vertexCount; i++)
        omp_init_lock(&vertexLocks[i]);
    
    #pragma omp parallel for schedule(static)
    for (int startingVertexIndex = 0; startingVertexIndex < vertexCount; startingVertexIndex++) {

        int threadNum = omp_get_thread_num();
        int currentVertexIndex = startingVertexIndex;

        for (int step = 0; step < walkLength; step++) {
            uint seed = (threadNum + 1) * (startingVertexIndex + 1) * (step + 1);
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

            omp_set_lock(&vertexLocks[currentVertexIndex]);
            vertexVisits[currentVertexIndex]++;
            omp_unset_lock(&vertexLocks[currentVertexIndex]);
        }
    }

    int* highestRankVertexIndices = (int *)malloc(sizeof(int) * PAGE_RANK_COUNT);
    memset(highestRankVertexIndices, 0, PAGE_RANK_COUNT * sizeof(int));

    omp_lock_t rankLocks[PAGE_RANK_COUNT];
    for (int i = 0; i < PAGE_RANK_COUNT; i++)
        omp_init_lock(&rankLocks[i]);

    #pragma omp parallel for schedule(static)
    for (int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++) {
        int currentVertexIndex = vertexIndex;
        int currentVertexVisits = vertexVisits[currentVertexIndex];
        for (int vertexRank = 0; vertexRank < PAGE_RANK_COUNT; vertexRank++) {
            omp_set_lock(&rankLocks[vertexRank]);
            int rankedVertexIndex = highestRankVertexIndices[vertexRank];
            int rankedVertexVisits = vertexVisits[rankedVertexIndex];
            if (currentVertexVisits > rankedVertexVisits) {
                highestRankVertexIndices[vertexRank] = currentVertexIndex;
                currentVertexIndex = rankedVertexIndex;
                currentVertexVisits = rankedVertexVisits;
            }
            omp_unset_lock(&rankLocks[vertexRank]);
        }
    }

    //for(int i = 0; i < PAGE_RANK_COUNT; i++) {
    //    printf("Rank %d: Vertex %d with visits = %d\n", (i + 1),
    //        highestRankVertexIndices[i], vertexVisits[highestRankVertexIndices[i]]);
    //}

    return highestRankVertexIndices;
}