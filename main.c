#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>

char* gettime(){
	time_t t;
	time(&t);
	struct tm *tm_info = localtime(&t);

	char* dateBuffer = (char*)malloc(30 * sizeof(char));
	strftime(dateBuffer, 30, "%d.%m.%Y@%H:%M.txt",tm_info);

	return dateBuffer;
}

int main(int argc, char** argv){
	int vertex = atoi(argv[1]);
	int userDefined = atoi(argv[2]);
	int directional = atoi(argv[3]);
	srand(time(NULL));

	int* neighbours = (int*)malloc(vertex*vertex*sizeof(int));

	for(int i = 0; i < vertex; i++){
		for(int j = 0; j < vertex; j++){
			int *current_node = &neighbours[i * vertex + j];
			*current_node = round((double)rand()/RAND_MAX);
			int connection = neighbours[j * vertex + i];
			if(!directional && connection == 1) *current_node = 0;
		}
	}

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
