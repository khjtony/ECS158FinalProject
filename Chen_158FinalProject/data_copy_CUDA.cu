cudaMalloc(A_device)  // Allocate Memory on Device
cudaMemcpy(A_host, A_device, cudaMemcpyHostToDevice)  // Initialize A with the Data from Host
cudaMemcpy(A_host, A_device, cudaMemcpyDeviceToHost)  // Copy the Resultant Data back to Host
cudaFree(A_device)  // Free Device Memory
