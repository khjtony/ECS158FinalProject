/*
    Introduction to OpenACC
    mmul_c.c Matrix Multiplication in C
    Not optimized
    Not claimed to be efficient
*/
#include "stdio.h"
#include "stdlib.h"

void mmul_c(float* A, float* B, int row, int col, float* out){
    // This code assume that out has been malloc-ed 
    int i=0;
    int j=0;
    int inner=0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            out[i*col+j] = 0.0;
            for (inner = 0; inner < col; inner++) {
                out[i*col+j] += A[i*col+inner] * B[inner*col+j]*1.0;
            }
        }
    }
}
int main(){
    // crate 3*3 matrix
    float A[]={1,2,3,4,5,6,7,8,9};
    float B[]={2,2,2,2,2,2,2,2,2};
    float out[9];
    mmul_c(A, B, 3, 3, out);
    return 0;
}