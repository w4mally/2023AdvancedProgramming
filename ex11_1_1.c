#include <stdio.h>
#include <string.h>

int main(void){
    FILE *fp;
    char input_filename[50];
    char check_BM[3];
    int check_pixel = 0;
    int check_offset = 0;
    int cnt = 0;

    printf("filename ? ");
    fgets(input_filename, sizeof(input_filename), stdin);

    input_filename[strlen(input_filename)-1] = '\0';

    fp = fopen(input_filename, "rb");

    if(fp == NULL){
        printf("Can not open.\n");
        return 1;
    }

    /*ファイル先頭2バイトの受け取り*/
    fseek(fp, 0x0000, SEEK_SET);
    fread(check_BM, sizeof(char), 2, fp);
    check_BM[2] = '\0';

    /*1ピクセル当たりのビット長の受け取り*/
    fseek(fp, 0x001c, SEEK_SET);
    fread(&check_pixel, sizeof(int), 1, fp);

    /*ビットマップファイルヘッダー内のオフセットの受け取り*/
    fseek(fp, 0x000a, SEEK_SET);
    fread(&check_offset, sizeof(int), 1, fp);

    if(strcmp(check_BM, "BM") == 0 && check_pixel == 24 && check_offset == 54){
        printf("OK.\n");
    } else {
        if(strcmp(check_BM, "BM") != 0) cnt++;
        if(check_pixel != 24) cnt++;
        if(check_offset != 54) cnt++;
        printf("Number of unsatisfied items = %d\n", cnt);
        printf("Different file type.\n");
    }

    fclose(fp);

    return 0;
}
