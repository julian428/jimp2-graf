#include "userinput.h"

int* getInput(char* u_edges, char* u_userDefined, char* u_directional){
	if(!isNumber(u_edges) || !isNumber(u_userDefined) || !isNumber(u_directional)) return NULL;

	int edges, userDefined, directional;

	if(u_edges) edges = atoi(u_edges);
	else edges = 1;

	if(u_userDefined) userDefined = atoi(u_userDefined);
	else userDefined = 0;

	if(u_directional) directional = atoi(u_directional);
	else directional = 1;

	if(edges < 1) edges = 1;
	if(userDefined < 0 || userDefined > 2) userDefined = 0;
	if(directional != 0 || directional != 1) directional = 0;
	
	int* inputs = (int*)malloc(3*sizeof(int));
	inputs[0] = edges;
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
				int connection = atoi(token);
				if(connection < 0) connection = 0;
				if(connection > 1) connection = 1;

				array[i * sideLength + j] = connection;
				token = strtok(NULL, " ");
			}
		}
	}
}
