#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------

typedef struct
{
    char *data;
    int   alloc;
    int   size;
} Chaine;

//----------------------------------------------

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

//----------------------------------------------

int main() {
    printf("Réallocation dynamique\n======================\n\n");

    Chaine str1;
    init_chaine(&str1);
    concat_chaine_char(&str1, 'a');
    concat_chaine_char(&str1, 'b');
    concat_chaine_char(&str1, 'w');
    concat_chaine_char(&str1, 't');

    Chaine str2;
    init_chaine(&str2);
    concat_chaine_char(&str2, 'k');
    concat_chaine_char(&str2, 'e');
    concat_chaine_char(&str2, 'v');
    concat_chaine_char(&str2, 'i');

    print_chaine(&str1);
    print_chaine(&str2);

    concat_chaine_chaine(&str1, &str2);

    print_chaine(&str1);

    clean_chaine(&str1);
    clean_chaine(&str2);

    return 0;
}
