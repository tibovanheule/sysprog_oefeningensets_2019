#include "adfgx.h"

int main(int argc, char* argv []) {
	// Test memory allocation
	char* test = allocate_strlen(26);
	for (int i = 0; i < 26; i++) {
		test[i] = 'A' + i;
	}
	printf("Memory allocation test:\n\n   %s\n\n", test);

	// Test deep copy
	char* copy = deep_copy(test);
	if (strncmp(test, copy, strlen(test)) != 0) {
		printf("Deep copy failed");
		getchar();
		exit(1);
	}
	free(test);
	printf("Deep copy test:\n\n   %s\n\n", copy);
	free(copy);

	// Read ADFGX settings
	char* settings = read_from_file("settings.txt");
	
	// Extract substrings
	char* alphabet = strtok(settings, "\r\n");
	char* symbols = strtok(NULL, "\r\n");
	char* dictionary = strtok(NULL, "\r\n");
	char* transposition = strtok(NULL, "\r\n");
	
	// Create ADFGX machine and free settings
	adfgx *m = create_adfgx(alphabet, symbols, dictionary, transposition);
	free(settings);
	
	// Print ADFGX settings
	printf("ADFGX settings:\n\n");
	printf("   Alphabet:      %s\n", m->alphabet);
	printf("   Symbols:       %s\n", m->symbols);
	printf("   Dictionary:    %s\n", m->dictionary);
	printf("   Transposition: %s\n", m->transposition);
	
	// Print dictionary
	printf("\nDictionary:\n\n");
	for (int i = 0, l = strlen(symbols); i < l; i++) {
		for (int j = 0; j < l; j++) {
			int k = i * l + j;
			printf("   %c = %c%c", m->alphabet[k], m->dictionary[2 * k], m->dictionary[2 * k + 1]);
		}
		printf("\n");
	}
	
	// Read plain text
	char* text = read_from_file("text.txt");
	printf("\nPlain text message:\n\n   %s\n\n", text);

	// Filter the plain text
	text = filter(m->alphabet, text);
	printf("Filtered plain text message:\n\n   %s\n\n", text);
	
	// Encode the plain text
	char* encoded_simple = encode_simple(m, text);
	printf("Simple encoded message:\n\n   %s\n\n", encoded_simple);
	
	// Decode the encoded message
	char* decoded_simple = decode_simple(m, encoded_simple);
	printf("Simple decoded message:\n\n   %s\n\n", decoded_simple);
	
	// Encode the plain text
	char* encoded_hard = encode_hard(m, text);
	printf("Complex encoded message:\n\n   %s\n\n", encoded_hard);
	
	// Decode the plain text
	char* decoded_hard = decode_hard(m, encoded_hard);
	printf("Complex decoded message:\n\n   %s\n\n", decoded_hard);
	
	// Read the first words of the plain text and the encoded message
	char* input = read_from_file("encoded.txt");
	char* decoded_start = strtok(input, "\r\n");
	char* encoded_message = strtok(NULL, "\r\n");
	
	// Decode the message using brute force
	printf("Brute force decoding... ");
	char* decoded_message = brute_force(m, encoded_message, decoded_start);
	if (decoded_message) {
		printf("The following message was decoded using transposition key \"%s\":\n\n", m->transposition);
		printf("   %s\n\n", decoded_message);
		write_to_file("decoded.txt", decoded_message);
		free(decoded_message);
	} else {
		printf("The message could not be decoded, your implementation is likely incorrect.\n\n");
	}
	
	// Free all memory
	free_adfgx(m);
	free(text);
	free(input);
	free(encoded_simple);
	free(decoded_simple);
	free(encoded_hard);
	free(decoded_hard);
	
	// Allow to read the console when debugging
	getchar();
	
	return 0;
}
