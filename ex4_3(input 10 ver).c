#include <stdio.h>

long long pow16(int x);
long long pow10(int x);

int main(void){
    unsigned int n;
    unsigned int n_10;
    int keta1;
    int keta2;
    char string[128];

    scanf("%x", &n);

    for(int j=0;j<128;j++){
        if(n%pow16(j+1)==n){
        keta1 = j+1;
        break;
        }
    }

    for(int j=keta1-1;j>0;j--){
        int r = n/pow16(j);
        n = n%pow16(j);
        n_10 += r*pow10(j);
    }

    n_10 += n;

    for(int j=0;j<128;j++){
        if(n_10%pow16(j+1)==n_10){
        keta2 = j+1;
        break;
        }
    }

    for(int j=keta2-1;j>0;j--){
        int r = n_10/pow16(j);
        n_10 = n_10%pow16(j);
        if(0<=r && r<=9){
            string[keta2-j-1] = r + '0';
        } else {
            string[keta2-j-1] = r + 87;
        }
    }

    if(0<=n_10 && n_10<=9){
        string[keta2-1] = n_10 + '0';
    } else {
        string[keta2-1] = n_10 + 87;
    }

    string[keta2] = '\0';

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

long long pow10(int x){
    long long ans = 1;
    for(int i=0;i<x;i++){
        ans = ans*10;
    }
    return ans;
}