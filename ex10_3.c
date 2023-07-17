/*
【計測結果】
fflushなし : 0.006[sec]
fflushあり : 0.257[sec]
(Windows10, Visual Studio 2022で実行して計測) 
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TEST_TIMES 100000

int main(void){
    clock_t start;
    clock_t end;
    FILE *fp;
    char filename[20] = "random_test.bin";

    fp = fopen(filename, "wb");

    if(fp == NULL){
        printf("Error!\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    start = clock();
    for(int i=0;i<TEST_TIMES;i++){
        fputc((rand()%256), fp);
    }
    end = clock();

    printf("No fflush : %lf[sec]\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for(int i=0;i<TEST_TIMES;i++){
        fputc((rand()%256), fp);
        fflush(fp);
    }
    end = clock();

    printf("Use fflush : %lf[sec]\n", (double)(end - start) / CLOCKS_PER_SEC);

    fclose(fp);

    return 0;
}