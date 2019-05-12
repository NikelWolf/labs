#include <stdio.h>
#include <stdlib.h>

int max(int *array, int size) {
    int max = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] > array[max]) {
            max = i;
        }
    }
    return array[max];
}

int min(int *array, int size) {
    int min = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] > array[min]) {
            min = i;
        }
    }
    return array[min];
}

int sum(int *array, int size) {
    int sum = 0;
    int i;
    for (i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

int mult(int *array, int size) {
    int mult = 0;
    int i;
    for (i = 0; i < size; i++) {
        mult *= array[i];
    }
    return mult;
}

int main() {
    int (*f)(int *, int);
    int array[20] = {1, 2, 1, 2, 14, 5, 4, 5, 452, 54, 1, 54, 21, 4, 51, 5, 4};
    char op;

    printf("enter operation(^/_/+/*): ");
    if (scanf("%c", &op) != 1) {
        fprintf(stderr, "error while reading operation\nexit\n");
        exit(EXIT_FAILURE);
    }

    switch (op) {
    case '^': {
        f = max;
    } break;
    case '_': {
        f = min;
    } break;
    case '+': {
        f = sum;
    } break;
    case '*': {
        f = mult;
    } break;
    default: {
        fprintf(stderr, "error while reading operation type\nunsupported operation '%c'\nexit\n", op);
        exit(EXIT_FAILURE);
    } break;
    }

    printf("result = %d\n", f(array, 20));
    return 0;
}
