#define MESSAGE "hello world\n"
#include <unistd.h>
#include <string.h>




int main(int argc, char *argv[]){
	write(STDOUT_FILENO,MESSAGE,strlen(MESSAGE));
}
