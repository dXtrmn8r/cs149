/**
 *	Description:					A program that lists all the names from a given text file as well as how many of each name in a line there are.
 *
 *	Author names:					Darren Peralta, Henry Choy
 *	Author emails:					{darrencarl.peralta,henry.choy}@sjsu.edu
 *	Last modified date:				02/19/2023
 *	Creation date:					02/15/2023
 */

#include <stdio.h>
#include <string.h>					// necessary for string functions
#include <ctype.h>					// necessary for character functions
#include <stdbool.h>				// to use booleans in C
#include <stdlib.h>					// to be able to use malloc and free operations

/**
 * Method that returns true if all the characters in a string are whitespace.
 * Assumptions:						None
 * Input Params:					s - a pointer to a constant character array/string to check for whitespace.
 * Returns:							true - if all the characters in s are whitespace
 * 									false - if there is at least one whitespace character
 */
bool is_blank(const char* s) {
	// while there are characters to be read.
	// this will terminate if s points to a null character
	while (*s) {
		// if s does not point to a whitespace character
		if (!isspace(*s))
			return false;
		s++;
	}
	return true;
}

/**
 * Main method that lists ll the names from a given text file as well as how many of each name in a line there are.
 * No assumptions.
 * Input Params:					argc - number of command line arguments
 * 									argv - array of command line arguments (strings)
 * Returns:							0 on success
 * 									1 if the file does not exist
 */
int main(int argc, const char *argv[]) {
	
	const char *filename = argv[1];
	FILE *fp = fopen(filename, "r");
	
	if (fp == NULL) {				// if the file is not in the same directory as the exec
		fprintf(stderr, "cannot open file\n");
		return 1;
	}
	
	unsigned long lines_read = 0;
	long bytes_read;				// indicates the number of bytes read
	char nameList[100][30];			// array where the names will be stored
	int nameCount[100];				// count of all names stored on nameList
	int names_stored = 0;			// number of names stored
	
	// initializes each element in nameCount to 0
	for (int i = 0; i < 100; i++) {
		nameCount[i] = 0;
	}
	
	size_t size = 30;				// maximum number of characters to be read
	char *input = NULL;				// the line to be inputted
	
	// this loop will execute when it hasn't read to the end of the file.
	while ((bytes_read = getdelim(&input, &size, '\n', fp)) != -1) {
		lines_read++;
		bool name_found = false;	// flag indicating the name is already on nameList

		// replaces the newline character with a NULL character
		if (input[bytes_read - 1] == '\n') {
			input[bytes_read - 1] = '\0';
			--bytes_read;
		}
		
		// linear searches the entire line is already stored on nameList one by one
		for (int i = 0; i < names_stored; i++) {
			// compares the input with an individual name already stored on nameList
			if (strcmp(input, nameList[i]) == 0) {
				nameCount[i]++;
				name_found = true;
				break;
			}
		}
		
		// if the line contains whitespaces
		if (is_blank(input)) {
			fprintf(stderr, "Warning - Line %lu is empty.\n", lines_read);
		}
		// if the name is already on the list
		else if (name_found == false) {
			strcpy(nameList[names_stored], input);
			nameCount[names_stored] = 1;
			names_stored++;
		}
	
	}
	
	// prints each name on nameList with the number of names in nameCount
	for (int i = 0; i < names_stored; i++) {
		printf("%s: %d\n", nameList[i], nameCount[i]);
	}
	
	// closes the file resource and the input pointer
	free(input);
	fclose(fp);
	return 0;
}
