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
	char* task = argv[2];
	srand(time(NULL));

	int* neighbours = (int*)malloc(vertex*vertex*sizeof(int));

	for(int i = 0; i < vertex; i++){
		for(int j = 0; j < vertex; j++){
			neighbours[i * vertex + j] = round((double)rand()/RAND_MAX);
		}
	}

	char fileName[40] = "graph-";
	strcat(fileName, gettime());

	FILE* graphFile = fopen(fileName, "w");
	
	for(int i = 0; i < vertex; i++){
		fprintf(graphFile, "%d ", i);
		for(int j = 0; j < vertex; j++){
			fprintf(graphFile, "%d", neighbours[i * vertex + j]);
		}
		fprintf(graphFile, "\n");
	}

	free(neighbours);
}
