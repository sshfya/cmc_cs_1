#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000

int i_cmp_s = 0;//selection sort comparisons
int i_swp_s = 0;//selection sort swaps

int i_cmp_q = 0;//QuickSort comparisons
int i_swp_q = 0;//QuickSort swaps


int cmp( int a, int b)//comparing 2 numbers modulo
{
    i_cmp_s++;

    return abs(a) - abs(b);
}

void select_sort( int *arr, int size)
{
    i_cmp_s = 0;
    i_swp_s = 0;

    for (int i = 0; i < size - 1 ; i++){
        int flag = 0;
        int min_pos = i;//we will search in the still unsorted array for the minimum element
        int min_arr = arr[i];
        for (int j = i + 1; j < size ; j++) {
            if (cmp(arr[j], min_arr) < 0) {//if there is one, then we write it in min_arr
                //otherwise the current element is the minimum
                min_pos = j;
                min_arr = arr[min_pos];
                flag = 1;
            }
        }
        if (flag)
        {
            i_swp_s++;//swap the current and found minimum
            arr[min_pos] = arr[i];
            arr[i] = min_arr;
        }
    }
}

void gen_sorted(int size, int *arr)//generates an increasing array
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }
}

void gen_not_sorted(int size, int *arr)//generates a descending array
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = size - i - 1;
    }
}

void gen_random(int size, int *arr)//generates a random array
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() * rand() * rand() * rand() * rand() % MOD;
    }
}

void arr_generate(int size, int *arr)//prompts you to select the
// order of the elements of the generated array
{
    int type;
    printf("Input type of input array\n");
    printf("1: sorted\n");
    printf("2: sorted in reverse order\n");
    printf("3, 4: random\n ");
    scanf("%d", &type);

    if (type == 1)
        gen_sorted(size, arr);
    else if (type == 2)
        gen_not_sorted(size, arr);
    else
        gen_random(size, arr);
}

void sort_rec(int *arr, size_t low, size_t high)//The function takes a pointer
// to an array arr of type long long int, the ordinal numbers
//of elements of type size_t, which begins (variable low) and ends
//(variable high) the sorting section and sorts the received array
{
    size_t i = low, j = high;
    int sup = arr[(low + (high-low)/2)];//select element with middle index

    do
    {
        for (;cmp(arr[i], sup) < 0; i++, i_cmp_q++);
        //counting the number of comparisons
        for (;cmp(arr[j], sup) > 0; j--, i_cmp_q++);

        if (i <= j)
        {
            if (cmp(arr[i], arr[j]) > 0 && ++i_cmp_q)//execute if i<=j and the element with
                // index i is greater than the element arr[j]
            {
                int tmp = arr[i];//swap these elements
                arr[i] = arr[j];
                arr[j] = tmp;
                i_swp_q++;
            }

            i++;

            if (j > 0)
            {
                j--;
            }
        }
    } while (i <= j);

    if (i < high)//recursion
    {
        sort_rec(arr, i, high);
    }

    if (j > low)//recursion
    {
        sort_rec(arr, low, j);
    }
}

void quick_sort( int *arr, int size)//To perform sorting, this function calls
//the recursive sort_rec function.
{
    sort_rec(arr, 0, size - 1);
}

void print_arr( int *a, int size)//printing an array as a table
{
    for (int i = 0; i < size; i++)
    {
        printf("%4d ", i);
    }

    putchar('\n');

    for (int i = 0; i < size; i++)
    {
        printf("%4d ", a[i]);
    }

    putchar('\n');
}

int main(void)
{
    int *arr_s, *arr_q;
    srand(time(NULL));

    int n;
    printf("Input the number of tests: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\t>>>TEST %d<<<\n", i);

        int size;
        printf("Input size of arrays: ");
        scanf("%d", &size);

        arr_s = (int *)malloc(sizeof(int) * size);//create 2 arrays
        arr_q = (int *)malloc(sizeof(int) * size);
        //generate an array and make a copy of it
        arr_generate(size, arr_s);
        memcpy((void *)arr_q, (void *)arr_s, size * sizeof(int));

        printf("\t>>GENERATED ARRAY<<\n");
        print_arr(arr_s, size);

        select_sort(arr_s, size);
        printf("\n\t>>SELECT SORTED ARRAY<<\n");
        print_arr(arr_s, size);
        printf("COMPARISONS: %d\nSWAPS: %d\n", i_cmp_s, i_swp_s);

        i_cmp_q = 0;
        i_swp_q = 0;
        quick_sort(arr_q, size);
        printf("\n\t>>QUICK SORTED ARRAY<<\n");
        print_arr(arr_q, size);
        printf("COMPARISONS: %d\nSWAPS: %d\n", i_cmp_q, i_swp_q);

        free(arr_q);
        free(arr_s);
    }

    return 0;
}