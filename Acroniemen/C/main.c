#define _CRT_SECURE_NO_DEPRECATE //in order to avoid deprecation warnings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../leaker/leaker.h"
#include "priority_queue.h"
#include "acronym.h"

#define BUFFER_SIZE 10

char* read_input(int* text_length){
	char* line = (char *) malloc(sizeof(char)* (BUFFER_SIZE+1));
	int reallocs = 1;
	int pos = 0;
	while(1){
		int c = fgetc(stdin);
		if (c == EOF ||c== '\n'){
			break;
		}
		if(pos%BUFFER_SIZE==0){
			reallocs++;
			line = realloc(line,reallocs*BUFFER_SIZE+2*sizeof(char));
		}
		if(line == NULL){
			printf("eroror");
			getchar();
			exit(1);
		}
		line[pos] = c;
		pos++;
	}
	line[pos]='\0';
	*text_length = pos;
	return line;
}

unsigned long get_file_length(FILE *ifp) {
	unsigned long size;
	if(ifp == NULL){
		printf("ERROR -main(get_file_length)- File pointer invalid.\n Halting execution.");
		getchar();
		exit(1);
	}
	fseek(ifp,0,SEEK_END);
	size = ftell(ifp);
	rewind(ifp);
	return size;
}

char* read_file(const char* filename) {
	FILE* file = fopen(filename,"r");
	if(file == NULL){
		printf("error kon bestand niet openen");
		getchar();
		exit(1);
	}
	long filelength = get_file_length(file);
	char * s =(char *)malloc((filelength+1)*sizeof(char));
	if (s == NULL){
		printf("outhveuf");
		exit(1);
	}
	fread(s,sizeof *s,filelength,file);
	s[filelength] = '\0';
	fclose(file);
	return s;
}

void start(){
	char *text, *word; 
	char** words; 
	int i, *acronym,list_size, line_size, *start_positions, *lengths, num_of_words, total_length;
	//create priority queue
	priority_queue* queue=pq_create();
	//read dictonary
	text = read_file("wordlist.txt"); 
	//create word list
	words=create_word_list(text,&list_size);
	//read input
	printf("Please provide input:\n");
	word=read_input(&line_size);
	//analyse input
	num_of_words=analyse_num_words(word,&total_length);
	start_positions=(int*)malloc(num_of_words*sizeof(int));
	if(start_positions == NULL){
		printf("ERROR -main(start)- start - Requested memory for start_positions could not be allocated. Available memory insufficient.\nHalting execution.");
		getchar();
		exit(1);
	}
	lengths=(int*)malloc(num_of_words*sizeof(int));
	if(lengths == NULL){
		printf("ERROR -main(start)- Requested memory for lengths could not be allocated. Available memory is insufficient.\nHalting execution.");
		getchar();
		exit(1);
	}
	//analyse acronym
	analyse_words(word,total_length,num_of_words,start_positions,lengths);
	acronym=(int*)malloc((num_of_words+1)*sizeof(int));
	if(acronym == NULL){
		printf("ERROR -main(start)- Requested memory for acronym could not be allocated. Available memory is insufficient.\nHalting execution.");
		getchar();
		exit(1);
	}
	//prepare acronym
	for(i=0;i<num_of_words;i++){
		acronym[i]=-2;
	}
	//create acronym
	generate_acronym_recursive(0,words,list_size,queue,acronym,word,num_of_words,start_positions,lengths);
	//print queue
	pq_print(queue);
	printf("Press any key to exit...");
	getchar();
	//free memory
	pq_free(queue);
	free(acronym);
	free(start_positions);
	free(lengths);
	for(i=0;i<list_size;i++){
		free(words[i]);
	}
	free(words);
	free(word);
	free(text);
}
int main(int argc, char * argv []) {
	start();
	return 0;
}
