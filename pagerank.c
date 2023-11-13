#include "surfing.h"

void handleInputFile(Graph *graph)
{
    long int src, dest, count = 0;

    FILE *infile;
    //infile = fopen("./input/facebook_combined.txt", "r"); // 4039 nodes
    //infile = fopen("./input/web-NotreDame_sorted.txt", "r"); // 325729 nodes
    //infile = fopen("./input/web-BerkStan_sorted.txt", "r"); // 685231 nodes
    infile = fopen("./input/web-Google_sorted.txt", "r"); // 916428 nodes

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
    
    //printf("\nAt end, count: %ld\n", count);
}

int main(int argc, char *argv[])
{
    int walkLength, threads;
    double damping;
    char infile[64];

    if (argc < 3)
    {
        printf("Usage: pagerank {int walk length > 0} {double damping: [0.0, 1.0]} {int threads} \n");
        exit(1);
    }

    if (argc == 4)
    {    
        walkLength = atoi(argv[1]);
        damping = atof(argv[2]);
        threads = atoi(argv[3]);
    }

    assert(threads >= 1);

    omp_set_num_threads(threads);

    //Graph *graph = createGraph(4039);
    //Graph *graph = createGraph(325729);
    //Graph *graph = createGraph(685231);
    Graph *graph = createGraph(916428);

    //printf("Graph Created\n");
    handleInputFile(graph);
    //printf("Input Handled\n");
    //printGraph(graph);
    //printf("Graph Printed\n");

    double time = omp_get_wtime();
    int* highestPageRanks = calculatePageRank(graph, walkLength, damping);
    time = omp_get_wtime() - time;

    for(int i = 0; i < PAGE_RANK_COUNT; i++) {
        printf("Rank %d: Vertex %d\n", (i + 1), highestPageRanks[i]);
    }
    printf("Page rank calculation time: %f seconds\n", time);
}