#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>

char* gettime(){
	time_t t;
	time(&t);
	struct tm *tm_info = localtime(&t);

	char* dateBuffer = (char*)malloc(20 * sizeof(char));
	strftime(dateBuffer, 20, "%d.%m.%Y@%H:%M",tm_info);

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


	for(int i = 0; i < vertex; i++){
		for(int j = 0; j < vertex; j++){
			printf("%d", neighbours[i * vertex + j]);
		}
		printf("\n");
	}

	char fileName[30] = "graph-";
	strcat(fileName, gettime());
	printf("%s", fileName);

	free(neighbours);
}
