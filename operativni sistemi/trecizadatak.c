#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_DIMENSION 100000

typedef struct {
    int *vector1;
    int *vector2;
    int *result;
    int start_index;
    int end_index;
} ThreadArgs;

int n, m;

void *add_vectors(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int *v1 = args->vector1;
    int *v2 = args->vector2;
    int *res = args->result;
    int start_idx = args->start_index;
    int end_idx = args->end_index;

    for (int i = start_idx; i < end_idx; i++) {
        res[i] = v1[i] + v2[i];
    }

    pthread_exit(NULL);
}

void sum_vectors_single_thread(int *v1, int *v2, int *result) {
    for (int i = 0; i < n; i++) {
        result[i] = v1[i] + v2[i];
    }
}

void print_vector(int *vec) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

int main() {
    struct timeval start_time, end_time;
    double elapsed_time_single, elapsed_time_multi;
    pthread_t threads[MAX_DIMENSION];
    ThreadArgs thread_args[MAX_DIMENSION];
    int vector1[MAX_DIMENSION], vector2[MAX_DIMENSION], result[MAX_DIMENSION];

    printf("Enter the dimension of the vectors (n): ");
    scanf("%d", &n);

    printf("Enter the number of threads (m): ");
    scanf("%d", &m);

    if (n <= 0 || n > MAX_DIMENSION || m <= 0 || m > MAX_DIMENSION || n % m != 0) {
        fprintf(stderr, "Invalid input dimensions\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        vector1[i] = i + 1; 
        vector2[i] = n - i; 
    }
    gettimeofday(&start_time, NULL);
    sum_vectors_single_thread(vector1, vector2, result);
    gettimeofday(&end_time, NULL);
    elapsed_time_single = (end_time.tv_sec - start_time.tv_sec) * 1000.0; 
    elapsed_time_single += (end_time.tv_usec - start_time.tv_usec) / 1000.0; 

    printf("Result vector (single thread): ");
    print_vector(result);
    printf("Execution time (single thread): %.3f milliseconds\n", elapsed_time_single);
    gettimeofday(&start_time, NULL);
    int elements_per_thread = n / m;
    for (int i = 0; i < m; i++) {
        thread_args[i].vector1 = vector1;
        thread_args[i].vector2 = vector2;
        thread_args[i].result = result;
        thread_args[i].start_index = i * elements_per_thread;
        thread_args[i].end_index = (i + 1) * elements_per_thread;
        pthread_create(&threads[i], NULL, add_vectors, (void *)&thread_args[i]);
    }

    for (int i = 0; i < m; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end_time, NULL);
    elapsed_time_multi = (end_time.tv_sec - start_time.tv_sec) * 1000.0; 
    elapsed_time_multi += (end_time.tv_usec - start_time.tv_usec) / 1000.0; 

    printf("Result vector (multi-thread): ");
    print_vector(result);
    printf("Execution time (multi-thread): %.3f milliseconds\n", elapsed_time_multi);

    return EXIT_SUCCESS;
}
