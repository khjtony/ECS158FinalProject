set path = ($path /home/matloff/Pub)
set path = ($path /home/matloff/Pub/omni/bin)
set path = ($path /usr/lib64/mpich/bin)
set path = ($path /usr/local/cuda-5.5/bin)
set path = ($path /usr/local/cuda-7.5/bin)
setenv LD_LIBRARY_PATH
setenv LD_LIBRARY_PATH /usr/local/cuda-5.5/targets/x86_64-linux/lib:$LD_LIBRARY_PATH
setenv LD_LIBRARY_PATH /usr/local/cuda-7.5/targets/x86_64-linux/lib:$LD_LIBRARY_PATH
