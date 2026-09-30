/*Develop a C program to generate first n Fibonacci numbers using OpenMP tasks. Use Fibonacci computation to represent workloads in digital systems. Measure execution time to analyze how task-based parallelism improves computational efficiency, scalability, and resource utilization, demonstrating the role of advanced computing technologies in supporting SDG-9: Industry, Innovation & Infrastructure.*/

#include <stdio.h>
#include <omp.h>

int fib(int n) {
    int i, j;

    if (n < 2)
        return n;
    else {
        #pragma omp task shared(i) firstprivate(n)
        i = fib(n - 1);

        #pragma omp task shared(j) firstprivate(n)
        j = fib(n - 2);

        #pragma omp taskwait
        return i + j;
    }
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    double st = omp_get_wtime();

    #pragma omp parallel num_threads(4) shared(n)
    {
        #pragma omp single
        {
            for (int i = 0; i <= n; i++) {
                printf("fib(%d) = %d\n", i, fib(i));
            }
        }
    }

    double end = omp_get_wtime();

    printf("Execution time = %.6f seconds", end - st);

    return 0;
}


// gcc -fopenmp q2.c
// ./a.out