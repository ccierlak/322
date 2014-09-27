#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
void signalHandler(int);
int sig_name2number(char *);
char * sig_number2name(int);
void increaseCount(int);
int main(int argc, char *argv[])
{
	int i;
	for(i=1; i<argc; i++) {
		if(signal(sig_name2number(argv[i]),signalHandler)==SIG_ERR) {
			//registers all commandline args with signalHandler, prints if error
			fprintf(stderr,"cannot catch %s\n",argv[i]);
		}
	}

	fprintf(stderr,"catcher: $$= %d\n",getpid());
	for(;;) {
		pause();
		//loop forever
	}
}

void signalHandler(int signalNum)
{
	static int termCount=0;
	if(signalNum == SIGTERM) {
		termCount++;
	} else {
		termCount=0;
	}
	if(signal(signalNum,signalHandler)== SIG_ERR) {
		fprintf(stderr,"cannot catch signal number %d\n",signalNum);
		//when signal errors
	} else {
		increaseCount(1);
		//increase signal count
		time_t caughtTime;
		time(&caughtTime);
		fprintf(stdout,"%s caught at %d\n",sig_number2name(signalNum),caughtTime);
	}
	if(termCount==3) {
		increaseCount(-1);
		//if 3 SIGTERMS are caught send end signal to increaseCount
	}
}

void increaseCount(int num)
{
	static int sigCount=0;
	if(num<0) {
		//negative num signals process to end
		fprintf(stderr,"catcher: total signals count = %d",sigCount);
		signal(SIGINT,SIG_DFL);
		raise(SIGINT);
	} else {
		//positive num increases signal count
		sigCount++;
	}
}
int sig_name2number(char *s)
{

	int signumber = -1;

	if (!strcmp(s, "HUP")) {
		signumber = SIGHUP;
	}

	if (!strcmp(s, "INT")) {
		signumber = SIGINT;
	}

	if (!strcmp(s, "QUIT")) {
		signumber = SIGQUIT;
	}

	if (!strcmp(s, "ILL")) {
		signumber = SIGILL;
	}

	if (!strcmp(s, "TRAP")) {
		signumber = SIGTRAP;
	}

	if (!strcmp(s, "ABRT")) {
		signumber = SIGABRT;
	}

	if (!strcmp(s, "IOT")) {
		//signumber = SIGIOT;
	}

	if (!strcmp(s, "BUS")) {
		signumber = SIGBUS;
	}

	if (!strcmp(s, "FPE")) {
		signumber = SIGFPE;
	}

	if (!strcmp(s, "KILL")) {
		signumber = SIGKILL;
	}

	if (!strcmp(s, "USR1")) {
		signumber = SIGUSR1 ;
	}

	if (!strcmp(s, "SEGV")) {
		signumber = SIGSEGV ;
	}

	if (!strcmp(s, "USR2")) {
		signumber = SIGUSR2 ;
	}

	if (!strcmp(s, "PIPE")) {
		signumber = SIGPIPE ;
	}

	if (!strcmp(s, "ALRM")) {
		signumber = SIGALRM ;
	}

	if (!strcmp(s, "TERM")) {
		signumber = SIGTERM ;
	}

	if (!strcmp(s, "STKFLT")) {
		//signumber = SIGSTKFLT ;
	}

	if (!strcmp(s, "CHLD")) {
		signumber = SIGCHLD ;
	}

	if (!strcmp(s, "CONT")) {
		signumber = SIGCONT ;
	}

	if (!strcmp(s, "STOP")) {
		signumber = SIGSTOP ;
	}

	if (!strcmp(s, "TSTP")) {
		signumber = SIGTSTP ;
	}

	if (!strcmp(s, "TTIN")) {
		signumber = SIGTTIN ;
	}

	if (!strcmp(s, "TTOU")) {
		signumber = SIGTTOU ;
	}

	if (!strcmp(s, "URG")) {
		signumber = SIGURG ;
	}

	if (!strcmp(s, "XCPU")) {
		signumber = SIGXCPU ;
	}

	if (!strcmp(s, "XFSZ")) {
		signumber = SIGXFSZ ;
	}

	if (!strcmp(s, "VTALRM")) {
		signumber = SIGVTALRM ;
	}

	if (!strcmp(s, "PROF")) {
		signumber = SIGPROF ;
	}

	if (!strcmp(s, "WINCH")) {
		signumber = SIGWINCH ;
	}

	return signumber;

}
char * sig_number2name(int sigNum)
{
	char *sigName="";
	if (sigNum == SIGHUP) {
		sigName = "SIGHUP";
	}

	if (sigNum==SIGINT) {
		sigName="SIGINT";
	}

	if (sigNum==SIGQUIT) {
		sigName = "SIGQUIT";
	}

	if (sigNum==SIGILL) {
		sigName = "SIGILL";
	}

	if (sigNum==SIGTRAP) {
		sigName = "SIGTRAP";
	}

	if (sigNum==SIGABRT) {
		sigName = "SIGABRT";
	}

	/*if (sigNum==SIGIOT) {
		sigName = "SIGIOT";
	}*/

	if (sigNum==SIGBUS) {
		sigName = "SIGBUS";
	}

	if (sigNum==SIGFPE) {
		sigName = "SIGFPE";
	}

	if (sigNum==SIGKILL) {
		sigName = "SIGKILL";
	}

	if (sigNum==SIGUSR1) {
		sigName = "SIGUSR1" ;
	}

	if (sigNum==SIGSEGV) {
		sigName = "SIGSEGV" ;
	}

	if (sigNum==SIGUSR2) {
		sigName = "SIGUSR2" ;
	}

	if (sigNum==SIGPIPE) {
		sigName = "SIGPIPE" ;
	}

	if (sigNum==SIGALRM) {
		sigName = "SIGALRM" ;
	}

	if (sigNum==SIGTERM) {
		sigName = "SIGTERM" ;
	}

	/*if (sigNum==SIGSTKFLT) {
		sigName = "SIGSTKFLT" ;
	}*/

	if (sigNum==SIGCHLD) {
		sigName = "SIGCHLD" ;
	}

	if (sigNum==SIGCONT) {
		sigName = "SIGCONT" ;
	}

	if (sigNum==SIGSTOP) {
		sigName = "SIGSTOP" ;
	}

	if (sigNum==SIGTSTP) {
		sigName = "SIGTSTP" ;
	}

	if (sigNum==SIGTTIN) {
		sigName = "SIGTTIN" ;
	}

	if (sigNum==SIGTTOU) {
		sigName = "SIGTTOU" ;
	}

	if (sigNum==SIGURG) {
		sigName = "SIGURG" ;
	}

	if (sigNum==SIGXCPU) {
		sigName = "SIGXCPU";
	}

	if (sigNum==SIGXFSZ) {
		sigName = "SIGXFSZ" ;
	}

	if (sigNum==SIGVTALRM) {
		sigName = "SIGVTALRM" ;
	}

	if (sigNum==SIGPROF) {
		sigName = "SIGPROF" ;
	}

	if (sigNum==SIGWINCH) {
		sigName = "SIGWINCH" ;
	}
}
