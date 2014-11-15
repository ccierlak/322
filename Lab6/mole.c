#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
FILE *log = fopen("lab6.txt","a");
fprintf(log,"pop %s\n", argv[0]);
fclose(log);
for(;;){
	//wait to get hit
	pause();
}
}
