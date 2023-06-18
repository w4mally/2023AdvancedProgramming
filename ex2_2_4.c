#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Nmeas 5
#define N 20000

void quick_sort(float data[], int left, int right);
int partition(float data[], int left, int right);
long long comp_cnt = 0;
long long swap_cnt = 0;

int main(void) {
    float data[N] = {0};
    float lower = 0;
    float upper = 10000;
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

        quick_sort(data, 0, N);

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

void quick_sort(float data[], int left, int right){
	int mid;
	if(left < right){
	mid = partition(data, left, right);
	quick_sort(data, left, mid);
	quick_sort(data, mid+1, right);
	}
}

int partition(float data[], int left, int right){
	float pivot, swap;
	int i,j;
	pivot = data[left];
	i = left;
	j = right;

	while(1){
		while(data[i]<pivot){
			i++;
            comp_cnt++;
		}
		while(data[j]>pivot){
			j--;
            comp_cnt++;
		}
		if(i >= j){
			break;
		}
		swap = data[i];
		data[i] = data[j];
		data[j] = swap;
        swap_cnt++;
	}

	return i;
}