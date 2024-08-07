#include <stdio.h>

void vec_mult_s(int n, float *in, float a, float *out);
int vec_div(int n, float *in, float a, float *out);
void vec_sub(int n, float *in1, float *in2, float *out);
int mat_inv(int n, float in[n][n], float out[n][n]);
void print_matrix(int n, float mat[n][n]);

int main(void){
    int n = 0;
    int check = 2;

    FILE *fp;
    char filename[] = "matrix.txt";

    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File is not found.");
    }

    fscanf(fp, "%d", &n);
    float in[n][n];
    float out[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fscanf(fp, "%f", &in[i][j]);
        }
    }

    fclose(fp);

    printf("(input matrix)\n");
    print_matrix(n, in);

    check = mat_inv(n, in, out);

    if(check==0){
        printf("(inverse matrix)\n");
        print_matrix(n, out);
    }
    else if(check==-1){
        printf("Not invertible");
    }

    return 0;
}

void vec_mult_s(int n, float *in, float a, float *out){
    for(int i=0;i<n;i++){
        out[i] = a*in[i];
    }
}

int vec_div(int n, float *in, float a, float *out){
    if(a==0){
        return 1;
    } else {
        for(int i=0;i<n;i++){
            out[i] = in[i]/a;
        }
        return 0;
    }
}

void vec_sub(int n, float *in1, float *in2, float *out){
    for(int i=0;i<n;i++){
        out[i] = in1[i] - in2[i];
    }
}

int mat_inv(int n, float in[n][n], float out[n][n]){
    float mat1[n][n];
    float mat2[n][n]; /*identity matrix*/
    /*temporary vector*/
    float vec1[n];
    float vec2[n];
    float vec3[n];
    float vec4[n];
    float vec5[n];
    float vec6[n];
    int flag = 0;

    /*copy and generate identity matrix*/
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mat1[i][j] = in[i][j];
            if(i==j){
                mat2[i][j] = 1;
            } else {
                mat2[i][j] = 0;
            }
        }
    }

    /*get inverse matrix*/
    for(int i=0;i<n;i++){
        if(mat1[i][i]==0){
            for(int j=i+1;j<n;j++){
                if(mat1[j][i]!=0){
                    for(int k=0;k<n;k++){
                        vec1[k] = mat1[j][k];
                        vec2[k] = mat2[j][k];
                    }
                    for(int k=0;k<n;k++){
                        mat1[j][k] = mat1[i][k];
                        mat2[j][k] = mat2[i][k];
                        mat1[i][k] = vec1[k];
                        mat2[i][k] = vec2[k];
                    }
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                return -1;
            }
            flag = 0;
        }
        /*step1 start*/
        for(int j=0;j<n;j++){
            /*copy line i*/
            vec1[j] = mat1[i][j];
            vec2[j] = mat2[i][j];
        }
        vec_div(n, vec1, mat1[i][i], vec3);
        vec_div(n, vec2, mat1[i][i], vec4);
        for(int j=0;j<n;j++){
            mat1[i][j] = vec3[j];
            mat2[i][j] = vec4[j];
        }
        /*step1 end*/
        /*step2 start*/
        for(int j=0;j<n;j++){
            if(i!=j){
                for(int k=0;k<n;k++){
                    vec3[k] = mat1[i][k];
                    vec4[k] = mat2[i][k];
                }
                vec_mult_s(n, vec3, mat1[j][i], vec5);
                vec_mult_s(n, vec4, mat1[j][i], vec6);
                for(int k=0;k<n;k++){
                    vec1[k] = mat1[j][k];
                    vec2[k] = mat2[j][k];
                }
                vec_sub(n, vec1, vec5, vec3);
                vec_sub(n, vec2, vec6, vec4);
                for(int k=0;k<n;k++){
                    mat1[j][k] = vec3[k];
                    mat2[j][k] = vec4[k];
                }
        }
    }
    /*step2 end*/
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            out[i][j] = mat2[i][j];
        }
    }
    return 0;
}

void print_matrix(int n, float mat[n][n]){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j!=n-1) printf("%f, ", mat[i][j]);
			else printf("%f\n", mat[i][j]);
		}
	}
	printf("\n");
}
