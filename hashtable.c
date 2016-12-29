#include "libdependency.h"

hashtable_t *ht_create(int size) {
	hashtable_t *hashtable = NULL;
	
	/*allocate for table*/
	hashtable = malloc(sizeof(hashtable_t));
	
	/*allocate for entry list*/
	hashtable->entry = malloc(sizeof(entry_t)*size);
	
	/*make entry list NULL*/
	memset(hashtable->entry, '\0', size);

	hashtable->size = size;
	return hashtable;
}

unsigned int ht_hash(hashtable_t *hashtable, char *key) {
	unsigned int hashval = 0;
	while ((*key) != '\0') {
		hashval = *key + (hashval << 5) - hashval;
		key++;
	}
	return hashval % hashtable->size;
}

entry_t *ht_new_entry(char *key, char *value) {
	entry_t *new_entry = malloc(sizeof(entry_t));
	new_entry->key = strdup(key);
	new_entry->value = strdup(value);
	new_entry->next = NULL;
	return new_entry;
}

entry_t *ht_entry_search(hashtable_t *hashtable, char *key ) {
	entry_t *entry_list;
	int hashval = ht_hash(hashtable, key);
	for (entry_list = hashtable->entry[hashval]; entry_list != NULL; entry_list = entry_list->next) {
		if (strcmp(entry_list->key, key) == 0) return entry_list;
	}
	return NULL;
}

size_t ht_entry_add(hashtable_t *hashtable, char *key, char *value) {
	
	/*allocate memory for new_list*/
	entry_t *new_list = NULL;
	entry_t *current_list = NULL;
	size_t hashval = ht_hash(hashtable, key);
	/*look for key presence in bucket*/

	current_list = ht_entry_search(hashtable, key);
	if(current_list != NULL) return 2;

	new_list = malloc(sizeof(entry_t));
	new_list = ht_new_entry(key, value);
	new_list->next = hashtable->entry[hashval];
	hashtable->entry[hashval] = new_list;
}


