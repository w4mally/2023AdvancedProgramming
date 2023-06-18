#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Nmeas 2
#define N 20000

int main(void) {
    float data[N] = { 0 };
    float lower = 0;
    float upper = 10000;

    for (int i = 0; i < Nmeas; i++) {
        printf("%d kaime\n", i + 1);

        srand(time(NULL) + i*1000);

        for (int j = 0; j < N; j++) {
            data[j] = (upper - lower) * rand() / (RAND_MAX+1)+lower;
        }

        printf("First : ");
        for (int j = 0; j < 10; j++) {
            printf("%f ", data[j]);
        }
        printf("\n");

        printf("Last : ");
        for (int j = 0; j < 10; j++) {
            printf("%f ", data[N-10+j]);
        }
        printf("\n");
    }

    return 0;
}