/*Develop a computational solution to estimate the value of π using the Leibniz series:
π=4k=0∑∞​2k+1(−1)k​
Supporting SDG 9 through efficient and innovative computing. Implement both serial and parallel versions by removing loop-carried dependency. Execute them for a large number of iterations, record execution times, and analyze the performance improvement achieved through parallel computing.*/

//   ACCEPTING ARGUMENTS VIA CLI

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(int argc, char *argv[]) {

    int tc = strtol(argv[1], NULL, 10);

    double sum = 0;
    double start, end;

    start = omp_get_wtime();

    for (int i = 0; i < strtol(argv[2], NULL, 10); i++) {
        sum += (pow(-1, i) / (2 * i + 1));
    }

    end = omp_get_wtime();

    printf("Sum = %f in serial took %f sec",
           4 * sum, end - start);

    sum = 0;
    start = omp_get_wtime();

    #pragma omp parallel for num_threads(tc) reduction(+:sum)
    for (int i = 0; i < strtol(argv[2], NULL, 10); i++) {
        sum += (pow(-1, i) / (2 * i + 1));
    }

    end = omp_get_wtime();

    printf("\nSum = %f in parallel took %f sec",
           4 * sum, end - start);

    return 0;
}

// gcc -fopenmp q3A.c -lm
// ./a.out 4 1000000000