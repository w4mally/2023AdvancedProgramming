#include <stdio.h>
#include <string.h>
#include <ctype.h>

int file_dump(char *filename);

int main(void){
    char input_filename[50];
    int result = 2;

    printf("filename? : ");
    scanf("%s", input_filename);
    

    result = file_dump(input_filename);

    if(result != 0){
        return 1; /*ファイルが開けなかったとき*/
    }

    return 0;
}

int file_dump(char *filename){
    FILE *fp;
    int flag1 = 0;
    char a[10];

    fp = fopen(filename, "rb");

    if(fp == NULL){
        printf("No file\n");
        return 1;
    }

    unsigned char get_data[16];
    int n = 0;

    while(flag1 == 0){
        for(int i=0;i<20;i++){
            n = (int)fread(get_data, sizeof(unsigned char), 16, fp);

            if(n == 0){
                flag1 = 1;
                break;
                } else {
                    /*16進数の2桁表示*/
                    for(int j=0;j<16;j++){
                        if(j<n){
                            printf("%02x ", get_data[j]); 
                        } else {
                            printf("   "); /*バイトサイズが16の倍数でなかった時はスペースを入れる*/
                        }
                    }

            printf("| ");

            /*ASCII文字表示*/
            for(int j=0;j<n;j++){
                if(isprint(get_data[j]) != 0){
                    printf("%c", get_data[j]);
                } else {
                    printf("   ");
                }
            }

            printf("\n");
            }

            n = 0;

            if(i == 19){
                printf("more ? ");
                scanf("%s", a);
                if(strcmp(a, "y") != 0){
                flag1 = 1; /*y以外が入力されたら終了*/
                }
            }
        }
    }

    fclose(fp);
    return 0;
}