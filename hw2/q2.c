#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
	// Create pipe
	int fds[2];
	int err = pipe(fds);
	if (err == -1){
		perror("pipe");
		return 1;
	}
	// Spawn child
	int ret = fork();
	if (ret < 0){
		printf("fork error");
		return 1;
	} else if (ret == 0){	
		close(fds[1]);
		// Duplicate read end of pipe in standard input
		close(0);
		dup(fds[0]);
		// Child 1 launches command "wc"
		char *argv[2];
		argv[0] = "wc";
		argv[1] = NULL;
		execvp(argv[0], argv);
	} else {
		// Spawn child
		int ret2= fork();
		if (ret2 < 0){
			printf("fork error");
			return 1;
		}else if (ret2 == 0){	
			// Close read end of pipe
			close(fds[0]);
			close(1);
			dup(fds[1]);
			// Child 2 launches command "ls -l"
			char *argv[3];
			argv[0] = "ls";
			argv[1] = "-l";
			argv[2] = NULL;
			execvp(argv[0], argv);
		} else if (ret2 >0) {
			close(fds[0]);
			close(fds[1]);
			wait(NULL);
			wait(NULL);
			printf("Process %d finished\n", ret);
			printf("Process %d finished\n", ret2);
		}	
	} 
	return 0;
}		