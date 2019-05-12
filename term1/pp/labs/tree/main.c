#include "bintree.h"
#include "string_worker.h"
#include "tree_printer.h"

#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"

root *tree_root;
node *cur_node;
void init_root() {
    tree_root = cur_node = create_root(0);
}

char **parse_command_on_args(const char *command) {
    char *striped_line = string_lrstrip(command);
    char **args = string_split(command, " ", -1);
    free(striped_line);
    return args;
}

void help() {
    printf(YELLOW
           "help:     print list of commands\n"
           "print:    print tree statistic\n"
           "info:     print count of leaves, inner nodes, nodes and check if tree is heap\n"
           "drawtree: draw ascii view of tree\n"
           "draw:     draw ascii view of tree started on current node\n"
           "set:      set current node to value\n"
           "root:     go back to root node\n"
           "back:     go back to parent node\n"
           "left:     go to left node from this if possible\n"
           "right:    go to right node from this if possible\n"
           "addleft:  add new node on left or right side\n"
           "addright: add new node on left or right side\n"
           "remleft:  remove left node and all subnodes\n"
           "remright: remove right node and all subnode\n"
           "save:     save tree to file\n"
           "load:     load tree from file\n"
           "clear:    clear tree\n"
           "exit:     exit from program\n" WHITE);
}

int get_number(char *string, int *number) {
    char *end;
    *number = strtol(string, &end, 10);
    if (string == end)
        return 0;

    return 1;
}

int main() {
    printf("Hello. Enter commands after greeting symbols '>>'. To show list of command print 'help'. To exit print 'exit'\n");
    init_root();
    while (1) {
        printf(">> ");

        char *line = NULL;
        size_t size;
        getline(&line, &size, stdin);
        line[strlen(line) - 1] = '\0';

        char **args = parse_command_on_args(line);
        int args_count = string_array_length((const char **)args);
        if (args_count >= 1) {
            if (string_equal(args[0], "help")) {
                help();
            } else if (string_equal(args[0], "print")) {
                printf(BLUE);
                print_tree_statistic(tree_root);
                printf(WHITE);
            } else if (string_equal(args[0], "info")) {
                printf(BLUE);
                printf("leaves: %u\ninner nodes: %u\nnodes: %u\nis heap: %s\n", get_leaves(tree_root), get_inner_nodes(tree_root), get_nodes(tree_root), is_tree_heap(tree_root) ? "true" : "false");
                printf(WHITE);
            } else if (string_equal(args[0], "drawtree")) {
                printf(GREEN);
                print_ascii_tree(tree_root);
                printf(WHITE);
            } else if (string_equal(args[0], "draw")) {
                printf(GREEN);
                print_ascii_tree(cur_node);
                printf(WHITE);
            } else if (string_equal(args[0], "set")) {
                if (args_count >= 2) {
                    int number;
                    if (get_number(args[1], &number)) {
                        set_node_value(cur_node, number);
                    } else {
                        printf(RED "error: not number argument '%s'\n" WHITE, args[1]);
                    }
                } else {
                    printf(RED "error: not enought arguments\n" WHITE);
                }
            } else if (string_equal(args[0], "addleft")) {
                if (args_count >= 2) {
                    int number;
                    if (get_number(args[1], &number)) {
                        add_node(cur_node, left, number);
                    } else {
                        printf(RED "error: not number argument '%s'\n" WHITE, args[1]);
                    }
                } else {
                    printf(RED "error: not enought arguments\n" WHITE);
                }
            } else if (string_equal(args[0], "addright")) {
                if (args_count >= 2) {
                    int number;
                    if (get_number(args[1], &number)) {
                        add_node(cur_node, right, number);
                    } else {
                        printf(RED "error: not number argument '%s'\n" WHITE, args[1]);
                    }
                } else {
                    printf(RED "error: not enought arguments\n" WHITE);
                }
            } else if (string_equal(args[0], "root")) {
                cur_node = go_to_root(cur_node);
            } else if (string_equal(args[0], "back")) {
                cur_node = change_node(cur_node, backward);
            } else if (string_equal(args[0], "left")) {
                cur_node = change_node(cur_node, left);
            } else if (string_equal(args[0], "right")) {
                cur_node = change_node(cur_node, right);
            } else if (string_equal(args[0], "remleft")) {
                remove_node(cur_node, left);
            } else if (string_equal(args[0], "remright")) {
                remove_node(cur_node, right);
            } else if (string_equal(args[0], "save")) {
                if (args_count >= 2) {
                    serialize_tree(tree_root, args[1]);
                } else {
                    printf(RED "error: not enought arguments\n" WHITE);
                }
            } else if (string_equal(args[0], "load")) {
                if (args_count >= 2) {
                    free_root(tree_root);
                    tree_root = deserialize_tree(args[1]);
                    if (tree_root == NULL) {
                        printf(RED "init tree root with o\n" WHITE);
                        tree_root = create_root(0);
                    }
                } else {
                    printf(RED "error: not enought arguments\n" WHITE);
                }
            } else if (string_equal(args[0], "clear")) {
                tree_root = cur_node = clear_tree(tree_root);
            } else if (string_equal(args[0], "exit")) {
                string_free_splited_array(args);
                break;
            } else {
                printf(RED "error: unknown command\n" WHITE);
            }
        } else {
            printf(RED "error: empty line\n" WHITE);
        }

        string_free_splited_array(args);
    }

    free_root(tree_root);

    return 0;
}
