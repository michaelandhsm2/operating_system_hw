#ifndef TASK_H
#define TASK_H

#include <chrono>
using namespace std::chrono;

class Task{
public:
  char *args[40];
  char *_line;

  Task(char *line){
    _line = line;
    created_at = system_clock::now();
    printTime("Creating", created_at);
    parse(line, args);
  }

  // 輸入進來的有三種狀況 -
  // 他是正常指令，他是定時指令(前面兩個args是"delay"跟秒數)，跟他是"list"(要吐所有的proecess)
  // 你需要改一下system(_line)這邊，讓他能夠忽略list,然後定時指令時從第三個args開始丟
  void execute(){
    initiated_at = system_clock::now();
    printTime("Executing", initiated_at);
    system(_line);
    finished_at = system_clock::now();
    printTime("Finished", finished_at);
  }


  // 透過下面時間點紀錄是否有值來判斷執行階段，並且print出指令、狀態、runtime及turnaround time
  void printStatus(){

  }

private:
  system_clock::time_point created_at;
  system_clock::time_point initiated_at;
  system_clock::time_point finished_at;

  // 從process開始執行到完成所需秒數
  double getRuntime(){

  }

  // 從process建立到完成所需秒數
  double getTurnaroundTime(){

  }

  void printTime(char const *string, system_clock::time_point time_point){
    time_t time = std::chrono::system_clock::to_time_t(time_point);
    char string_time[80];
    strftime(string_time, sizeof(string_time), "%a %Y-%m-%d %H:%M:%S %Z", localtime(&time));
    printf("%s - %s command '%s'\n", string_time, string, _line);
  }

  void parse(char *line, char **argv){
    while (*line != '\0') {       /* if not the end of line ....... */
      while (*line == ' ' || *line == '\t' || *line == '\n')
        *line++ = '\0';     /* replace white spaces with 0    */
      *argv++ = line;          /* save the argument position     */
      while (*line != '\0' && *line != ' ' &&
        *line != '\t' && *line != '\n')
        line++;             /* skip the argument until ...    */
    }
  }
};

#endif
