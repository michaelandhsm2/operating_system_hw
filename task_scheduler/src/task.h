#ifndef TASK_H
#define TASK_H

#include <chrono>
using namespace std::chrono;

class Task{
public:
  char *args[40];
  char *_line;
  bool isDelayed = false;

  Task(char *line){
    _line = strdup(line);
    created_at = system_clock::now();
    parse(line, args);
    if(strcmp(args[0], "delay") && strcmp(args[0], "exit") && strcmp(args[0], "list")){
      printTime("Creating", created_at);
    }
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
    printf("------------------\n");
    printf("Command '%s' :\n", _line);
    printf("  ");
    printTime("Created", created_at);
    if(timeStarted(finished_at)){
      printf("  ");
      printTime("Executed", initiated_at);
      printf("  ");
      printTime("Finished", finished_at);
      printf("  Runtime - %f seconds\n", getRuntime());
      printf("  Turnaround Time - %f seconds\n", getTurnaroundTime());
    }else if(timeStarted(initiated_at)){
      printf("  ");
      printTime("Executing", initiated_at);
      printf("  Currently being executed.\n");
    }else{
      if(isDelayed)
        printf("  Is being delayed\n");
      else
        printf("  Currently waiting in Queue\n");
    }
  }

private:
  system_clock::time_point created_at;
  system_clock::time_point initiated_at;
  system_clock::time_point finished_at;
  char string_time[80];

  // 從process開始執行到完成所需秒數
  double getRuntime(){
    duration<double> run_time = finished_at - initiated_at;
    return run_time.count();
  }

  // 從process建立到完成所需秒數
  double getTurnaroundTime(){
    duration<double> turnaround_time = finished_at - created_at;
    return turnaround_time.count();
  }

  void printTime(char const *string, system_clock::time_point time_point){
    printf("%s - %s command '%s'\n", timeString(time_point), string, _line);
  }

  char *timeString(system_clock::time_point time_point){
    time_t time = system_clock::to_time_t(time_point);
    strftime(string_time, sizeof(string_time), "%a %Y-%m-%d %H:%M:%S %Z", localtime(&time));
    return(string_time);
  }

  bool timeStarted(system_clock::time_point time_point){
    return time_point.time_since_epoch().count();
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
