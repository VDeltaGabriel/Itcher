#include <curl/curl.h>
#include "itcher.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

itch_manager g_itchManager;
itch_manager* g_pItchManager = &g_itchManager;

int itcher_init(const char* callback_url) {
    strcpy(g_itchManager.m_oauth_url, callback_url);

    return 0;
}

void itcher_shutdown(void) {
    free(g_pItchManager);
}