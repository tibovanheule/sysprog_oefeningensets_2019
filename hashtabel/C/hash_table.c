#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "../leaker/leaker.h"

void free_ht_entry(ht_entry ht){
/* Sleutel vrijgeven */
	if(ht.key!=NULL)
		free(ht.key);
/* Value vrijgeven */
	if(ht.value!=NULL)
		free(ht.value);
}

/* Geeft een getal terug tussen 0 en ht.table_size-1 */
unsigned int ht_hash_index(const hash_table* ht, const char* key) {
	return ht_joaat_hash(key) % (unsigned int)(ht->table_size);
}

/* Creert een hashtabel
   Alloceert daar voldoende geheugenruimte voor
   Geeft een pointer terug die wijst naar deze nieuw gealloceerde structuur
   De tabelrij krijgt als tabelgrootte DEFAULT_TABLE_SIZE */
hash_table* ht_create() {
	int h;
	hash_table* ht = (hash_table*)malloc(sizeof(hash_table));
	if (ht == NULL) {
		printf("ERROR - memory allocation failed\n");
		return NULL;
	}
	ht->table_size = DEFAULT_TABLE_SIZE;
	ht->count = 0;
	ht->table_array = (ht_entry_list**)malloc(ht->table_size * sizeof(ht_entry_list*));
	if (ht->table_array == NULL) {
		printf("ERROR - memory allocation failed\n");
		free(ht);
		return NULL;
	}
	for (h = 0; h < ht->table_size; h++) {
		ht->table_array[h] = NULL;
	}
	return ht;
}

/*  Deze functie geeft het aantal waarden terug die in de hashtabel met de sleutel geassocieerd worden.
    De bijhorende array die de waarden bevat wordt �by reference� doorgegeven (cursus hoofdstuk 6.3).
    Geeft NOT_AN_ELEMENT terug als de sleutel niet in de hashtabel voorkomt.*/
int ht_get_value(const hash_table* ht, const char* key, indx** i) {
	unsigned int hash_index = ht_hash_index(ht, key);
	ht_entry_list* list = ht->table_array[hash_index];
	while (list != NULL) {
		if (strcmp(key, list->current.key) == 0) {
			*i=list->current.value;
			return list->current.nr_of_occurrences;
		}
		list = list->next;
	}
	/* Element met sleutel komt niet voor*/
	return NOT_AN_ELEMENT;
}

/* Zorgt ervoor dat de hashtabel de index met de sleutel associeert.
   Geeft het aantal indexes terug die die na uitvoeren van deze operatie met de sleutel in de hashtabel worden geassocieerd.
   Geeft NOT_AN_ELEMENT terug als een nieuw element in de hashtabel wordt toegevoegd.
   In dat geval wordt van de sleutel een diepe kopie gemaakt */
int ht_set_value(hash_table* ht, const char* key, indx value) {
	unsigned int hash_index = ht_hash_index(ht, key);
	ht_entry_list* added;
	ht_entry_list* list = ht->table_array[hash_index];
	while (list != NULL) {
		if (strcmp(key, list->current.key) == 0) {
			/* Element met sleutel komt voor: voeg toe in array */
			//int previous = list->current.nr_of_occurences;
			list->current.nr_of_occurrences++;
			list->current.value=(indx*) realloc(list->current.value,list->current.nr_of_occurrences*sizeof(indx));
			if (list->current.value==NULL) {
				printf("ERROR - memory allocation failed\n");
				exit(2);
			}
			list->current.value[list->current.nr_of_occurrences-1] = value;
			return list->current.nr_of_occurrences;
			//return 1;
		}
		list = list->next;
	}
	/* Element met sleutel kwam nog niet voor */
	added = (ht_entry_list*)malloc(sizeof(ht_entry_list));
	if (added == NULL) {
		printf("ERROR - memory allocation failed\n");
		exit(2);
	}
	added->current.key = (char*)malloc((strlen(key) + 1) * sizeof(char));
	if (added->current.key == NULL) {
		printf("ERROR - memory allocation failed\n");
		exit(2);
	}
	strcpy(added->current.key, key);
	added->current.value = (indx*)malloc(sizeof(indx));
	if (added->current.value == NULL) {
		printf("ERROR - memory allocation failed\n");
		exit(2);
	}
	added->current.value[0] = value;
	added->next = ht->table_array[hash_index];\
	added->current.nr_of_occurrences=1;
	ht->table_array[hash_index] = added;
	ht->count++;
	rehash(ht);
	return NOT_AN_ELEMENT;
}

/* Verwijdert een gegeven element
   Geeft het aantal indexes terug die met de sleutel in de hashtabel werden geassocieerd.*/
int ht_remove_entry(ht_entry_list** list) {
	int previous = (*list)->current.nr_of_occurrences;
	ht_entry_list* next = (*list)->next;
	/* entry vrijgeven */
	free_ht_entry((*list)->current);
	/* ht_entry_list vrijgeven */
	free(*list);
	/* Pointer vervangen */
	*list = next;
	return previous;

}

/* Verwijdert het element met een gegeven sleutel uit de hashtabel
   Geeft de oude waarde terug als de sleutel reeds in de hashtabel voorkwam
   Geeft NOT_AN_ELEMENT terug de sleutel niet in de hashtabel voorkwam
   In dat geval wordt uiteraard niets verwijderd */
int ht_remove(hash_table* ht, const char* key) {
	unsigned int hash_index = ht_hash_index(ht, key);
	ht_entry_list** list = &(ht->table_array[hash_index]);
	while ((*list) != NULL) {
		if (strcmp(key, (*list)->current.key) == 0) {
			int previous = ht_remove_entry(list);
			ht->count--;
			rehash(ht);
			return previous;
		}
		list = &((*list)->next);
	}
	/* Element met sleutel kwam niet voor */
	return NOT_AN_ELEMENT;
}

/* Geeft het geheugen gealloceerd door de hashtabel volledig vrij
   Zet de pointer naar de hashtabel op NULL om een dangling pointer te vermijden */
//(signatuur fixed, implementatie voor student)
void ht_destroy(hash_table** ht) {
	int h;
	for (h = 0; h < (*ht)->table_size; h++) {
		while ((*ht)->table_array[h] != NULL) {
			ht_remove_entry(&((*ht)->table_array[h]));
		}
	}
	free((*ht)->table_array);
	free(*ht);
	*ht = NULL;
}

/* Print per index: de index zelf, gevolgd door de sleutels en hun corresponderende waarden in die rij
   Indices zonder sleutels worden niet geprint */
void ht_print(const hash_table* ht) {
	int empty = 1;
	int h,i;
	for (h = 0; h < ht->table_size; h++) {
		if (ht->table_array[h] != NULL) {
			ht_entry_list* list = ht->table_array[h];
			empty = 0;
			printf("Hash index %d:\n", h);
			while (list != NULL) {
				for(i=0;i<list->current.nr_of_occurrences;i++){
					printf("  %s => message %d -- word %d\n", list->current.key, list->current.value[i].messagenr,list->current.value[i].wordnr );
				}
				list = list->next;
			}
		}
	}
	if (empty) {
		printf("Empty hash table_array\n");
	}
}

/* Geeft 0 terug als er niet opnieuw gehasht moet worden
   Geeft de nieuwe tabelgrootte terug als er wel opnieuw gehasht moet worden */
int rehash_table_size(const hash_table* ht) {
	if (ht->count > 8 * ht->table_size) {
		return 16 * ht->table_size;
	}
	else if (ht->table_size > DEFAULT_TABLE_SIZE && ht->table_size > 8 * ht->count) {
		return ht->table_size / 16;
	}
	return 0;
}

/* Hasht opnieuw indien nodig */
void rehash(hash_table* ht) {
	int new_table_size = rehash_table_size(ht);
	if (new_table_size > 0) {
		int h;
		/* Hou oude tabelgrootte en tabelrij bij */
		int old_table_size = ht->table_size;
		ht_entry_list** old_table_array = ht->table_array;
		/* Vervang tabelgrootte en tabelrij */
		ht->table_size = new_table_size;
		ht->table_array = (ht_entry_list**)malloc(ht->table_size * sizeof(ht_entry_list*));
		if (ht->table_array == NULL) {
			printf("ERROR - memory allocation failed\n");
			exit(2);
		}
		for (h = 0; h < ht->table_size; h++) {
			ht->table_array[h] = NULL;
		}
		/* Haal de elementen uit oude tabelrij en voeg ze toe aan nieuwe tabelrij */
		/* Elementen worden gealloceerd, diep gekopieerd, en de oude vrijgegeven */
		/* Liever hergebruiken we gewoon dezelfde elementen en passen de pointers aan */
		for (h = 0; h < old_table_size; h++) {
			while (old_table_array[h] != NULL) {
				ht_entry_list* list = old_table_array[h];
				unsigned int hash_index = ht_hash_index(ht, list->current.key);
				old_table_array[h] = list->next;
				list->next = ht->table_array[hash_index];
				ht->table_array[hash_index] = list;
			}
		}
		free(old_table_array);
	}
}

/* Geeft een hashwaarde terug voor de string sleutel tussen 0 en 2^32-1 */
unsigned int ht_joaat_hash(const char* key) {
	/* Bob Jenkins' JOAAT-functie "Jenkins one at a time" */
	unsigned int hash_value = 0;
	unsigned int i = 0;
	for (i = 0; i < strlen(key); i++){
		hash_value += key[i];
		hash_value += (hash_value << 10);
		hash_value ^= (hash_value >> 6);
	}
	hash_value += (hash_value << 3);
	hash_value ^= (hash_value >> 11);
	hash_value += (hash_value << 15);
	return hash_value;
}
