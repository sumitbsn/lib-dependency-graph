#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct entry_s {
	char *key;
	char *value;
	struct entry_s *next;
}entry_t;

typedef struct hashtable_s {
	int size;
	struct entry_s **entry;
}hashtable_t;


#endif