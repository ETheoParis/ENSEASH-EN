#define SIZE 1024
#define MESSAGE "hello world\n"
#include <unistd.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char* argv[]){
	write(STDOUT_FILENO,MESSAGE,strlen(MESSAGE));
	
	char input[SIZE];
	read(STDIN_FILENO,input,SIZE);
	
	input[strcspn(input, "\n")] = '\0';
	
	if(execl(input,input,NULL)==-1){
		execlp(input,input,NULL);}

}
