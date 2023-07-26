#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
    unsigned int x = atoi(argv[1]);
    unsigned int y = atoi(argv[2]);
    int i = 31;
    int tmp[32];
    int maxbit = 0;
    unsigned long long ans = 1;
    unsigned long long ull_x = x;

    /*bit_yにyの2進表現を配列で格納する*/
    while(1){
        int a = 1 << i;
        if((y&a) == 0) tmp[31-i] = 0;
        else tmp[31-i] = 1;

        if(i == 0) break;
        i--;
    }

    for(int j=0;j<32;j++){
        if(tmp[j] == 1){
            maxbit = 32 - j;
            break;
        }
    }

    int bit_y[maxbit];

    for(int j=0;j<maxbit;j++){
        bit_y[j] = tmp[32 - maxbit + j];
    }

    /*べきの計算*/
    for(int j=0;j<maxbit;j++){
        if(j == 0){
            ans = x;
        } else {
            if(bit_y[j] == 0) ans = ans*ans;
            else if(bit_y[j] == 1){
                ans = ans*ans;
                ans = ans*ull_x;
            } 
        }
    }

    printf("%llu\n", ans);

    return 0;
}