/**
 * @brief      This file implements utility functions for arrays
 *
 * @author     Jeremie
 * @date       2020
 */
#include <stdlib.h>
#include <time.h>
#include <utils.h>

int init_rn_generator ()
{
    static unsigned int is_rn_seed_loaded = 0;
    if (is_rn_seed_loaded == 0)
    {
        srand (time (NULL));
        is_rn_seed_loaded++;
    }
    return is_rn_seed_loaded;
}

void init_array (int t[], unsigned int N, unsigned int V_MAX)
{
    for (unsigned int i = 0; i < N; i++)
    {
        t[i] = rand () % V_MAX;
    }
}

void swap_value_in_array (int t[], unsigned int i, unsigned int j)
{
    int temp = t[i];
    t[i]     = t[j];
    t[j]     = temp;
}
