#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "../leaker/leaker.h"
#include "priority_queue.h"

char** create_word_list(char* text,int* list_size){
	char** words;
	unsigned long size,begin,counter,index,word_length;

	counter=0;
	size=0;
	begin=0;
	while(text[counter]!='\0'){
		if(text[counter]=='\n'||text[counter]==' '){
			size++;
		}
		counter++;
	}
	size++;

	words=(char**)malloc(size*sizeof(char*));
	if(words == NULL){
		printf("ERROR -acronym(create_word_list)- Requested memory for words could not be allocated. Available memory insufficient.\nExecution halted.");
		getchar();
		exit(1);
	}
	counter=index=0;
	while(text[counter]!='\0'){
		if(text[counter]=='\n'||text[counter]==' '){
			word_length=counter-begin;
			words[index] = (char*)malloc((word_length+1)*sizeof(char));
			if(words[index] == NULL){
				printf("ERROR -acronym(create_word_list)- The requested words[%lu] for buffer could not be allocated. Available memory is insufficient.\nExecution halted.",index);
				getchar();
				exit(1);
			}
			for(unsigned int i=0;i<word_length;i++){
				words[index][i]=text[begin+i];
			}
			words[index][word_length]='\0';
			begin=counter+1;
			index++;
		}
		counter++;
	}
	*list_size=index;
	return words;
}
int check_wordlist(char** wordlist,char* acroniem,int list_size){
	int i,found;
	char lower;

	found=0;
	for(i=0;i<list_size&&found==0;i++){
		int j=0;
		while(1){
			if(acroniem[j]>='A'&&acroniem[j]<='Z'){
				lower=tolower(acroniem[j]);
			}else{
				lower=acroniem[j];
			}		
			if(wordlist[i][j]=='\0'&&acroniem[j]=='\0'){
				found=1;
				break;
			}else if(wordlist[i][j]!=lower){
				break;
			}
			j++;
		}
	}
	return found;
}
int calculate_priority(char* acronym){
	int i=0; 
	int priority=INT_MAX;

	while(acronym[i]!='\0'){
		priority-=acronym[i];
		i++;
	}
	priority-=1000*i;
	return priority;
}
void print_acr(char* word,int* acronym,int num_of_words,int* start_indices){
	int i=0;

	for(i=0;i<num_of_words;i++){
		printf("%c",word[start_indices[i]]);
		if(acronym[i]!=-1){
			printf("%c",word[acronym[i]]);
		}
	}
	printf("\n");
}
char* convert_to_acronym(char* word,int* acronym,int num_of_words,int* start_indices){
	char* new_acronym;
	int i=0;
	int j=0;
	int num_of_letters=0;

	for(i=0;i<num_of_words;i++){
		if(acronym[i]>-1){
			num_of_letters++;
		}
	}
	new_acronym=(char*)malloc((num_of_letters+num_of_words+1)*sizeof(char));
	if(new_acronym == NULL){
		printf("ERROR -acronym(convert_to_acronym)- The requested memory for new_acronym could not be allocated. Available memory is insufficient.\nExecution halted.");
		getchar();
		exit(1);
	}
	for(i=0;i<num_of_words;i++){
		new_acronym[j]=word[start_indices[i]];
		j++;
		if(acronym[i]!=-1){
			new_acronym[j]=word[acronym[i]];
			j++;
		}
	}
	new_acronym[j]='\0';
	return new_acronym;
}
void generate_acronym_recursive(int i,char** wordlist,int list_size,priority_queue* queue,int* acronym,char* word,int num_of_words,int* start_indices,int* lengths){
	int unique;
	int newIndex=0;
	int j;
	for(j=-2;j<lengths[i]-1;j++){
		if(acronym[i]==-1){
			//+1 because the first letter is fixed
			newIndex=start_indices[i]+1;
		}else{
			//acronym does not contain letters but the positions of the letter 
			newIndex=acronym[i]+1;
		}
		if(newIndex<start_indices[i]+lengths[i]){
			acronym[i]=newIndex;
			//check if done
			if(acronym[num_of_words-1]!=-2){
				char* new_acr=convert_to_acronym(word,acronym,num_of_words,start_indices);
				if(check_wordlist(wordlist,new_acr,list_size)){
					unique=pq_add(queue,new_acr,calculate_priority(new_acr));
					if(!unique){
						//word already in queue
						free(new_acr);
					}
				}else{
					free(new_acr);
				}
			}else{
				generate_acronym_recursive(i+1,wordlist,list_size,queue,acronym,word,num_of_words,start_indices,lengths);
			}
		}	
	}
	acronym[i]=-2;
}

int analyse_num_words(char* words,int* total_length){
	int i=0;
	int num_words=1;

	while(words[i]!='\0'){
		if((words[i]==' ' ||words[i]=='\n')&&words[i+1]!='\0'){
			num_words++;
		}
		i++;
	}
	*total_length=i;
	return num_words;
}
void analyse_words(char* word,int total_length,int num_of_words,int* start_indices,int* lengths){
	int num_words;
	int i=0;
	int word_length=0;

	i=0;
	num_words=0;
	word_length=1;
	start_indices[0]=0;
	while(word[i]!='\0'){
		if((word[i]==' ' ||word[i]=='\n')&&word[i+1]!='\0'){
			lengths[num_words]=word_length-1;
			word_length=0;
			start_indices[num_words+1]=i+1;
			num_words++;
		}
		i++;
		word_length++;
	}
	if(word[i]=='\0'){
		lengths[num_words]=word_length-1;
		word_length=0;
	}
}
