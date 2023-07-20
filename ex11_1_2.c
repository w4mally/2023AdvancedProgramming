#include <stdio.h>
#include <string.h>

int check_filetype(FILE *fp);

typedef struct{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}color_info;

char check_BM[3];
int check_pixel = 0;
int check_offset = 0;

int main(void){
    FILE *fp;
    char input_filename[50];
    int flag = 2;
    int width = 0; /*横幅*/
    int height = 0; /*縦幅*/
    int padding = 0; /*パディングの長さ*/

    printf("filename ? ");
    fgets(input_filename, sizeof(input_filename), stdin);

    input_filename[strlen(input_filename)-1] = '\0';

    fp = fopen(input_filename, "rb");

    if(fp == NULL){
        printf("Can not open.\n");
        return 1;
    }

    flag = check_filetype(fp); /*step 2*/

    if(flag == -1){
        return 0; /*bmpファイルでないならここで終了*/
    }
    
    /*縦横ピクセル数の読み取り*/
    fseek(fp, 0x0012, SEEK_SET);
    fread(&width, sizeof(int), 1, fp);
    fread(&height, sizeof(int), 1, fp);

    printf("Horizontal size = %d, Vertical size = %d\n", width, height);

    color_info color[height][width];

    /*パディングの計算*/
    if(width%4 == 0){
        padding = 0;
    } else {
        padding = 4 - ((width*3) % 4);
    }

    /*全てのピクセルの色情報の入手*/
    fseek(fp, check_offset, SEEK_SET);
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            fread(&color[i][j].b, sizeof(unsigned char), 1, fp);
            fread(&color[i][j].g, sizeof(unsigned char), 1, fp);
            fread(&color[i][j].r, sizeof(unsigned char), 1, fp);
        }
        fseek(fp, padding, SEEK_CUR);
    }

    /*四隅の色情報の出力*/
    printf("Upper-left (R=%d, G=%d, B=%d)\n", color[height - 1][0].r, color[height - 1][0].g, color[height - 1][0].b);
    printf("Upper-right (R=%d, G=%d, B=%d)\n", color[height - 1][width - 1].r, color[height - 1][width - 1].g, color[height - 1][width - 1].b);
    printf("Lower-left (R=%d, G=%d, B=%d)\n", color[0][0].r, color[0][0].g, color[0][0].b);
    printf("Lower-right (R=%d, G=%d, B=%d)\n", color[0][width - 1].r, color[0][width - 1].g, color[0][width - 1].b);

    fclose(fp);

    return 0;
}

int check_filetype(FILE *fp){

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
        return 0;
    } else {
        printf("Different file type.\n");
        return -1;
    }
}