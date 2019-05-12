#ifndef TREE_PRINTER_H
#define TREE_PRINTER_H

#define INFINITY (1 << 20)
#define MAX_HEIGHT 1000

;

typedef struct asciinode_struct {
    struct asciinode_struct *left;
    struct asciinode_struct *right;
    int edge_length;
    int height;
    int lablen;
    int parent_dir;
    char label[11];
} asciinode;

#include "bintree.h"

asciinode *build_ascii_tree_recursive(tree *t);
asciinode *build_ascii_tree(tree *t);
void free_ascii_tree(asciinode *node);
void free_ascii_tree(asciinode *node);
void compute_lprofile(asciinode *node, int x, int y);
void compute_rprofile(asciinode *node, int x, int y);
void compute_edge_lengths(asciinode *node);
void print_level(asciinode *node, int x, int level);
void print_ascii_tree(tree *t);

#endif
