#include "listechaines.h"

#define MAXSIZE 30

//Affichage de la liste en ligne
void afficher_liste(Liste liste) {
    printf("%s\n", liste->val);
    afficher_liste(liste->suiv);
}

//Ajout d'un mot en tete de la liste
void ajout_tete(Liste * liste, char * mot) {
    PtCellule ptr = malloc(sizeof(Cellule));
    if (ptr == NULL) return;
    
    strcpy(ptr->val, mot);
    ptr->suiv = *liste;
    *liste = ptr;
}

//Suppression du mot en tete de la liste
void supp_tete(Liste * liste) {
    PtCellule ptr = *liste;
    *liste = ptr->suiv;
    free(ptr);
}

//Ajout d'un mot dans une liste chainee triée
void ajout_alphab(Liste * pl, char * mot)
{
    // liste vide ou mot < mot prochain => ajout en tête
    if ( (*pl == NULL) || (strcmp(mot, (*pl)->val) < 0) )
    {
        ajout_tete(pl,mot);
    }
    else
    {
        // mot > mot prochain => ajouter après dans la liste
        if (strcmp(mot, (*pl)->val) > 0)
        {
            ajout_alphab(&(*pl)->suiv,mot);
        }
        //else => mot déjà dans la liste, ne rien faire?
    }
}

//Dit si un mot donne est dans la liste pas forcement triee
bool appartient(Liste liste, char * mot) {
    // Si la liste est vide
    if (liste == NULL) {
        return false;
    }
    // Si le mot est trouvé
    if (strcmp(mot, liste->val) == 0) {
        return true;
    } else {
        return appartient(liste->suiv, mot);
    }
}

//Donne la taille de la liste.
int taille(Liste liste) {
    PtCellule ptr = liste;
    int size = 0;
    while (ptr != NULL) {
        size++;
        ptr = ptr->suiv;
    }
    
    return size;
}

//Construit une liste triee a partir d'un fichier
void charge_fichier(FILE * fp, Liste * pl)
{
    char mot[MAXSIZE];
    //Nb d'elements à lire dans chaque fscanf
    const int NB_A_LIRE = 1;

    //`man fscanf` pour comprendre les valeurs de retour!!!
    while (fscanf(fp, "%s", mot) == NB_A_LIRE)
    {
        ajout_alphab(pl, mot);
    }

    //On peut tester la bonne ou mauvaise terminaison de la lecture
    if(feof(fp)) printf("Fin normal de lecture\n");
    if(ferror(fp)) printf("ERREUR de lecture\n");
}

//Destruction de Liste.
void detruire_liste(Liste * liste) {
    if (*liste == NULL) {
        liste = NULL;
    } else {
        supp_tete(liste);
        detruire_liste(liste);
    }
}