#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hugeint.h"

void print_huge_int(huge_int *in);

int main(int argc, char *argv[]){
    huge_int *x = from_uchar(0);
    huge_int *ten = from_uchar(10);
    
    /*入力された非負整数を文字列からhugeintに変換*/
    int len = (int)strlen(argv[1]);
    for(int i=0;i<len;i++){
        huge_int *tmp = from_uchar((unsigned char)(argv[1][i] - '0')); /*今回の桁の一時保存先*/
        huge_int *mul10 = huge_multiply(x, ten); /*ここまでの結果を10倍*/
        free(x);
        x = huge_add(mul10, tmp);
        free(tmp);
        free(mul10);
    }
    free(ten);

    /*xからファイル内容を復元*/
    FILE *fp;
    fp = fopen(argv[2], "wb");

    fwrite(x->num, sizeof(unsigned char), x->size, fp);

    fclose(fp);

    return 0;
}

void print_huge_int(huge_int *in){
    char rev_ans[10000];
    char ans_char[10000];
    int cnt = 0;
    unsigned long long tmp_ull = 0;
    huge_int *ten = from_uchar(10);
    while(1){
        if(is_zero(in)) break;
        huge_pair tmp_div = huge_divide(in, ten);
        tmp_ull = to_ulonglong(tmp_div.r);
        rev_ans[cnt] = "0123456789"[tmp_ull%10];
        free(in);
        in = tmp_div.q;
        free(tmp_div.r);
        cnt++;
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