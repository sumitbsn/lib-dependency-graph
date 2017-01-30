/***************************************File Name: libdependency.c**************************************************/
/************************************************Author: Sumit Kumar************************************************/
/**********************************Header File Name: "libdependency.h"**********************************************/
/*******************************************LICENSE: MIT License****************************************************/
/****************************************Copyright (c) [2016] [sumit kumar]*****************************************/

#include "libdependency.h"
	
hashtable_t *hashtable = NULL;
entry_t *entry = NULL;;

char *processed[SIZE] = {0};
int count = 0;

int search(char *processed[], char *lib_path) {
 	int i = 0;
 	for (i=0; i < count; i++) {
 		if (strcmp( processed[i], lib_path) == 0) return 0;
 	}
 	return -1;
}

int add(char *processed[], char *lib_path)
{
	processed[count] = malloc(strlen(lib_path)+1);
	memset(processed[count], 0, strlen(lib_path)+1);
	strcpy(processed[count], lib_path);
	count++;
}

int readelf(char *lib_path)
{

	if (count != 0 && (search(processed, lib_path) == 0) )   
		return;

	add(processed, lib_path);
	
	char *deps[SIZE];
	char command[SIZE] ;
	memset(command, 0, SIZE );
	sprintf(command, "readelf -a %s | grep NEEDED | awk -F ' ' '{print $5}' | tr -d '[]'", lib_path);
	
	FILE *readelf_open = popen(command, "r");
	if(readelf_open == NULL) {
		printf("open err\n");
		return -1;
	}	
	char *line = 0;
	ssize_t len;
	char *parent_lib_name = NULL;
	parent_lib_name = basename(lib_path);
	int dep_count = 0, m = 0;

	printf("%-20s -> ", parent_lib_name);

	while(getline(&line, &len, readelf_open) != -1)
	{	
		int i = 0;
		while(line[i] != '\n') i++; line[i] = '\0';
		
		deps[dep_count] = malloc(sizeof(char)*(i+1));
		memset(deps[dep_count], 0, i+1);
		strncpy(deps[dep_count], line, i);
		deps[dep_count++][i] = '\0';
	}


	for (m=0; m<dep_count; m++) {
		printf("%20s", deps[m]);
	}

	printf("\n");

	for (m=0; m<dep_count; m++) {
		entry = (entry_t *)ht_entry_search(hashtable, deps[m]);
		if (entry == NULL) {
			printf("Error: ldd could't find element: %s\n", deps[m]);
			continue;
		}
		
		if( access(entry->value, F_OK) != -1 ){
			readelf(entry->value);			
		}	
	}
	pclose(readelf_open);
}

int ldd(char *lib_path)
{
	int node_count = 0;
	char command[SIZE] ;
	memset(command, 0, SIZE );
	sprintf(command, "ldd %s | awk -F ' ' '{print $1 \"\t\" $3}'", lib_path);
	FILE *ldd_open = popen(command, "r");
	if(ldd_open == NULL) 
	{
		printf("open err\n");
		return -1;
	}	
	char *line = 0;
	ssize_t len;

	hashtable = (hashtable_t *)ht_create(50);

	while(getline(&line, &len, ldd_open) != -1)
	{
		char key[SIZE], val[SIZE];
		memset(key, 0, SIZE);
		memset(val, 0, SIZE);
		sscanf(line, "%s %s", key, val);
		
		ht_entry_add(hashtable, basename(key) , (val));
		node_count++;
	}
	pclose(ldd_open);
	return node_count;
}
int main(int argc, char **argv)
{
	if(argc ==2) 
	{
		ldd(argv[1]);
		printf("\n\n********************************************************TABLE VIEW OF LIBRARY DEPENDENCY*************************************************************\n");
		readelf(argv[1]);
		printf("********************************************************************END******************************************************************************\n");
	}
	if((argc < 2) || (argc > 2))
		printf("Invalid Input\n");
	//cleanup
	return 0;
}	
