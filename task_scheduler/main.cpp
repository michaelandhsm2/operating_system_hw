#define QUEUE_SIZE 10

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <string.h>
#include "src/task.h"
#include "src/scheduler.h"

// 1. 這邊在開始loop前加些說明文字解釋如何使用 (ie.打exit可以離開等)
// 2. 讓他在打 delay {seconds} {command} 時呼叫 scheduler 的 addDelayedTask
// 3. 讓他在打 list 的時候呼叫 scheduler 的 printAllTaskStatus
// 4. 看你想如何優化這個界面 XD (或許是他直接用選的,而不是像現在要做什麼用指令) 優化完把界面使用方法打在 Readme

int main(void)
{
	Scheduler *scheduler = new Scheduler();
	printf("\n┎‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐┑");
	printf("\n   使用說明：" );
	printf("\n   * 直接輸入欲執行的指令" );
	printf("\n   特定指令說明：" );
	printf("\n   * list：列出每個task的狀態" );
	printf("\n   * delay：指令在指定時間後進行" );
	printf("\n   * exit：離開" );
	printf("\n┕‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐┙");
	printf("\n\n開始輸入指令>\n ");
	char *line;
	char *args[80];
	std::string s;
	std::string strDelay="delay";
	int seconds;

	while(1){
		fflush(stdout);
		// scanf("%[^\n]%*c", line);
		getline(std::cin, s);
		line = (char*)s.c_str();
		if(strcmp(line, "") != 0){
			Task *task = new Task(line);

			if( strcmp(task->args[0], "exit") == 0 ){
				exit(0);
			}
			else if( strcmp(task->args[0], "delay") == 0 ){
				printf("請輸入要執行delay的指令>\n" );
				fflush(stdout);
				getline(std::cin, s);
				line = (char*)s.c_str();
				printf("請輸入要執行delay的秒數>\n" );
				scanf("%d", &seconds);
				task = new Task(line);
				scheduler->addDelayedTask(task, seconds);
			}
			else if( strcmp(task->args[0], "list") == 0 ){
				scheduler->printAllTaskStatus();
			}
			else{
				scheduler->addTask(task);
			}
		}
	}
	return 0;
}
