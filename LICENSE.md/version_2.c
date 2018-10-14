#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define bufSize 1024
int main(int argc,char **argv){
	if(argc!=3){
		printf("Usage: %s <read_rate> <rate>",argv[0]);
		exit(0);
	}
	//while(1){
		int read_rate=atoi(argv[1]);
		int print_rate=atoi(argv[2]);
		int avg=(print_rate/read_rate)+1;
		FILE *fp=NULL,*fp1=NULL,*fp2=NULL;
		char buffer[bufSize];
		float *user=malloc(avg*sizeof(float));
		float *kernel=malloc(avg*sizeof(float));
		float *idle=malloc(avg*sizeof(float));
		float *mem_total=malloc(avg*sizeof(float));
		float *mem_available=malloc(avg*sizeof(float));
		float *ctx=malloc(avg*sizeof(float));
		float *prs=malloc(avg*sizeof(float));
		float *read_total=malloc(avg*sizeof(float));
		float *write_total=malloc(avg*sizeof(float));
		int count=0;
		char *token=NULL;
		char *filter=" ";
		int filter_count;
		//printf("Lets take %d number of sample reading to display\n",avg);
		while(avg--){
			fp=fopen("/proc/stat","r");
			fp1=fopen("/proc/meminfo","r");
			fp2=fopen("/proc/diskstats","r");
			if(fp==NULL||fp1==NULL||fp2==NULL){
				perror("/proc/:");
				exit(0);
			}else{
				while(fgets(buffer,bufSize,fp)!=NULL){
					buffer[strlen(buffer)-1]='\0';
					if(strncmp(buffer,"cpu  ",strlen("cpu  "))==0){
						printf("Red line :\t%s\n",buffer);
						token=strtok(buffer,filter);						
						filter_count=0;	
						while(token!=NULL){         
				                	//printf("Token is \t%s\n",token);
                					if(filter_count==1){        
                        					user[count]=atoi(token);
                        					printf("Total user mode %f\n",user[count]);
                					}
                					if(filter_count==3){                     
                        					kernel[count]=atoi(token);     
                        					printf("Total kernel mode %f\n",kernel[count]);
                					}           
                					if(filter_count==4){
                        					idle[count]=atoi(token);
                        					printf("Total idle mode %f\n",idle[count]);
                					}                    
							token=strtok(NULL,filter);
                					filter_count++;                
        					}	
					}
					token=NULL;
					if(strncmp(buffer,"ctxt ",strlen("ctxt "))==0){
						printf("\n%s\n",buffer);
						token=strtok(buffer," ");
						token=strtok(NULL," ");
						ctx[count]=atoi(token);
						printf("\nTotal context switch\t%f\n",ctx[count]);
					}
					if(strncmp(buffer,"processes ",strlen("processes "))==0){
						printf("\n%s\n",buffer);
                                                token=strtok(buffer," ");
                                                token=strtok(NULL," ");
                                                prs[count]=atoi(token);
                                                printf("\nTotal number of processes\t%f\n",prs[count]);
					}
					memset(buffer,0,bufSize);
				}
				fclose(fp);
				int mem_line=0;
				token=NULL;
				while(fgets(buffer,bufSize,fp1)!=NULL){
					buffer[strlen(buffer)-1]='\0';
					//printf("\nBuffer:%s\n",buffer);
					if(strncmp(buffer,"MemTotal:",strlen("MemTotal:"))==0){
						token=strtok(buffer,"        ");
						//printf("\nFirst toekn:%s\n",token);
						token=strtok(NULL,filter);	
						//printf("\nsecond tokn:%s\n",token);
						mem_total[count]=(float)atoi(token);
						printf("\ntotal memory \t%f\n",mem_total[count]);
					}
					if(strncmp(buffer,"MemAvailable:",strlen("MemAvailable:"))==0){
						token=strtok(buffer,"        ");
						//printf("\nFirst toekn:%s\n",token);
                                                token=strtok(NULL,filter);
						//printf("\nsecond toekn:%s\n",token);
                                                mem_available[count]=(float)atoi(token);
						printf("\ntotal available memory \t%f\n",mem_available[count]);
					}
					if(mem_line>4) break;
					mem_line++;
				}
				fclose(fp1);

				//disk stats from /proc/diskstats
				token=NULL;
				memset(buffer,0,bufSize);
                                while(fgets(buffer,bufSize,fp2)!=NULL){
                                        buffer[strlen(buffer)-1]='\0';
					//printf("Disk file red line\t%s\n",buffer);
                                        if(strncmp(buffer,"   8       0 sda ",strlen("   8       0 sda "))==0){
						printf("Disk read line for sda macthed\n");
                                                token=strtok(buffer,"       ");
                                                printf("\ntoken:%s\n",token);
                                                token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
                                                read_total[count]=(float)atoi(token);
                                                printf("\ntotal Read \t%f\n",read_total[count]);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						token=strtok(NULL," ");
                                                printf("\ntoken:%s\n",token);
						write_total[count]=(float)atoi(token);
                                                printf("\ntotal Read \t%f\n",write_total[count]);
                                        }
					
                                }
                                fclose(fp2);

				sleep(2);
			}
			count++;
		}
		float sum=0;
		printf("Total samples red\t%d\n",count);
		for(int i=0;i<count-1;i++){
			sum+=user[i+1]-user[i];
		}
		float user_avg=sum/(count-1);
		printf("\n");
		sum=0;
		for(int i=0;i<count-1;i++){
			sum+=kernel[i+1]-kernel[i];

		}
		float kernel_avg=sum/(count-1);
		printf("\n");
		sum=0;
		for(int i=0;i<count-1;i++){
			sum+=idle[i+1]-idle[i];
		}
		printf("\n");
		float idle_avg=sum/(count-1);
		float total_time=user_avg+kernel_avg+idle_avg;
		printf("\n\n***************Processor stats*******************\n\n");
		printf("Total user avg\t%fkernel avg\t%fidle avg\t%f",user_avg,kernel_avg,idle_avg);
		user_avg=(user_avg*100)/total_time;
		kernel_avg=(kernel_avg*100)/total_time;
		idle_avg=(idle_avg*100)/total_time;
		printf("\nStats of user \t%f,kernel\t%f and idle \t%ffor %s seconds\n",user_avg,kernel_avg,idle_avg,argv[2]);	
		printf("\n\n***************Memory stats*********************\n\n");
		sum=0;
		for(int i=0;i<count;i++){
			sum+=(mem_available[i]/mem_total[i])*100;
		}
		float mem_avg=sum/(count-1);
		float mem_non_avg=100-mem_avg;
		printf("\nTotal available memory percentage\t%f\t Total unavailabe meory percentage\t%f\n",mem_avg,mem_non_avg);

		printf("\n*****************Context Switch rate***************\n\n");
		sum=0;
		for(int i=0;i<count-1;i++){
			sum+=ctx[i+1]-ctx[i];	
			printf("%f\t%f\t",ctx[i],ctx[i+1]);
		}
		printf("Total context switcg\t%f\n",sum);
		float ctx_avg=sum/(count-1);
		printf("Average context switch\t%f\n",ctx_avg);
		ctx_avg/=print_rate;
		printf("Rate of context switcg\t%f\n",ctx_avg);
		printf("\n*****************process creation rate***************\n\n");
                sum=0;
                for(int i=0;i<count-1;i++){
                        sum+=prs[i+1]-prs[i];
			printf("%f\t",prs[i]);
                }
		printf("\n");
		printf("Sum is \t%f\n",sum);
                float prs_avg=sum/(count-1);
		printf("Average \t%f\n",prs_avg);
                prs_avg/=print_rate;
                printf("Rate of Process creation\t%f\n",prs_avg);

		printf("\n*****************Disk stats***************\n\n");
		sum=0;
		for(int i=0;i<count-1;i++){
			sum+=read_total[i+1]-read_total[i];
		}
		printf("\nTotal read of disks\t%f\n",sum);
		float read_avg=sum/(count-1);
		read_avg/=print_rate;
		printf("Read disk rate is \t%f\n",read_avg);
		sum=0;
                for(int i=0;i<count-1;i++){
                        sum+=write_total[i+1]-write_total[i];
                }
                printf("\nTotal read of disks\t%f\n",sum);
                float write_avg=sum/(count-1);
                write_avg/=print_rate;
                printf("Read disk rate is \t%f\n",write_avg);
		printf("Done reading for %s second\n",argv[2]);
		free(user);
		free(kernel);
		free(idle);
		free(mem_total);
		free(mem_available);
		free(ctx);
		free(prs);
		free(read_total);
		free(write_total);
	//}
	return 0;
}
