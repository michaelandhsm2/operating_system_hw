#ifndef TIMER_H
#define TIMER_H
#include <queue>
#include <pthread.h>
#include "task.h"
#include "queue.h"

struct arg_struct {
    int arg1;
    Task * arg2;
};

std::queue <Task *> _qTask;

void *delay(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
    printf("It will be done after %d second(s).\n", args -> arg1);
    sleep(args -> arg1);
    _qTask.push(args -> arg2);
    pthread_exit(NULL);
}

class Timer{
public:
  Timer(int * sec, Task * task){
    args.arg1 = *sec;
    args.arg2 = task;
    pthread_create(&some_thread, NULL, delay, (void *)&args);
  }

  ~Timer(){
    pthread_cancel(some_thread);
  }

private:
  pthread_t some_thread;
  struct arg_struct args;
};

#endif
