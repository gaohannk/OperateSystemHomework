#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main(){
	int fdsptoc[2];
	int fdsctop[2];
	
	pipe(fdsctop);
	pipe(fdsptoc);

	int pid = fork();
	int i;
	char buffer[10];
	if (pid == 0){
		// Child
		for (i = 0; i < 5; i++){
			close(fdsptoc[1]);
			read(fdsptoc[0],buffer,1);
			printf("%d. Child\n", i + 1);
			fflush(stdout);	
			close(fdsctop[0]);
			write(fdsctop[1],"1",1);
		}
	}
	else{
		// Parent
		for (i = 0; i < 5; i++){
			printf("%d. Parent\n", i + 1);
			fflush(stdout);
			close(fdsptoc[0]);
			write(fdsptoc[1],"1",1);
			close(fdsctop[1]);
			read(fdsctop[0],buffer,1);
		}
		wait(NULL);
	}
}