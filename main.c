#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#include "lib/userinput.h"
#include "lib/utils.h"
#include "lib/api.h"

#define SARG(n) ((argc > (n)) ? argv[(n)] : NULL) // zwraca podany argument jeżeli został podany

int main(int argc, char** argv){
	int* inputs = getInput(SARG(1), SARG(2), SARG(3));

	if(inputs == NULL){
		char* modifiedJSON = modifyMessageContent(getJSONFromFile("data/request.json"), SARG(1));
		printf("%s\n", modifiedJSON);
		queryLLM(modifiedJSON);
		return 0;
	}

	int vertex = inputs[0];
	int userDefined = inputs[1];
	int directional = inputs[2];

	srand(time(NULL));

	int* neighbours = (int*)malloc(vertex*vertex*sizeof(int));

	if(userDefined == 0) generateGraphRepresentation(neighbours, vertex);
	else getGraphFromUser(neighbours, vertex);

	if(directional == 1) cleanDoubleConnections(neighbours, vertex);

	saveGraph(neighbours, vertex);

	free(neighbours);
	return 0;
}
