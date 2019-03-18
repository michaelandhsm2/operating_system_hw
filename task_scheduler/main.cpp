#define QUEUE_SIZE 10

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "src/scheduler.h"

// 1. 這邊在開始loop前加些說明文字解釋如何使用 (ie.打exit可以離開等)
// 2. 讓他在打 delay {seconds} {command} 時呼叫 scheduler 的 addDelayedTask
// 3. 讓他在打 list 的時候呼叫 scheduler 的 printAllTaskStatus
// 4. 看你想如何優化這個界面 XD (或許是他直接用選的,而不是像現在要做什麼用指令) 優化完把界面使用方法打在 Readme

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

		if( strcmp(task->args[0], "exit") == 0 ){
			exit(0);
		}else{
			scheduler->addTask(task);
		}
	}
	return 0;
}
