#ifndef __UTILS_H__
#define __UTILS_H__


/**
 * @brief      Initializes the random number generator
 *
 * @return     int value, should be > 0 if the generator has been initialized
 */
int init_rn_generator ();

/**
 * @brief      Initializes a array of integer, values will range from 0 to V_MAX (excluded)
 *
 * @param      t      array of integers should be at least of size N
 * @param[in]  N      number of values to initialize
 * @param[in]  V_MAX  max value (excluded) that the cell will have
 */
void init_array (int t[], unsigned int N, unsigned int V_MAX);

/**
 * @brief      Swat 2 cells in an array
 *
 * @param      t     array of integers should be at least of size max(i+1, j+1)
 * @param[in]  i     index of the first cell to swap
 * @param[in]  j    index of the second cell to swap
 */
void swap_value_in_array (int t[], unsigned int i, unsigned int j);

#endif //__UTILS_H__
