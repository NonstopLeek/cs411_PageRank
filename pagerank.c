#include "surfing.h"

void handleInputFile(Graph *graph)
{
    long int src, dest, count = 0;

    FILE *infile;
    infile = fopen("facebook_combined.txt", "r");

    if (!infile)
    {
        printf("Error reading file\n");
        return;
    }

    while(!feof(infile))
    {
        char *beans;
        char lineBuff[64];
        ++count;
        // graph = realloc(graph, sizeof(*graph) * count);
        beans = fgets(lineBuff, 64, infile);
        // printf("beans: %s\n", beans);
        sscanf(beans, "%ld %ld", &src, &dest);

        // printf("\nsrc: %d     dest: %d\n", src, dest);
        createEdge(graph, src, dest);
        // if (count == 1) printf("\nsrc: %d     dest: %d\n", src, dest);
    }
    
    printf("\nAt end, count: %ld\n", count);
}

int main(int argc, char *argv[])
{
    int walkLength;
    double damping;
    char infile[64];

    if (argc < 2)
    {
        printf("Usage: pagerank {int walk length > 0} {double damping: [0.0, 1.0]}\n");
        exit(1);
    }

    walkLength = atoi(argv[1]);

    if (argc == 3)
    {
        damping = atof(argv[2]);
    }

    Graph *graph = createGraph(4039);
    printf("Graph Created\n");
    handleInputFile(graph);
    printf("Input Handled\n");
    printGraph(graph);
    printf("Graph Printed\n");

    int* highestPageRanks = calculatePageRank(graph, walkLength, damping);
    for(int i = 0; i < PAGE_RANK_COUNT; i++) {
        printf("Rank %d: Vertex %d\n", (i + 1), highestPageRanks[i]);
    }
}