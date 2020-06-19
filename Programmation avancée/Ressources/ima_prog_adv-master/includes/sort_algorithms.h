#ifndef __SORT_ALGORITHM_H__
#define __SORT_ALGORITHM_H__


/**
 * @brief      Applies selection sort on t
 *
 * @param      t     the array to sort, should be at least of size N
 * @param[in]  N     the first N cells to sort
 */
void selection_sort (int t[], unsigned int N);

/**
 * @brief      Applies insertion sort on t
 *
 * @param      t     the array to sort, should be at least of size N
 * @param[in]  N     the first N cells to sort
 */
void insertion_sort (int t[], unsigned int N);

/**
 * @brief      Applies merge sort on t
 *
 * @param      t     the array to sort, should be at least of size N
 * @param[in]  N     the first N cells to sort
 */
void merge_sort (int t[], unsigned int N);

#endif //__SORT_ALGORITHM_H__