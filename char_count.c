#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
	FILE *fp;
	char character[];

	if(argc < 2){
		exit(0);
	}

	fp = fopen(argv[1],"r");
}
