#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../leaker/leaker.h"
#include "hash_table.h"
#include "message_indexer.h"

#define MAX_LENGTH 257
#define CONTEXTSIZE 3

int print_word_context(message* in,indx i);
void run(int argc, char** argv);
void debug_ht(int argc, char** argv);
void debug_mi(int argc, char** argv);

int main(int argc, char** argv) {
	if (argc > 1){
		if(strcmp(argv[1],"run")==0)
			run(argc, argv);
		else if(strcmp(argv[1],"debug_ht")==0)
			debug_ht(argc, argv);
		else if(strcmp(argv[1],"debug_mi")==0)
			debug_mi(argc, argv);
		else printf("No valid program arguments.");
	}
	else
		printf("No program arguments.\n");
}

void debug_ht(int argc, char** argv){
	hash_table *ht=ht_create();
	indx t1={1,1}, t2={1,2}, t3={1,3}, t4={1,4}, t5={2,1};
	indx* id=NULL;
	int i;
	ht_set_value(ht,"this",t1);
	ht_set_value(ht,"is",t2);
	ht_set_value(ht,"a",t3);
	ht_set_value(ht,"test",t4);
	ht_print(ht);
	printf("-----------------\n");
	if(ht_remove(ht,"a")==NOT_AN_ELEMENT)
		printf("no word deleted\n");
	else{
		ht_print(ht);
		printf("-----------------\n");
	}

	printf("%d elements are associated with the word 'test'.\n",ht_set_value(ht,"test",t5));
	ht_print(ht);
	printf("-----------------\n");

	printf("The index values of the word 'test' are:\n");
	for (i=0;i<ht_get_value(ht,"test",&id);i++){
		printf("\t %d: message %d - word %d\n",i+1,id->messagenr,id->wordnr);
		id++;
	}

	if(ht_remove(ht,"test")==NOT_AN_ELEMENT)
		printf("no word deleted\n");
	else{
		ht_print(ht);
		printf("-----------------\n");
	}
	ht_destroy(&ht);
	printf("HASHTABLE DESTROYED\n");
}

void debug_mi(int argc, char** argv){
	hash_table *ht=ht_create();
	message m={0};
	init_message(&m,"test.txt");
	index_message(ht,&m,1);
	ht_print(ht);
	free_message(m);
	printf("MESSAGE DESTROYED\n");
	ht_destroy(&ht);
	printf("HASHTABLE DESTROYED\n");
}

void run(int argc, char** argv) {
	message inbox[3]={0};
	char input[MAX_LENGTH];
	int i, indexnr=0;
	hash_table *ht=ht_create();
	init_message(&inbox[indexnr],"usa.txt");
	index_message(ht,&inbox[indexnr],indexnr);
	indexnr++;
	init_message(&inbox[indexnr],"hologram.txt");
	index_message(ht,&inbox[indexnr],indexnr);
	indexnr++;
	init_message(&inbox[indexnr],"qantas.txt");
	index_message(ht,&inbox[indexnr],indexnr);
	indexnr++;
	ht_print(ht);

	while (1) {
		indx* indx=NULL;
		printf("\n");
		printf("Which token you want to search for? (type \"stop\" to stop)\n");
		scanf("%256s", input);
		if (strcmp(input, "stop") != 0) {
			int value = ht_get_value(ht, input, &indx);
			if (value > 0) {
				printf("Token \"%s\" was found %d time(s)\n", input, value);
				for(int i=0;i<value;i++){
					printf("Message %d - word %d :",indx->messagenr,indx->wordnr);
					print_word_context(inbox,*indx);
					printf("\n");
					indx++;
				}
			}
			else {
				printf("Token \"%s\" was not found.\n", input);
			}
		}
		else {
			break;
		}
	}
	ht_destroy(&ht);
	printf("HASHTABLE DESTROYED\n");
	for(i=0;i<indexnr;i++)
		free_message(inbox[i]);
	printf("MESSAGES DESTROYED\n");
}


/* Print de context van het woord af op het scherm.
   CONTEXTSIZE duidt op het aantal woorden voor en na het opgezochte woord.
 */

int print_word_context(message* in, indx i){
	int start=0,end=in[i.messagenr].nr_of_words-1;
	char *p=NULL;
	if(i.wordnr>CONTEXTSIZE)
		start=i.wordnr-CONTEXTSIZE;
	if(i.wordnr<in[i.messagenr].nr_of_words-CONTEXTSIZE-1)
		end=i.wordnr+CONTEXTSIZE+1;
	p=in[i.messagenr].word_index[start];
	printf("...");
	while(p!=in[i.messagenr].word_index[end]){
		printf("%c",*p);
		p++;
	}
	printf("...");
	return 1;
}

