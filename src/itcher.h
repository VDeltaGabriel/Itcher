#ifndef ITCHER_LIBRARY_H
#define ITCHER_LIBRARY_H

#include "user.h"
#include "auth_server.h"

#define OAUTH_URL "https://itch.io/user/oauth?client_id=%s&scope=%s&redirect_uri=%s"
#define API_URL "https://itch.io/api/1/%s/%s"

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
    char* m_szToken;
} itch_manager;

/*
 * Initialize itch manager
 */
extern int itch_manager_init(itch_manager* manager);

#endif //ITCHER_LIBRARY_H
