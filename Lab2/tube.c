#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[], char *envp[])
{
	int fd[2];//0 for read, 1 for write
	int pipeSuccess=pipe(fd);
	if(pipeSuccess==-1) {
		printf("pipe error");
		return -1;
	} else {
		pid_t child1Pid,child2Pid;
		int i, commaPos=0;
		char *argvChild1[argc];
		char *argvChild2[argc];
		for(i=1; i<argc; i++) {
			if((int)argv[i][0]==44) {
				commaPos=i;
				//find location of comma (44) separating commands
			} else if(commaPos==0) {
				argvChild1[i-1]=argv[i];
				//fill argvChild1 with command 1 args from argv
			} else {
				argvChild2[i-commaPos-1]=argv[i];
				//fill argvChild2 with command 2 args from argv
			}
		}
		argvChild1[commaPos-1]=NULL;
		argvChild2[argc-commaPos-1]=NULL;
		//null terminator to end arguments
		child1Pid=fork();
		if(child1Pid==0) {
			//in child 1
			close(fd[0]);
			dup2(fd[1],1);
			//rewire stdout to pipe
			execve(argvChild1[0], argvChild1, envp);
			printf("Error executing command: %s\n",argvChild1[0]);
			return -1;

		}
		child2Pid=fork();
		if(child2Pid==0) {
			//in child 2
			close(fd[1]);
			dup2(fd[0],0);
			//rewire stdin to pipe
			execve(argvChild2[0],argvChild2,envp);
			printf("Error executing command: %s\n",argvChild2[0]);
			return -1;
		}
		//in the parent
		close(fd[0]);
		close(fd[1]);
		//close pipe
		int *status1,status2;
		fprintf(stderr,"%s $$: %d\n",argvChild1[0],child1Pid);
		fprintf(stderr,"%s $$: %d\n",argvChild2[0],child2Pid);
		waitpid(child1Pid,&status1,0);//waits for forked child 1
		waitpid(child2Pid,&status2,0);//waits for forked child 1
		fprintf(stderr,"%s $?: %d\n",argvChild1[0],status1);
		fprintf(stderr,"%s $?: %d\n",argvChild2[0],status2);
		return 1;
	}
}
