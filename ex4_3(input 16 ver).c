#include <stdio.h>

long long pow16(int x);

int main(void){
    unsigned int n=0;
    char string[128];
    int keta=0;

    scanf("%x", &n);

    for(int j=0;j<128;j++){
        if(n%pow16(j+1)==n){
        keta = j+1;
        break;
        }
    }

    for(int j=keta-1;j>0;j--){
        int r = n/pow16(j);
        n = n%pow16(j);
        if(0<=r && r<=9){
            string[keta-j-1] = r + '0';
        } else {
            string[keta-j-1] = r + 87;
        }
    }

    if(0<=n && n<=9){
        string[keta-1] = n_10 + '0';
    } else {
        string[keta-1] = n_10 + 87;
    }

    string[keta] = '\0';

    printf("%s", string);


    return 0;
}

long long pow16(int x){
    long long ans = 1;
    for(int i=0;i<x;i++){
        ans = ans*16;
    }
    return ans;
}