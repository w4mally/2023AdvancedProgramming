#include <stdio.h>

int main(void) {
    char string[128];
    int n = 0;

    scanf("%s", string);

    int len = 0;
    for(int i = 0; i < 128; i++) {
        if (string[i] == '\0') {
            len = i;
            break;
        }
    }

    for(int i = 0; i < len; i++) {
        int x = string[i] - 48;
        int y = 1;
        for(int j = len - i - 1; j > 0; j--) {
            y = y * 10;
        }
        n += x * y;
    }
    
    printf("\n%d\n", n);

    return 0;
}