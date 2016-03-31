/*
Created by Han Gao. This is for Operate System Course Homwork 4
Modify Feb 16
*/
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
	char *stdin_redirect;
	char *stdout_redirect;
	int background;
};


void ReadCommand(char *line, struct Command * command);
void PrintCommand(struct Command * command);
void ReadArgs(char *in, char **argv, int size);
void PrintArgs(char **argv);
void ReadRedirectsAndBackground(struct Command *command);

int main(){
	char line[200];
	// Read a string from the user
	printf("Enter a string: ");
	fgets(line, sizeof(line), stdin);
	// Extract arguments and print them
	struct Command *command= malloc(sizeof(struct Command));
	//printf("%lu\n",sizeof(struct Command));
	ReadCommand(line, command);
	ReadRedirectsAndBackground(command);
	PrintCommand(command);
}

void ReadRedirectsAndBackground(struct Command *command){
	int i;
	//Only consider the last sub command 
	for(i=MAX_ARGS-1;i>=0;i--){
		char *argv=command->sub_commands[command->num_sub_commands-1].argv[i];
		if(argv==NULL)
			continue;
		else if(!strcmp(argv,"&")){
			command->background=1;
			command->sub_commands[command->num_sub_commands-1].argv[i]=NULL;
		}else if(!strcmp(argv,">")){
			command->stdout_redirect=command->sub_commands[command->num_sub_commands-1].argv[i+1];
			command->sub_commands[command->num_sub_commands-1].argv[i+1]=NULL;
			command->sub_commands[command->num_sub_commands-1].argv[i]=NULL;
		}else if(!strcmp(argv,"<")){
			command->stdin_redirect=command->sub_commands[command->num_sub_commands-1].argv[i+1];
			command->sub_commands[command->num_sub_commands-1].argv[i+1]=NULL;
			command->sub_commands[command->num_sub_commands-1].argv[i]=NULL;
		}
	}
}

void ReadCommand(char *line, struct Command *command){
	line[strlen(line)-1]='\0';
	char *pch = strtok(line, "|");
	int id=0;
	while(pch!=NULL){
		command->sub_commands[id].line=malloc(sizeof(pch));
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
		printf("Command %d:\n", i);
		PrintArgs(command->sub_commands[i].argv);
		printf("\n");
		i++;
	}
	// print stdin stdout and &
	if(command->stdin_redirect!=NULL)
		printf("Redirect stdin: %s\n", command->stdin_redirect);
	if(command->stdout_redirect!=NULL)
		printf("Redirect stdout: %s\n", command->stdout_redirect);
	if(command->background==1)
		printf("Background: yes\n");
	else
		printf("Background: no\n");
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
	//Don't forget Set NULL to argv
	*argv=NULL;
}

void PrintArgs(char ** argv){
	int i=0;
	while(*argv){
		printf("argv[%d] = '%s'\n",i,*argv);
		argv++;
		i++;
	}
}
