#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*function_type)(int *, int);

int sum(int *array, int size) {
    int sum = 0;
    int i;
    for (i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int cmp_m(const void *a, const void *b) {
    return (*((int *)a) - *((int *)b));
}

int cmp_l(const void *a, const void *b) {
    return -cmp_m(a, b);
}

void sort_m(int *array, int size) {
    qsort(array, size, sizeof(int), cmp_m);
}

void sort_l(int *array, int size) {
    qsort(array, size, sizeof(int), cmp_l);
}

void reverse(int *array, int size) {
    int i;
    for (i = 0; i < size / 2; i++) {
        swap(&array[i], &array[size - 1 - i]);
    }
}

function_type generator(int *array, int size) {
    if (sum(array, size) == array[0]) {
        return reverse;
    } else if (sum(array, size) > array[0]) {
        return sort_m;
    } else if (sum(array, size) < array[0]) {
        return sort_l;
    } else {
        return NULL;
    }
}

int main() {
    srand(time(NULL));

    int size = 15 + rand() % 21;
    int *array = malloc(sizeof(int) * size);

    int i;
    for (i = 0; i < size; i++) {
        array[i] = rand() % 50 - 25;
    }

    printf("array = [");
    for (i = 0; i < size; i++) {
        printf("%d%s", array[i], i == size - 1 ? "]\n" : ", ");
    }

    function_type f = generator(array, size);
    f(array, size);

    printf("array = [");
    for (i = 0; i < size; i++) {
        printf("%d%s", array[i], i == size - 1 ? "]\n" : ", ");
    }

    return 0;
}
