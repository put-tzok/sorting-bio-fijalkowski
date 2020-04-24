#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 10,100,1000 ,10000, 100000};

void fill_increasing(int *t, unsigned int n)
{
    for(int i = 0; i < n; i++)
    {
        t[i] = i;
    }
}

void fill_decreasing(int *t, unsigned int n)
{
    for (int i = 0 ; i < n ; i++ )
    {
        t[i] = n-i;

    }
}
void fill_vshape(int *t, unsigned int n)
{
    int i = 0, j = 0;
    int m = n-1;




    for (int i = 0; i <= (n/2); i++)
    {
        //JUMP from assigning n-i to t[i] or t[n-1]
        // i = 1, t[0] = n

        t[i] = m-j;
        t[m-i] = t[i]-1;
        j++;
        j++;



    }
}

//POCZATEK SELECTION SORT
void selection_sort (int *t, unsigned n)
{
    int temp;
    int j;
    int i;
    for (i = 0; i < n; i++)
    {

        j = argmin(t, n, i);

        temp = t[j];
        t[j] = t[i];
        t[i] = temp;
        ;


    }
}

int argmin(int *t, unsigned n, int i)
{
    int argmin = i;
    for (int j = i+1; j < n; j++)
    {
        if(t[j] < t[argmin])
        {
            argmin = j;
        }
    }

    return argmin;
}
//KONIEC SELECTION SORT



void insertion_sort(int *t, unsigned int n)
{

    int i,j,key;

    for(j = 1; j < n; j++)
    {

        key = t[j];
        i = j-1;

        while (i>=0 && t[i]>key)
        {
            t[i+1] = t[i];
            i--;
        }
        t[i+1] = key;
    }

}



//POCZATEK QUICK_SORT
void quicksort(int *t, int p, int r);


int partition(int *t, int p, int r)
{
    int piv,i,j,tmp;
    piv = t[r];
    i = p - 1;
    for (j = p ; j < r; j++)
    {
        if( t[j] <= piv )
        {
            i++;
            tmp = t[i];
            t[i] = t[j];
            t[j] = tmp;

        }
    }

    i++;
    tmp = t[i];
    t[i] = t[r];
    t[r] = tmp;
    return i;
}

int quick_random(int *t, int p, int r)
{



    int i = p + rand() % (r-p);
    int tmp;

    tmp = t[i];
    t[i] = t[r];
    t[r] = tmp;

    return partition(t,p,r);

}

void quicksort(int *t, int p, int r)
{
    int q;
    if (p<r)
    {
        q = quick_random(t, p, r);
        //q = partition(t, p, r);
        quicksort(t, q+1, r);
        quicksort(t, p, q-1);
    }
}

void quick_sort(int *t, unsigned int n)
{

    quicksort(t, 0, n-1);
}
//KONIEC QUICK_SORT


void heap_sort(int *t, unsigned int n)
{
    ;// TODO
}

void fill_random(int *t, unsigned int n)
{
    for (unsigned int i = 0; i < n; i++)
    {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n)
{
    return;
}

void is_increasing(int *t, unsigned int n)
{
    for (unsigned int i = 1; i < n; i++)
    {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n)
{
    for (unsigned int i = 1; i < n; i++)
    {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n)
{
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1)
    {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n)
{
    for (unsigned int i = 1; i < n; i++)
    {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, /* heap_sort */};

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main()
{
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++)
    {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++)
        {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++)
            {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
