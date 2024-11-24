#include <curl/curl.h>
#include "itcher.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "auth_server.h"
#include "logger.h"

itch_manager g_itchManager;
itch_manager* g_pItchManager = &g_itchManager;

int itcher_init(const char* callback_url) {
    if (auth_server_start(g_pAuthServer) != 0) {
        printf("Failed to start auth server\n");
        return -1;
    }

    strcpy(g_itchManager.m_oauth_url, callback_url);

    return 0;
}

void itcher_shutdown(void) {
    auth_server_stop(g_pAuthServer);
}