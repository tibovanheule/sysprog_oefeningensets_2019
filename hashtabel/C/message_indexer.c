#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../leaker/leaker.h"
#include "message_indexer.h"


/*Initialisatie van een message door het inlezen van de tekst en het opslaan van de tekstgrootte.*/
void init_message(message* m, char* filename){
	if(m->text!=NULL)
		free_message(*m);
	m->textsize=read_file_into_string(filename, &m->text);
}

/*Opruimen van message.*/
void free_message(message m){
	free(m.word_index);
	if(m.text!=NULL)
		free(m.text);
}

/*	Indexeren van de woorden van message m in de hash tabel ht.
    In message m wordt hierbij ook een woordindex aangemaakt.
	Dit is nodig om bij het opzoeken van een woord de woorden van de context snel en correct weer te geven.
	return waarde = het aantal geindexeerde woorden. */
int index_message(hash_table* ht, message* m, int messagenr){
	char buffer[50]; //voor de eenvoud ervan uitgaand dat woord = max 49 karakters
	int pos = 0;
	unsigned int i = 0;
	char* p=m->text;
	int wordindex= 0;

	for (i = 0; i < strlen(p)+1; i++) {
		char c = p[i];
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| c == '-') {
			buffer[pos++] = c;
		}
		else {
			if (pos > 0) {
				buffer[pos] = '\0';
				pos = 0;
				{
					indx i={messagenr,wordindex};
					ht_set_value(ht, buffer, i);
					printf("indexing '%s'\n",buffer);
					if (m->word_index == NULL) {
						m->word_index = (char**)malloc(sizeof(char*));
						if (m->word_index == NULL) {
							printf("ERROR - memory allocation failed");
							exit(2);
						}
					}
					else {
						m->word_index = (char**)realloc(m->word_index, sizeof(char*)*(wordindex + 1));
						if (m->word_index == NULL) {
							printf("ERROR - memory allocation failed");
							exit(2);
						}
					}
					m->word_index[wordindex]=p;
					wordindex++;
				}
			}
		}
	}
	m->nr_of_words=wordindex;
	return wordindex;
}


/* Inlezen van een bestand in een string
RETURN=lengte van de string */
int read_file_into_string(char* filename,char** text){
  FILE * pFile;
  long lSize;
  size_t result;

  pFile = fopen (filename , "rb" );
  if (pFile==NULL) {
	  fputs("File error",stderr);
	  exit (1);
  }
  fseek(pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind(pFile);

  *text = (char*) malloc (sizeof(char)*(lSize+1));
  if (*text == NULL) {
	  fputs("Memory error",stderr);
	  exit(2);
  }
  result = fread (*text,1,lSize,pFile);
  (*text)[lSize] = '\0';
  if (result != lSize) {
	  fputs("Read error",stderr);
	  exit(3);
  }
  fclose (pFile);
  return lSize;
}
