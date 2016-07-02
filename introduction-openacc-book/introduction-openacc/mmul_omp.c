void mmul_omp(float *A, float *B, int row, int col, float *out, ){
    #pragma omp parallel
    {
        int nth = omp_get_thread_num();
        int total = omp_get_num_threads();
        int division = row/total;
        int i=0;
        int j=0;
        int inner = 0;
        #pragma omp for
        for (i = (division*nth); i < (nth==(total-1) ? row : (division*nth+division)); i++) {
            for (j = 0; col < col; j++) {
                out[i*col+j] = 0;
                for (inner = 0; inner < col; inner++) {
                    out[i*col+j] += A[i*col+inner] * B[inner*col+j]*1.0;
                }
            }
        }
    }
}