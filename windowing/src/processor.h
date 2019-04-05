#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <queue>
#include <stdlib.h>
#include "queue.h"
#include "task.h"

class Processor{
public:
  Processor(int window_size){
    _window_size = window_size;
    sem_init(&mutex, 0, 1);
    _queue = new Queue(_window_size, &_vTask, &mutex);
  }

  ~Processor(){
    _vTask.clear();
  }

  void newInput(char *line){
    std::vector<int> args;
    char *text = strtok (line, " ,.-");
    while (text != NULL)
    {
      _queue->push(atoi(text));
      text = strtok(NULL, " ,.-");
    }
  }

  void printAllTaskStatus(){
    for (int i = 0; i < _vTask.size() ; i++){
      _vTask[i] -> printStatus();
    }
    if(_vTask.size() > 0)
      printf("------------------\n");
    else
      printf("There is no history records available.\n");
  }

private:
  std::vector<Task *> _vTask;
  int _window_size;
  Queue *_queue;
  sem_t mutex;
};

#endif
