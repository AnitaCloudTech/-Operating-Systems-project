#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_MATRIX_SIZE 100

int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
int rotated_matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
int m;

typedef struct {
    int start_row;
    int end_row;
} ThreadArgs;

void *rotate_matrix(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int start_row = args->start_row;
    int end_row = args->end_row;

    for (int layer = start_row; layer < end_row; layer++) {
        int first = layer;
        int last = m - 1 - layer;

        for (int i = first; i < last; i++) {
            int offset = i - first;
            int top = matrix[first][i];

            rotated_matrix[first][i] = matrix[last - offset][first];

            rotated_matrix[last - offset][first] = matrix[last][last - offset];

            rotated_matrix[last][last - offset] = matrix[i][last];
            rotated_matrix[i][last] = top;
        }
    }

    pthread_exit(NULL);
}

int main() {
    FILE *fp;
    pthread_t threads[MAX_MATRIX_SIZE];
    ThreadArgs thread_args[MAX_MATRIX_SIZE];
    
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &m);
    if (m <= 0 || m > MAX_MATRIX_SIZE) {
        fprintf(stderr, "Invalid matrix size\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
    fclose(fp);
    int num_threads = m / 2;
    for (int i = 0; i < num_threads; i++) {
        thread_args[i].start_row = i;
        thread_args[i].end_row = m - i;
        pthread_create(&threads[i], NULL, rotate_matrix, (void *)&thread_args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(fp, "%d ", rotated_matrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

