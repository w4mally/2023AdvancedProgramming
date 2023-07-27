#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hugeint.h"

int main(int argc, char *argv[]){
    huge_int *x = from_uchar(0); /*argv[1]の格納先*/
    huge_int *y = from_uchar(0); /*argv[2]の格納先*/
    huge_int *ten = from_uchar(10);
    unsigned long long tmp_ull = 0;
    char rev_ans[10000];
    char ans_char[10000];
    int flag = 2;

    /*1つ目の引数のhugeintへの変換*/
    int len1 = (int)strlen(argv[1]);
    for(int i=0;i<len1;i++){
        huge_int *tmp = from_uchar((unsigned char)(argv[1][i] - '0')); /*今回の桁の一時保存先*/
        huge_int *mul10 = huge_multiply(x, ten); /*ここまでの結果を10倍*/
        free(x);
        x = huge_add(mul10, tmp);
        free(tmp);
        free(mul10);
    }

    /*2つ目の引数のhugeintへの変換*/
    int len2 = (int)strlen(argv[2]);
    for(int i=0;i<len2;i++){
        huge_int *tmp = from_uchar((unsigned char)(argv[2][i] - '0')); /*今回の桁の一時保存先*/
        huge_int *mul10 = huge_multiply(y, ten); /*ここまでの結果を10倍*/
        free(y);
        y = huge_add(mul10, tmp);
        free(tmp);
        free(mul10);
    }

    huge_int *ans = huge_add(x, y); /*和の計算*/

    if (x->size == 0 && y->size == 0) {
        flag = 1;
    }
    else {
        flag = 0;
    }

    free(x);
    free(y);

    /*計算結果をchar配列に書き込んで文字列化していく、ただしこの時点では正しい出力と反転している*/
    int cnt = 0;
    while(1){
        if(is_zero(ans)) break;
        huge_pair tmp_div = huge_divide(ans, ten);
        tmp_ull = to_ulonglong(tmp_div.r);
        rev_ans[cnt] = "0123456789"[tmp_ull%10];
        free(ans);
        ans = tmp_div.q;
        free(tmp_div.r);
        cnt++;
    }

    rev_ans[cnt] = '\0';

    /*rev_ansを反転させて正しい出力をans_charに書き込む*/
    for(int i=0;i<cnt;i++){
        ans_char[i] = rev_ans[cnt-1-i];
    }

    ans_char[cnt] = '\0';

    if (flag == 1) printf("0\n");
    else printf("%s\n", ans_char);

    free(ten);
    free(ans);

    return 0;
}
