#include <stdio.h>

#define NUMBER_OF_TIMES 1000

int main(void){
    FILE *fp;
    short int tmp = 0;
    int sum = 0;

    fp = fopen("ex9_2.dat", "rb");

    for(int i=0;i<NUMBER_OF_TIMES;i++){
        fread(&tmp, sizeof(tmp), 1, fp);
        sum += tmp;
    }

    fclose(fp);

    printf("%d", sum);

    return 0;
}