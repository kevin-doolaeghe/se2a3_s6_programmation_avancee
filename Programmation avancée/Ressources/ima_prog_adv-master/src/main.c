/**
 * @brief      This file initializes arrays and sort them using 3 different algorithms
 *
 * @author     Jeremie
 * @date       2020
 */
#include <memory.h>
#include <sort_algorithms.h>
#include <stdbool.h>
#include <stdio.h>
#include <utils.h>

/**
 * @brief      Compares 3 arrays of integers
 *
 * @param      t1    1st array
 * @param      t2    2nd array
 * @param      t3    3rd array
 * @param[in]  N     the first N cells will to be checked
 *
 * @return     { description_of_the_return_value }
 */
bool compare_tab (int t1[], int t2[], int t3[], unsigned int N)
{
    for (unsigned int i = 0; i < N; i++)
    {
        if ((t1[i] != t2[i]) || (t2[i] != t3[i])) return false;
    }
    return true;
}

int main ()
{
    const unsigned int TAILLE  = 100;
    const unsigned int VAL_MAX = 50;
    int                orig_tab[TAILLE];
    int                insert_tab[TAILLE];
    int                select_tab[TAILLE];
    int                merge_tab[TAILLE];
    // Init sample array
    init_rn_generator ();
    init_array (orig_tab, TAILLE, VAL_MAX);
    // Copy
    memcpy (insert_tab, orig_tab, TAILLE * sizeof (int));
    memcpy (select_tab, orig_tab, TAILLE * sizeof (int));
    memcpy (merge_tab, orig_tab, TAILLE * sizeof (int));
    // Sort
    selection_sort (select_tab, TAILLE);
    insertion_sort (insert_tab, TAILLE);
    merge_sort (merge_tab, TAILLE);
    // Message
    if (compare_tab (insert_tab, select_tab, merge_tab, TAILLE) == true)
        printf ("the 3 arrays are equal\n");
    else
        printf ("ERROR: the 3 arrays are different\n");

    return 0;
}
