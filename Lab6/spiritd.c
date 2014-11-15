#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

pid_t* moles;
void signalHandler(int);
void makeMole(int);
void killMole(int);
int main(int argc, char **argv)
{
	umask(0);
	pid_t pid = fork();
	if(pid < 0) {
		//in the
		printf("fork error");
		exit(1);
	}
	if(pid > 0) {
		//in the parent
		exit(0);
	}
	if(pid == 0) {
		//in the child (daemon)
		//create new session (and group)
		pid_t sid =  setsid();
		if(sid < 0) {
			printf("setsid error");
			exit(1);
		}
		//change working directory to '/'
		chdir("/");
		//reroute std files to /dev/null
		int fileno = open("/dev/null",O_WRONLY);
		dup2(fileno,0);
		dup2(fileno,1);
		dup2(fileno,2);
		close(fileno);
		//allocate for moles
		moles = malloc(2*sizeof(pid_t));
		moles[0]=-1;
		moles[1]=-1;
		//handle signals
		if(signal(SIGTERM,signalHandler)==SIG_ERR) {
			//signal sigterm error
			printf("cannot catch SIGTERM");
		}
		if(signal(SIGUSR1,signalHandler)==SIG_ERR) {
			//signal sigterm error
			printf("cannot catch SIGUSR1");
		}
		if(signal(SIGUSR2,signalHandler)==SIG_ERR) {
			//signal sigterm error
			printf("cannot catch SIGUSR2");
		}
		for(;;) {
			pause();
			//loop forever
		}
	}
}

void signalHandler( int signalno)
{
	if(signalno == SIGTERM) {
		//terminate moles, terminate daemon
		if(moles[0]!=-1) {
			kill(moles[0],SIGTERM);
		}
		if(moles[1]!=-1) {
			kill(moles[1],SIGTERM);
		}
		free(moles);
		raise(SIGTERM);
		exit(0);
	}
	if(signalno == SIGUSR1) {
		//kill mole1
		killMole(1);
		//choose random between 1 and 2
		int moleno=rand()%2;
		makeMole(moleno);
	}
	if(signalno == SIGUSR2) {
		//kill mole2
		killMole(2);
		//choose random between 1 and 2
		int moleno=rand()%2;
		makeMole(moleno);
	}
}

void makeMole(int moleno)
{
	if(moles[moleno-1]>0) {
//there's already a mole in that spot
	} else {
		pid_t moleMaker = fork();
		if(moleMaker<0) {
			printf("fork error");
			exit(1);
		}
		if(moleMaker==0) {
			//in child
			char *mole;
			if(moleno==1) {
				//argv[0] mole1
				mole = "mole1";
			} else {
				//argv[0] mole2
				mole = "mole2";
			}
			char * const args[]= {mole,NULL};
			execv("~/prog6/mole",args);
			//if this runs there was an error
			printf("execv error");
			exit(1);
		}
		if(moleMaker>0) {
			//in the parent
			//store mole pid in moles[]
			moles[moleno-1]=moleMaker;
		}
	}
}

void killMole(int moleno)
{
	pid_t moleToKill=moles[moleno-1];
	if(moleToKill == -1) {
//no such mole
	} else {
		//kill mole, set flag in moles to empty
		kill(moleToKill,SIGTERM);
		moles[moleno-1]=-1;
	}
}
