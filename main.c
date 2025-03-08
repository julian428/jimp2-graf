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
		char* userPrompt = combineStringArray(&argv[1], argc-1);
		char* jsonBody = getJSONFromFile("data/inputRequest.json");
		char* modifiedJSON = modifyMessageContent(jsonBody, userPrompt);
		char* jsonResponse = queryLLM(modifiedJSON);
		char** responseValues = extractValuesFromJson(getMessageContent(jsonResponse));

		int newVert = atoi(responseValues[0]);
		int newDir = convertBoolToInt(responseValues[1]);
		
		inputs = (int*)malloc(3 * sizeof(int));
		inputs[0] = newVert;
		inputs[1] = 0;
		inputs[2] = newDir;
	}

	int edge = inputs[0];
	int userDefined = inputs[1];
	int directional = inputs[2];

	int* neighbours = (int*)malloc(edge*edge*sizeof(int));

	if(userDefined == 2){
		char* graphCreationPrompt;
		asprintf(&graphCreationPrompt, "Generate a one-dimensional binary adjacency array for an %d × %d grid graph, where index (r * X + c) represents an edge (1 for connected, 0 otherwise)", edge, edge);

		char* jsonBody = getJSONFromFile("data/generationRequest.json");
		char* modifiedJSON = modifyMessageContent(jsonBody, graphCreationPrompt);

		char* jsonResponse = queryLLM(modifiedJSON);
		extractGraphArray(getMessageContent(jsonResponse), neighbours, edge * edge);

		saveGraph(neighbours, edge);
		return 0;
	}

	srand(time(NULL));


	if(userDefined == 0) generateGraphRepresentation(neighbours, edge);
	else getGraphFromUser(neighbours, edge);

	if(directional == 1) cleanDoubleConnections(neighbours, edge);

	saveGraph(neighbours, edge);

	free(neighbours);
	return 0;
}
