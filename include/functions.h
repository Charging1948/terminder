//
// Created by jk on 2/26/23.
//

#ifndef TERMINDER_FUNCTIONS_H
#define TERMINDER_FUNCTIONS_H

#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include "list.h"
#include "stdio.h"

List createList(void);
void clearList(List);
void insertElement(List, time_t, const char *);
Element * findElement(List, const char *);
bool deleteElement(List, const char *);
void printAppointment(Appointment*);
void printList(List, int, int, int);
void printFullList(List);
List parseFile(const char *);
void saveList(List, const char *);
void entry(void);
void menu(List);
void goodbye(void);

#endif //TERMINDER_FUNCTIONS_H
