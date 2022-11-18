#ifndef PILE_H
#define PILE_H

typedef struct _Element {
    int value;
    char c;
    struct _Element *next;
} Element;

typedef struct _Pile {
    Element *first;
    int size;
} Pile;

Pile *createPile();
void addPileInt(Pile *pile, int value);
void addPileChar(Pile *pile, char value);
int removePileInt(Pile *pile);
char removePileChar(Pile *pile);
int topPileInt(Pile *pile);
int isEmptyPile(Pile *pile);
void printPile(Pile *pile);
void freePile(Pile *pile);

#endif