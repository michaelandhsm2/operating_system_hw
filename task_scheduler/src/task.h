#ifndef TASK_H
#define TASK_H

class Task{
public:
  char *args[40];
  char *_line;

  Task(char *line){
    _line = line;
    time(&created_at);
    printTime("Creating", created_at);
    parse(line, args);
  }

  void execute(){
    time(&initiated_at);
    printTime("Executing", initiated_at);
    system(_line);
    time(&finished_at);
    printTime("Finished", finished_at);
  }

  int getRuntime(){

  }

  int getThroughputTime(){

  }

private:
  time_t created_at;
  time_t initiated_at;
  time_t finished_at;

  void printTime(char const *string, time_t time){
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
