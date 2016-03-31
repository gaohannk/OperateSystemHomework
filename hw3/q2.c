#define MAX_SUB_COMMANDS 5
#define MAX_ARGS 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct SubCommand
{
	char *line;
	char *argv[MAX_ARGS];
};
struct Command
{
	struct SubCommand sub_commands[MAX_SUB_COMMANDS];
	int num_sub_commands;
};


void ReadCommand(char *line, struct Command * command);
void PrintCommand(struct Command * command);
void ReadArgs(char *in, char **argv, int size);
void PrintArgs(char **argv);

int main(){
	char line[200];
	// Read a string from the user
	printf("Enter a string: ");
	fgets(line, sizeof(line), stdin);
	// Extract arguments and print them
	struct Command *command= malloc(sizeof(struct Command));
	//printf("%lu\n",sizeof(struct Command));
	ReadCommand(line, command);
	PrintCommand(command);
}

void ReadCommand(char *line, struct Command *command){
	line[strlen(line)-1]='\0';
	char *pch = strtok(line, "|");
	int id=0;
	while(pch!=NULL){
		//command->sub_commands[id].line=malloc(sizeof(pch));
		command->sub_commands[id].line=strdup(pch);
		command->num_sub_commands++;
		pch=strtok(NULL,"|");
		id++;
	}
	id=0;
	while(id<command->num_sub_commands){
		ReadArgs(command->sub_commands[id].line,command->sub_commands[id].argv,MAX_ARGS);
		id++;
	} 
}
void PrintCommand(struct Command * command){
	int i=0;
	while(i<command->num_sub_commands){
		PrintArgs(command->sub_commands[i].argv);
		i++;
	}
}

void ReadArgs(char *in, char **argv, int size){
	char *dup =strdup(in);
	dup[strlen(dup)]='\0';
	char *pch = strtok(dup, " ");
	while(pch!=NULL){
		*argv=pch;
		argv++;	
		pch=strtok(NULL," ");
	}
}

void PrintArgs(char ** argv){
	int i=0;
	while(*argv){
		printf("argv[%d] = '%s'\n",i,*argv);
		argv++;
		i++;
	}
}
