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


    // n = matrix dimension; k = subimage dimension; start and end are for parallelism; pix is the pointer to the matrix.
int brightssplit (float *pix, int n, int k, float thresh, int start, int end) {
	float count = 0, check[n];
	for (int i = 0; i < n; ++i)
	{	// iterate throught ALL n rows
    // Clear book keeping variables for a new round
    	   	float minus, sum = 0;
    // Count the number of bright pixel in a single row of 1 x k
    // i * n locate row, + j locate column
			for (int j = start; j < start+k; ++j) if (pix[i*n+j] > thresh) {sum++;}
    // end - k + 1 basically recovers the boundary by the 1st column index of each window
    // which could be understood as the window column index
    // instead of the last column index which is end itself
    // Now we run from the starting window column index to the end WCI
    // Visually, we are moving a 1 x k block across row i to track bright block
			for (int j = start; j < (end-k+1); ++j)
			{
    // minus:
    // This is a smart way of moving the 1 x k block to the right.
    // Instead of using excessive for loops and repetitive checking,
    // we simply look at the left most pixel of that block,
    // and later we can see what we could do with sum.
				if (pix[i*n+j] > thresh) {minus = 1;} else {minus = 0;}
    // Check List for keeping track of the number of 1 x k bright unit
    // in terms of window column index
    // Initialized when going through the first row
	
				if (i == 0) {if (sum >= k) {check[j] = 1;} else {check[j] = 0;}}
    // Now we are out of the first row, that means we get to +/- to the list,
    // and hopefully hit a bring window when count >= k!
    // Keep Count++ when check[j] >= k
    // Clear it when we hit a 1 x k block with non-bright pixels.
				else {
					if (sum >= k) {
						check[j] ++;
						if (check[j] >= k) {count ++;}}
					else {check[j] = 0;}}
    // Now we are about to move the 1 x k block to the right. Rmb the minus?
    // We can now use it to change sum, together with the information of
    // the one new pixel the 1 x k block now includes.
    // Again, elegant way of avoiding repetitive checking!

				if(minus == 0 && pix[i*n+j+k] > thresh) {sum++;}
				else if(minus == 1 && pix[i*n+j+k] <= thresh) {sum--;}
			}
	}

	return count;
}

int brights (float *pix, int n, int k, float thresh) {
		brightssplit (pix, n, k, thresh, 0, n);
}


int main (int argc, char const *argv[])
{

	float A[MAX_SIZE*MAX_SIZE];	// use one dimensional array to represent the matrix
	seed(MAX_SIZE,MAX_SIZE,A);	// generate random matrix
    int count = 0;
    int i=0;
    for (i=0;i<N_ITERS;i++){
        count += brights (A, 1000, 5, 0.2);
    }

    printf("There are average %d starts in %d iters.\n", count/N_ITERS, N_ITERS);
	return 0;
}