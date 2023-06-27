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
    printf("(Array address)\n");
    for(int i=0;i<3;i++){
    	printf("a[%d]:%p\n", i, &a[i]);
    }
    printf("(a[0] member address)\n");
    printf("\n");
    printf("str1: %p\n", &a[0].str1);
    printf("num1: %p\n", &a[0].num1);
    printf("str2: %p\n", &a[0].str2);
    printf("num2: %p\n", &a[0].num2);
    printf("str3: %p\n", &a[0].str3);
    return 0;
}
