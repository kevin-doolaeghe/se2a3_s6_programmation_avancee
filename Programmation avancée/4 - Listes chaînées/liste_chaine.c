#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//----------------------------------------------

/*
typedef struct {
    char *data;
    int alloc;
    int size;
} Chaine;

typedef struct _cell { // _cell --> Nom temporaire pour suivant car Cellule est déclaré après
    struct _cell *suivant;
    Chaine chaine;
} Cellule;

typedef Cellule *ListeString;
typedef Cellule *PtCellule;
*/

typedef struct Element Element;
struct Element {
    Element *suivant;
    int nb;
};

typedef Element *Liste;
typedef Element *PtElement;

//----------------------------------------------

/*
void init_chaine(Chaine *str) {
    str->alloc = 1;
    str->size = 0;
    str->data = malloc(sizeof(char));
    str->data[0] = '\0';
}

void clean_chaine(Chaine *str) {
    str->alloc = 0;
    str->size = 0;
    free(str->data);
    str->data = NULL;
}

void print_chaine(Chaine *str) { // Pointeur pour ne pas recopier la variable
    printf("%s\n", str->data);
}

void concat_chaine_char(Chaine *str, char c) {
    if (str->size + 1 > str->alloc) {
        str->alloc++;
        str->data = realloc(str->data, str->alloc * sizeof(char));
    }

    str->data[str->size] = c;
    str->size++;
    str->data[str->size] = '\0';
}

void concat_chaine_chaine(Chaine *str1, Chaine *str2) {
    for (int i = 0; i <= str2->size; i++) {
        concat_chaine_char(str1, str2->data[i]);
    }
}
*/

//----------------------------------------------

PtElement allouer(int nb) {
    PtElement ptr = malloc(sizeof(Element));
    ptr->nb = nb;
    ptr->suivant = NULL;

    return ptr;
}

void append_liste(Liste *liste, int i) {
    PtElement ptr = allouer(i);
    if (ptr == NULL) return;

    ptr->suivant = *liste;
    *liste = ptr;
}

void liberer_last(Liste liste) {
    PtElement ptr = liste;
    liste = ptr->suivant;
    free(ptr);
}

void liberer_liste(Liste liste) {
    PtElement ptr = liste;
    while (ptr != NULL) {
        ptr = ptr->suivant;
        liberer_last(liste);
    }
    liste = NULL;
}

void affiche_liste(Liste liste) {
    PtElement ptr = liste;

    while (ptr != NULL) {
        printf("%d\n", ptr->nb);
        ptr = ptr->suivant;
    }
}

bool recherche_element(Liste liste, int nb) {
    PtElement ptr = liste;

    while (ptr != NULL) {
        if (ptr->nb == nb) return true;
        ptr = ptr->suivant;
    }

    return false;
}

bool liste_triee(Liste liste) {
    PtElement ptr = liste;

    while (ptr != NULL) {
        if (ptr->suivant != NULL)
            return 1;
        if (ptr->nb > ptr->suivant->nb)
            return 0;

        ptr = ptr->suivant;
    }

    return 1;
}

//----------------------------------------------

void ajout_tri_liste(Liste *liste, int nb) {
    if (!recherche_element(*liste, nb)) {
        if (*liste == NULL)
            append_liste(liste, nb);
        else if ((*liste)->nb > nb)
            append_liste(liste, nb);
        else ajout_tri_liste(&(*liste)->suivant, nb);
    }
}

void lire_liste_fichier(Liste *liste, FILE *fp) {
    int nb = 0;

    while (fscanf(fp, "%d", &nb) != EOF) {
        ajout_tri_liste(liste, nb);
    }
}

//----------------------------------------------

bool test_doublon(Liste liste) {
    PtElement ptr = liste;

    while (ptr != NULL) {
        if (recherche_element(liste, ptr->nb))
            return true;

        ptr = ptr->suivant;
    }

    return false;
}

void recopie(Liste *src, Liste *dest) {
    PtElement ptr = *src;
    while (ptr != NULL) {
        ajout_tri_liste(dest, ptr->nb);
        ptr = ptr->suivant;
    }
}

void union_listes(Liste *l1, Liste *l2, Liste *dest) {
    recopie(l1, dest);
    recopie(l2, dest);
}

//----------------------------------------------

int main() {
    printf("Listes chaînées\n===============\n\n");

    Liste liste = NULL;

    /*
    int nb = 0;
    while (scanf("%d", &nb) != EOF) {
        ajout_tri_liste(&liste, nb);
    }
    */

    FILE *fp;
    fp = fopen("liste1.txt", "r");

    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier");
        exit(-1);
    }

    lire_liste_fichier(&liste, fp);
    fclose(fp);

    affiche_liste(liste);
    printf("\nDoublon : %s\n", test_doublon(liste) ? "oui" : "non");

    //append_liste(&liste, 0);
    //printf("\nDoublon : %s\n", test_doublon(liste) ? "oui" : "non");

    Liste liste2 = NULL;

    fp = fopen("liste2.txt", "r");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier");
        exit(-1);
    }
    lire_liste_fichier(&liste2, fp);
    fclose(fp);

    affiche_liste(liste2);
    printf("\nDoublon : %s\n", test_doublon(liste2) ? "oui" : "non");


    Liste dest = NULL;
    union_listes(&liste, &liste2, &dest);

    affiche_liste(dest);
    printf("\nDoublon : %s\n", test_doublon(dest) ? "oui" : "non");

    return 0;
}
