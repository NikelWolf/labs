#include <stdlib.h>
#include <string.h>

#include "stack.h"

static void init_stack(stack *st, size_t element_size) {
    st->array = NULL;
    st->element_size = element_size;
    st->current_number = 0;
}

stack *create_stack(size_t element_size) {
    stack *st = (stack *)malloc(sizeof(stack));

    init_stack(st, element_size);

    return st;
}

void free_stack(stack *st) {
    if (st) {
        if (st->array)
            free(st->array);
        free(st);
    }
}

int push(stack *st, void *element) {
    if (st) {
        void *tmp_array = malloc(st->element_size * (st->current_number + 1));

        memcpy(tmp_array, st->array, st->current_number * st->element_size);
        memcpy(tmp_array + (st->element_size * st->current_number), (void *)element, st->element_size);

        if (st->array)
            free(st->array);

        st->array = tmp_array;

        st->current_number++;

        return 1;
    }

    return 0;
}

int pop(stack *st, void *element) {
    if (st && st->array) {
        if (st->current_number > 0) {
            void *tmp_array = malloc(st->element_size * st->current_number);

            memcpy(tmp_array, st->array, (st->current_number - 1) * st->element_size);
            memcpy((void *)element, st->array + ((st->current_number - 1) * st->element_size), st->element_size);

            if (st->array)
                free(st->array);

            st->array = tmp_array;

            st->current_number--;

            return 1;
        }
    }

    return 0;
}
