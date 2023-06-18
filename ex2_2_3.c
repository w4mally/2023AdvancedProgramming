#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Nmeas 5
#define N 20000

int main(void) {
    float data[N] = {0};
    float lower = 0;
    float upper = 10000;
    float temp = 0;
    long long comp_cnt = 0;
    long long swap_cnt = 0;
    long long comp_cnt_data[Nmeas] = {0};
    long long swap_cnt_data[Nmeas] = {0};
    long long comp_ave = 0;
    long long swap_ave = 0;
    int flag = 0;

    for (int times = 0; times < Nmeas; times++) {
        comp_cnt = 0;
        swap_cnt = 0;

        srand(time(NULL) + times*1000);
        for (int i = 0; i < N; i++) {
            data[i] = (upper - lower) * rand() / (RAND_MAX+1)+lower;
        }

        for(int i=0;i<N-1;i++){
            flag = 0;
            for(int j=0;j<N-1;j++){
                comp_cnt++;
                if(data[j] > data[j+1]){
                    temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                    swap_cnt++;
                    flag = 1;
                    }
                }
            if(flag==0) break;
        }

        printf("Result%d\n", times+1);
        printf("First : ");
        for(int i=0;i<10;i++){
            printf("%f ", data[i]);
        }
        printf("\n");
        printf("Last : ");
        for(int i=0;i<10;i++){
            printf("%f ", data[N-10+i]);
        }
        printf("\n");

        printf("The number of comparisons : %lld\n", comp_cnt);
        printf("The number of swaps : %lld\n", swap_cnt);
        printf("\n");

        comp_cnt_data[times] = comp_cnt;
        swap_cnt_data[times] = swap_cnt;
    }

    for(int i=0;i<Nmeas;i++){
        comp_ave += comp_cnt_data[i];
        swap_ave += swap_cnt_data[i];
    }

    comp_ave = comp_ave / Nmeas;
    swap_ave = swap_ave / Nmeas;

    printf("Average the number of comparisons : %lld\n", comp_ave);
    printf("Average the number of swaps : %lld\n", swap_ave);

    return 0;
}