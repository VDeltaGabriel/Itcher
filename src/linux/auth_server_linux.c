//
// Created by gabrielv on 11/23/24.
//

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "auth_server.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "logger.h"
#include "config.h"
#include "itcher.h"

int auth_server_run(auth_server* pServer, struct sockaddr* addr, socklen_t* addrlen) {
    int subs = 0;
    pid_t pid;
    while (1) {
        if (subs <= 10) {
            pid = fork();
            subs++;
        }

        if (pid == -1) {
            ERROR("fork() failed");
            return -1;
        }

        if (pid == 0) {
            int csock;
            while (1) {
                csock = accept(pServer->m_socket, addr, addrlen);

                if (csock == -1) {
                    ERROR("accept() failed (%s)\n", strerror(errno));
                    return -1;
                }

                char* header = get_message(csock);
                char req[1024];

                sscanf(header, "GET %s HTTP/1.1", req);
                free(header);

                char response[1024];

                int code = 200;
                char* status = "OK";
                char* type = "text/plain";
                char message[1024];
                if (strncmp(req, "/auth", 4) == 0) {
                    char token[128];
                    sscanf(req, "/auth?tkn=%s", token);
                    snprintf(message, sizeof(message),  "Token Retrieved %s", token);
                    strcpy(g_pItchManager->m_token, token);
                } else if (strcmp(req, "/callback") == 0) {
                    type = "text/html";
                    snprintf(message, sizeof(message), "<!DOCTYPE html><html><head><title>Itcher Auth</title><script>if(window.location.hash){const parsedHash=new URLSearchParams(window.location.hash.substring(1));var req=new XMLHttpRequest();req.open('GET',`http://localhost:%d/auth?tkn=${parsedHash.get('access_token')}`,false);req.send(null);console.log(req.responseText);}</script></head><body><h1>Login successful. You can close this window and go back to the application</h1></body></html>", PORT);
                } else {
                    code = 404;
                    status = "Not Found";
                    snprintf(message, sizeof(message), "Route %s not found.", req);
                }
                snprintf(response, 1024, HTTP_HEADER, code, status, type);
                write_message(csock, response);
                write_message(csock, message);

                close(csock);
            }
        }
    }
    return 0;
}

int auth_server_start(auth_server* pServer) {
    pServer->m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (pServer->m_socket == -1) {
        ERROR("Failed to create socket (%s)\n", strerror(errno));
        return -1;
    }

    const int enable = 1;
    if (setsockopt(pServer->m_socket, SOL_SOCKET, SO_REUSEADDR,
        &enable, sizeof(int)) < 0) {
        ERROR("Failed to set socket option (%s)\n", strerror(errno));
        return -1;
    }

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);

    if (bind(pServer->m_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        ERROR("Failed to bind (%s)\n", strerror(errno));
        return -1;
    }

    if (listen(pServer->m_socket, 10) < 0) {
        ERROR("Failed to listen on socket (%s)\n", strerror(errno));
        return -1;
    }

    int addrlen = sizeof(addr);
    auth_server_run(pServer, (struct sockaddr*)&addr, &addrlen);
    return 0;
}

void auth_server_stop(auth_server* pServer) {
    if (!pServer) return;
    if (!pServer->m_socket) return;
    close(pServer->m_socket);
    pServer->m_socket = 0;
}

auth_server g_authServer;
auth_server* g_pAuthServer = &g_authServer;
