#ifndef _ACRONYM_H
#define _ACRONYM_H

char** create_word_list(char* text,int* list_size);
int check_wordlist(char** wordlist,char* acroniem,int list_size);
int calculate_priority(char* acronym);
char* convert_acronym(char* words,int* acronym,int num_of_words,int* start_indices);
void generate_acronym_recursive(int i,char** wordlist,int list_size,priority_queue* queue,int* acronym,char* words,int num_of_words,int* start_indices,int* lengths);
int analyse_num_words(char* words,int* total_length);
void analyse_words(char* words,int total_length,int num_of_words,int* start_indices,int* lengths);

#endif