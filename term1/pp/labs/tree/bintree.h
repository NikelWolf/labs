#ifndef BINTREE_H
#define BINTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum direction_e { left,
                           right,
                           backward } direction;

typedef struct node_s {
    int element;
    int is_root;
    struct node_s *parent;
    struct node_s *left;
    struct node_s *right;
} node;

typedef node root;
typedef node tree;

node *create_node(int value);
root *create_root(int value);
tree *create_tree(int value);
void free_node(node *n);
void free_root(root *r);
void free_tree(tree *t);
unsigned int get_leaves(tree *t);
unsigned int get_inner_nodes(tree *t);
unsigned int get_nodes(tree *t);
void set_node_value(node *n, int value);
void remove_node(node *n, direction d);
node *add_node(node *n, direction d, int value);
node *change_node(node *n, direction d);
root *go_to_root(node *n);
void serialize_tree(tree *t, const char *filepath);
tree *deserialize_tree(const char *filepath);
tree *clear_tree(tree *t);
int is_tree_heap(tree *t);
void print_node_statistic(node *n);
void print_node_statistic_header();
void print_tree_statistic(tree *t);

#endif
