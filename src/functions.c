#include "functions.h"
void receive_command(void){
		char input[SIZE];
		
		//read the command
		if(read(STDIN_FILENO,input,SIZE)==-1)	{perror("read");}
		input[strcspn(input, "\n")] = '\0';
		
		//verify if need to exit
		if(strcmp(input,"exit")==0){
		if(write(STDOUT_FILENO,"bye bye \n",10)==-1)	{perror("bye bye error");}
		exit(EXIT_SUCCESS);
	}
}
