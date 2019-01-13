#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#define DEFAULT_TABLE_SIZE 16
#define NOT_AN_ELEMENT -1

typedef struct indx{
	int messagenr; /* nummer van het bericht waarin het woord voorkomt */
	int wordnr; /* volgnummer van het woord in het bericht */
} indx;

/*
Combinatie van sleutel met een geassocieerde waarde
Deze waarde is een array van indexes. Het aantal indexes wordt opgeslagen in nrofoccurences
*/
typedef struct ht_entry {
	char* key; /* sleutel == te indexeren woord */
	int nr_of_occurrences; /* aantal indices == lengte van value array */
	indx* value; /* array met de indices waarop key voorkomt*/
} ht_entry;

/*
Vrijgeven van een hash table entry.
*/
void free_ht_entry(ht_entry ht);

/*
Struct met ht_entry en een pointer naar het volgende element van de gelinkte lijst
*/
typedef struct ht_entry_list {
	ht_entry current;
	struct ht_entry_list* next;
} ht_entry_list;

/*
Hashtabel die ook tabelgrootte en aantal elementen bijhoudt
*/
typedef struct hash_table {
	int table_size;
	int count;
	ht_entry_list** table_array;
} hash_table;


/* Creert een hashtabel
   Alloceert daar voldoende geheugenruimte voor
   Geeft een pointer terug die wijst naar deze nieuw gealloceerde structuur
   De tabelrij krijgt als tabelgrootte DEFAULT_TABLE_SIZE */
hash_table* ht_create();

/* Geeft de waarde terug die in de hashtabel met de sleutel geassocieerd wordt
   Geeft NOT_AN_ELEMENT terug als de sleutel niet in de hashtabel voorkomt */
int ht_get_value(const hash_table* ht, const char* key, indx** i);

/* Zorgt ervoor dat de hashtabel de indx met de sleutel associeert.
   Geeft het aantal indexes terug die die na uitvoeren van deze operatie met de sleutel in de hashtabel worden geassocieerd.
   Geeft NOT_AN_ELEMENT terug als een nieuw element in de hashtabel wordt toegevoegd.
   In dat geval wordt van de sleutel een diepe kopie gemaakt */
int ht_set_value(hash_table* ht, const char* key, indx value);


/* Verwijdert een gegeven element
   Geeft het aantal indexes terug die met de sleutel in de hashtabel werden geassocieerd.*/
int ht_remove_entry(ht_entry_list** list);

/* Verwijdert het element met een gegeven sleutel uit de hashtabel
   Geeft de oude waarde terug als de sleutel reeds in de hashtabel voorkwam
   Geeft NOT_AN_ELEMENT terug de sleutel niet in de hashtabel voorkwam
   In dat geval wordt uiteraard niets verwijderd */
int ht_remove(hash_table* ht, const char* key);

/* Geeft het geheugen gealloceerd door de hashtabel volledig vrij
   Zet de pointer naar de hashtabel op NULL om een dangling pointer te vermijden */
void ht_destroy(hash_table** ht);

/* Print per indx: de indx zelf, gevolgd door de sleutels en hun corresponderende waarden in die rij
   Indices zonder sleutels worden niet geprint */
void ht_print(const hash_table* ht);

/* Geeft 0 terug als er niet opnieuw gehasht moet worden
   Geeft de nieuwe tabelgrootte terug als er wel opnieuw gehasht moet worden */
int rehash_table_size(const hash_table* ht);

/* Hasht opnieuw indien nodig */
void rehash(hash_table* ht);

/* Geeft een hashwaarde terug voor de string sleutel tussen 0 en 2^32-1 */
unsigned int ht_joaat_hash(const char* key);


#endif
