#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_FILENAME_LENGTH 20
void process_file(char *filename) {
 FILE *fp;
 int matrix[3][3];
 int i, j;
 int sum_negatives = 0;
 fp = fopen(filename, "r");
 if (fp == NULL) {
 perror("Error opening file");
 exit(EXIT_FAILURE);
 }
 for (i = 0; i < 3; i++) {
 for (j = 0; j < 3; j++) {
 fscanf(fp, "%d", &matrix[i][j]);
 if (matrix[i][j] < 0) {
 sum_negatives += matrix[i][j];
 }
 }
 }
 fclose(fp);
 char temp_filename[MAX_FILENAME_LENGTH];
 sprintf(temp_filename, "temp_%d.txt", getpid());
 fp = fopen(temp_filename, "w");
 if (fp == NULL) {
 perror("Error creating temporary file");
 exit(EXIT_FAILURE);
 }
 fprintf(fp, "%d\n", sum_negatives);
 fclose(fp);
}
int main(int argc, char *argv[]) {
 if (argc < 2) {
 fprintf(stderr, "Usage: %s n\n", argv[0]);
 return EXIT_FAILURE;
 }
 int n = atoi(argv[1]);
 pid_t pid;
 int i;
 char filename[MAX_FILENAME_LENGTH];
 for (i = 1; i <= n; i++) {
 sprintf(filename, "input%d.txt", i);
 pid = fork();
 if (pid < 0) {
 perror("Fork failed");
 return EXIT_FAILURE;
 } else if (pid == 0) {
 process_file(filename);
 exit(EXIT_SUCCESS);
 }
 }
 for (i = 1; i <= n; i++) {
 wait(NULL);
 }
 FILE *temp_fp;
 int sum_negatives;
 int results[n][2];
 char temp_filename[MAX_FILENAME_LENGTH];
 for (i = 1; i <= n; i++) {
 sprintf(temp_filename, "temp_%d.txt", getpid());
 temp_fp = fopen(temp_filename, "r");
 if (temp_fp == NULL) {
 perror("Error opening temporary file");
 return EXIT_FAILURE;
 }
 fscanf(temp_fp, "%d", &sum_negatives);
 fclose(temp_fp);
 results[i - 1][0] = sum_negatives;
 results[i - 1][1] = i;
 remove(temp_filename);
 }
 for (i = 0; i < n - 1; i++) {
 for (int j = 0; j < n - i - 1; j++) {
 if (results[j][1] > results[j + 1][1]) {
 int temp_sum = results[j][0];
 int temp_idx = results[j][1];
 results[j][0] = results[j + 1][0];
 results[j][1] = results[j + 1][1];
 results[j + 1][0] = temp_sum;
 results[j + 1][1] = temp_idx;
 }
 }
 }
 FILE *output_fp = fopen("output.txt", "w");
 if (output_fp == NULL) {
 perror("Error opening output file");
 return EXIT_FAILURE;
 }
 for (i = 0; i < n; i++) {
 fprintf(output_fp, "Време извршавања процеса %d, улазна матрица процеса %d, збир ненегативних чланова матрице %d\n",
 results[i][1], results[i][1], results[i][0]);
 }
 fclose(output_fp);
 return EXIT_SUCCESS;
}
