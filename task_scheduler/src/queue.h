#ifndef QUEUE_H
#define QUEUE_H

class Queue{
public:
  Queue(std::queue<Task *> qTask){
    _qTask = qTask;
  }

  void loop(void){
    while(true){
      if(!_qTask.empty()){
          _qTask.front()->execute();
          _qTask.pop();
      }
      sleep(1);
    }
  }

private:
  std::queue <Task *> _qTask;
};

#endif
