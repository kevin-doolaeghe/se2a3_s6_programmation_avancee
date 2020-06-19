/**
 * @brief      This file implements unit tests for sorting algorithms
 *
 * @author     Jeremie
 * @date       2020
 */
#include <check.h>
#include <sort_algorithms.h>
#include <stdlib.h>
#include <utils.h>

START_TEST (test_rn) { ck_assert (init_rn_generator () == 1); }
END_TEST

START_TEST (test_init)
{
    const unsigned int V = 10;
    const unsigned int T = 5;
    int                array[T];
    init_array (array, T, V);
    for (unsigned int i = 0; i < T; i++)
    {
        ck_assert (array[i] >= 0);
        ck_assert (array[i] < (int)V);
    }
}
END_TEST

START_TEST (test_swap)
{
    const unsigned int T = 5;
    int                tableau[T];

    const int first_value  = 10;
    const int second_value = -3;

    const int first_index  = 0;
    const int second_index = 3;

    tableau[first_index]  = first_value;
    tableau[second_index] = second_value;

    swap_value_in_array (tableau, first_index, second_index);

    ck_assert (tableau[first_index] == second_value);
    ck_assert (tableau[second_index] == first_value);
}
END_TEST

START_TEST (test_selection_sort)
{
    const unsigned int T = 100;
    const unsigned int V = 10;

    int tableau[T];
    init_array (tableau, T, V);
    selection_sort (tableau, T);

    for (unsigned int i = 0; i < T - 1; i++) ck_assert (tableau[i] <= tableau[i + 1]);
}
END_TEST

START_TEST (test_insertion_sort)
{
    const unsigned int T = 100;
    const unsigned int V = 10;

    int tableau[T];
    init_array (tableau, T, V);
    insertion_sort (tableau, T);

    for (unsigned int i = 0; i < T - 1; i++) ck_assert (tableau[i] <= tableau[i + 1]);
}
END_TEST

START_TEST (test_merge_sort)
{
    const unsigned int T = 100;
    const unsigned int V = 10;

    int tableau[T];
    init_array (tableau, T, V);
    merge_sort (tableau, T);

    for (unsigned int i = 0; i < T - 1; i++) ck_assert (tableau[i] <= tableau[i + 1]);
}
END_TEST

Suite *sort_suite (void)
{
    Suite *s       = suite_create ("SortAlgorithms");
    TCase *tc_core = tcase_create ("Core");
    tcase_add_test (tc_core, test_rn);
    tcase_add_test (tc_core, test_init);
    tcase_add_test (tc_core, test_swap);
    TCase *tc_sorts = tcase_create ("Sorts");
    tcase_add_test (tc_core, test_insertion_sort);
    tcase_add_test (tc_core, test_selection_sort);
    tcase_add_test (tc_core, test_merge_sort);
    suite_add_tcase (s, tc_core);
    suite_add_tcase (s, tc_sorts);

    return s;
}

int main (void)
{
    int      no_failed = 0;
    Suite *  s         = sort_suite ();
    SRunner *runner    = srunner_create (s);
    srunner_run_all (runner, CK_NORMAL);
    no_failed = srunner_ntests_failed (runner);
    srunner_free (runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
