#ifndef TASK_H
#define TASK_H

#include <unistd.h>
#include <chrono>
using namespace std::chrono;

struct arg_struct {
  int *window;
  int window_size;
  int result;
  sem_t *mutex;
  system_clock::time_point initiated_at;
  system_clock::time_point finished_at;
};

int slidingWindowTask(int *window, int window_size){
  int sum = 0;
  for (int i = 0; i < window_size ; i++){
    sum += window[i];
  }
  sleep(1);
  return(sum);
}

void *runTask(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  sem_wait(args->mutex);

  args->initiated_at = system_clock::now();
  args->result = slidingWindowTask(args->window, args->window_size);
  args->finished_at = system_clock::now();

  sem_post(args->mutex);
  pthread_exit(NULL);
}

class Task{
public:
  Task(int *window, int window_size, sem_t *mutex){
    args.window_size = window_size;
    args.window = window;
    args.mutex = mutex;
    created_at = system_clock::now();
    pthread_create(&some_thread, NULL, runTask, (void *)&args);
  }

  ~Task(){
    pthread_cancel(some_thread);
  }

  // 透過下面時間點紀錄是否有值來判斷執行階段，並且print出指令、狀態、runtime及turnaround time
  void printStatus(){
    printf("------------------\n");
    printf("  Window - ");

    for (int i = 0; i < args.window_size ; i++){
      printf("%d", args.window[i]);
      if (i + 1 == args.window_size)
        printf("\n");
      else
        printf(", ");
    }
    printf("  ");
    printTime("Created", created_at);
    if(timeStarted(args.finished_at)){
      printf("  ");
      printTime("Executed", args.initiated_at);
      printf("  ");
      printTime("Finished", args.finished_at);
      printf("  Result - %d\n", args.result);
      printf("  Runtime - %f seconds\n", getRuntime());
      printf("  Turnaround Time - %f seconds\n", getTurnaroundTime());
    }else if(timeStarted(args.initiated_at)){
      printf("  ");
      printTime("Executing", args.initiated_at);
      printf("  Currently being executed.\n");
    }else{
      printf("  Currently waiting in Queue\n");
    }
  }

private:
  pthread_t some_thread;
  struct arg_struct args;
  system_clock::time_point created_at;
  char string_time[80];

  // 從process開始執行到完成所需秒數
  double getRuntime(){
    duration<double> run_time = args.finished_at - args.initiated_at;
    return run_time.count();
  }

  // 從process建立到完成所需秒數
  double getTurnaroundTime(){
    duration<double> turnaround_time = args.finished_at - created_at;
    return turnaround_time.count();
  }

  void printTime(char const *string, system_clock::time_point time_point){
    printf("%s - %s\n", timeString(time_point), string);
  }

  char *timeString(system_clock::time_point time_point){
    time_t time = system_clock::to_time_t(time_point);
    strftime(string_time, sizeof(string_time), "%a %Y-%m-%d %H:%M:%S %Z", localtime(&time));
    return(string_time);
  }

  bool timeStarted(system_clock::time_point time_point){
    return time_point.time_since_epoch().count();
  }
};

#endif
