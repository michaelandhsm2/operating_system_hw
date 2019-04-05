#define QUEUE_SIZE 10

#include <iostream>
#include <cstring>
#include "src/processor.h"
#include "src/task.h"

int main(void)
{
	// printf("\n┎‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐┑");
	// printf("\n   使用說明：" );
	// printf("\n   * 直接輸入欲執行的指令" );
	// printf("\n   特定指令說明：" );
	// printf("\n   * list：列出每個task的狀態" );
	// printf("\n   * delay：指令在指定時間後進行" );
	// printf("\n   * exit：離開" );
	// printf("\n┕‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐┙");

	int window_size;
	printf("請輸入Sliding Window的Window Size: ");
	scanf("%d", &window_size);


	Processor *processor = new Processor(window_size);

	// printf("\n\n開始輸入指令\n ");

	// Flush Input
	char ch;
  while ((ch = getchar()) != '\n' && ch != EOF);

	std::string s;
	char *line;
	while(1){
		printf("> ");
		fflush(stdout);
		getline(std::cin, s);
		line = (char*)s.c_str();
		if(strcmp(line, "") != 0){
			if( strcmp(line, "exit") == 0 ){
				exit(0);
			}
			else if( strcmp(line, "list") == 0 ){
				processor->printAllTaskStatus();
			}
			else{
				processor->newInput(line);
			}
		}
	}
	return 0;
}
