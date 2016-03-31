#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PrintArgs(char **argv);
void ReadArgs(char *in, char **argv, int size);

int main(){
	char s[200];
	char *argv[10];
	// Read a string from the user
	printf("Enter a string: ");
	fgets(s, sizeof s, stdin);
	// Extract arguments and print them
	ReadArgs(s, argv, 30);
	PrintArgs(argv);
}

void PrintArgs(char ** argv){
	int i=0;
	while(*argv){
		printf("argv[%d] = '%s'\n",i,*argv);
		argv++;
		i++;
	}
}

void ReadArgs(char *in, char **argv, int size){
	char *dup =strdup(in);
	dup[strlen(dup)-1]='\0';
	char *pch = strtok(dup, " ");
	while(pch!=NULL){
		*argv=pch;
		argv++;		
		pch=strtok(NULL," ");
	}
}


