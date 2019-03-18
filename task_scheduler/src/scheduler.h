#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <pthread.h>
#include <time.h>
#include "iterator.h"
#include "task.h"
#include "queue.h"

static void *thread_init(void *queue){
  Queue *_queue = (Queue *)queue;
  _queue->loop();
}

class Scheduler{
public:

  class TaskIterator : public Iterator<Task *> {
  public:
    TaskIterator(Scheduler * scheduler){_scheduler = scheduler;}
    void first() { _currentPosition = _scheduler->_vTask.begin(); }
    void next() { ++_currentPosition; }
    bool isDone() const { return (_currentPosition == _scheduler->_vTask.end()); }
    Task *currentItem() {return *_currentPosition;}
  private:
    Scheduler * _scheduler;
    std::vector<Task *>::iterator _currentPosition;
  };

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

  void addDelayedTask(){

  }

  void checkTask(){

  }

  Iterator<Task *> *listTask(){
    return new TaskIterator(this);
  }

private:
  std::vector<Task *> _vTask;
  std::queue <Task *> _qTask;
  Queue *_queue;
  pthread_t thread;
};

#endif
