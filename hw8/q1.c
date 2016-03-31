/*
Created by Han Gao. This is for Operate System Course Homwork 4
Modify Feb 16
*/
#define MAX_ARGS 5
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>  
#include <unistd.h>


int main(int argc, char ** argv){
	if(!strcmp(argv[1],"rm")){
		int err=remove(argv[2]);
		if(err){
			perror("error");
			exit(0);
		}
	}else if(!strcmp(argv[1],"info")){
		struct stat *buf= malloc(sizeof(stat));
		int err=stat(argv[2], buf);
		if(err){
			perror("Error: No such file or directory");
			exit(0);
		}
		//printf("Info for file %s\n",argv[2]);
		printf("Inodes: %llu\n", buf->st_ino);
		printf("Size: %llu\n", buf->st_size);
		printf("Permission: ");
		if((buf->st_mode & S_IRUSR)==S_IRUSR)
			printf("r");
		else
			printf("-");
		if((buf->st_mode & S_IWUSR)==S_IWUSR)
			printf("w");
		else
			printf("-");
		if((buf->st_mode & S_IXUSR)==S_IXUSR)
			printf("x");
		else
			printf("-");
		if((buf->st_mode & S_IRGRP)==S_IRGRP)
			printf("r");
		else
			printf("-");
		if((buf->st_mode & S_IWGRP)==S_IWGRP)
			printf("w");
		else
			printf("-");
		if((buf->st_mode & S_IXGRP)==S_IXGRP)
			printf("x");
		else
			printf("-");
		if((buf->st_mode & S_IROTH)==S_IROTH)
			printf("r");
		else
			printf("-");
		if((buf->st_mode & S_IWOTH)==S_IWOTH)
			printf("w");
		else
			printf("-");
		if((buf->st_mode & S_IXOTH)==S_IXOTH)
			printf("x");
		else
			printf("-");
		printf("\n");
	}else if(!strcmp(argv[1],"link")){
		int err=link(argv[2],argv[3]);
		if(err){
			perror("error");
			exit(0);
		}
	}else if(!strcmp(argv[1],"symlink")){
		int err=symlink(argv[2],argv[3]);
		if(err){
			perror("error");
			exit(0);
		}
	}
}




