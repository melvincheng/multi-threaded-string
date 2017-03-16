#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>


typedef struct{
	char c;
	int count;
} node;

char **character;
int length = 0;
int total_length = 0;

int search(char c);
int main(int argc, char *argv[]){
	FILE *fp;
	char string[256];
	char *final_string, *temp;

	character = malloc(0);
	final_string = malloc(0);

	// if(argc < 2){
	// 	fprintf(stderr, "Not enought arguments\n");
	// 	exit(1);
	// }

	fp = fopen("test","r");

	while(fgets(string, 256, fp) != NULL){
		total_length += strlen(string);
		temp = realloc(final_string, sizeof(char) * total_length);
		if(!temp){
			fprintf(stderr, "Unable to realloc\n");
			exit(1);
		}
		final_string = temp;
		strcat(final_string, string);
	}

	printf("%s\n", final_string);

	for(int i = 0; i < total_length; i++){
		search(final_string[i]);
	}

	for(int i = 0; i < length; i++){
		printf("%c: %d\n", character[i][0], character[i][1]);
	}
}

int search(char c){
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