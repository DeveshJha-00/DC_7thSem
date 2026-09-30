/*Write a program to sort an array of n elements using both sequential and parallel merge sort
(using Section). Record the difference in execution time.*/

#include <stdio.h>
#include <string.h>
#include <omp.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;

    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;

        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);

        merge(arr, l, mid, r);
    }
}

void mergeSortParallel(int arr[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSortParallel(arr, l, mid);
            }

            #pragma omp section
            {
                mergeSortParallel(arr, mid + 1, r);
            }
        }

        merge(arr, l, mid, r);
    }
}

int main() {
    int original[] = {10, 30, 50, 20, 40};
    int n = sizeof(original) / sizeof(original[0]);

    int sequential[n];
    int parallel[n];

    memcpy(sequential, original, sizeof(original));
    memcpy(parallel, original, sizeof(original));

    double start, end;
    double sequentialTime, parallelTime;

    start = omp_get_wtime();

    mergeSort(sequential, 0, n - 1);

    end = omp_get_wtime();

    sequentialTime = end - start;

    start = omp_get_wtime();

    mergeSortParallel(parallel, 0, n - 1);

    end = omp_get_wtime();

    parallelTime = end - start;

    printf("Sequential Merge Sort:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", sequential[i]);

    printf("\nExecution Time: %.9f seconds\n\n", sequentialTime);

    printf("Parallel Merge Sort:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", parallel[i]);

    printf("\nExecution Time: %.9f seconds\n\n", parallelTime);

    printf("Time Difference: %.9f seconds\n", sequentialTime - parallelTime);

    return 0;
}


// gcc -fopenmp q1.c 
// ./a.out --> replace .out with .exe in windows 