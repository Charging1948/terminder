#ifndef TERMINDER_ELEMENT_H
#define TERMINDER_ELEMENT_H

#include "appointment.h"

typedef struct Element
{
    Appointment *appointment;
    struct Element *next;
} Element;

#endif //TERMINDER_ELEMENT_H
