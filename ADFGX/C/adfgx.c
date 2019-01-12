#include "adfgx.h"

/*****************
* Help functions *
*****************/

/* Checks if memory allocation or file opening was successful
*/
void validation_check(void* input, char* description) {
	if (input==NULL){
		printf("error: %s",description);
		getchar();
		exit(1);
	}
}

/*
Allocates memory for a string, checks if this allocation was successful and terminates with EOS
*/
char* allocate_strlen(unsigned long strlen) {
	char * a =  malloc(sizeof*a * (strlen+1));
	a[strlen] = '\0';
	return a;
}

/* Makes a deep copy of a string */
char* deep_copy(const char* s) {
	char * d = allocate_strlen(strlen(s));
	strcpy(d,s);
	validation_check(d,"deep copy failed");
	return d;
}

// Alphabetically sorts a given string
char* sort(const char* s) {
	char* sorted = deep_copy(s);
	for (int i = 1, l = strlen(sorted); i < l + 1; i++) {
		for (int j = 0; j < l - i; j++) {
			if (sorted[j] > sorted[j + 1]) {
				char c = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = c;
			}
		}
	}
	return sorted;
}

// Returns the first index of a character in a given string, -1 if the character cannot be found
int get_index(const char c, const char* s) {
	char* index = strchr(s,c);
	return index ? index -s: -1;
}

// Returns a filtered, uppercase version of the specified message
char* filter(const char* alphabet, char* text) {
	int pos = 0;
	char* result = allocate_strlen(strlen(text));
	for(int i =0;i<strlen(text);i++){
		if(strchr(alphabet,text[i])!=NULL && strchr(alphabet,toupper(text[i]))!=NULL){
			result[pos] = toupper(text[i]);
			pos++;
		}
	}
	result[pos] ='\0';
	//strlen exludes '\0'
	int length = strlen(result)+1;
	result = realloc(result,sizeof *result * length);
	validation_check(result,"Error processing filter");
	return result;
}

// Transposes a matrix defined in a 1D array, given the specified width of the matrix
char* transpose(const char* matrix, unsigned int width) {
	
	char * transposed = allocate_strlen(strlen(matrix));
		for (int i = 0, l = strlen(matrix); i < l; i++) {
		int j = strlen(matrix) / width * (i % width) + i / width;
		transposed[j] = matrix[i];
	}
	return transposed;
}

// Returns the content of a given file
char* read_from_file(const char* filename) {
	// Open het bestand met de in te lezen tekst
	FILE* file = fopen(filename, "r");
	validation_check(file, "file in read_from_file");
	fseek(file, 0L, SEEK_END);
	long size_tell = ftell(file);
	rewind(file);
	char* output = allocate_strlen(size_tell);
	long size_read = fread(output, sizeof *output, size_tell, file);
	fclose(file);
	if (size_tell != size_read) {
		output = realloc(output, sizeof *output * (size_read + 1));
		validation_check(output, "output in read_from_file");
		output[size_read] = '\0';
	}
	return output;
}

// Writes text to a given file
void write_to_file(const char* filename, const char* text) {
	FILE* file = fopen(filename, "w");
	validation_check(file, "file in read_from_file");
	fprintf(file, "%s", text);
	fclose(file);
}

/*****************
* Main functions *
*****************/

// Creates a new ADFGX machine
adfgx* create_adfgx(const char* alphabet, const char* symbols, const char* dictionary, const char* transposition) {
	adfgx* encoder =(adfgx*) malloc(sizeof(*encoder));
	encoder->alphabet = deep_copy(alphabet);
	encoder->dictionary = deep_copy(dictionary);
	encoder->symbols = deep_copy(symbols);
	encoder->transposition = deep_copy(transposition);
	return encoder;
}

// Sets the transposition for a given ADFGX machine
void set_transposition(adfgx* m, const char* transposition) {
	m->transposition = realloc(m->transposition,sizeof(*m->transposition) * (strlen(transposition)+1));
	validation_check(m->transposition,"error");
	strcpy(m->transposition,transposition);
}

// Encodes a message using a given ADFGX machine
char* encode_simple(adfgx* m, const char* text) {
	char* encoded = allocate_strlen(2 * strlen(text));
	for (int i = 0, l = strlen(text); i < l; i++) {
		int j = get_index(text[i], m->alphabet);
		encoded[2 * i] = m->dictionary[2 * j];
		encoded[2 * i + 1] = m->dictionary[2 * j + 1];
	}
	return encoded;
}

// Decodes a message using a given ADFGX machine
char* decode_simple(adfgx* m, const char* encoded) {
	char* decoded = allocate_strlen(strlen(encoded) / 2);
	for (int i = 0, l = strlen(encoded) / 2; i < l; i++) {
		for (int j = 0, k = strlen(m->alphabet); j < k; j++) {
			if (encoded[2 * i] == m->dictionary[2 * j] && encoded[2 * i + 1] == m->dictionary[2 * j + 1]) {
				decoded[i] = m->alphabet[j];
			}
		}
	}
	return decoded;
}

// Encodes and transposes a message using a given ADFGX machine
char* encode_hard(adfgx* m, const char* text) {
	char* encoded_simple = encode_simple(m, text);
	int width = strlen(m->transposition);
	int height = (int) ceil(((double) strlen(encoded_simple)) / ((double) width));
	char* matrix = allocate_strlen(height * width);
	char* t_sorted = sort(m->transposition);
	int l = strlen(encoded_simple);
	for (int i = 0; i < width; i++) {
		int j = get_index(m->transposition[i], t_sorted);
		for (int k = i; k + j - i < height * width; k += width) {
			if (k < l) {
				matrix[k + j - i] = encoded_simple[k];
			} else {
				matrix[k + j - i] = '?';
			}
		}
	}
	char* matrix_trans = transpose(matrix, width);
	free(encoded_simple);
	free(t_sorted);
	free(matrix);
	return filter(m->symbols, matrix_trans);
}

// Transposes and decodes a message using a given ADFGX machine
char* decode_hard(adfgx* m, const char* encoded) {
	int height = strlen(m->transposition);
	int width = (int) ceil((double) strlen(encoded) / ((double) height));
	char* matrix = allocate_strlen(height * width);
	char* t_sorted = sort(m->transposition);
	int i, j, k = 0, l = 0, r = strlen(encoded) % height;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width - 1; j++) {
			matrix[k++] = encoded[l++];
		}
		if (r == 0 || get_index(t_sorted[i], m->transposition) < r) {
			matrix[k++] = encoded[l++];
		} else {
			matrix[k++] = '?';
		}
	}
	char* matrix_trans = transpose(matrix, width);
	for (i = 0; i < height; i++) {
		j = get_index(t_sorted[i], m->transposition);
		for (k = i; k < height * width; k += height) {
			matrix[k + j - i] = matrix_trans[k];
		}
	}
	matrix = filter(m->symbols, matrix);
	char* decoded_simple = decode_simple(m, matrix);
	free(matrix);
	free(t_sorted);
	free(matrix_trans);
	return decoded_simple;
}

// Finds the transposition for a given ADFGX machine
char* brute_force(adfgx* m, const char* encoded, const char* start) {
	char* permutation_array = read_from_file("permutations.txt");
	char *permutation = strtok(permutation_array, "\r\n");
	while ((permutation = strtok(NULL, "\r\n"))) {
		set_transposition(m, permutation);
		char* decoded = decode_hard(m, encoded);
		if (strncmp(decoded, start, strlen(start)) == 0) {
			free(permutation_array);
			return decoded;
		}
		free(decoded);
	}
	free(permutation_array);
	return NULL;
}

// Frees allocated memory of a given ADFGX machine
void free_adfgx(adfgx* m) {
	free(m->alphabet);
	free(m->symbols);
	free(m->dictionary);
	free(m->transposition);
	free(m);
}
