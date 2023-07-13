#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_TIMES 1000
#define MAX 10000
#define MIN 0

int main(void){
    FILE *fp;
    int tmp = 0;

    fp = fopen("ex9_1.txt", "w");

    srand(1); /*乱数初期化*/

    for(int i=0;i<NUMBER_OF_TIMES;i++){
        tmp = (int)(rand()*(MAX - MIN + 1) / (1 + RAND_MAX));
        fprintf(fp, "%d\n", tmp);
    }

    fclose(fp);

    return 0;
}