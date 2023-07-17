#include <stdio.h>
#include <stdlib.h>

typedef union{
    unsigned long long ull;
    unsigned char uc[8];
} ulonglong_uchar;

long long pow256(long long n);

int main(void){
    ulonglong_uchar test;
    long long tmp = 0;
    char string[128];
    scanf("%s", string);

    tmp = atoll(string);

    for(int i=0;i<8;i++){
        if(i != 7){
            if(tmp/pow256(7-i) == 0){
                test.uc[7-i] = 0;
            } else {
                test.uc[7-i] = tmp/pow256(7-i);
                tmp = tmp%pow256(7-i);
            }
        }
        else if(i == 7){
            test.uc[0] = tmp;
        }
    }

    printf("%llu\n", test.ull);

    return 0;
}

long long pow256(long long n){
    long long res = 1;
    for(int i=0;i<n;i++){
        res = res*256;
    }
    return res;
}