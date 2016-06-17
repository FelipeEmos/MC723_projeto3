#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	int i;
	char** argv_cpy = (char**) malloc(argc * sizeof(char*));
	
	
	for(i = 0; i < argc; i++){
		argv_cpy[i] = (char*) malloc(strlen(argv[i]) * sizeof(char));
		strcpy(argv_cpy[i], argv[i]);
	}

	for(i = 0; i < argc; i++){
		printf("argv[%d] = %s\n--argv_cpy[%d] = %s\n", i, argv[i], i, argv_cpy[i]);
	}

	return 0;
}
