#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int main(int argc, char** argv){
	int vertex = atoi(argv[1]);
	char* polecenie = argv[2];
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
	free(neighbours);
}
