#include <stdio.h>

void swap1(char a, char b){
	char temp;
	printf("In swap1: addresses of a: %p, addresses of b: %p\n", &a, &b);
	temp = a;
	a = b;
	b = temp;
}

void swap2(char *a, char *b){
	char temp;
	printf("In swap2: addresses of a: %p, addresses of b: %p\n", a, b);
	temp = *a;
	*a = *b;
	*b = temp;
}

int main(void){
	char a = 'A';
	char b = 'B';

	printf("In main: addresses of a: %p, addresses of b: %p\n", &a, &b);

	swap2(&a, &b);

	printf("a = %c, b = %c\n", a,b);

	return 0;
}
