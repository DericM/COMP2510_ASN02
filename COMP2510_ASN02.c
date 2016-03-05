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

void condense_special(char set[]);
void expand_range(char set[]);
void read_input(const char set1[], const char set2[]);
void truncate(char set1[], char set2[]);
void check_size(size_t s);
char get_escape_char(const char c);
int is_last(size_t j, char c, const char s[]);
int validate_range(char set[], size_t i, int flag);

int main(int argc, char *argv[])
{
	char set1[MAX_SIZE];
	char set2[MAX_SIZE];

	strcpy(set1, argv[1]);
	strcpy(set2, argv[2]);


	if (argc != 3) {
		perror("usage: {FILE.c} {SET1} {SET2} \n");
		exit(1);
	}

	condense_special(set1);
	condense_special(set2);
	expand_range(set1);
	expand_range(set2);
	truncate(set1, set2);
	read_input(set1, set2);


	return 0;
}



/*
Get file/user input.
*/
void read_input(const char set1[], const char set2[]) {
	int i, c, flag;
	/* printf("%s\n%s", set1, set2); */

	while ((c = getchar()) != EOF) {
		flag = 0;
		for (i = 0; set1[i] != '\0' || set2[i] != '\0'; i++) {
			
			if (c == set1[i] && is_last(i, set1[i], set1)) {
				putchar(set2[i]);
				flag = 1;
			}
		}
		if (flag == 0)
			putchar(c);
	}
}


/*
Returns 1 if c at index i in string s is the last instance of itself.
otherwise return 0.
*/
int is_last(size_t j, char c, const char s[]) {
	size_t i;
	for (i = 0; s[i] != '\0';i++) {
		if (i > j && s[i] == c)
			return 0;
	}
	return 1;
}

/*
Condenses special characters into one array slot.
*/
void condense_special(char set[]) {
	size_t i, j;

	for (i = 0, j = 0; set[i] != '\0'; i++, j++) {
		if (set[i] == '\\' && set[i + 1] != '\0') {
			set[j] = get_escape_char(set[i + 1]);
			i++;
		}
		else {
			set[j] = set[i];
		}
	}
	set[j] = '\0';
}

/*
expands all ranges(a-c)->(abc)
*/
void expand_range(char set[]) {
	size_t i, j;
	int flag = -1;
	char c;
	char tmp[MAX_SIZE];
	strcpy(tmp, set);
	
	for (i = 0, j = 0; tmp[i] != '\0'; i++, j++) {
		if (validate_range(tmp, i, flag)) {
			flag = i;
			
			for (c = (tmp[i - 1] + 1); c <= tmp[i + 1]; c++, j++) {
				check_size(j);
				set[j] = c;
			}
			i++;
			j--;
		} 
		else {
			check_size(j);
			set[j] = tmp[i];
		}
	}
	set[j] = '\0';
}

/*
Check that a range is valid.
*/
int validate_range(char set[], size_t i, int flag) {
	if (set[i] == '-'
		&& (int)i > flag + 1
		&& set[i + 1] != '\0'
		&& set[i - 1] + 1 <= set[i + 1])
		return 1;
	return 0;
}



/*
Ends the program if the set has breached the max size.
*/
void check_size(size_t s) {
	if (s >= MAX_SIZE) {
		perror("MAX_SIZE");
		exit(1);
	}
}

/*
truncate set1 and set2 to identical length.
*/
void truncate(char set1[], char set2[]) {
	size_t i;
	for (i = 0;; i++) {
		if (set1[i] == '\0' || set2[i] == '\0') {
			set1[i] = set2[i] = '\0';
			break;
		}
	}
}

/*
Returns the apropriate escape character, depending on c.
*/
char get_escape_char(const char c) {
	switch (c) {
		case '\\':
			return '\\';
		case 'a':
			return '\a';
		case 'b':
			return '\b';
		case 'f':
			return '\f';
		case 'n':
			return '\n';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case 'v':
			return '\v';
		case '\'':
			return '\'';
		case '\"':
			return '\"';
		default:
			perror("Invalid set.");
			exit(1);
	}
}






