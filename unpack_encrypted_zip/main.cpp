#define PASSWORD_LENGTH 8
#define PASSWORD_FILE_NAME "dictionary.txt"
#define NUMBER_OF_PROCESS 50
#define TARGET_FILE_NAME "group7.zip"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

void update_digits(char *target, int digit, int max_digit, std::ofstream &file){
	for(int i = 0; i <= 9; i++){
		target[digit] = i + '0';
		if(digit < max_digit - 1)
			update_digits(target, digit + 1, max_digit, file);
		else
			file << target << '\n';
	}
}

void generate_password_file(void){
  std::ofstream file;
  file.open(PASSWORD_FILE_NAME);
	for(int digits = 1; digits <= PASSWORD_LENGTH; digits++){
		char *password = (char *) malloc(sizeof(char)*digits);
		update_digits(password, 0, digits, file);
		free(password);
	}
  file.close();
}

void *unencrypt_file(void *arguments){
  int number = *(int *)arguments;
	char filename[5];
	char command[100];
	std::string password;
	std::string correct_password;

	sprintf (filename, "x%02d", number);
	std::ifstream file(filename);

  while ( std::getline (file, password) )
  {
		// sprintf (command, "unzip -q -P %s %s", password.c_str(), TARGET_FILE_NAME);
		sprintf (command, "7z e %s -y -p%s", TARGET_FILE_NAME, password.c_str());
		if(system(command)==0){
			printf("Found Password: %s\n", password.c_str());
			correct_password = password;
			break;
		}
  }
  file.close();
	remove(filename);
	printf("Correct Password: %s\n", correct_password.c_str());
}

int main () {
  std::ifstream file(PASSWORD_FILE_NAME);
	char command[100];

	// Generate Dictionary if it doesn't exist
	sprintf (command, "[ -f %s ]", PASSWORD_FILE_NAME);
  if(system (command) != 0)
		generate_password_file();

	// Split file into chunks
	sprintf (command, "split -d -n l/%d %s", NUMBER_OF_PROCESS, PASSWORD_FILE_NAME);
	system(command);

	// Brute Force Password in Threads
  pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * NUMBER_OF_PROCESS);
  int *thread_id = (int *)malloc(sizeof(int) * NUMBER_OF_PROCESS);
	for(int i = 0; i < NUMBER_OF_PROCESS; i++){
		thread_id[i] = i;
		pthread_create(&threads[i], NULL, unencrypt_file, &thread_id[i]);
	}
	for(int i = 0; i < NUMBER_OF_PROCESS; i++){
		pthread_join(threads[i], NULL);
	}
	free(thread_id);
	free(threads);
  return 0;
}
