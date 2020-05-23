#include <stdio.h>

//----------------------------------------------

void conversion(int h, int *p_m, int *p_s) {
    *p_m = h * 60;
    *p_s = h * 3600;
}

void ex2() {
    int h = 35;
    int m = 0;
    int s = 0;

    conversion(h, &m, &s);
    printf("%d %d %d", h, m, s);
}

//----------------------------------------------

void calcMinEtMax(int *tab, unsigned int n, int *p_min, int *p_max) {
    *p_min = *tab;
    *p_max = *tab;

    for (unsigned int i = 0; i < n; i++) {
        if (*tab < *p_min) *p_min = *tab;
        if (*tab > *p_max) *p_max = *tab;
        tab++;
    }
}

void ex3() {
    unsigned int n = 5;
    int tab[n];
    int min;
    int max;

    calcMinEtMax(tab, n, &min, &max);

    printf("\nmin : %d\nmax : %d", min, max);
}

//----------------------------------------------

void ex4() {
    int tab[2] = {0, 0};

    printf("%d", tab[10]);
}

//----------------------------------------------

//typedef int **DOUBLE_PTR_INT;

void ex5() {
    int v = 12;
    int *pv = &v;
    int **ppv = &pv;

    printf("%d %d %d", v, *pv, **ppv);
}

//----------------------------------------------

void proc(int n, int p, int *q) {

}

void ex6() {
    int n = 3;
    int p = 5;
    int q;

    proc(n, p, &q);
}

//----------------------------------------------

int main()
{
    //ex2();
    //ex3();
    //ex4();
    ex5();
    ex6();

    return 0;
}
