#include "utils.h"

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

void saveGraph(int* graph, int sideLength){
	char fileName[40] = "graph-";
	strcat(fileName, gettime());

	FILE* graphFile = fopen(fileName, "w");
	
	for(int i = 0; i < sideLength; i++){
		fprintf(graphFile, "%d ", i);
		for(int j = 0; j < sideLength; j++){
			fprintf(graphFile, "%d", graph[i * sideLength + j] * !(i == j));
		}
		fprintf(graphFile, "\n");
	}

	fclose(graphFile);
}
