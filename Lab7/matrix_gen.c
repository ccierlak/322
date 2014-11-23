#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	int j;
	int k;
	signed char* bits;
	signed char randNum;
	int n = atoi(argv[1]);
	//n*n is size of matrix
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			//signed char to hold int as 8 bits
			randNum = 100-rand()%200;
			//change to 8 bit representation, little endian
			if(randNum<0) {
				//for negative numbers set negative bit and make number postive for modular operation
				bits[0]=1;
				randNum*=-1;
			}
			for(k=7; k>0; k--) {
				if(randNum%2==1) {
					bits[k]=1;
				} else {

					bits[k]=0;
				}
				//shift randNum right
				randNum=randNum>>1;
			}
			for(k=0; k<8; k++) {
				printf("%d",bits[k]);
				//clear bit
				bits[k]=0;
			}
		}
	}
	//write null terminator
	printf("\0");
	return 0;
}
