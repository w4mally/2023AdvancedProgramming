#include <stdio.h>
#include <string.h>
#include <ctype.h>

int file_dump(char *filename);

int main(void){
    FILE *fp;
    char filename[50] = "big2.bin";
    unsigned int a = 0;
    unsigned int b = 0;
    long long bytes_a[3];
    long long bytes_b[3];
    unsigned long long ans = 0;

    fp = fopen(filename, "rb+");

    if(fp == NULL){
        printf("File Not Found.\n");
        return 1;
    }

    /*Aの書き出し*/
    for(int i=0;i<3;i++){
        bytes_a[i] = fgetc(fp);
        if(bytes_a[i] == EOF){
            fprintf(stderr, "Read Error");
            return 1;
        }
    }
    a = bytes_a[0] << 16 | bytes_a[1] << 8 | bytes_a[2];

    /*Bの書き出し*/
    for(int i=0;i<3;i++){
        bytes_b[i] = fgetc(fp);
        if(bytes_b[i] == EOF){
            fprintf(stderr, "Read Error");
            return 1;
        }
    }
    b = bytes_b[0] << 16 | bytes_b[1] << 8 | bytes_b[2];

    /*積の計算*/
    ans = a*b;

    fseek(fp, 6, SEEK_SET);

    /*計算結果の書き込み*/
    for(int i=0;i<6;i++){
        fputc((ans >> (8*(5-i)))&0xff, fp);
    }

    fclose(fp);

    file_dump(filename);

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