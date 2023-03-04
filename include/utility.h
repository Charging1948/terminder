//
// Created by jk on 12/15/22.
//
#ifndef TERMINDER_UTILITY_H
#define TERMINDER_UTILITY_H
#include <stdbool.h> 
#include <time.h>
#include <stdarg.h>
#include "list.h"
#include "stdio.h"

time_t readDate();
char *readString();
void printOptions();
void clearBuffer();
char *dateToString(time_t);

#endif //TERMINDER_UTILITY_H
