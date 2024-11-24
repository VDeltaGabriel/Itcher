//
// Created by gabrielv on 11/24/24.
//
#include "auth_server.h"

#include <logger.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* get_message(int fd) {
    FILE* stream = fdopen(fd, "r");
    if (stream == NULL) {
        ERROR("Error opening file descriptor in get_message()\n");
        return NULL;
    }

    size_t size = 1;

    char* block;
    if ((block = malloc(sizeof(char) * size)) == NULL) {
        ERROR("Error allocating memory for block\n");
        return NULL;
    }
    *block = '\0';

    char *tmp;
    if( (tmp = malloc(sizeof(char) * size)) == NULL )
    {
        ERROR("Error allocating memory for temp block\n");
        return NULL;
    }
    *tmp = '\0';

    int end;
    size_t oldsize = 1;

    while( (end = getline( &tmp, &size, stream)) > 0)
    {
        if( strcmp(tmp, "\r\n") == 0) break;

        block = realloc(block, size+oldsize);
        oldsize += size;
        strcat(block, tmp);
    }

    // Free tmp. No longer needed
    free(tmp);

    // Return the header
    return block;
}

int write_message(int fd, const char* message) {
    return write(fd, message, strlen(message));
}