//
// Created by gabrielv on 11/23/24.
//
#include "auth_server.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "logger.h"


class AuthServerWindows : public AuthServer {
public:
    AuthServerWindows();
    ~AuthServerWindows();

    virtual int StartServer();
};

AuthServerWindows::AuthServerWindows() {}

int AuthServerWindows::StartServer() {
    if ((m_hSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ERROR("Failed to create socket");
        return -1;
    }

    return 0;
}

AuthServer* g_pAuthServer = new AuthServerWindows();
