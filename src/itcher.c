#include <curl/curl.h>
#include "itcher.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "auth_server.h"
#include "logger.h"

int itch_manager_init(itch_manager* manager) {
    manager = (itch_manager*)malloc(sizeof(itch_manager));
    if (!manager) return -1;

    return 0;
}

int main(int argc, char** argv) {
    printf("Starting auth server\n");
    if (auth_server_start(g_pAuthServer) != 0) {
        printf("Failed to start auth server\n");
        return -1;
    }
    while (1) {
        printf("> ");
        char cmd[64];
        scanf("%s", cmd);

        if (strcmp(cmd, "exit") == 0) {
            break;
        }
    }
    printf("Stopping auth server\n");
    auth_server_stop(g_pAuthServer);
    return 0;
}