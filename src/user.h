//
// Created by gabrielv on 11/14/24.
//

#ifndef ITCHER_USER_H
#define ITCHER_USER_H

#include <stdint.h>

typedef struct itch_user_s {
    unsigned int m_id;
    uint8_t m_type_flags;
    uint8_t m_gamer;
    uint8_t m_press;
    uint8_t m_developer;
    char* m_username;
    char* m_display_name;
    char* m_cover_url;
    char* m_user_url;
} itch_user_t;

#endif //ITCHER_USER_H