#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int* parse(char*, int);
int* toDecimal(int*);
char* toAscii(int*);
int* toParity(int*);
int printTable(int*,int*,int*);
char ascii[]= {'N','U','L','S','O','H','S','T','X','E','T','X','E','O','T','E','N','Q','A','C','K','B','E','L','B','S',' ','T','A','B','L','F',
               ' ','V','T',' ','F','F',' ','C','R',' ','S','O',' ','S','I',' ','D','L','E','D','C','1','D','C','2','D','C','3','D','C','4','N','A','K',
               'S','Y','N','E','T','B','C','A','N','E','M',' ','S','U','B','E','S','C','F','S',' ','G','S',' ','R','S',' ','U','S','S','P','C'
              };
int main(int argc, char* argv[])
{
	int len=0,index,myFile,readSuccess,bytes=1;
	char *input,*inputRead;
	if(argc==1) {
		//no filename, use stdin
		myFile=stdin;

	}
	for(index=1; index<argc; index++) {
		//while there are arguments remaining
		if(argv[index][0]=='-') {
			printf("stdin\n");
			myFile=stdin;
		} else {
			myFile=open(argv[index], O_RDONLY);
			if(myFile==0) {
				//myFile=0 when error
				printf("could not open file %d\n",index);
				system("pause");
				return -1;
			}
		}
		input=(char*)malloc(sizeof(char));
		inputRead=(char*)malloc(sizeof(char));
		readSuccess=read(myFile,inputRead,sizeof(char));
		while(readSuccess>0) {
			//readSuccess=number of bytes read
			bytes++;
			input[len]=inputRead[0];
			len+=readSuccess;
			input=realloc(input,bytes*sizeof(char));
			//reallocate more bytes for input
			readSuccess=read(myFile,inputRead,sizeof(char));
		}
		close(myFile);

	}
	int* parsedInput = parse(input, len);
	int* parsedDecimal = toDecimal(parsedInput);
	free(decimalArray);
	int* parsedParity = toParity(parsedInput);
	free(parityArray);
	int printSuccess= printTable(parsedInput,parsedDecimal,parsedParity);
	free(parsedInput);
	free(parsedDecimal);
	free(parsedParity);
	free(parsedInput);
	free(inputArray);
	system("pause");

	return 1;
}

int* parse(char* input, int len)
{
	int index,zeros =0;

	while(len%8>0) {
		//accounts for padding zeros
		len++;
		zeros++;
	}
	len++;
	int* parsedInput=(int*)malloc(len*sizeof(int));//allocate extra spot for len at position 0
	parsedInput[0]=len;
	for(index=1; index<len; index++) {
		//ascii to decimal, 48=0
		parsedInput[index]=(int)input[index-1]-48;
		printf("%d @parsedindex %d\n",parsedInput[index],index);
	}
	while(zeros>0) {
		parsedInput[len-zeros]=0;
		zeros--;
	}
	return parsedInput;
}

int* toDecimal(int* inputArray)
{
	int index,len=inputArray[0],deciLen=((len-1)/8)+1, deciIndex=0;
	int* decimalArray =(int*) calloc(deciLen,sizeof(int));
	decimalArray[0]=deciLen;
	for(index=1; index<len; index++) {
		if(index%8==1) {
			//parity bit, shift decimalArray index
			deciIndex++;
		}
		if(inputArray[index]==1) {
			switch(index%8) {
			case 2:
				//64 bit
				decimalArray[deciIndex]+=64;
				break;
			case 3:
				//32 bit
				decimalArray[deciIndex]+=32;
				break;
			case 4:
				//16 bit
				decimalArray[deciIndex]+=16;
				break;
			case 5:
				//8 bit
				decimalArray[deciIndex]+=8;
				break;
			case 6:
				//4 bit
				decimalArray[deciIndex]+=4;
				break;
			case 7:
				//2 bit
				decimalArray[deciIndex]+=2;
				break;
			case 0:
				//1 bit
				decimalArray[deciIndex]+=1;
				break;
			}
		}
		//printf("%d @index %d\t%d @deciindex %d\n",inputArray[index],index,decimalArray[deciIndex],deciIndex);

	}
	return decimalArray;

}

int* toParity(int* inputArray)
{
	int index,parityIndex=0,len=inputArray[0],parityLen=((len-1)/8)+1;
	int* parityArray=(char*)calloc(parityLen,sizeof(int));
	for(index=1; index<parityLen; index++) {
		//empties mem locations
		parityArray[index]=0;
	}
	parityArray[0]=parityLen;
	for(index=1; index<len; index++) {
		if(index%8==1) {
			//shift index if end of 8 bit is reached
			parityIndex++;
		}
		parityArray[parityIndex]+=inputArray[index];
		if(index%8==0) {
			//stores parity as 1 for odd, 0 for even
			parityArray[parityIndex]%=2;
		}
		//printf("%d parity\n",parityArray[parityIndex]);

	}
	return parityArray;
}

int printTable(int* inputArray, int* decimalArray, int* parityArray)
{
	int index,indexBit,indexAscii,len = decimalArray[0];
	printf("%-10s %-10s %-10s %-10s %-10s\n","Original","ASCII","Decimal","Parity","T. Error" );
	printf("------------------------------------------------------\n");
	for(index=1; index<len; index++) {
		for(indexBit=0; indexBit<8; indexBit++) {
			//read 8 ints from input array beginning from position 1
			printf("%d",inputArray[indexBit+((index-1)*8)+1]);
		}
		if(decimalArray[index]>32) {
			printf("   %-12c", (char)decimalArray[index]);
		} else {
			printf("   %c%c%-10c",ascii[decimalArray[index]*3],ascii[1+decimalArray[index]*3],ascii[2+decimalArray[index]*3]);
		}

		printf("%-10d",decimalArray[index]);
		switch(parityArray[index]) {
		case(0):
			printf(" %-10s %-10s\n","EVEN","FALSE");
			break;
		case(1):
			printf(" %-10s %-10s\n","ODD","TRUE");
			break;
		}
	}
	return 1;

}
