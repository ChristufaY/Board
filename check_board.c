///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      board1.txt
// Semester:         CS 354 Fall 2021
// Instructor:       deppeler
//
// Author:           Christopher Yang
// Email:            cyang397@wisc.edu
// CS Login:         chrisy
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Dad, helped with the high level thinking of "valid_board" method,
//		     specifically how I should use a temporary 1D array and check for
//  		     duplicated if the spot in the 1D array was already taken.
//		     No other person helped.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* COMPLETED (DO NOT EDIT):
 * Read the first line of input file to get the size of that board.
 *
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 */
void get_board_size(FILE *fptr, int *size) {
    char *line1 = NULL;
    size_t len = 0;

    if ( getline(&line1, &len, fptr) == -1 ) {
        printf("Error reading the input file.\n");
        exit(1);
    }

    char *size_chars = NULL;
    size_chars = strtok(line1, DELIM);
    *size = atoi(size_chars);

	// free memory allocated for reading first link of file
	free(line1);
	line1 = NULL;
}



/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 *
 * A valid row or column contains only blanks or the digits 1-size,
 * with no duplicate digits, where size is the value 1 to 9.
 *
 * Note: p2A requires only that each row and each column are valid.
 *
 * board: heap allocated 2D array of integers
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {

int *temp = 0;
temp = (int*)malloc(sizeof(int)*size);
int boardNum;

// row-wise validation
for(int i = 0; i < size; i++) {
	// initialize temp after each use
	for(int a = 0; a < size; a++) 
		*(temp + a) = 0;
	for(int j = 0; j < size; j++) {
		boardNum = *(*(board + i) + j);
		if(boardNum < 0 || boardNum > size) {
			free(temp);
			temp = 0;
			return 0;
		}
		else {
			if(boardNum != 0){
				if(*(temp + boardNum - 1) == 0){
					*(temp + boardNum - 1) = 1;
				}
				else {
					free(temp);
					temp = 0;
					return 0;
				}
			}
		}
	}
}
// column-wise validation
for(int i = 0; i < size; i++) {
	// initiailize temp after each use
        for(int a = 0; a < size; a++)
                *(temp + a) = 0;
        for(int j = 0; j < size; j++) {
                boardNum = *(*(board + j) + i);
                if(boardNum < 0 || boardNum > size) {
                        free(temp);
                        temp = 0;
                        return 0;
                }
                else {
                        if(boardNum != 0){
                                if(*(temp + boardNum - 1) == 0){
                                        *(temp + boardNum - 1) = 1;
                                }
                                else {
                                        free(temp);
                                        temp = 0;
                                        return 0;
                                }
                        }
                }
        }
}
    free(temp);
    temp = 0;
    return 1;

}



/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * argc: CLA count
 * argv: CLA value
 */
int main( int argc, char *argv[] ) {

    // TODO: Check if number of command-line arguments is correct.
    if(argc < 2 || argc > 2) {
	printf("Usage: ./check_board <input_filename>.\n");
	exit(1);
    }
//	printf("argc: %d\n", argc);
//	printf("argv[0]: %s\n", *(argv));
//	printf("argv[1]: %s\n", *(argv + 1));
    // Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    // Declare local variables.
    int size = 0;
 
    // TODO: Call get_board_size to read first line of file as the board size.
	get_board_size(fp, &size);
//	printf("Size: %d", size);
    // TODO: Dynamically allocate a 2D array for given board size.
	int **inputArr;
	inputArr = malloc(sizeof(int *) * size);
	for(int i = 0; i < size; i++)
		*(inputArr + i) = malloc(sizeof(int) * size);
    // Read the rest of the file line by line.
    // Tokenize each line wrt the delimiter character
    // and store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading line %i of the file.\n", i+2);
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            // TODO: Complete the line of code below
            // to initialize your 2D array.
            *(*(inputArr + i) + j) = atoi(token);
            token = strtok(NULL, DELIM);
        }
    }

    // TODO: Call the function valid_board and print the appropriate
    //       output depending on the function's return value.
    int result = 0;
    result = valid_board(inputArr, size);
    if(result == 1)
	printf("valid\n");
    else
	printf("invalid\n");
    // TODO: Free all dynamically allocated memory.
    for(int i = 0; i < size; i++) 
	free(*(inputArr + i));
    free(inputArr);
    inputArr = NULL;
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    }

    return 0;
}






// f21

