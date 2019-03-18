#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <pthread.h>
#include <time.h>
#include "task.h"
#include "queue.h"

static void *thread_init(void *queue){
  Queue *_queue = (Queue *)queue;
  _queue->loop();
}

class Scheduler{
public:
  Scheduler(){
    _queue = new Queue(&_qTask);
    pthread_create (&thread, NULL, thread_init, (void *)_queue);
  }

  ~Scheduler(){
    pthread_cancel(thread);
  }

  void addTask(Task * task){
    _qTask.push(task);
  }

  // 丟近來後開一個子process並且把task, 自己本身 與 seconds 帶進去
  // 在子process內sleep，直到時間到時再呼叫 addTask
  void addDelayedTask(Task * task, int seconds){

  }

  // 走過所有的tasks並且呼叫printStatus
  void printAllTaskStatus(){

  }

private:
  std::vector<Task *> _vTask;
  std::queue <Task *> _qTask;
  Queue *_queue;
  pthread_t thread;
};

#endif
