#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void print_args(int argc, char **argv);
int get_args(char *in, char **argv, int max_args);

int main(){
	char s[200];
	char *argv[10];
	int argc;
	// Read a string from the user
	printf("Enter a string: ");
	fgets(s, sizeof s, stdin);
	// Extract arguments and print them
	argc = get_args(s, argv, 10);
	print_args(argc, argv);
}

void print_args(int argc, char ** argv){
	for(int i=0;i<argc;i++){
		printf("argv[%d] = '%s'\n",i,*argv);
		argv++;
	}
}

int get_args(char *in, char **argv, int max_args){
	char *dup =strdup(in);
	int i=0;
	dup[strlen(dup)-1]='\0';
	char *pch = strtok(dup, " ");
	while(pch!=NULL&& i<max_args){
		*argv=pch;
		argv++;		
		pch=strtok(NULL," ");
		i++;
	}
	return i;
}



