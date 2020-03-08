#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct _readmod {

	uint8_t FP : 1;

};

inline void chk_ascii(register uint8_t chr);

int main(int argc,char** argv) 
{

	char *input;
	argv++;
	struct _readmod readmod;

	readmod.FP = 1;

	if (argc == 1 || (argc == 2 && strncmp(*argv,"-in",3) == 0)) 
	{
		printf("[-] invalid parameters\n");
		goto error;
	}
	else if (strncmp(*argv,"-h",2) == 0)
	{

		printf("Create by pr4gasm\n[*] hexdump 1.0\n\n-h print information\n-in input file\n-readline print line after wait user press enter\n-readlines print lines\n");
		_exit(0);

	}

	if (argc == 4) 
	{

		if ((strncmp(argv[2],"-readline",sizeof("-readline")) == 0) || (strncmp(argv[2],"-readlines",sizeof("-readlines")) == 0));
		else goto error;
	
		if (strncmp(*(argv+2),"-readline",sizeof("-readline")) == 0)
	
			readmod.FP = 0;

		else if (strncmp(*(argv+2),"-readlines",sizeof("-readlines")) == 0)
			readmod.FP = 1;	
	}

	if (strncmp(*argv,"-in",3) == 0)

		input = argv[1];


	else
	{
error:
		printf("[*] hexdump 1.0 press -h to help\n");
		_exit(0);

	}

	FILE *fp;

	fp = fopen(input,"r");

	if (fp == 0x00) 
	{
	
		printf("[-] Error file not found\n");
		_exit(-1);

	}

	uint8_t buf[12];

	register unsigned char i = 0;

	register long adr = 0;
	register int offset = 0;

	printf("%000000000000000016lX: ",adr);

	do 
	{
		if (i == 12)
		{
			adr+=6*2;
			i = 1;
			offset = 0;
			putchar(' ');
			for(register uint8_t i2 = 0;i2 < 12;i2++) 
				chk_ascii(buf[i2]);

			if(readmod.FP == 0) getchar();
				
			printf("\n%000000000000000016lX: ",adr);

		}
		else ++i;

		fread((void*)&buf[i-1],1,1,fp);

		offset+=3;
	
		if(i % 2 != 0) putchar(' ');
	
		printf("%002X",buf[i-1]);

	}

	while(feof(fp) != 1);

	putchar('\n');

	fclose(fp);

	_exit(0);

}

inline void chk_ascii(register uint8_t chr) 
{

	if (chr >= 0x20 && chr <= 0x7e) putchar(chr);
	else putchar('.');

}
