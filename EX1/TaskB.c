#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <inttypes.h>
#include <string.h>
#include <x86intrin.h>

int timesTest(){
  int ns_max = 50;
  int histogram[ns_max];
  memset(histogram, 0, sizeof(int)*ns_max);

  struct tms t1;
  struct tms t2;
  for(int i = 0; i < 10*1000*1000; i++){

      times(&t1);
      times(&t2);

      int ns = (intmax_t)(t2.tms_stime - t1.tms_stime); //* ??
      if(ns >= 0 && ns < ns_max){
          histogram[ns]++;
      }
  }
  for(int i = 0; i < ns_max; i++){
      printf("%d\n", histogram[i]);
  }
  return 0;
}

int getTimeTest(){
  int ns_max = 50;
  int histogram[ns_max];
  memset(histogram, 0, sizeof(int)*ns_max);

  struct timespec t1, t2;
  for(int i = 0; i < 10*1000*1000; i++){

      clock_gettime( CLOCK_REALTIME, &t1);
      clock_gettime( CLOCK_REALTIME, &t2);

      int ns = (intmax_t)(t2.tv_nsec - t1.tv_nsec); //* ??
      if(ns >= 0 && ns < ns_max){
          histogram[ns]++;
      }
  }
  for(int i = 0; i < ns_max; i++){
      printf("%d\n", histogram[i]);
  }
  return 0;
}

int rdtscTest(){

    int ns_max = 50;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);
    uint64_t t1, t2;
    for(int i = 0; i < 10*1000*1000; i++){

        t1 = __rdtsc();
        t2 = __rdtsc();

        int ns = (intmax_t)(t2 - t1); //* ??
        if(ns >= 0 && ns < ns_max){
            histogram[ns]++;
        }
    }
    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }
    return 0;
}



int main(int argc, char *argv[])
{

  // timesTest();
  // getTimeTest();
  rdtscTest();
  printf("Hello     world\n");
  return     0;
}
