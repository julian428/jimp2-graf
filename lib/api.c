#include "api.h"

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t real_size = size * nmemb;
    struct ResponseBuffer *mem = (struct ResponseBuffer *)userdata;

    char *temp = realloc(mem->data, mem->size + real_size + 1);
    if (temp == NULL) {
        fprintf(stderr, "Not enough memory to store response\n");
        return 0;
    }

    mem->data = temp;
    memcpy(&(mem->data[mem->size]), ptr, real_size);
    mem->size += real_size;
    mem->data[mem->size] = '\0';

    return real_size;
}
char* queryLLM(char* jsonBody) {
    CURL *curl;
    CURLcode res;

    struct ResponseBuffer response = {NULL, 0};

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (!curl) {
        curl_global_cleanup();
        return NULL;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/chat");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "LLM request failed: %s\n", curl_easy_strerror(res));
        free(response.data);
        response.data = NULL;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return response.data;
}
