#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------

const int MAX_LIVRES = 100;

typedef struct {
    int annee;
    int mois;
    int jour;
} Date;

typedef struct {
    char titre[20];
    char auteur[20];
    int id;
    Date date_publication;
} Livre;

typedef struct {
    Livre livres[MAX_LIVRES];
    int dernier;
} Bibliotheque;

//----------------------------------------------

int lire_date(Date *date) {
    printf("Entrez une date (jour mois année) :\n");
    scanf("%d %d %d", &date->jour, &date->mois, &date->annee);

    return 0;
}

void affiche_date(Date date) {
    printf("Date : %d/%d/%d\n", date.jour, date.mois, date.annee);
}

int lire_livre(Livre *livre) {
    printf("Entrez le titre :\n");
    scanf("%s", livre->titre);

    printf("Entrez le nom de l'auteur :\n");
    scanf("%s", livre->auteur);

    printf("Entrez le numéro d'identification :\n");
    scanf("%d", &livre->id);

    lire_date(&livre->date_publication);

    return 0;
}

void affiche_livre(Livre livre) {
    printf("Titre : %s\n", livre.titre);
    printf("Auteur : %s\n", livre.auteur);
    printf("Numéro d'identification : %d\n", livre.id);
    affiche_date(livre.date_publication);
}

void affiche_bibliotheque(Bibliotheque bibliotheque) {
    for (int i = 0; i <= bibliotheque.dernier; i++) {
        printf("----------- %d -----------\n", i);
        affiche_livre(bibliotheque.livres[i]);
    }
}

int ajouter_livre(Bibliotheque *bibliotheque, Livre livre) {
    if (bibliotheque->dernier < MAX_LIVRES - 1 || bibliotheque->dernier == -1) {
        bibliotheque->dernier++;
        bibliotheque->livres[bibliotheque->dernier] = livre;

        return 0;
    } else return 1;
}

Bibliotheque recherche_livre(Bibliotheque bibliotheque, char *rech) {
    Bibliotheque temp;
    temp.dernier = -1;

    for (int i = 0; i <= bibliotheque.dernier; i++) {
        if (strcmp(bibliotheque.livres[i].titre, rech) > 0) {
            ajouter_livre(&temp, bibliotheque.livres[i]);
        }
    }

    return temp;
}

//----------------------------------------------

int main()
{
    printf("IE - Kevin Doolaeghe - 9 mars 2020\n==================================\n\n");
    Bibliotheque bibliotheque;
    bibliotheque.dernier = -1;

    Livre livre;
    lire_livre(&livre);

    ajouter_livre(&bibliotheque, livre);

    printf("\nBibliothèque :\n");
    affiche_bibliotheque(bibliotheque);

    printf("\Résultat de la recherche :\n");

    Bibliotheque resultat = recherche_livre(bibliotheque, "test");
    affiche_bibliotheque(resultat);

    return 0;
}
