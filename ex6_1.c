#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *a[10];
    for(int i=0;i<10;i++){
        a[i] = NULL;
    }

    for(int i=0;i<5;i++){
        a[i] = (int *)malloc(sizeof (int));
    }
    printf("C)\n");
    for(int i=0;i<10;i++){
        printf("a[%d] = %p\n", i, a[i]);
    }

    free(a[1]);
    free(a[2]);
    free(a[4]);
    a[1] = NULL;
    a[2] = NULL;
    a[4] = NULL;

    printf("E)\n");
    for(int i=0;i<10;i++){
    printf("a[%d] = %p\n", i, a[i]);
    }

    for(int i=5;i<10;i++){
        a[i] = (int *)malloc(sizeof (int));
    }

    printf("G)\n");
    for(int i=0;i<10;i++){
    printf("a[%d] = %p\n", i, a[i]);
    }

    for(int i=0;i<10;i++){
        if(a[i] != NULL){
            free(a[i]);
        }
    }
}