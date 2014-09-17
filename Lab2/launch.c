#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[], char *envp[])
{
	pid_t childPid;
	int i;
	childPid=fork();

	if(childPid==0) {
		//in the child
		execve(argv[1], argv+1, envp);
		//argv+1 because we want to pass a pointer to argv starting at the 1nth position 
	} else {
		//in the parent
		int *status;
		fprintf(stderr,"Child pid: %d\n",childPid);
		waitpid(childPid,&status,0);//waits for forked child
		fprintf(stderr,"Child status: %d\n",status);
	}
	return 1;
}
