//
// Created by gabrielv on 11/23/24.
//

#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include "config.h"

#define HTTP_HEADER "HTTP/1.0 %d %s\nServer: " ITCHER_VER "\nContent-Type: %s\n\n"

typedef struct auth_server {
    int m_socket;
    int m_serverFd;
} auth_server;

typedef struct http_request {
    int m_returnCode;
    char* m_fileName;
} http_request;

extern int auth_server_start(auth_server* pServer);
extern void auth_server_stop(auth_server* pServer);

extern char* get_message(int fd);
extern int write_message(int fd, const char* message);

extern auth_server *g_pAuthServer;

#endif //AUTH_SERVER_H
