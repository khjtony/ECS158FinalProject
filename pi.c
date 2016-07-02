#include <stdio.h>
#include <sys/time.h>

#define N 2000000000

#define vl 1024


double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}



int main(void) {

  double pi = 0.0f;
  long long i;
  double time_begin=get_wall_time();
  
  #pragma acc parallel vector_length(vl) 
  #pragma acc loop reduction(+:pi)
  for (i=0; i<N; i++) {
    double t= (double)((i+0.5)/N);
    pi +=4.0/(1.0+t*t);
  }

  double time_end=get_wall_time();
  printf("pi=%11.10f\n",pi/N);
  printf("Total elapsed time is: %.4lf\n", (time_end - time_begin));

  return 0;

}