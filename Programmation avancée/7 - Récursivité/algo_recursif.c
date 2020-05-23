#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Element Element;
struct Element {
    Element *suivant;
    int entier;
    int multiplicite;
};

typedef Element *Liste;
typedef Element *PtElement;

//----------------------------------------------

PtElement allouer(int entier) {
    PtElement ptr = malloc(sizeof(Element));

    ptr->entier = entier;
    ptr->multiplicite = 1;
    ptr->suivant = NULL;

    return ptr;
}

void ajout_en_tete(Liste *liste, int entier) {
    PtElement ptr = allouer(entier);
    if (ptr == NULL) return;

    ptr->suivant = *liste;
    *liste = ptr;
}

void suppression_en_tete(Liste *liste) {
    PtElement ptr = *liste;
    *liste = ptr->suivant;
    free(ptr);
}

void suppression_liste(Liste *liste) {
    PtElement ptr = *liste;
    while (ptr != NULL) {
        ptr = ptr->suivant;
        suppression_en_tete(liste);
    }
    *liste = NULL;
}

bool recherche_element(Liste liste, int entier) {
    PtElement ptr = liste;

    while (ptr != NULL) {
        if (ptr->entier == entier) return true;
        ptr = ptr->suivant;
    }

    return false;
}

void incrementer_multiplicite(Liste *liste, int entier) {
    PtElement ptr = *liste;

    while (ptr != NULL) {
        if (ptr->entier == entier) ptr->multiplicite++;
        ptr = ptr->suivant;
    }
}

void ajout_entier(Liste *liste, int entier) {
    if (!recherche_element(*liste, entier)) {
        if (*liste == NULL)
            ajout_en_tete(liste, entier);
        else if ((*liste)->entier > entier)
            ajout_en_tete(liste, entier);
        else ajout_entier(&((*liste)->suivant), entier);
    } else {
        incrementer_multiplicite(liste, entier);
    }
}

void lecture_fichier(Liste *liste, FILE *fp) {
    int entier = 0;

    while (fscanf(fp, "%d", &entier) != EOF) {
        ajout_entier(liste, entier);
    }
}

void affiche_liste(Liste liste) {
    PtElement ptr = liste;

    while (ptr != NULL) {
        printf("%d\t%d\n", ptr->entier, ptr->multiplicite);
        ptr = ptr->suivant;
    }
}

void recopie(Liste *src, Liste *dest) {
    PtElement ptr = *src;

    while (ptr != NULL) {
        for (int i = 0; i < ptr->multiplicite; i++) {
            ajout_entier(dest, ptr->entier);
        }
        ptr = ptr->suivant;
    }
}

void mixage(Liste *l1, Liste *l2, Liste *dest) {
    recopie(l1, dest);
    recopie(l2, dest);
}

bool test_tri(Liste liste) {
    PtElement ptr = liste;

    while (ptr != NULL) {
        if (ptr->suivant != NULL)
            return 1;
        if (ptr->entier > ptr->suivant->entier)
            return 0;

        ptr = ptr->suivant;
    }

    return 1;
}

bool test_tri_recursif(Liste liste) {
    if (liste == NULL) return 1;
    else if (liste->suivant != NULL) {
        if (liste->entier > liste->suivant->entier) return 0;
    }

    return test_tri_recursif(liste->suivant);
}

int recuperer_multiplicite(Liste liste, int entier) {
    if (liste == NULL) return 0;
    if (liste->entier == entier) return liste->multiplicite;

    return recuperer_multiplicite(liste->suivant, entier);
}

int calcul_cardinal(Liste liste) {
    if (liste == NULL) return 0;
    return liste->multiplicite + calcul_cardinal(liste->suivant);
}

//----------------------------------------------

int main() {
    printf("Algorithmes récursifs\n=====================\n\n");

    Liste liste1 = NULL;
    Liste liste2 = NULL;

    FILE *fp;
    fp = fopen("liste1.txt", "r");

    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(-1);
    }

    lecture_fichier(&liste1, fp);
    fclose(fp);

    fp = fopen("liste2.txt", "r");

    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(-1);
    }

    lecture_fichier(&liste2, fp);
    fclose(fp);

    printf("Liste n°1 :\n");
    affiche_liste(liste1);
    printf("\n\nListe n°2 :\n");
    affiche_liste(liste2);
    printf("\n\nMix de liste n°1 et liste n°2 :\n");
    Liste dest = NULL;
    mixage(&liste1, &liste2, &dest);
    affiche_liste(dest);

    printf("\n\nTest tri : %d\n", test_tri(liste1));
    printf("Test tri récursif : %d\n", test_tri_recursif(liste1));

    printf("\nMultiplicité de -2 dans la liste n°1 : %d\n", recuperer_multiplicite(liste1, -2));
    printf("Cardinal de la liste n°1 : %d\n", calcul_cardinal(liste1));

    suppression_liste(&liste1);
    suppression_liste(&liste2);
    suppression_liste(&dest);

    return 0;
}
