#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------

typedef struct Date Date;

struct Date {
    int annee;
    int mois;
    int jour;
};

/*
typedef struct {
    int annee;
    int mois;
    int jour;
} Date;
*/

Date lire_date() {
    Date date;

    //printf("Entrez une date (jour/mois/année) :\n");
    scanf("%d %d %d", &date.jour, &date.mois, &date.annee);

    return date;
}

void affiche_date(Date date) {
    printf("Date : %d/%d/%d\n", date.jour, date.mois, date.annee);
}

void ex1() {
    Date date = lire_date();
    affiche_date(date);
}

//----------------------------------------------

typedef struct {
    char nom[20];
    char prenom[20];
    Date date;
    char numero[10];
} Personne;

int lire_personne(Personne *ptr_pers) {
    //printf("Entrez un nom :\n");
    char buff[50];
    if (scanf("%s", buff) == EOF) return 1;
    else strcpy((*ptr_pers).nom, buff);

    //printf("Entrez un prénom :\n");
    scanf("%s", (*ptr_pers).prenom);

    (*ptr_pers).date = lire_date();

    //printf("Entrez un numéro de téléphone :\n");
    scanf("%s", (*ptr_pers).numero);

    return 0;
}

void affiche_personne(Personne p) {
    printf("Nom : %s\n", p.nom);
    printf("Prénom : %s\n", p.prenom);
    printf("Numéro de téléphone : %s\n", p.numero);
    affiche_date(p.date);
}

void ex2() {
    Personne p;
    lire_personne(&p);
    affiche_personne(p);
}

//----------------------------------------------

const unsigned int MAX_PERSONNES = 100;

typedef struct {
    Personne personnes[MAX_PERSONNES];
    int dernier;
} Annuaire;

void construire_annuaire(Annuaire *annuaire) {
    int i = 0;
    while (lire_personne(&annuaire->personnes[i]) != 1) {
        i++;
    }
    annuaire->dernier = i;
}

void affiche_annuaire(Annuaire *annuaire) {
    for (int i = 0; i < annuaire->dernier; i++) {
        printf("----------- %d -----------\n", i);
        affiche_personne(annuaire->personnes[i]);
    }
}

void ex4() {
    Annuaire annuaire;
    annuaire.dernier = -1;

    construire_annuaire(&annuaire);
    affiche_annuaire(&annuaire);
}

//----------------------------------------------

int cmp_date(Date d1, Date d2) {
    if (d1.annee == d2.annee) {
        if (d1.mois == d2.mois) {
            if (d1.jour == d2.jour) {
                return 0;
            } else if (d1.jour < d2.jour) {
                return -1;
            } else {
                return 1;
            }
        } else if (d1.mois < d2.mois) {
            return -1;
        } else {
            return 1;
        }
    } else if (d1.annee < d2.annee) {
        return -1;
    } else {
        return 1;
    }
}

void tri_date(Annuaire *annuaire) {
    for (int i = 0; i < annuaire->dernier; i++) {
        for (int j = i + 1; j < annuaire->dernier; j++) {
            if (cmp_date(annuaire->personnes[i].date, annuaire->personnes[j].date) == 1) {
                Personne temp = annuaire->personnes[i];
                annuaire->personnes[i] = annuaire->personnes[j];
                annuaire->personnes[j] = temp;
            }
        }
    }
}

void tri_nom(Annuaire *annuaire) {
    for (int i = 0; i < annuaire->dernier; i++) {
        for (int j = i + 1; j < annuaire->dernier; j++) {
            if (strcmp(annuaire->personnes[i].nom, annuaire->personnes[j].nom) > 0) {
                Personne temp = annuaire->personnes[i];
                annuaire->personnes[i] = annuaire->personnes[j];
                annuaire->personnes[j] = temp;
            }
        }
    }
}

void ex5() {
    Annuaire annuaire;
    annuaire.dernier = -1;

    construire_annuaire(&annuaire);
    affiche_annuaire(&annuaire);

    printf("\nTri par date :\n\n");

    tri_date(&annuaire);
    affiche_annuaire(&annuaire);

    printf("\nTri par nom :\n\n");

    tri_nom(&annuaire);
    affiche_annuaire(&annuaire);
}

//----------------------------------------------

const char *chemin = "annu.txt";

void chargement_date(FILE *fp, Date *date) {
    fscanf(fp, "%d %d %d", &date->jour, &date->mois, &date->annee);
}

void chargement_personne(FILE *fp, Personne *personne) {
    fscanf(fp, "%s", personne->nom);
    fscanf(fp, "%s", personne->prenom);
    chargement_date(fp, &personne->date);
    fscanf(fp, "%s", personne->numero);
}

void chargement_annuaire(const char *chemin, Annuaire *annuaire) {
    FILE *fp;
    fp = fopen(chemin, "r");

    if (fp != NULL) {
        int i = 0;

        while (!feof(fp)) {
            chargement_personne(fp, &annuaire->personnes[i]);
            i++;
        }
        annuaire->dernier = i;

        fclose(fp);
    } else {
        printf("Fichier impossible à ouvrir !\n");
        exit(-1);
    }
}

void ex6() {
    Annuaire annuaire;
    annuaire.dernier = -1;

    chargement_annuaire(chemin, &annuaire);
    affiche_annuaire(&annuaire);
}

//----------------------------------------------

void affiche_args(int argc, char *argv[]) {
    int i = 0;
    printf ("Nombre d'argument(s) : %d\n", argc);

    while (i < argc) {
        printf ("  - Argument %d : %s\n", i, argv[i]);
        i++;
    }
    printf("\n");
}

void usage() {
    printf("Usage : ./a.out fichier_annuaire\n");
}

void ex7(int argc, char *argv[]) {
    affiche_args(argc, argv);

    if (argc != 2) {
        usage();
        exit(-1);
    }

    Annuaire annuaire;
    annuaire.dernier = -1;

    chargement_annuaire(argv[1], &annuaire);
    affiche_annuaire(&annuaire);
}

//----------------------------------------------

Annuaire rech_dicho(Annuaire annuaire, char *rech) {
    Annuaire annu;

    return annu;
}

void ex8(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        exit(-1);
    }

    Annuaire annuaire;
    annuaire.dernier = -1;

    chargement_annuaire(argv[1], &annuaire);
    affiche_annuaire(&annuaire);

    if (argc == 3) {

    }
}

//----------------------------------------------

const char *chemin_final = "annu_trie.txt";

void ecrire_date(Date date, FILE *fp) {
    fprintf(fp, "Date : %d/%d/%d\n", date.jour, date.mois, date.annee);
}

void ecrire_personne(Personne p, FILE *fp) {
    fprintf(fp, "Nom : %s\n", p.nom);
    fprintf(fp, "Prénom : %s\n", p.prenom);
    fprintf(fp, "Numéro de téléphone : %s\n", p.numero);
    ecrire_date(p.date, &fp);
}

void ecrire_annuaire(Annuaire *annuaire, FILE *fp) {
    for (int i = 0; i < annuaire->dernier; i++) {
        fprintf(fp, "----------- %d -----------\n", i);
        ecrire_personne(annuaire->personnes[i], &fp);
    }
}

void sauvegarder(Annuaire *annuaire, const char* chemin) {
    FILE *fp;
    fp = fopen(chemin, "W");

    if (fp != NULL) {
        ecrire_annuaire(&annuaire, chemin);

        fclose(fp);
    } else {
        printf("Fichier impossible à ouvrir !\n");
        exit(-1);
    }
}

void ex9(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        exit(-1);
    }

    Annuaire annuaire;
    annuaire.dernier = -1;

    chargement_annuaire(argv[1], &annuaire);
    sauvegarder(&annuaire, chemin_final);
}

//----------------------------------------------

int main(int argc, char *argv[])
{
    printf("Exercices sur les structures\n============================\n\n");

    //ex1();
    //ex2();
    //ex4();
    //ex5();
    //ex6();
    //ex7(argc, argv);
    ex8(argc, argv);
    ex9(argc, argv);

    return 0;
}
