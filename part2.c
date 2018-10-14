#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



void function_allocate(){
	printf("Look into memory after the function call\n");
	getchar();
	printf("Memory display before malloc");
        getchar();
        char * ptr=NULL;
        ptr=(char *)malloc (5*sizeof(char));
        if(ptr==NULL){
                printf("No memory allocation");
                exit(0);
        }
        printf("Inspect virtual memory after malloc and before free\n");
        getchar();
        free(ptr);
        printf("Inspect memory after free and before return\n");
        getchar();
	return;
}

int main(){

	printf("Welcome to virtual memeory inspection program\n");
	printf("Memory display before malloc");
	getchar();
	char * ptr=NULL;
	ptr=(char *)malloc (5*sizeof(char));
	if(ptr==NULL){
		printf("No memory allocation");
		exit(0);
	}
	printf("Inspect virtual memory after malloc and before free\n");
	getchar();
	free(ptr);
	printf("Inspect memory after free\n");
	getchar();
	function_allocate();
	printf("Inspect memory after returning from function\n");
	return 0;
}
