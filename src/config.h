//
// Created by gabrielv on 11/24/24.
//

#ifndef CONFIG_H
#define CONFIG_H

// Itcher version for Web Server
#define ITCHER_VER "Itcher v1.0.0"

// Itcher Web Server port
#define PORT 32000
// Itcher Web Server IP
#define IP "0.0.0.0"

#define DEAFULT_SCOPE "profile%3Ame"
#define OAUTH_URL "https://itch.io/user/oauth?client_id=%s&scope=%s&response_type=token&redirect_uri=%s"
#define API_URL "https://itch.io/api/1/%s/%s"

#endif //CONFIG_H
