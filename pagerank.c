#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int k, d;

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
}