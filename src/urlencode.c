//
// Created by gabrielv on 11/24/24.
//

#include "urlencode.h"

#include <ctype.h>
#include <stdio.h>

char enc_tab[256] = {0};

void url_encoder_init(void) {
    for (int i = 0; i < 256; i++)
        enc_tab[i] = (isalnum( i) || i == '*' || i == '-' || i == '.' || i == '_') ? i : (i == ' ') ? '+' : 0;
}

char* url_encode(unsigned char *url, char* out) {
    for (; *url; url++) {
        if (enc_tab[*url]) *out = enc_tab[*url];
        else sprintf(out, "%%%02X", *url);
        while (*++out);
    }
    return out;
}