#include "userinput.h"

int* getInput(char* u_random, char* u_userDefined, char* u_directional){
	if(!isNumber(u_random) || !isNumber(u_userDefined) || !isNumber(u_directional) > 1) return NULL;

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
}
