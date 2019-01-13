#ifndef _MESSAGE_INDEXER_H_
#define _MESSAGE_INDEXER_H_

#include "hash_table.h"

typedef struct message{
	char* text; /*de tekst van de email*/
	char** word_index; /*een tabel waarvan de elementen de woorden van de tekst zijn, en hun index in de tabel hun volgnummer is*/
	int textsize; /*de lengte van de tekst */
	int nr_of_words; /* de lengte van de woordindex*/
} message;

/* Initialisatie van een message door het inlezen van de tekst en het opslaan van de tekstgrootte.*/
void init_message(message* m,char* filename);

/*Opruimen van message.*/
void free_message(message m);

/*	Indexeren van de woorden van message m in de hash tabel ht. 
    In message m wordt hierbij ook een woordindex aangemaakt. 
	Dit is nodig om bij het opzoeken van een woord de woorden van de context snel en correct weer te geven. 
	return waarde = het aantal geindexeerde woorden. */
int index_message(hash_table* ht, message* m, int messagenr);

/* Inlezen van een bestand in een string
RETURN=lengte van de string */
int read_file_into_string(char* filename, char** text); 

#endif