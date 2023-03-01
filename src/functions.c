//
// Created by jk on 2/26/23.
//
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/functions.h"
#include "../include/utility.h"

List createList() {
    List result;

    Element *head = malloc(sizeof(Element));
    Element *tail = malloc(sizeof(Element));

    head->appointment = tail->appointment = NULL;

    head->next = tail->next = tail;

    result.head = head;
    result.tail = tail;

    return result;
}

void clearList(List list) {
    Element *current = list.head->next;
    while (current->next != current) {
        Element *old = current;
        current = current->next;
        free(old);
    }
    free(list.head);
    free(list.tail);
}

void insertElement(List list, time_t start, const char *text) {
    Appointment *appointment = (Appointment *)malloc(sizeof(Appointment));
    appointment->description = text;
    appointment->start = start;

    struct Element *element = (struct Element *)malloc(sizeof(struct Element));
    element->appointment = appointment;
    Element *current = list.head;
    while (current != current->next) {

        Element *old = current;
        current = current->next;

        if (current == current->next ||
            difftime(start, current->appointment->start) <= 0) {
            element->next = old->next;
            old->next = element;
        }
    }
}

Element *findElement(List list, const char *text) {
    Element *current = list.head->next;
    while (current->next != current) {
        const char *desc = current->appointment->description;
        if (strncmp(desc, text, sizeof((char *)desc)) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}


bool deleteElement(List list, const char *text) {
    Element *current = list.head->next;
    while (current->next != current) {
        const char *desc = current->appointment->description;
        if (strncmp(desc, text, sizeof((char *)desc)) == 0) {
            Element *old = current;
            current = current->next;
            free(old);
            return true;
        }
        current = current->next;
    }
    return false;
}

void printAppointment(Appointment *appointment) {
    printf("--------------------------------------\n");
    printf("Appointment: %s\n", appointment->description);
    printf("Fällig am: %s", asctime(localtime(&appointment->start)));
    printf("--------------------------------------\n");
}

void printList(List list, int day, int month, int year) {
    struct Element *ptr = list.head->next;
    bool found = false;

    // start from the beginning
    while (ptr != ptr->next) {
        struct tm *start = localtime(&ptr->appointment->start);
        if (start->tm_mday == day && start->tm_mon == month &&
            start->tm_year == year) {
            printAppointment(ptr->appointment);
            found = true;
        }
        ptr = ptr->next;
    }
    if (!found) printf("Keine Termine gefunden!\n");
}

void printFullList(List list) {
    struct Element *ptr = list.head->next;

    // start from the beginning
    while (ptr != ptr->next) {
        printAppointment(ptr->appointment);
        ptr = ptr->next;
    }
}

List parseFile(const char *filename) {
    // read appointments from file saved in "filename" by saveList
    FILE *file = fopen(filename, "r");
    List list = createList();
    if (file == NULL) {
        printf("File %s not found. Creating new file.\n", filename);
        return list;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        char *token = strtok(line, "|");
        char *description = malloc(sizeof(char) * strlen(token));
        strcpy(description, token);
        token = strtok(NULL, ";");
        time_t start = (time_t) strtol(token, NULL, 10);
        insertElement(list, start, description);
    }
    fclose(file);
    return list;
}

void saveList(List list, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei %s", filename);
        exit(1);
    }
    Element *current = list.head->next;
    while (current->next != current) {
        fprintf(file, "%s|", current->appointment->description);
        fprintf(file, "%ld;", current->appointment->start);
        current = current->next;
    }
    fclose(file);
}

void entry() {
    printf("Terminder - Version 0.1\n");
}

void menu(List main_list) {
    int input;
    int option = 0;
    while(true) {
        printOptions();

        if (scanf("%d", &input) == 1 && input >= 1 && input <= 8) {
            option = input;
        } else {
            printf("Ungültige Eingabe!\n");
        }

        time_t ct = time(NULL);
        struct tm *ctm = localtime(&ct);
        switch (option) {
            case 1:
                printList(main_list, ctm->tm_mday, ctm->tm_mon, ctm->tm_year);
                break;
            case 2:
                time_t date_time = readDate();
                struct tm *date_tm = localtime(&date_time);
                printList(main_list, date_tm->tm_mday, date_tm->tm_mon,
                          date_tm->tm_year);
                break;
            case 8:
                printf("\n");
                return;
        }
    }
}
void goodbye() {
    printf("See you soon!\n");
}