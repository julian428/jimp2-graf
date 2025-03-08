#ifndef _API_H

#include<curl/curl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ResponseBuffer {
    char *data;
    size_t size;
};


char* queryLLM(char*);

#endif
