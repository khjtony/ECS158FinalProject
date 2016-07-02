#include <stdio.h>
#include <time.h>


void findpaths(int *adjm, int n, int k, int *paths, int *numpaths) {
    int count = 0;
    int times = n;
    for (int i = 0; i < k; ++i) {times = times * n;}	// Dimension of time = n^k
    int arr[k+1];			// Create an array arr that is indexed from 0 to k
    
    for (int i = 0; i < k+1; ++i) {arr[i] = 0;}	// Initialize all elements in arr to be 0
    #pragma acc parallel loop
    for (int i = 0; i < times; ++i)
    {
        int temp = i, index = k, check = 1, r;
        while(temp!=0) 
        {
            r=(temp%n);
            temp/=n;
            arr[index] = r;
            index--;
        }

        for (int i = 0; i < k; ++i) 
        {
            check *= adjm[arr[i]*n+arr[i+1]];
        }

        if(check) 
        {
            for (int i = 0; i < k+1; ++i)
            {
                paths[count*(k+1)+i] = arr[i];
            }
            #pragma acc atomic update
	    count++;
        }
    }


    *numpaths = count;
}

int main(int argc, char const *argv[])
{
	int n = 5, k = 4;
	int path[2000000], numpaths;
	static int A[400] = {
    0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0,
    1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1,
    1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0,
    1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
    1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
    0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1,
    1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1,
    0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0,
    0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0,
    0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
    1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1,
    0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0};

	findpaths(A, n, k, path, &numpaths);

	printf("%d\n",numpaths);
	for (int i = 0; i < numpaths; ++i)
	{
		for (int j = 0; j < k+1; ++j)
		{
			printf("%d->", path[i*(k+1)+j]);
		}
		printf("\n");
	}


	return 0;
}