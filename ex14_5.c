#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hugeint.h"

huge_int *str_to_hugeint(char *str); /*文字列からhugeintに変換を行う*/
void print_huge_int(huge_int *in); /*hugeintで表されている整数を文字列に変換して表示する関数*/
huge_int *RSA_decode(huge_int *c, huge_int *n, huge_int *d);

int main(int argc, char *argv[]){
    huge_int *c = str_to_hugeint(argv[1]);
    huge_int *n = str_to_hugeint(argv[2]);
    huge_int *d = str_to_hugeint(argv[3]);

    huge_int *plain =  RSA_decode(c, n, d);

    print_huge_int(plain);

    free(c);
    free(n);
    free(d);

    return 0;
}

huge_int *str_to_hugeint(char *str){
    huge_int *ten = from_uchar(10);
    huge_int *x = from_uchar(0);

    int len = (int)strlen(str);

    for(int i=0;i<len;i++){
        huge_int *tmp = from_uchar((unsigned char)(str[i] - '0')); /*今回の桁の一時保存先*/
        huge_int *mul10 = huge_multiply(x, ten); /*ここまでの結果を10倍*/
        free(x);
        x = huge_add(mul10, tmp);
        free(tmp);
        free(mul10);
    }
    free(ten);

    return x;
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
        free(tmp_div.r);
        tmp_div.r = NULL;
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

huge_int *RSA_decode(huge_int *c, huge_int *n, huge_int *d){
    huge_int *zero = from_uchar(0);
    huge_int *two = from_uchar(2);
    huge_int *p = from_uchar(1);
    huge_int *base = huge_add(c, zero);
    huge_int *mod = huge_add(n, zero);
    huge_int *exp = huge_add(d, zero);

    huge_int *tmp_1 = from_uchar(0);
    huge_int *tmp_2 = from_uchar(0);
    huge_int *tmp_3 = from_uchar(0);

    while(is_zero(exp) != 1){
        if(exp->num[0]%2 == 1){
            free(tmp_1);
            tmp_1 = huge_multiply(p, base);
            free(p);
            huge_pair tmp1_div_mod = huge_divide(tmp_1, mod);
            p = huge_add(tmp1_div_mod.r, zero);
            free(tmp1_div_mod.q);
            free(tmp1_div_mod.r);
        }

        free(tmp_2);
        tmp_2 = huge_multiply(base, base);
        huge_pair base_div_mod = huge_divide(tmp_2, mod);
        free(base);
        base = huge_add(base_div_mod.r, zero);
        free(base_div_mod.q);
        free(base_div_mod.r);
        free(tmp_3);
        huge_pair exp_half = huge_divide(exp, two);
        tmp_3 = huge_add(exp_half.q, zero);
        free(exp);
        exp = huge_add(tmp_3, zero);
        free(exp_half.q);
        free(exp_half.r);
    }

    free(zero);
    free(two);
    free(base);
    free(exp);
    free(mod);
    free(tmp_1);
    free(tmp_2);
    free(tmp_3);

    return p;
}
