#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1001

int main(void) {
    char buff[BUF_SIZE];
    int i = 0;
    FILE* fp1;
    FILE* fp2;
    fp1 = fopen("ex9_0_plain.txt", "r");
    fp2 = fopen("ex9_0_cipher.txt", "a");

    while (fgets(buff, sizeof(buff), fp1) != NULL) {
        i = 0;
        buff[strlen(buff)] = '\0';
        while (buff[i] != '\0') {
            if ('A' <= buff[i] && buff[i] <= 'W') {
                buff[i] = buff[i] + 3;
            }
            else if (buff[i] == 'X') {
                buff[i] = 'A';
            }
            else if (buff[i] == 'Y') {
                buff[i] = 'B';
            }
            else if (buff[i] == 'Z') {
                buff[i] = 'C';
            }
            i++;
        }
        fputs(buff, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}