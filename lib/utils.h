#ifndef _UTILS_H

#include<time.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

char* gettime();
void generateGraphRepresentation(int*, int);
void cleanDoubleConnections(int*, int);
void saveGraph(int*, int);
int isNumber(char*);

#endif
