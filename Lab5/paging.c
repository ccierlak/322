#include <stdio.h>

int main(int argc, char **argv)
{
unsigned long int page;
if(argc != 2){
	printf("too many agruments\n");
	exit(1);
}
page=atoi(argv[1]);
printf("the address %d contains:\npage number = %d\noffset = %d",
	page,page/4096,page%4096);
	return 0;
}
