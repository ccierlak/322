#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	int j;
	int n = atoi(argv[1]);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
				printf("%d\t",100-rand()%200);
		}
		printf("\n");
	}
	return 0;
}
