#include "listechaines.h"

int main() {
    Liste liste = NULL;
    
    FILE *fp;
    fp = fopen("dico.txt", "r");

    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(-1);
    }
    
    charge_fichier(fp, &liste);
    
    printf("Le fichier contient %i mots\n", taille(liste));
    afficher_liste(liste);
    //printf(appartient(liste, "cc") ? "Le mot 'cc' appartient à la liste\n" : "Le mot 'cc' n'appartient pas à la liste\n");

    fclose(fp);
    detruire_liste(&liste);
    
    return 0;
}