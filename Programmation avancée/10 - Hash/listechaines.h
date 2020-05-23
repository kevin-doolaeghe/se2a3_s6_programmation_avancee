#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 30

//Declaration de liste chainee de chaines de caracteres
struct cell {
    char val[MAXSIZE];
    struct cell * suiv;
};

typedef struct cell Cellule;
typedef struct cell * Liste;
typedef struct cell * PtCellule;

//Affichage de la liste en ligne
void afficher_liste(struct cell *);

//Ajout d'un mot en tete de la liste
void ajout_tete(struct cell **, char *);

//Suppression du mot en tete de la liste
void supp_tete(struct cell **);

//Ajout un mot dans une liste supposee triée dans l'ordre alphabetique
void ajout_alphab(struct cell **, char *);

//Dit si un mot donné est dans la liste pas forcément triée
bool appartient(struct cell *, char *);

//Donne la taille de la liste.
int taille(struct cell *);

//Construit une liste triée à partir d'un fichier
void charge_fichier(FILE *, struct cell **);

//Destruction de la liste.
void detruire_liste(struct cell **);