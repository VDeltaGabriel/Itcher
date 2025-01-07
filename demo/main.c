//
// Created by gabrielv on 11/24/24.
//
#include <stdio.h>
#include <string.h>
#include "itcher.h"

int main(int argc, char** argv) {
    itcher_init("http://localhost:32000/callback");

    while (1) {
        printf("> ");
        char cmd[64];
        scanf("%s", cmd);

        if (strcmp(cmd, "exit") == 0) {
            break;
        }
    }
    itcher_shutdown();
    return 0;
}