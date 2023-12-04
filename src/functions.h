#define SIZE 1024
#define MESSAGE "enseash % "
#define CHILDPID 0
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

void receive_command(void);
