#define SIZE 1024
#define MESSAGE "enseash % "
#define MAXSIZEARG 1024
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>


void complexCom(char*input, char**buffer){
	char* sep =" ";
	char* tok = strtok(input,sep);
	int i = 0;
	while (tok != NULL){
		buffer[i] = tok;
		tok = strtok(NULL,sep);
		i++;
	}
	buffer[i] = NULL;
}

void redirectManager(char* input, char**buffer){
	int oldfd=-1;
	complexCom(input,buffer);
	
	for(int i=0; buffer[i]!=NULL;++i){
		if(strcmp(buffer[i],"<")==0){
			oldfd=open(buffer[i+1],O_RDONLY);
			if (oldfd==-1){
				perror("Failed to open");
				exit(EXIT_FAILURE);
			}
			close(oldfd);
			dup2(oldfd, STDIN_FILENO);
			buffer[i]=NULL;
			break;
		}
		else if(strcmp(buffer[i],">")==0){
			oldfd=open(buffer[i+1],O_WRONLY | O_CREAT | O_TRUNC,00700);
			if (oldfd==-1){
				perror("Failed to open");
				exit(EXIT_FAILURE);
			}
			dup2(oldfd,STDOUT_FILENO);
			close(oldfd);
			buffer[i]=NULL;
			break;
		}
	}
}

void executeCommand(char* input, int pidoriginal) {
    struct timespec start, end;
    int status;
    char* arguments[MAXSIZEARG];
    
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    redirectManager(input, arguments);
    
    int pid = fork();

    if (pid < 0) {
        perror("fork impossible");
        exit(EXIT_FAILURE);
    }
	
	//execute function only if child
    if (pid == 0) {
		
	//execv to execute functions functions defined in our file and execvp to execute builtin functions
        if (execv(arguments[0], arguments) == -1) {
            if (execvp(arguments[0], arguments) == -1) {
                perror("wrong command");
                exit(EXIT_FAILURE);
            }
        }
        exit(EXIT_SUCCESS);
    }
	//wait for functions to end before asking for an other command
    wait(&status);
    
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    long timeelapsed = (end.tv_nsec - start.tv_nsec) / 1000000;
    
    //prompt result of function
	char prompt[100];
    if (WIFEXITED(status)) {
        snprintf(prompt, 100, "enseash [exit:%d]|[%ldms] %%", WEXITSTATUS(status), timeelapsed);
    } else if (WIFSIGNALED(status)) {
        snprintf(prompt, 100, "enseash [sign:%d]|[%ldms] %%", WTERMSIG(status), timeelapsed);
    }
    write(STDOUT_FILENO, prompt, strlen(prompt));
}

int main(int argc, char* argv[]) {
    char input[SIZE];
    int pidoriginal = getpid();

    while (1) {
		//ask for command
        if (write(STDOUT_FILENO, MESSAGE, strlen(MESSAGE)) == -1) {
            perror("write enseash");
        }
		
		//read command
        if (read(STDIN_FILENO, input, SIZE) == -1) {
            perror("read");
        }

        input[strcspn(input, "\n")] = '\0';
		
		//verify if command is exit
        if (strcmp(input, "exit") == 0) {
            if (write(STDOUT_FILENO, "bye bye \n", 10) == -1) {
                perror("bye bye error");
            }
            exit(EXIT_SUCCESS);
        }
		
		
        executeCommand(input, pidoriginal);
    }
    return 0;
}
