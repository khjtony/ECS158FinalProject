/*
    Introduction to OpenACC: From desktop to hand
    mmul_acc.c matrix multiplication in acc
    No optimization guarantee
    No effieicny 
*/

#include <stdio.h>
#include <stdlib.h>

#define N_ITERS 30000

void mmul_acc(float* A, float* B, int row, int col, float* out){
    // This code assume that out has been malloc-ed 
    int i=0;
    int j=0;
    int inner=0;
    float temp_sum=0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            out[i*col+j] = 0.0;
            for (inner = 0; inner < col; inner++) {
                temp_sum += A[i*col+inner] * B[inner*col+j]*1.0;
            }
            out[i*col+j]=temp_sum;
            temp_sum=0;
        }
    }
}

void printMatrix(float* A, int row, int col){
    if (row>10 && col >10){
        printf("Matrix too large\n");
        return;
    }
    int i=0;
    int j=0;
    for (i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%.2f\t", A[i*col+j]);
        }
        printf("\n");
    }
}

int main(){
    // crate 3*3 matrix
    int row =50;
    float *A=(float*)malloc(row*row*sizeof(float));
    float *B=(float*)malloc(row*row*sizeof(float));
    float *out=(float*)malloc(row*row*sizeof(float));

    int i=0;
    for(i=0;i<(row*row);i++){
        A[i]=i+1;
        B[i]=2;
        out[i]=0;
    }


    printf("A is:\n");
    printMatrix(A, row, row);
    printf("B is:\n");
    printMatrix(B, row, row);
    for (i=0;i<N_ITERS;i++){
       mmul_acc(A, B, row, row, out); 
       if(i%100000==0){
        printf("Now its %d iters\n", i);
       }
    }
    printf("out is:\n");
    printMatrix(out, row, row);
    return 0;
}