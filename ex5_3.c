#include <stdio.h>

void print_matrix(int n, int mat[n][n]);
void square_matrix(int n, int mat[n][n]);


int main(void){
	int n = 0;
	scanf("%d", &n);

	int mat[n][n];

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			mat[i][j] = i*n + j;
		}
	}
	printf("(M)\n");
	print_matrix(n, mat);
	printf("(M^2)\n");
	square_matrix(n, mat);
	print_matrix(n, mat);
	printf("(M^4)\n");
	square_matrix(n, mat);
	print_matrix(n, mat);

	return 0;
}

void print_matrix(int n, int mat[n][n]){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j!=n-1) printf("%d, ", mat[i][j]);
			else printf("%d\n", mat[i][j]);
		}
	}
	printf("\n");
}

void square_matrix(int n, int mat[n][n]){
	int temp_mat[n][n];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			temp_mat[i][j] = 0;
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){

			for(int k=0;k<n;k++){
				temp_mat[i][j] += mat[i][k]*mat[k][j];
			}

		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			mat[i][j] = temp_mat[i][j];
		}
	}
}
