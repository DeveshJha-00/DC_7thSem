/*Develop a computational solution to estimate the value of π using the Leibniz series:
π=4k=0∑∞​2k+1(−1)k​
Supporting SDG 9 through efficient and innovative computing. Implement both serial and parallel versions by removing loop-carried dependency. Execute them for a large number of iterations, record execution times, and analyze the performance improvement achieved through parallel computing.*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

void main() {
    int thread_cnt, it;

    printf("Enter thread count: ");
    scanf("%d", &thread_cnt);

    printf("Enter iterations for pi: ");
    scanf("%d", &it);

    double sum = 0;
    double start, end;

    start = omp_get_wtime();

    for (int i = 0; i < it; i++) {
        sum += (pow(-1, i) / (2 * i + 1));
    }

    end = omp_get_wtime();

    printf("Sum = %f in serial took %f sec",
           4 * sum, end - start);

    sum = 0;
    start = omp_get_wtime();

    #pragma omp parallel for num_threads(thread_cnt) reduction(+:sum)
    for (int i = 0; i < it; i++) {
        sum += (pow(-1, i) / (2 * i + 1));
    }

    end = omp_get_wtime();

    printf("\nSum = %f in parallel took %f sec",
           4 * sum, end - start);
}

// gcc -fopenmp q3A.c -lm
// ./a.out