#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int n = atoi(argv[1]);

    if (n < 0 || n > 100) {
        printf("n must be between 1 and 100.\n");
        return 1;
    }
    int *arr;
    arr = malloc(n * sizeof(int));

    FILE *fp;
    fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file");
        return 1;
    }

    float sum = 0;
    int max = 0;
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", arr + i);

        int value = *(arr+i);
        sum += value;
        if (value > max) {
            max = value;
        }
    }

    printf("Mean: %.2f\nMax: %d\n", sum/n, max);
    fclose(fp);
    free(arr);
}