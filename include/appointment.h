#include <bits/types/time_t.h>

#ifndef TERMINDER_APPOINTMENT_H
#define TERMINDER_APPOINTMENT_H

typedef struct
{
    time_t start;
    const char *description;
} Appointment;

#endif //TERMINDER_APPOINTMENT_H
