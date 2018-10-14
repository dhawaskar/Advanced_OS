#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bufSize 1024
int main(){

	FILE *fp=NULL;
	char buffer[bufSize];
	char family[]="cpu family	: 6";
	char family1[]="cpu family       : 4";
	char family2[]="cpu family       : 5";
	char family3[]="cpu family       : 15";
	printf("*************************************Printing the Processor type**************************************\n");
	fp=fopen("/proc/cpuinfo","r");
	if(fp==NULL){
		perror("/proc/cpuinfo:");
		exit(0);
	}else{
		while(fgets(buffer,bufSize,fp)!=NULL){
			buffer[strlen(buffer)-1]='\0';
			if(strcmp(buffer,family)==0) 
				printf("Its a processor which could be from pentium pro to Haswell expect for Netburst\n");
			if(strcmp(buffer,family1)==0)
				printf("Its a 80486 processor\n");
			if(strcmp(buffer,family2)==0)
				printf("Its a pentium processor\n");
			if(strcmp(buffer,family3)==0)
				printf("Its a netburst processor\n");	
			if(strncmp(buffer,"model name",strlen("model name"))==0)
				printf("The model name of the processor is\t%s\n",buffer);
			memset(buffer,0,bufSize);
		}
	}
	fclose(fp);
	printf("*************************************Printing the kernel version***********************************\n");
	fp=fopen("/proc/version","r");
	if(fp==NULL){
		perror("/proc/version:");
		exit(0);
	}else{
		while(fgets(buffer,bufSize,fp)!=NULL){
			buffer[31]='\0';
			printf("%s\n",buffer);
			memset(buffer,0,bufSize);	
		}
	}
	fclose(fp);
	printf("*************************************Printing the amount of memory configred into this computer***********************************\n");
	fp=fopen("/proc/meminfo","r");
	if(fp==NULL){
		perror("/proc/meminfo:");
		exit(0);
	}else{
		while(fgets(buffer,bufSize,fp)!=NULL){
			if(strncmp(buffer,"MemTotal:        ",strlen("MemTotal:        "))==0){
				printf("%s",buffer);
			}
			memset(buffer,0,bufSize);
		}
	}
	fclose(fp);
	printf("*************************************Printing the uptime of computer after it is booted***********************************\n");
	fp=fopen("/proc/uptime","r");
	if(fp==NULL){
		perror("/proc/uptime:");
		exit(0);
	}else{
		while(fgets(buffer,bufSize,fp)!=NULL){
                	printf("%s",buffer);
                        memset(buffer,0,bufSize);
                }
	}
	fclose(fp);
	return 0;
}
