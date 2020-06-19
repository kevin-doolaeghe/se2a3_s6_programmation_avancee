/**
 * @brief      This file implements 3 sorting algorithms
 *
 * @author     Jeremie
 * @date       2020
 */
#include <sort_algorithms.h>
#include <utils.h>

void selection_sort (int t[], unsigned int N)
{
    for (unsigned int ideb = 0; ideb < N - 1; ideb++)
    {
        unsigned int imin = ideb;
        for (unsigned int i = ideb + 1; i < N; i++)
        {
            if (t[i] < t[imin]) imin = i;
        }
        swap_value_in_array (t, ideb, imin);
    }
}

void insertion_sort (int t[], unsigned int N)
{
    for (unsigned int i = 1; i < N; i++)
    {
        int current_element = t[i];
        int insertion_index = i;

        while ((insertion_index >= 1) && (t[insertion_index - 1] > current_element))
        {
            t[insertion_index] = t[insertion_index - 1];
            insertion_index--;
        }
        t[insertion_index] = current_element;
    }
}

/**
 * @brief      merge in place two sorted arrays
 *
 * @param      t                array containing the two sorted sub-arrays
 * @param[in]  start_sub_tab_1  starting index for the first array
 * @param[in]  last_sub_tab_1   ending index for the first array
 * @param[in]  last_sub_tab_2   ending index for the second array
 */
void merge (int t[], unsigned int start_sub_tab_1, int last_sub_tab_1, int last_sub_tab_2)
{
    // starting index for the second array
    int first_sub_tab_2 = last_sub_tab_1 + 1;

    int c2 = first_sub_tab_2;
    int c1 = start_sub_tab_1;
    int merged_Array[last_sub_tab_2 - start_sub_tab_1 + 1];

    for (unsigned int i = 0; i < last_sub_tab_2 - start_sub_tab_1 + 1; i++)
    {
        if ((c1 <= last_sub_tab_1) && ((t[c1] < t[c2]) || (c2 > last_sub_tab_2)))
        {
            merged_Array[i] = t[c1];
            c1++;
        }
        else
        {
            merged_Array[i] = t[c2];
            c2++;
        }
    }

    for (unsigned int i = 0; i < last_sub_tab_2 - start_sub_tab_1 + 1; i++)
    {
        t[start_sub_tab_1 + i] = merged_Array[i];
    }
}

/**
 * @brief      Recursive function for merge sort
 *
 * @param      t      array of integer
 * @param[in]  first  first index to consider
 * @param[in]  last   last index to consider
 */
void recursive_merge (int t[], unsigned int first, unsigned int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;

        recursive_merge (t, first, mid);
        recursive_merge (t, mid + 1, last);

        merge (t, first, mid, last);
    }
}

void merge_sort (int t[], unsigned int N)
{
    if (N > 1) recursive_merge (t, 0, N - 1);
}