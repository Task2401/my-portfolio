#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <xi> <pi>\n", argv [0]);
        return 1;
    }

    int size = argc - 1;
    double numbers[size];
    double mean = 0.0;
    int xi = 0;
    int pi = 1;

    for (int i = 0; i < size; i++) 
        numbers[i] = atof(argv[i+1]);

    while ((xi < size -1) && (pi < size)) {
        mean += numbers[xi] * numbers[pi];
        xi += 2;
        pi += 2;
    }

    printf("The mean of the random variable is: %.8f\n", mean);
    return 0;
}