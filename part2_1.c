#include <stdio.h>
#include <stdlib.h>

int main(){

	char * ptr;
	for(int i=1;i<4;i++){
		ptr=malloc(1*i);
		printf("Allocated pointer\t%p\n",ptr);
		char * track=ptr-0x10;
		while(track!=ptr){
			printf("\t%p \t %02x\t",track,*track);
			track=track+1;
		}
		printf("\t%p \t %02x\n",track,*track);
	}
	free(ptr);
	getchar();
	//malloc again
	printf("Lets malloc again agin***");
	int *ptr1=NULL;
	ptr1=(int *)malloc(1*sizeof(int));
        printf("allocated pointer\t%p\n",ptr1);
	getchar();
}
