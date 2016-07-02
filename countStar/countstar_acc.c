#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MATRIX_MAX 1
#define MAX_SIZE 1400
#define N_ITERS 1000


void seed(int r, int c, float *out) {   //generate a random matrix
    time_t t;
    srand((unsigned) time(&t));
    for (int i=0;i<r;i++){
        for (int j=0;j<c;j++){
            out[i*c+j]=(float)(MATRIX_MAX*((int)(rand()%100)/100.0));
        }
    }
}


#pragma acc routine seq 
int brightssplit (float *pix, int n, int k, float thresh, int start, int end) {
    float count = 0, check[n];
    #pragma acc data copy(pix[0:n*n], check[0:n])
    {

        #pragma acc loop 
        for (int i = 0; i < n; ++i)
        {
            float minus, sum = 0;

            for (int j = start; j < start+k; ++j){
                if (pix[i*n+j] > thresh){
                    sum++;
                }
            } 
            #pragma acc loop
            for (int j = start; j < (end-k+1); ++j)
            {
                if (pix[i*n+j] > thresh){
                    minus = 1;
                } else {
                    minus = 0;
                }
    
                if (i == 0) {
                    if (sum >= k) {
                        check[j] = 1;
                    } else {
                        check[j] = 0;
                    }
                }
                else {
                    if (sum >= k) {
                        check[j] ++;
                        if (check[j] >= k) {
                            count ++;
                        }
                    }
                    else {
                        check[j] = 0;
                    }
                }

                if(minus == 0 && pix[i*n+j+k] > thresh) {sum++;}
                else if(minus == 1 && pix[i*n+j+k] <= thresh) {sum--;}
            }
        }
    }

    return count;
}

int brights (float *pix, int n, int k, float thresh) {
	int i=0;
    int blocks = n/k-1;
    int count = 0;
	#pragma acc data create(pix)
    #pragma acc parallel loop reduction(+:count)
    for (i=0;i<blocks;i++){
        count += brightssplit (pix, n, k, thresh, k*i, k*(i+1)+k-1);
    }
        
    count += brightssplit(pix, n, k, thresh, k*i, n);
    return count;
}


int main (int argc, char const *argv[])
{

	float A[MAX_SIZE*MAX_SIZE];
    seed(MAX_SIZE,MAX_SIZE,A);

    int count = 0;
    int i=0;
    for (i=0;i<N_ITERS;i++){
        count += brights (A, 1000, 5, 0.2);
    }

    printf("There are average %d starts in %d iters.\n", count/N_ITERS, N_ITERS);
	return 0;
}
