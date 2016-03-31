#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv){
	while(1){
		printf("$ ");
		char * str=(char *)malloc(256*sizeof(char));
		fgets(str,100,stdin);
		int length =strlen(str);
		str[length-1]='\0';
		printf("%s\n",str);
	}
}
