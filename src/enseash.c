#define SIZE 1024
#define MESSAGE "enseash % "
#define CHILDPID 0
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	
	char input[SIZE];
	int status;
	while(1){
		if(write(STDOUT_FILENO,MESSAGE,strlen(MESSAGE))==-1){perror("write");}
		int pid = fork();
		if(pid<0){perror("fork impossible");}
		if(pid == CHILDPID){
			if(read(STDIN_FILENO,input,SIZE)==-1){perror("read");}
		
	
			input[strcspn(input, "\n")] = '\0';
	
			if(execl(input,input,NULL)==-1){
				if(execlp(input,input,NULL)==-1){perror("wrong command");}
			}
			
		}
		if(pid > 0){wait(&status);}
	}
	
}
