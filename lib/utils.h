#ifndef _UTILS_H

#include<time.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<cjson/cJSON.h>

char* gettime();
void generateGraphRepresentation(int*, int);
void cleanDoubleConnections(int*, int);
void saveGraph(int*, int);
int isNumber(char*);
char* getJSONFromFile(char*);
char* modifyMessageContent(char*, char*);
char* combineStringArray(char**, int);
char* getMessageContent(const char*);
char** extractValuesFromJson(const char*);
void extractGraphArray(const char*, int*, int);
int convertBoolToInt(char*);

#endif
