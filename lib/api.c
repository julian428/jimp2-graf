#include "api.h"

int* getGraphFromLLM(char* prompt){
	CURL* curl;
	CURLcode res;

	const char* jsonBody = "";

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if(!curl){
		curl_global_cleanup();
		return NULL;
	}

	curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/chat");
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody);

	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "Content-Type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	res = curl_easy_perform(curl);

	if(res != CURLE_OK)
		fprintf(stderr, "LLM request failed: %s", curl_easy_strerror(res));
	else
		printf("success");

	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}
