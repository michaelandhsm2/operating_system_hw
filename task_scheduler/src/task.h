#ifndef TASK_H
#define TASK_H

class Task{
public:
  char *args[40];

  Task(char *line){
    time(&created_at);
    parse(line, args);
  }

  void execute(){
    char string_time[80];
    strftime(string_time, sizeof(string_time), "%a %Y-%m-%d %H:%M:%S %Z", localtime(&created_at));
    printf("Executing command created at %s", string_time);
    execvp(args[0], args);
    printf("Finished command created at %s", string_time);
  }

  int getRuntime(){

  }

  int getThroughputTime(){

  }

private:
  time_t created_at;
  time_t initiated_at;
  time_t finished_at;

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
