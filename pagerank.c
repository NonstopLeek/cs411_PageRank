#include "pagerank.h"

int main(int argc, char *argv[])
{
    int k, d;
    char infile[64];

    if (argc < 2)
    {
        printf("Error, incorrect parameters passed into program. Exiting.\n");
        exit(1);
    }

    k = atoi(argv[1]);

    if (argc == 3)
    {
        d = atoi(argv[2]);
    }

    Graph *graph = createGraph(88235);
    printf("Graph Created\n");
    handleInputFile(graph);
    printf("Input Handled\n");
    printGraph(graph);
    printf("Graph Printed\n");


}

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
        sscanf(beans, "%d %d", &src, &dest);

        // printf("\nsrc: %d     dest: %d\n", src, dest);
        createEdge(graph, src, dest);
        // if (count == 1) printf("\nsrc: %d     dest: %d\n", src, dest);
    }
    
    printf("\nAt end, count: %d\n", count);
}