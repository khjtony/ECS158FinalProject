
__global__ void kernel(float *A, float *B, int row, int col, float *out){
    int nth = threadIdx.x;
    int division = r1/total;
    int i=0;
    int j=0;
    int inner=0;
    for (i = (division*nth); i < (nth==(total-1) ? row : (division*nth+division)); i++) {
        for (j = 0; j < col; j++) {
            out[i*col+j] = 0;
            for (inner = 0; inner < col; inner++) {
                out[i*col+j] += a[i*col+inner] * b[inner*col+j]*1.0;
            }
        }
    }
}

void mmul_cuda(float *A, float *B, int row, int col, float *out){
    float *dA, *dB, *dout;
    int msize = row*col*sizeof(float);
    cudaMalloc((void**)&dA, msize);
    cudaMalloc((void**)&dB, msize);
    cudaMalloc((void**)&dm, msize);
    cudaMemcpy(dA, A, msize, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, B, msize, cudaMemcpyHostToDevice);

    int blockSize = 4;  // use 4 blocks
    dim3 dimGrid(blockSize, 1);
    dim3 dimBlock(1,1,1);

    kernel<<<dimGrid, dimBlock>>>(dA, dB, row, col, dm);

    cudaMemcpy(out, dm, msize, cudaMemcpyDeviceToHost);
    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dm);

    return;

}