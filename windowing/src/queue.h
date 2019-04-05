#ifndef QUEUE_H
#define QUEUE_H

#include <semaphore.h>
#include <pthread.h>
#include "task.h"

class Queue{
public:
  Queue(int window_size, std::vector<Task *> *vTask, sem_t *mutex){
    _window_size = window_size;
    _vTask = vTask;
    _mutex = mutex;
  }

  void push(int number){
    _qNumber.push_back(number);

    if(_qNumber.size() == _window_size){

      int *window = (int *)malloc(sizeof(int)*_window_size);
      for (int i = 0; i < _window_size; i++){
        window[i] = _qNumber[i];
      }

      Task *task = new Task(window, _window_size, _mutex);
      _vTask->push_back(task);

      _qNumber.pop_front();
    }
  }

private:
  int _window_size;
  std::deque<int> _qNumber;
  std::vector<Task *> *_vTask;
  sem_t *_mutex;
};

#endif
