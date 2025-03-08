#include "userinput.h"

int* getInput(char* u_random, char* u_userDefined, char* u_directional){
	if(!isNumber(u_random) || !isNumber(u_userDefined) || !isNumber(u_directional)) return NULL;

	int random, userDefined, directional;

	if(u_random) random = atoi(u_random);
	else random = 1;

	if(u_userDefined) userDefined = atoi(u_userDefined);
	else userDefined = 0;

	if(u_directional) directional = atoi(u_directional);
	else directional = 1;
	
	int* inputs = (int*)malloc(3*sizeof(int));
	inputs[0] = random;
	inputs[1] = userDefined;
	inputs[2] = directional;

	return inputs;
}

void getGraphFromUser(int* array, int sideLength){
	printf("Podaj z którymi krawędziami ma się łączyć aktualna krawędź (1 - połączenie, 0 - brak połączenia).\n  ");
	for(int i = 0; i < sideLength; i++) printf("%d ", i);
	printf("\n");
	
	for(int i = 0; i < sideLength; i++){
		printf("%d ", i);
		char* line;
		size_t len = 0;

		if(getline(&line, &len, stdin) != -1){
			char* token = strtok(line, " ");
			char* rest = line;

			for(int j = 0; token != NULL; j++){
				array[i * sideLength + j] = atoi(token);
				token = strtok(NULL, " ");
			}
		}
	}
}
