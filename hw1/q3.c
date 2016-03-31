#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
	int ret = fork();
	int num;
	if (ret < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (ret == 0){
		printf("Enter a number: ");
		scanf("%d", &num);
		//fgets(num,100,stdin);
		exit(num);
	}
	else{
		wait(&num);
		printf("%p\n", &num);
		if (WIFEXITED(num)){
			printf("Child exited with status %d\n", WEXITSTATUS(num));
		}
	}
	return 0;
}
