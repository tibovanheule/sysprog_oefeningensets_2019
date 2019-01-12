#ifndef _ADFGX_HEADER_
#define _ADFGX_HEADER_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../leaker/leaker.h"

/*****************
*  ADFGX struct  *
*****************/

typedef struct {
	char* alphabet;      // Defines the supported characters by the encryption algorithm
	char* symbols;       // Defines the symbols used to encrypt a message
	char* dictionary;    // Defines the translation for all characters defined in alphabet
	char* transposition; // Defines the transposition key used in the second encryption step
} adfgx;

/*****************
* Help functions *
*****************/

// Checks if memory allocation or file opening was successful
void validation_check(void* input, char* description);

// Allocates memory for a string, checks if this allocation was successful and terminates with EOS
char* allocate_strlen(unsigned long strlen);

// Makes a deep copy of a string
char* deep_copy(const char* s);

// Alphabetically sorts a given string
char* sort(const char* s);

// Returns the index of a character in a given string, -1 if the character cannot be found
int get_index(const char c, const char* s);

// Returns a filtered, lowercase version of the specified message
char* filter(const char* alphabet, char* text);

// Transposes a matrix defined in a 1D array, given the specified width of the matrix
char* transpose(const char* matrix, unsigned int width);

// Returns the content of a given file
char* read_from_file(const char* filename);

// Writes text to a given file
void write_to_file(const char* filename, const char* text);

/*****************
* Main functions *
*****************/

// Creates a new ADFGX machine
adfgx* create_adfgx(const char* alphabet, const char* symbols, const char* dictionary, const char* transposition);

// Sets the transposition for a given ADFGX machine
void set_transposition(adfgx* m, const char* transposition);

// Encodes a message using a given ADFGX machine
char* encode_simple(adfgx* m, const char* text);

// Decodes a message using a given ADFGX machine
char* decode_simple(adfgx* m, const char* encoded);

// Encodes and transposes a message using a given ADFGX machine
char* encode_hard(adfgx* m, const char* text);

// Transposes and decodes a message using a given ADFGX machine
char* decode_hard(adfgx* m, const char* encoded);

// Finds the transposition for a given ADFGX machine
char* brute_force(adfgx* m, const char* encoded, const char* start);

// Frees allocated memory of a given ADFGX machine
void free_adfgx(adfgx* m);

#endif
