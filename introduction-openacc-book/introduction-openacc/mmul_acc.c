void mmul_acc(float* A, float* B, int row, int col, float* out){
    // This code assume that out has been malloc-ed 
    int i=0;
    int j=0;
    int inner=0;
    float temp_sum=0;
    #pragma acc data create(A[0:(row*col)],B[0:(row*col)]) copy(out[0:row*col])
    {
        #pragma acc parallel loop
        for (i = 0; i < row; i++) {
            #pragma acc loop
            for (j = 0; j < col; j++) {
                out[i*col+j] = 0.0;
                #pragma acc loop reduction(+:temp_sum)
                for (inner = 0; inner < col; inner++) {
                    temp_sum = A[i*col+inner] * B[inner*col+j]*1.0;
                }
                out[i*col+j]=temp_sum;
                temp_sum=0;
            }
        }
    }
}
