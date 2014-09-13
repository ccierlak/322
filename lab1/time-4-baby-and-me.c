//Collin Cierlak
//time-4-baby-and-me
//comp322 lab 1
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/times.h>
void printProcessInfo(pid_t);
void printTimes();
struct tms timesStruct;//predefined in sys/times.h
int main(int argc, char **argv)
{
	time_t startTime,endTime;
	pid_t forkPid;
	startTime = time(NULL);
	printf("Start time: %d\n", startTime);
	forkPid = fork();//gets pid to determine if child or parent
	if(forkPid<0) {
		printf("fork error");
		return -1;
	} else if(forkPid ==0) {
		int i;
		for(i=0;i<99999999;i++){
		
		}
		printProcessInfo(forkPid);
	} else {
		printProcessInfo(forkPid);
		endTime=time(NULL);
		printf("End time: %d\n", endTime);
	}
	return 1;
}

void printProcessInfo(pid_t childPid)
{
	pid_t myPid,parentPid;
	int * status;
	myPid=getpid();
	parentPid=getppid();
	printf("pid: %d\tppid: %d\n",myPid,parentPid);
	if(childPid!=0) {
		//case for parent process
		waitpid(-1,&status,0);
		//waits for return of any child, returns child's pid, stores child's status in status
		printf("child pid: %d\tchild status: %d\n", childPid,status);
		times(&timesStruct);
		//fills timesStruct with times information
		printf("use time: %d\tsys time: %d\nc use time: %d\tc sys time: %d\n",
		       timesStruct.tms_utime,timesStruct.tms_stime,timesStruct.tms_cutime,timesStruct.tms_cstime);
	}
}
