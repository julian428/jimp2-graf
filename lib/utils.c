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

int isNumber(char* s){
	if (!s || *s == '\0') return 0;  // Empty or NULL string is invalid

	for (int i = 0; s[i] != '\0'; i++) {
		if (!isdigit((unsigned char)s[i])) return 0;
	}
	return 1;
}

char* getJSONFromFile(char* fileName){
	FILE* jsonFile = fopen(fileName, "rb");
	if(!jsonFile){
		perror("Nie udało się otworzyć pliku z zapytaniem.");
		return NULL;
	}

	fseek(jsonFile, 0, SEEK_END);
	long fileSize = ftell(jsonFile);
	rewind(jsonFile);

	char* buffer = (char*)malloc(fileSize + 1);
	fread(buffer, 1, fileSize, jsonFile);
	buffer[fileSize] = '\0';

	fclose(jsonFile);
	return buffer;
}

char* modifyMessageContent(char *jsonString, char *newContent) {
	cJSON *json = cJSON_Parse(jsonString);
	free(jsonString);

	if (!json) {
		perror("Error parsing JSON!\n");
		return NULL;
	}

	cJSON *messages = cJSON_GetObjectItem(json, "messages");
	if (!cJSON_IsArray(messages)) {
		perror("\"messages\" is not an array!\n");
		cJSON_Delete(json);
		return NULL;
	}

	cJSON *firstMessage = cJSON_GetArrayItem(messages, 0);
	if (!firstMessage) {
		perror("No messages found!\n");
		cJSON_Delete(json);
		return NULL;
	}

	cJSON *contentField = cJSON_GetObjectItem(firstMessage, "content");
	if (contentField) {
		cJSON_SetValuestring(contentField, newContent);
	} else {
		perror("\"content\" field not found!\n");
		cJSON_Delete(json);
		return NULL;
	}

	char *modifiedJsonString = cJSON_Print(json);
	cJSON_Delete(json);

	return modifiedJsonString;
}

char* combineStringArray(char** strings, int length){
	int combinedLength = 1; // zaczyna się od jeden bo '\0'

	for(int i = 0; i < length; i++){
		combinedLength += strlen(strings[i]) + 1;
	}

	char* combinedString = (char*)malloc(combinedLength);
	combinedString = '\0';
	for(int i = 0; i < length; i++){
		strcat(combinedString, strings[i]);
		if(i < length - 1) strcat(combinedString, " ");
	}

	return combinedString;
}
