/*
 * hd2bin.c
 *
 * Version: 0.1
 * Author : Jens Wirth <jw@snej.de>
 * 
 * This tool converts the output of 'hexdump -C' back into a binary file
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <jw@snej.de> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 512

unsigned char processByte(unsigned char* p)
{
	unsigned char byte;
	int i;

	for (i=0, byte=0; i<2; i++, p++)
	{
		byte *= 16;
		if (*p >= 'a' && *p <= 'f')
			byte += *p - 'a' + 10;
		else if (*p >= '0' && *p <= '9')
			byte += *p - '0';
		else
			exit(0);
	}

	return byte;
}

int main(int argc, char* argv[])
{
	FILE *infile, *outfile;
	unsigned char buf[MAXLINE];
	unsigned char byte, *p;
	int i;

	infile = fopen(argv[1], "rb");
	outfile = fopen(argv[2], "wb");

	while ( (p=fgets(buf, MAXLINE, infile)) > 0 )
	{
		for (p+=10; p<(buf+32); p+=3)
		{
			byte = processByte(p);
			fputc(byte, outfile);
		}
		for (p+=1; p<(buf+57); p+=3)
		{
			byte = processByte(p);
			fputc(byte, outfile);
		}
		for (i=0; i<MAXLINE; i++)
			buf[i]=0;
	}

	fclose(outfile);
	fclose(infile);

	return 0;
}
