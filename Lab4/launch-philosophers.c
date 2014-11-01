#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
void parentSignalHandler(int sigNum);
void childSignalHandler(int sigNum);
void eat(int seat);
void think(int seat);
void wait(sem_t semaphore);
void done(sem_t semaphore);
int loop = 1;
int main(int argc, char **argv)
{
	if(argc!=2) {
		//only take one arg
		printf("too many arguments\n");
		exit(1);
	}
	int seats = (int)(argv[1][0]-'0');

//create process group
	pid_t myPid = getpid();
	if(setpgid(myPid,myPid)!=0) {
		//process group creation failed
		printf("process group creation failed\n");
		exit(1);
	}

//set up semaphores
	sem_t *chopsticks = (sem_t *) malloc(seats * sizeof(sem_t));
	if(chopsticks==NULL) {
		//malloc failed
		printf("chopstick malloc failed\n");
		exit(1);
	}
	int i;
	for(i = 0; i<seats; i++) {
		sem_init(&chopsticks[i],1,1);
	}
	sem_t chopstickGate;
	sem_init(&chopstickGate,1,1);

//create philosophers
	int philosophers[seats];
	int mySeat = -1;
	i=0;
	for(i = 0; i<seats; i++) {
		pid_t forked = fork();
		if(forked == 0) {
			//in a child
			mySeat = i;
			break;
		} else {
			//in parent
			philosophers[i]=forked;
			//add children to process group
			setpgid(forked,myPid);
		}
	}

	if(mySeat<0) {
		//in the parent
		//register sigterm
		printf("%d\n",myPid);
		if(signal(SIGTERM,parentSignalHandler)==SIG_ERR) {
			//signal failed
			printf("parent signal handler setup failed\n");
			exit(1);
		}

		//wait for children
		int *status = (int *)malloc(seats*sizeof(int));
		i=0;
		for(i =0; i<seats; i++) {
			//save status of children on exit
			waitpid(philosophers[i],&status[i],0);
		}

		//destroy semaphores
		i=0;
		for(i = 0; i<seats; i++) {
			if(sem_destroy(&chopsticks[i])!=0) {
				//error destroying semaphores
				printf("sem_destroy on semaphore %d failed\n",i);
			}
		}
	} else {
		//in a child
		//register sigterm
		if(signal(SIGTERM,childSignalHandler)==SIG_ERR) {
			//signal failed
			printf("child signal handler setup failed\n");
			exit(1);
		}
		//loop for philosophers
		int cycles=0;
		while(loop==1) {
			//wait for chopstick gate
			wait(chopstickGate);
			//wait for chopsticks
			wait(chopsticks[mySeat]);
			wait(chopsticks[(mySeat+1)%seats]);
			eat(mySeat);
			//release chopsticks
			done(chopsticks[mySeat]);
			done(chopsticks[(mySeat+1)%seats]);
			//release chopstick gate
			done(chopstickGate);
			think(mySeat);
			cycles++;
		}
		printf("philosopher %d has completed %d cycles",mySeat,cycles);
	}
	return 0;
}

void parentSignalHandler(int sigNum)
{
	//caught sigterm
	//send sigterm to group
	if(kill(0,sigNum)<0) {
		//kill error
		printf("signal to group failed\n");
		exit(1);
	}
}

void childSignalHandler(int sigNum)
{
	//caught sigterm
	printf("sigterm");
	loop=0;
}

void eat(int seat)
{
	static int eatCycles=0;
	eatCycles++;
	printf("philosopher %d is eating...\n",seat);
	//sleep random length of time
	if(usleep(rand()%1000000)!=0) {
		//sleep failed
		printf("philosopher %d failed to sleep while eating\n",seat);
	}
}

void think(int seat)
{
	static int thinkCycles=0;
	thinkCycles++;
	printf("philosopher %d is thinking...\n",seat);
	//sleep random length of time
	if(usleep(rand()%1000000)!=0) {
		//sleep failed
		printf("philosopher %d failed to sleep while thinking\n",seat);
	}
}

void wait(sem_t semaphore)
{
	if(sem_wait(&semaphore)==-1) {
		printf("sem_wait failure");
		exit(1);
	}
}

void done(sem_t semaphore)
{
	if(sem_post(&semaphore)==-1) {
		printf("sem_post failure");
		exit(1);
	}
}
