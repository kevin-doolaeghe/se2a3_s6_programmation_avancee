#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const unsigned int MAX          = 50;
const unsigned int TEL_LENGTH   = 11;
const unsigned int MAX_PERSONNE = 1000;

typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;

typedef struct
{
    char nom[MAX];
    char prenom[MAX];
    char telephone[TEL_LENGTH]; // 10 chiffres + 1 carac pour '\0'
    Date date_naissance;
} Personne;

typedef struct
{
    Personne espace[MAX_PERSONNE];
    int      dernier;
} Annuaire;

Date lire_date (FILE *fp)
{
    Date res;
    fscanf (fp, "%d %d %d", &res.jour, &res.mois, &res.annee);
    return res;
}

void affiche_date (Date d, FILE * fp) { fprintf (fp, "%02d-%02d-%d\n", d.jour, d.mois, d.annee); }

int lire_personne (Personne *ptr_pers, FILE *fp)
{
    if (fscanf (fp, "%s", ptr_pers->nom) == EOF) return 1;

    fscanf (fp, "%s", ptr_pers->prenom);
    ptr_pers->date_naissance = lire_date (fp);
    fscanf (fp, "%s", ptr_pers->telephone);
    return 0;
}

void affiche_personne (Personne p, FILE * fp)
{
    fprintf (fp,"Nom:\t\t%s\n", p.nom);
    fprintf (fp, "Prenom:\t\t%s\n", p.prenom);
    fprintf (fp, "Date Naissance\t");
    affiche_date (p.date_naissance, fp);
    fprintf (fp, "Telephone:\t%s\n", p.telephone);
}

void construire_annuaire (Annuaire *ptr, FILE *fp)
{
    Personne p;
    while (lire_personne (&p, fp) == 0)
    {
        ptr->dernier++;
        ptr->espace[ptr->dernier] = p;
    }
}

void affiche_annuaire (Annuaire a, FILE * fp)
{
    for (int i = 0; i <= a.dernier; i++)
    {
        // printf ("--------  %d --------\n", i);
        affiche_personne (a.espace[i], fp);
    }
}

int compare_date (Date d1, Date d2)
{
    if (d1.annee < d2.annee) return -1;
    if (d1.annee > d2.annee) return 1;
    if (d1.mois < d2.mois) return -1;
    if (d1.mois > d2.mois) return 1;
    if (d1.jour < d2.jour) return -1;
    if (d1.jour > d2.jour) return 1;
    return 0;
}

void tri_annuaire_date (Annuaire *ptr)
{
    for (int i = 0; i < ptr->dernier; i++)
    {
        for (int j = i; j < ptr->dernier; j++)
        {
            if (compare_date (ptr->espace[j].date_naissance, ptr->espace[j + 1].date_naissance) > 0)
            {
                Personne temp      = ptr->espace[j];
                ptr->espace[j]     = ptr->espace[j + 1];
                ptr->espace[j + 1] = temp;
            }
        }
    }
}

void tri_annuaire_nom (Annuaire *ptr)
{
    for (int i = 0; i < ptr->dernier; i++)
    {
        for (int j = i; j < ptr->dernier; j++)
        {
            if (strcmp (ptr->espace[j].nom, ptr->espace[j + 1].nom) > 0)
            {
                Personne temp      = ptr->espace[j];
                ptr->espace[j]     = ptr->espace[j + 1];
                ptr->espace[j + 1] = temp;
            }
        }
    }
}

void usage()
{
    printf("usage: ./a.out fichier_annuaire fichier_sauvegarde\n");
}

int main (int argc, char * argv [])
{
    if (argc != 3) // on s'assure qu'il y a au moins 1 paramètre
    {
        usage();
        exit(-1);
    }

    Annuaire a;     // declaration d'une variable annuaire
    a.dernier = -1; // initialisation (Annuaire vide)
    FILE *fp;
    fp = fopen (argv[1], "r");
    if (fp == NULL) // on s'assure que le fichier a été ouvert
    {
        printf("Impossible d'ouvrir %s\n", argv[1]);
        exit(-1);
    }
    construire_annuaire (&a, fp); // remplissage
    fclose (fp);
//    affiche_annuaire (a);   // affichage
    tri_annuaire_date (&a); // tri par date
//    affiche_annuaire (a);   // affichage annuaire trié (date)
    tri_annuaire_nom (&a);  // tri annuaire suivant nom
    fp = fopen(argv[2], "w");
    if (fp == NULL) // on s'assure que le fichier a été ouvert en écriture
    {
        printf("Impossible d'ouvrir %s en écriture\n", argv[2]);
        exit(-1);
    }
    affiche_annuaire (a, fp);   // affichage annuaire trié (nom)
    return 0;
}
