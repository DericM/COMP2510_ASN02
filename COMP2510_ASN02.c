/*
*	File:	COMP2510_ASN02.c
*	Author: Deric Mccadden
*	Date:	2016/02/19
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 256

int main(int argc, char *argv[])
{
	char set1[MAX_SIZE];
	char set2[MAX_SIZE];

	if (argc != 3) {
		perror("usage: %s {SET1} {SET2} {inputfile} {outputfile}\n");
		exit(1);
	}
	
	strcpy(set1, argv[1]);
	strcpy(set2, argv[2]);

	printf("%s\n", set1);
	printf("%s", set2);



	getchar();
	return 0;
}

