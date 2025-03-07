#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "lib/userinput.h"

char* gettime(){
	time_t t;
	time(&t);
	struct tm *tm_info = localtime(&t);

	char* dateBuffer = (char*)malloc(30 * sizeof(char));
	strftime(dateBuffer, 30, "%d.%m.%Y@%H:%M.txt",tm_info);

	return dateBuffer;
}

void generateGraphRepresentation(int* array, int sideLength){
	for(int i = 0; i < sideLength; i++){
		for(int j = 0; j < sideLength; j++){
			int *current_node = &array[i * sideLength + j];
			*current_node = round((double)rand()/RAND_MAX);
		}
	}
}

void cleanDoubleConnections(int* array, int sideLength){
	for(int i = 0; i < sideLength; i++){
		for(int j = 0; j < sideLength; j++){
			int *current_node = &array[i * sideLength + j];
			int connection = array[j * sideLength + i];
			if(connection == 1) *current_node = 0;
		}
	}
}

int main(int argc, char** argv){
	int* inputs = getInput(argv[1], argv[2], argv[3]);
	int vertex = inputs[0];
	int userDefined = inputs[1];
	int directional = inputs[2];

	srand(time(NULL));

	int* neighbours = (int*)malloc(vertex*vertex*sizeof(int));
	generateGraphRepresentation(neighbours, vertex);
	if(directional == 1) cleanDoubleConnections(neighbours, vertex);

	char fileName[40] = "graph-";
	strcat(fileName, gettime());

	FILE* graphFile = fopen(fileName, "w");
	
	for(int i = 0; i < vertex; i++){
		fprintf(graphFile, "%d ", i);
		for(int j = 0; j < vertex; j++){
			fprintf(graphFile, "%d", neighbours[i * vertex + j] * !(i == j));
		}
		fprintf(graphFile, "\n");
	}

	fclose(graphFile);
	free(neighbours);
}
