//
// Created by gabrielv on 11/23/24.
// Simple logger wrapper for unity logger
//

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define INFO(...) printf("[ITCHER/INFO] " __VA_ARGS__)
#define WARNING(...) printf("[ITCHER/WARN] " __VA_ARGS__)
#define ERROR(...) printf("[ITCHER/ERR] " __VA_ARGS__);

#endif //LOGGER_H
