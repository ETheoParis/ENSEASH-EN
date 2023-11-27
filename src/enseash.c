#define SIZE 1024
#define MESSAGE "enseash % "
#define CHILDPID 0
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
	
	char input[SIZE];
	int status;
	int pidoriginal = getpid();
	int pid=pidoriginal;

	while(1){
		if(write(STDOUT_FILENO,MESSAGE,strlen(MESSAGE))==-1)	{perror("write enseash");}
		if(pid<0)	{perror("fork impossible");}
		if(pid > 0){
			if(read(STDIN_FILENO,input,SIZE)==-1){perror("read");}
			input[strcspn(input, "\n")] = '\0';
		
			if(strcmp(input,"exit")==0){
				if(write(STDOUT_FILENO,"bye bye \n",10)==-1)	{perror("bye bye error");}
			exit(EXIT_SUCCESS);
			
			}
			if(getpid() == pidoriginal){pid = fork();}
			if(pid == CHILDPID){
				if(execl(input,input,NULL)==-1){
					if(execlp(input,input,NULL)==-1)	{perror("wrong command");}
				}
				exit(EXIT_SUCCESS);
			}
			wait(&status);
	}
	
	}
}
