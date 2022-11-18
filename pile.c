#include "pile.h"

#include <stdio.h>
#include <stdlib.h>

Pile *createPile() {
    Pile *pile = malloc(sizeof(Pile));
    pile->first = NULL;
    pile->size = 0;
    return pile;
}
void addPileInt(Pile *pile, int value) {
    if (pile->first == NULL) {
        pile->first = malloc(sizeof(Element));
        pile->first->value = value;
        pile->first->c = '\0';
        pile->first->next = NULL;
    } else {
        Element *current = pile->first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(Element));
        current->next->value = value;
        current->next->c = '\0';
        current->next->next = NULL;
    }
    pile->size++;
}
void addPileChar(Pile *pile, char value) {
    if (pile->first == NULL) {
        pile->first = malloc(sizeof(Element));
        pile->first pile->first->c = value;
        pile->first->next = NULL;
    } else {
        Element *current = pile->first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(Element));
        current->next->c = value;
        current->next->next = NULL;
    }
    pile->size++;
}
int removePileInt(Pile *pile) {
    if (pile->first == NULL) return -1;
    Element *current = pile->first;
    pile->first = pile->first->next;
    int value = current->value;
    free(current);
    pile->size--;
    return value;
}
char removePileChar(Pile *pile) {
    if (pile->first == NULL) return -1;
    Element *current = pile->first;
    pile->first = pile->first->next;
    char value = current->c;
    free(current);
    pile->size--;
    return value;
}
int topPileInt(Pile *pile) {
    if (pile->first == NULL) return -1;
    Element *current = pile->first;
    while (current->next != NULL) {
        current = current->next;
    }
    // return 1 if the top is an int
    return (current->value != 0);
}
int isEmptyPile(Pile *pile) { return pile->first == NULL; }
void printPile(Pile *pile) {
    Element *current = pile->first;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}
void freePile(Pile *pile) {
    Element *current = pile->first;
    while (current != NULL) {
        Element *next = current->next;
        free(current);
        current = next;
    }
    free(pile);
}