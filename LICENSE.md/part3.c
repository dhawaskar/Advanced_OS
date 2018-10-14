#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(){
	char *str;
	str=strdup("This is my initial string");
	while(str){
		printf("%s\t%p\n",str,str);
		sleep(5);
	}
	return 0;
}
