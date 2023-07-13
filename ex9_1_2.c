#include <stdio.h>

#define NUMBER_OF_TIMES 1000

int main(void){
    FILE *fp;
    int tmp = 0;
    int sum = 0;

    fp = fopen("ex9_1.txt", "r");

    for(int i=0;i<NUMBER_OF_TIMES;i++){
        fscanf(fp, "%d", &tmp);
        sum += tmp;
    }

    fclose(fp);

    printf("%d", sum);

    return 0;
}