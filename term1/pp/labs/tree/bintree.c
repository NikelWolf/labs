#include "bintree.h"

static void init_node(node *n, int value) {
    n->element = value;
    n->is_root = 0;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
}

node *create_node(int value) {
    node *n = (node *)malloc(sizeof(node));

    init_node(n, value);

    return n;
}

root *create_root(int value) {
    node *n = create_node(value);

    n->is_root = 1;

    return n;
}

tree *create_tree(int value) {
    return create_root(value);
}

void free_node(node *n) {
    if (n) {
        if (n->left)
            free_node(n->left);
        if (n->right)
            free_node(n->right);

        free(n);
    }
}

void free_root(root *r) {
    free_node(r);
}

void free_tree(tree *t) {
    free_node(t);
}

static unsigned int count_leaves(tree *t) {
    if (t == NULL)
        return 0;

    unsigned int leaves = 0;
    if (t->left)
        leaves += count_leaves(t->left);
    else
        leaves++;

    if (t->right)
        leaves += count_leaves(t->right);
    else
        leaves++;

    return leaves;
}

unsigned int get_leaves(tree *t) {
    if (t == NULL)
        return 0;

    return count_leaves(t);
}

static unsigned int count_inner_nodes(tree *t) {
    if (t == NULL)
        return 0;

    unsigned int nodes = 1;
    if (t->left)
        nodes += count_inner_nodes(t->left);

    if (t->right)
        nodes += count_inner_nodes(t->right);

    return nodes;
}

unsigned int get_inner_nodes(tree *t) {
    if (t == NULL)
        return 0;

    return count_inner_nodes(t);
}

unsigned int get_nodes(tree *t) {
    if (t == NULL)
        return 0;

    return count_inner_nodes(t) + count_leaves(t);
}

void set_node_value(node *n, int value) {
    n->element = value;
}

void remove_node(node *n, direction d) {
    if (n == NULL)
        return;

    switch (d) {
    case left: {
        free_node(n->left);

        n->left = NULL;
    } break;
    case right: {
        free_node(n->right);

        n->right = NULL;
    } break;
    default: {
        return;
    } break;
    }
}

node *add_node(node *n, direction d, int value) {
    if (n == NULL) {
        return NULL;
    }

    node *chld = create_node(value);

    switch (d) {
    case left: {
        if (n->left)
            free_node(n->left);

        n->left = chld;
        chld->parent = n;
    } break;
    case right: {
        if (n->right)
            free_node(n->right);

        n->right = chld;
        chld->parent = n;
    } break;
    default: {
        return NULL;
    } break;
    }

    return chld;
}

node *change_node(node *n, direction d) {
    if (n == NULL)
        return NULL;

    switch (d) {
    case left: {
        if (n->left)
            return n->left;

        return n;
    } break;
    case right: {
        if (n->right)
            return n->right;

        return n;
    } break;
    case backward: {
        if (n->parent)
            return n->parent;

        return n;
    } break;
    default: {
        return n;
    } break;
    }
}

root *go_to_root(node *n) {
    if (n == NULL)
        return NULL;

    if (n->is_root)
        return n;

    return go_to_root(n->parent);
}

static void serialize_node(node *n, FILE *file) {
    if (n == NULL)
        return;

    fprintf(file, " ( %d%c%c", n->element, n->left ? '+' : '-', n->right ? '+' : '-');

    if (n->left)
        serialize_node(n->left, file);
    else
        fprintf(file, " ()");

    if (n->right)
        serialize_node(n->right, file);
    else
        fprintf(file, " ()");

    fprintf(file, " )");
}

void serialize_tree(tree *t, const char *filepath) {
    if (t == NULL || t->is_root == 0)
        return;

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "\x1b[31m"
                        "error: serialize\n"
                        "\x1b[37m");
        return;
    }

    serialize_node(t, file);

    fclose(file);
}

static node *deserialize_node(node *n, FILE *file) {
    int number;
    char left_char;
    char right_char;

    node *chld;
    fscanf(file, " ( %d%c%c", &number, &left_char, &right_char);
    chld = create_node(number);

    if (left_char == '+')
        chld->left = deserialize_node(chld, file);
    else
        fscanf(file, " ()");

    if (right_char == '+')
        chld->right = deserialize_node(chld, file);
    else
        fscanf(file, " ()");

    fscanf(file, " )");

    chld->parent = n;

    return chld;
}

tree *deserialize_tree(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "\x1b[31m"
                        "error: deserialize\n"
                        "\x1b[37m");
        return NULL;
    }

    root *r = deserialize_node(NULL, file);
    r->is_root = 1;

    fclose(file);

    return r;
}

tree *clear_tree(tree *t) {
    free_node(t);

    return create_tree(0);
}

static int is_node_part_of_heap(node *n) {
    if (n == NULL)
        return 1;

    if (n->left == NULL && n->right == NULL)
        return 1;

    if (n->left == NULL && n->right != NULL)
        return 0;

    if (n->left != NULL && n->left->element > n->element)
        return 0;

    if (n->right != NULL && n->right->element > n->element)
        return 0;

    return is_node_part_of_heap(n->left) && is_node_part_of_heap(n->right);
}

int is_tree_heap(tree *t) {
    if (t == NULL)
        return 0;

    return is_node_part_of_heap(t);
}

void print_node_statistic(node *n) {
    printf("[ %14p => %11d | %4d | %14p | %14p | %14p ]\n", n, n->element, n->is_root, n->parent, n->left, n->right);
}

void print_node_statistic_header() {
    printf("[     %s    =>     %s   | %s |      %s    |      %s      |      %s     ]\n", "current", "value", "root", "parent", "left", "right");
}

void print_tree_statistic(tree *t) {
    if (t) {
        if (t->is_root == 1) {
            print_node_statistic_header();
            printf("\n");
        }

        print_node_statistic(t);
    } else
        return;

    print_tree_statistic(t->left);
    print_tree_statistic(t->right);
}
