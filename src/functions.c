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
    list.head->next = list.tail;
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
        if (strcmp(desc, text) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

bool deleteElement(List list, const char *text) {
    bool result = false;
    Element *current = list.head;
    while (current->next != current->next->next) {
        const char *desc = current->next->appointment->description;
        if (strncmp(desc, text, sizeof((char *)desc)) == 0) {
            Element *old = current->next;
            current->next = old->next;
            free(old);
            result = true;
        }
        current = current->next;
    }
    return result;
}

void printAppointment(Appointment *appointment) {
    printf("--------------------------------------\n");
    printf("Appointment: %s\n", appointment->description);
    printf("Faellig am: %s\n", dateToString(appointment->start));
    printf("--------------------------------------\n");
}

void printList(List list, int day, int month, int year) {
    bool ignoreDate = day == 0 && month == 0 && year == 0;
    struct Element *ptr = list.head->next;
    bool found = false;

    while (ptr != ptr->next) {
        struct tm *start = localtime(&ptr->appointment->start);
        if ((start->tm_mday == day && start->tm_mon == month &&
            start->tm_year == year) || ignoreDate) {
            printAppointment(ptr->appointment);
            found = true;
        }
        ptr = ptr->next;
    }
    if (!found) printf("Keine Termine gefunden!\n");
}

void printFullList(List list) {
    printList(list, 0,0,0);
}

List parseFile(const char *filename) {
    // read appointments from file saved in "filename" by saveList
    FILE *file = fopen(filename, "r");
    List list = createList();
    if (file == NULL) {
        printf("Datei '%s' nicht gefunden. Neue Liste wird erstellt.\n", filename);
        return list;
    }
    printf("Datei '%s' wird zum Speichern benutzt.\n", filename);
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        char *token = strtok(line, "|");
        char *description = token;
        token = strtok(NULL, ";");
        time_t start = (time_t) strtol(token, NULL, 10);

        if (difftime(start, time(NULL)) >= 0)
            insertElement(list, start, description);
//        free(description);
    }
    fclose(file);
    return list;
}

void saveList(List list, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Fehler beim Oeffnen der Datei '%s'!\n", filename);
        exit(1);
    }
    Element *current = list.head->next;
    while (current->next != current) {
        fprintf(file, "%s|", current->appointment->description);
        fprintf(file, "%ld;\n", current->appointment->start);
        current = current->next;
    }
    fclose(file);
}

void entry() {
    printf("Terminder - Version 0.1\n");
}

void menu(List main_list) {
    int option = 0;
    while(true) {
        int input;
        printOptions();

        if (scanf("%d", &input) == 1 && input >= 1 && input <= 8) {
            option = input;
            clearBuffer();
        } else {
            clearBuffer();
            printf("Ungueltige Eingabe!\n");
            sleep(1);
            continue;
        }

        time_t ct = time(NULL);
        struct tm *ctm = localtime(&ct);
        char *input_str = NULL;
        time_t date_time;
        switch (option) {
            case 1:
                printList(main_list, ctm->tm_mday, ctm->tm_mon, ctm->tm_year);
                break;
            case 2:
                date_time = readDate();
                struct tm *date_tm = localtime(&date_time);
                printList(main_list, date_tm->tm_mday, date_tm->tm_mon,
                          date_tm->tm_year);
                break;
            case 3:
                printFullList(main_list);
                break;
            case 4:
                printf("Neuer Termin:\n");
                input_str = readString();
                time_t start = readDate();
                insertElement(main_list, start, input_str);
                break;
            case 5:
                printf("Termin suchen:\n");
                input_str = readString();
                Element *element = findElement(main_list, input_str);
                if (element != NULL) {
                    printAppointment(element->appointment);
                } else {
                    printf("Termin nicht gefunden!\n");
                }
                break;
            case 6:
                printf("Termin loeschen:\n");
                input_str = readString();
                if (deleteElement(main_list, input_str)) {
                    printf("Termin geloescht!\n");
                } else {
                    printf("Termin nicht gefunden!\n");
                }
                break;
            case 7:
                clearList(main_list);
                printf("Liste geloescht!\n");
                break;
            case 8:
                // aus Schleife austreten, Programm beenden
                return;
        }
    }
}
void goodbye(List list) {
    clearList(list);
    free(list.head);
    free(list.tail);

    printf("Bis bald!\n");
}