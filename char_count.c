#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>


typedef struct{
	char c;
	int count;
} node;

typedef struct{
	char *prev_string;
	char *new_string;
}replace_table_t;


int char_search(char c);
int char_replace(char *old_c, char new_c);
void replace_insert(replace_table_t **table, char* prev_string, char* new_string);

char **character;
char **replace_character;
char **string_array;
int length = 0;
int replace_length = 0;
int table_size = 0;
int total_words = 0;

int main(int argc, char *argv[]){
	(void)argc;
	(void)argv;
	replace_table_t *table;
	FILE *fp_input, *fp_replace;
	char string[256];
	char *final_string, *temp_char, *token, *temp_final_string;
	char *prev_string = NULL;
	char *new_string = NULL;
	int total_length = 0;
	
	

	character = NULL;
	replace_character = NULL;
	final_string = NULL;
	table = NULL;
	string_array = NULL;

	// if(argc < 2){
	// 	fprintf(stderr, "Not enought arguments\n");
	// 	exit(1);
	// }

	fp_input = fopen("input","r");
	if(!fp_input){
		fprintf(stderr, "No input file found\n");
		exit(-1);
	}

	// reading replace file and putting it into a table
	fp_replace = fopen("replace", "r");
	if(fp_replace){
		while(fgets(string, 256, fp_replace) != NULL){
			prev_string = strtok(string, " \n");
			new_string = strtok(NULL, " \n");		
			replace_insert(&table, prev_string, new_string);
		}
	}

	// reads the input file and puts the entire file into a single string
	while(fgets(string, 256, fp_input) != NULL){
		total_length += strlen(string);
		temp_char = realloc(final_string, sizeof(char) * total_length);
		if(!temp_char){
			fprintf(stderr, "Unable to realloc\n");
			exit(-1);
		}
		final_string = temp_char;
		strcat(final_string, string);
	}

	// copies the string so that the final string is not affected
	temp_final_string = malloc(sizeof(char) * strlen(final_string));
	strcpy(temp_final_string, final_string);

	// seperates words into another array
	token = strtok(temp_final_string, " \n\r\t");
	while(token){
		total_words++;
		string_array = realloc(string_array, sizeof(char*) * total_words);
		string_array[total_words - 1] = malloc(sizeof(char) * strlen(token));
		strcpy(string_array[total_words - 1], token);
		token = strtok(NULL, " \n\r\t");
	}

	for(int i = 0; i < total_length; i++){
		char_search(final_string[i]);
	}

	if(fp_replace){

		char_replace(&final_string[i]);
	}
	printf("%s\n", final_string);

	for(int i = 0; i < length; i++){
		printf("%c: %d\n", character[i][0], character[i][1]);
	}

	fclose(fp_input);
}



int char_search(char c){
	char *inner_array;
	if(c == '\n' || c == '\r' || c == ' '){
		return 1;
	}
	for(int i = 0; i < length; i++){
		if(character[i][0] == c){
			character[i][1] += 1;
			return 0;
		}
	}
	character = realloc(character, (length + 1) * sizeof(char*));
	inner_array = malloc(sizeof(char) * 2 * (length + 1));
	character[length] = inner_array;

	character[length][0] = c;
	character[length][1] = 1;
	length++;
	return 1;
}

int char_replace(char *c, replace_table_t *table){
	if(*c == '\n' || *c == '\r' || *c == ' '){
		return 1;
	}
	for(int i = 0; i < table_size; i++){
		for(int j = 0)
	}

	return 1;
}

void replace_insert(replace_table_t **table, char* prev_string, char* new_string){
	replace_table_t *temp_table;

	temp_table = *table;
	temp_table = realloc(temp_table, sizeof(replace_table_t) * (table_size + 1));

	temp_table[table_size].prev_string = malloc(sizeof(char) * strlen(prev_string));
	temp_table[table_size].new_string = malloc(sizeof(char) * strlen(new_string));

	strcpy(temp_table[table_size].prev_string, prev_string);
	strcpy(temp_table[table_size].new_string, new_string);

	*table = temp_table;

	table_size++;
}

// void replace(replace_table_t *table, char ***final_string){
// 	char **
// }