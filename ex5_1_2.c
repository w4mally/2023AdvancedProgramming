#include <stdio.h>

typedef struct{
    char str1[3];
    unsigned char num1;
    char str2[7];
    unsigned char num2;
    char str3[10];
} test_t;

int main(void){
    test_t a[3];
    printf("(Array address) a[0]:%p, a[1]:%p, a[2]:%p\n", &a[0], &a[1], &a[2]);
    printf("(a[0] member address) str1:%p, num1:%p, str2:%p, num2:%p, str3:%p\n", &a[0].str1, &a[0].num1, &a[0].str2, &a[0].num2, &a[0].str3);

    return 0;
}