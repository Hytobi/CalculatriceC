#include "lecture.h"

#include <stdio.h>

#include "pile.h"
#include "rage.h"

// Lire dans le terminale
char* lireTerminal() {
    char* str = malloc(sizeof(char) * 100);
    if (!fgets(str, 100, stdin)) {
        RAGE_QUIT("Erreur lors de la lecture du terminal");
    }
    return str;
}

int estNombre(char c) { return c >= '0' && c <= '9'; }

int estOperateur(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
int estUnaire(char c) { return c == '#'; }
void calculerUnaire(Pile* p) {
    int a = removePileInt(p);
    addPileInt(p, -a);
}

void calculer(Pile* pile, char c) {
    int a = removePileInt(pile);
    int b = removePileInt(pile);
    int result = 0;
    switch (c) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
    }
    addPileInt(pile, result);
}
int estSeparateur(char c) { return c == ' ' || c == '\t' || c == '\n'; }
int NPI(Pile* p, char* str) {
    int i = 0;

    while (str[i] != '\0') {
        while (estSeparateur(str[i])) i++;
        if (str[i] == '\0')
            break;
        else if (estOperateur(str[i]))
            calculer(p, str[i]);
        else if (estUnaire(str[i]))
            calculerUnaire(p);
        else if (estNombre(str[i])) {
            int j = 0;
            char* nombre = malloc(sizeof(char) * 100);
            while (!estSeparateur(str[i]) && str[i] != '\0') {
                nombre[j] = str[i];
                i++;
                j++;
            }
            nombre[j] = '\0';
            addPileInt(p, atoi(nombre));
        } else {
            RAGE_QUIT("Erreur lors du traitement de la chaine de caractère");
        }
        i++;
    }
    return removePileInt(p);
}
// Traitement de la chaine de caractère
int traitementNPI() {
    Pile* p = createPile();
    char* str = lireTerminal();
    return NPI(p, str);
}

int checkParenthese(char* str) {
    int i = 0;
    int nbParenthese = 0;
    while (str[i] != '\0') {
        if (str[i] == '(')
            nbParenthese++;
        else if (str[i] == ')')
            nbParenthese--;
        i++;
    }
    return nbParenthese == 0;
}

int niveauPriorite(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '#')
        return 3;
    else
        return 0;
}

char* converPostFixe_to_NPI(char* str) {
    Pile* p = createPile();
    char* result = malloc(sizeof(char) * 100);
    int i = 0;
    int j = 0;
    char c;
    while (str[i] != '\0') {
        while (estSeparateur(str[i])) i++;
        if (str[i] == '\0')
            break;
        else if (estNombre(str[i])) {
            while (!estSeparateur(str[i]) && str[i] != '\0') {
                result[j] = str[i];
                i++;
                j++;
            }
            result[j++] = ' ';
        } else if (str[i] == '(') {
            addPileChar(p, str[i]);

        } else if (str[i] == ')') {
            while ((c = removePileChar(p)) != '(') {
                result[j++] = c;
                result[j++] = ' ';
            }
        } else if (estOperateur(str[i]) || estUnaire(str[i])) {
            c = removePileChar(p);
            while (!isEmptyPile(p) &&
                   niveauPriorite(c) >= niveauPriorite(str[i])) {
                result[j++] = c;
                result[j++] = ' ';
                c = removePileChar(p);
            }
            if (c == '(') addPileChar(p, c);
            addPileChar(p, str[i]);
        } else {
            RAGE_QUIT("Erreur lors de la conversion de l'expression");
        }
        i++;
    }
    while (!isEmptyPile(p)) {
        result[j++] = removePileChar(p);
        result[j++] = ' ';
    }
    result[j] = '\0';
    return result;
}
int traitementInfixe() {
    Pile* p = createPile();
    char* strPost = lireTerminal();

    if (!checkParenthese(strPost)) {
        RAGE_QUIT("Erreur de parenthèse");
    }
    char* strNPI = converPostFixe_to_NPI(strPost);
    printf("%s\n", strNPI);

    return NPI(p, strNPI);
}
