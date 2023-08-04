#include <stdio.h>
#include <stdlib.h>
#include "hugeint.h"

void print_huge_int(huge_int *in); /*hugeintで表されている整数を文字列に変換して表示する関数*/

int main(int argc, char *argv[]){
    FILE *fp;
    fp = fopen(argv[1], "rb");

    if(fp == NULL){
        printf("File Open Error!\n");
        return 1;
    }

    /*ファイルサイズ(バイト数)の調査*/
    size_t filesize = 0;
    fseek(fp, 0, SEEK_SET);

    while(fgetc(fp) != EOF){
        filesize++;
    }

    /*ファイル内容の非負整数化*/
    huge_int *result = malloc(sizeof(huge_int) + filesize);
    result->size = filesize;

    fseek(fp, 0, SEEK_SET);
    fread(result->num, sizeof(unsigned char), filesize, fp);

    fclose(fp);

    print_huge_int(result);

    return 0;
}

void print_huge_int(huge_int *in){
    char rev_ans[10000];
    char ans_char[10000];
    int cnt = 0;
    unsigned long long tmp_ull = 0;
    huge_int *ten = from_uchar(10);
    huge_pair tmp_div;
    while(1){
        if(is_zero(in)){
            free(in);
            break;
        }
        tmp_div = huge_divide(in, ten);
        tmp_ull = to_ulonglong(tmp_div.r);
        rev_ans[cnt] = "0123456789"[tmp_ull%10];
        free(in);
        in = tmp_div.q;
        cnt++;
        free(tmp_div.r);
    }

    rev_ans[cnt] = '\0';

    /*rev_ansを反転させて正しい出力をans_charに書き込む*/
    for(int i=0;i<cnt;i++){
        ans_char[i] = rev_ans[cnt-1-i];
    }

    ans_char[cnt] = '\0';

    printf("%s\n", ans_char);

    free(ten);
}
