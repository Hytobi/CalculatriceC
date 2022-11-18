#include <stdio.h>
#include <stdlib.h>

#include "lecture.h"
#include "pile.h"
#include "rage.h"

void printChoix() {
    printf("Choisissez une option:\n");
    printf("1. Calculer une expression en notation polonaise inversée\n");
    printf("2. Calculer une expression en infixe\n");
    printf("3. Quitter\n");
    printf("Choix: ");
}

int main(int argc, char **argv) {
    int choix = 0;
    char c;
    do {
        printChoix();
        if (!scanf("%d", &choix)) {
            // vide le buffer
            printf("Erreur de lecture du choix\n");
            while (c = getchar() != '\n' && c != EOF)
                ;
        }
    } while (choix != 1 && choix != 2 && choix != 3);

    while (c = getchar() != '\n' && c != EOF)
        ;
    if (choix == 1) {
        printf("Resultat: %d\n", traitementNPI());
    } else if (choix == 2) {
        printf("Resultat: %d\n", traitementInfixe());
    } else {
        printf("Au revoir!\n");
    }

    return EXIT_SUCCESS;
}