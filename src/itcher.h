#ifndef ITCHER_LIBRARY_H
#define ITCHER_LIBRARY_H

#include "user.h"
#include "auth_server.h"

/*
 * TODO: Finish basic API communication,
 * add DRM for both in-app and standalone products
 */

typedef enum api_endpoint {
    GET_PROFILE,
    DRM,
    CRED_INFO
} api_endpoint;

static const char* getEndpoint(api_endpoint endpoint) {
    switch (endpoint) {
        case CRED_INFO:
            return "credentials/info";
        default:
        case GET_PROFILE:
            return "me";
        case DRM:
            return "game/%s/download_keys?user_id=%d";
    }
}

typedef struct itch_manager {
    char* m_oauth_url;
    char* m_token;
} itch_manager;

/*
 * Initialize itch manager
 */
extern int itcher_init(const char* callback_url);
extern void itcher_shutdown(void);

extern itch_manager* g_pItchManager;

#endif //ITCHER_LIBRARY_H
