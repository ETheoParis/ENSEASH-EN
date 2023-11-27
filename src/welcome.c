#define BUFFSIZE 11
       #include <stdint.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/stat.h>
       #include <sys/sysmacros.h>
       #include <time.h>
       #include <unistd.h>
       #include <fcntl.h>



int main(int argc, char *argv[]){
	write(STDOUT_FILENO,"hello world",BUFFSIZE);
	


}
