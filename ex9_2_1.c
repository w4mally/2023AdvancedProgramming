#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_TIMES 1000
#define MAX 10000
#define MIN 0

int main(void){
    FILE *fp;
    short int x = 0;

    fp = fopen("ex9_2.dat", "wb");

    srand(1); /*乱数初期化*/

    for(int i=0;i<NUMBER_OF_TIMES;i++){
        x = (int)(rand()*(MAX - MIN + 1) / (1 + RAND_MAX));
        fwrite(&x, sizeof(x), 1, fp);
    }

    fclose(fp);

    return 0;
}