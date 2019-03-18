#define QUEUE_SIZE 10

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "src/scheduler.h"

int main(void)
{
	Scheduler *scheduler = new Scheduler();

	char line[1024];
	char *args[80];
	while(1){
		fflush(stdout);
		printf("\n>");
		scanf("%s", line);
		printf("\n");
		Task *task = new Task(line);

		if( strcmp(task->args[0],"exit") == 0 ){
			exit(0);
		}else{
			scheduler->addTask(task);
		}
	}
	return 0;
}
