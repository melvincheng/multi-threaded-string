#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>


typedef struct{
	char c;
	int count;
} char_count_t;

typedef struct{
	char *prev_string;
	char *new_string;
}replace_table_t;

typedef struct {
	char *string;
	int count;
} string_count_t;


int char_search(char c);
int word_replace(char *old_string, replace_table_t *table);
void replace_table_insert(replace_table_t **table, char* prev_string, char* new_string);
int contain_subtring(char *old_string, char *sub_string, int sub_string_initial);
int word_search(char *string);

char_count_t *character;
string_count_t *words;
char **replace_character;
char **string_array;
int length = 0;
int string_count_length = 0;
int replace_length = 0;
int table_size = 0;
int total_words = 0;

int main(int argc, char *argv[]){
	replace_table_t *table;
	FILE *fp_input, *fp_replace;
	char string[256];
	char **final_string, *temp_char, *token, *temp_final_string;
	char *prev_string = NULL;
	char *new_string = NULL;
	int total_length = 0;
	
	character = NULL;
	replace_character = NULL;
	final_string = NULL;
	table = NULL;
	string_array = NULL;
	words = NULL; 

	if(argc < 2){
		fprintf(stderr, "Not enought arguments\n");
		exit(1);
	}

	fp_input = fopen(argv[1],"r");
	if(!fp_input){
		fprintf(stderr, "No input file found\n");
		exit(-1);
	}

	// reading replace file and putting it into a table
	fp_replace = fopen("replace", "r");

	if(fp_replace){
		while(fgets(string, 256, fp_replace) != NULL){
			prev_string = strtok(string, " \n\r\t");
			new_string = strtok(NULL, " \n\r\t");	
			replace_table_insert(&table, prev_string, new_string);			
		}
	}

	// reads the input file and puts the entire file into a single string
	// while(fgets(string, 256, fp_input) != NULL){
	// 	total_length += strlen(string);
	// 	temp_char = realloc(final_string, sizeof(char) * total_length);
	// 	if(!temp_char){
	// 		fprintf(stderr, "Unable to realloc\n");
	// 		exit(-1);
	// 	}
	// 	final_string = temp_char;
	// 	strcat(final_string, string);
	// }

	char temp_string[256];
	char **char_arr = NULL;
	int total = 0;
	while(fscanf(fp_input, "%s", temp_string) > 0){
		// printf("%s\n", temp_string);
		// total_length += strlen(temp_string);
		final_string = realloc(final_string, sizeof(char*) * ++total);
		final_string[total - 1] = malloc(256);
		strcpy(final_string[total - 1], temp_string);
		// strcat(final_string, temp_string);
		total_length++;
	}

	// for(int i = 0; i < length; i++){
	// 	printf("%s\n", final_string[i]);
	// }
	// printf("done\n");
	// copies the string so that the final string is not affected
	// temp_final_string = malloc(sizeof(char) * strlen(final_string));
	// strcpy(temp_final_string, final_string);

	// seperates words into another array
	// int final_string_length_counter = 0;
	// token = strtok(final_string, " \n\r\t");
	// while(token){
	// 	final_string_length_counter += strlen(token);
		
	// 	total_words++;
	// 	printf("%s\n", token);
	// 	printf("%d\n", total_words);
	// 	printf("%d\n", strlen(token));
	// 	string_array = realloc(string_array, sizeof(char*) * total_words);
	// 	string_array[total_words - 1] = (char*)malloc(sizeof(char) * strlen(token));

	// 	strcpy(string_array[total_words - 1], token);

	// 	while(final_string[final_string_length_counter] == ' ' ||
	// 		final_string[final_string_length_counter] == '\r' ||
	// 		final_string[final_string_length_counter] == '\n' ||
	// 		final_string[final_string_length_counter] == '\t' ||
	// 		final_string[final_string_length_counter] == NULL){
	// 		if(final_string[final_string_length_counter] == ' ' ||
	// 			final_string[final_string_length_counter] == NULL){
	// 			total_words++;
	// 			string_array = realloc(string_array, sizeof(char*) * total_words);
	// 			string_array[total_words - 1] = malloc(sizeof(char) * 1);
	// 			strcpy(string_array[total_words - 1], " ");
	// 			final_string_length_counter++;
	// 		}else if(final_string[final_string_length_counter] == '\n'){
	// 			total_words++;
	// 			string_array = realloc(string_array, sizeof(char*) * total_words);
	// 			string_array[total_words - 1] = malloc(sizeof(char) * 1);
	// 			strcpy(string_array[total_words - 1], "\n");
	// 			final_string_length_counter++;
	// 		}else if(final_string[final_string_length_counter] == '\t'){
	// 			total_words++;
	// 			string_array = realloc(string_array, sizeof(char*) * total_words);
	// 			string_array[total_words - 1] = malloc(sizeof(char) * 1);
	// 			strcpy(string_array[total_words - 1], "\t");
	// 			final_string_length_counter++;
	// 		}else if(final_string[final_string_length_counter] == '\r'){
	// 			final_string_length_counter++;
	// 		}
	// 		// sleep(1);
	// 		// printf("%d\r", (int)final_string[final_string_length_counter]);
	// 	}
	// 	token = strtok(NULL, " \n\r\t");
	// }

	// total_words++;
	// string_array = realloc(string_array, sizeof(char*) * total_words);
	// string_array[total_words - 1] = malloc(sizeof(char) * 1);
	// strcpy(string_array[total_words - 1], "\n");
	// printf("done\n");

	// for(int i = 0; i < table_size; i++){
	// 	printf("%s %s\n", table[i].prev_string, table[i].new_string);
	// }

	// for(int i = 0; i < total_words; i++){
	// 	printf("%s\n", string_array[i]);
	// }

	// printf("Before replacements\n");
	// printf("-----\n");
	// for(int i = 0; i < total_words; i++){
	// 	printf("%s", string_array[i]);
	// }
	// printf("-----\n\n");


	// count characters
	#pragma omp parallel num_threads(100)
	{
		#pragma omp for
		// #pragma omp parallel for num_threads(1)
		// for(int i = 0; i < total_length; i++){
		// 	for(int j = 0; j < strlen(final_string[i]); j++){
		// 		char_search(final_string[i][j]);
		// 	}
		// }
		for(int i = 0; i < total_length; i++){
			for(int j = 0; j < strlen(final_string[i]); j++){
				char_search(final_string[i][j]);
			}
			word_search(final_string[i]);
		}

		#pragma omp for
		for(int i = 0; i < total_length; i++){
			word_replace(final_string[i], table);
		}
	}

	// char count
	printf("Character count\n");
	printf("-----\n");
	for(int i = 0; i < length; i++){
		printf("%c: %d\n", character[i].c, character[i].count);
	}
	printf("-----\n\n");


	// word count
	printf("Word count\n");
	printf("-----\n");
	for(int i = 0; i < string_count_length; i++){
		printf("%s: %d\n", words[i].string, words[i].count);
	}
	printf("-----\n\n");


	// printf("After replacements\n");
	// printf("-----\n");
	// for(int i = 0; i < total_words; i++){
	// 	printf("%s", string_array[i]);
	// }

	fclose(fp_input);
}



int char_search(char c){
	int exit = 1;
	if(c == '\n' || c == '\r' || c == ' ' || c == '\t'){
		return 1;
	}
	#pragma omp critical (character_count)
	{
		for(int i = 0; i < length; i++){
			if(character[i].c == c){
				character[i].count++;
				exit = 0;
			}
		}
		if(exit == 1){
			character = realloc(character, (length + 1) * sizeof(char_count_t));

			character[length].c = c;
			character[length].count = 1;
			length++;
		}
	}
	return 1;
}

int word_search(char *string){
	int exit = 1;
	if(strcmp(string, "\n") == 0 || 
		strcmp(string, "\r") == 0 ||
		strcmp(string, " ") == 0 ||
		strcmp(string, "\t") == 0){
		return 1;
	}

	#pragma omp critical (word_count)
	{
		for(int i = 0; i < string_count_length; i++){
			if(strcmp(words[i].string, string) == 0){
				words[i].count++;
				exit = 0;
				// return 0;
			}
		}
		if(exit == 1){
			words = realloc(words, (string_count_length + 1) * sizeof(string_count_t));
			words[string_count_length].string = malloc(sizeof(char) * strlen(string));
			strcpy(words[string_count_length].string, string);
			words[string_count_length].count = 1;
			string_count_length++;
		}
	}
	return 1;
}

int word_replace(char *old_string, replace_table_t *table){
	// int contains = 1;
	if(*old_string == '\n' || *old_string == '\r' || *old_string == ' '){
		return 1;
	}
	for(int i = 0; i < table_size; i++){
		for(int j = 0; j < strlen(table[i].prev_string); j++){
			// contains = contain_subtring(old_string, table[i].prev_string, j);
			if(strcmp(old_string, table[i].prev_string) == 0){
				strcpy(old_string, table[i].new_string);
			}else{
				break;
			}
			// if(contains == 1){
			// 	break;
			// }else if(contains == 0){
			// 	strcpy(old_string, table[i].new_string);
			// 	return 0;
			// }
		}
	}
	return 1;
}
// int contain_subtring(char *old_string, char *sub_string, int sub_string_initial){
// 	for(int k = 0; k < strlen(sub_string); k++){
// 		if(strlen(old_string - sub_string_initial) < strlen(sub_string)){
// 			return 1;
// 		}
// 		if(old_string[k + sub_string_initial] != sub_string[k]){
// 			return 1;
// 		}
// 	}
// 	return 0;
// }

void replace_table_insert(replace_table_t **table, char* prev_string, char* new_string){
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