#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <inttypes.h>

struct timespec timespec_normalized(time_t sec, long nsec){
    while(nsec >= 1000000000){
        nsec -= 1000000000;
        ++sec;
    }
    while(nsec < 0){
        nsec += 1000000000;
        --sec;
    }
    return (struct timespec){sec, nsec};
}
struct timespec timespec_sub(struct timespec lhs, struct timespec rhs){
    return timespec_normalized(lhs.tv_sec - rhs.tv_sec, lhs.tv_nsec - rhs.tv_nsec);
}
struct timespec timespec_add(struct timespec lhs, struct timespec rhs){
    return timespec_normalized(lhs.tv_sec + rhs.tv_sec, lhs.tv_nsec + rhs.tv_nsec);
}
int timespec_cmp(struct timespec lhs, struct timespec rhs){
    if (lhs.tv_sec < rhs.tv_sec)
        return -1;
    if (lhs.tv_sec > rhs.tv_sec)
        return 1;
    return lhs.tv_nsec - rhs.tv_nsec;
}

void busy_wait(struct timespec t){
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    struct timespec then = timespec_add(now, t);
    while(timespec_cmp(now, then) < 0){
        for(int i = 0; i < 10000; i++){}
        clock_gettime(CLOCK_MONOTONIC, &now);
    }
}

int delay(){
  struct tms start_cpu;
  struct tms stop_cpu;

  times(&start_cpu);
  times(&stop_cpu);
  // printf("Real Time: %jd", (intmax_t)(start_cpu.tms_stime + start_cpu.tms_utime));
  // printf("Real Time: %jd", (intmax_t)sysconf(_SC_CLK_TCK));
  while((intmax_t)(stop_cpu.tms_stime + stop_cpu.tms_utime)<sysconf(_SC_CLK_TCK)){
    times(&stop_cpu);
    // printf("Real Time: %jd", (intmax_t)(stop_cpu.tms_stime + stop_cpu.tms_utime - start_cpu.tms_stime - start_cpu.tms_utime));
  }
  printf("Real Time: %jd", (intmax_t)(stop_cpu.tms_stime + stop_cpu.tms_utime - start_cpu.tms_stime - start_cpu.tms_utime));
}

int main(int argc, char *argv[])
{
  // usleep(1000000);
// sleep(1);
  // struct timespec ts;
  // ts.tv_sec = 1;
  // busy_wait(ts);

  delay();

  printf("Hello     world\n");
  return     0;
}
