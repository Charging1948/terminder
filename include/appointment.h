//
// Created by jk on 12/15/22.
//
#include <bits/types/time_t.h>

#ifndef TERMINDER_APPOINTMENT_H
#define TERMINDER_APPOINTMENT_H

typedef struct
{
    time_t start;
    const char *description;
} Appointment;

#endif //TERMINDER_APPOINTMENT_H
