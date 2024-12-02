/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 12/01/2024
 * Description: Program that implements a tree data structure
 ---------------------------------------------*/
#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Helper function to create a new tree node
struct tree_node* create_node(const char* name) {
    struct tree_node* new_node = malloc(sizeof(struct tree_node));
    if (!new_node) {
        perror("Failed to allocate memory for tree node");
        exit(EXIT_FAILURE);
    }
    strncpy(new_node->data.name, name, sizeof(new_node->data.name)-1);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct tree_node* find(const char* name, struct tree_node* root) {
    if (root == NULL) return NULL; // Not found
    int cmp = strcmp(name, root->data.name);
    if (cmp == 0) return root;     // Found
    return (cmp < 0) ? find(name, root->left) : find(name, root->right); // Search left or right
}

struct tree_node* insert(const char* name, struct tree_node* root) {
    if (root == NULL) return create_node(name); // Insert at the root
    int cmp = strcmp(name, root->data.name);
    if (cmp < 0) root->left = insert(name, root->left);  // Left subtree
    else if (cmp > 0) root->right = insert(name, root->right); // Right subtree
    return root;
}

void clear(struct tree_node* root) {
    if (root == NULL) return;
    clear(root->left);
    clear(root->right);
    free(root);
}

// Internal helper function to handle indentation and recursive printing
void print_helper(struct tree_node* root, int depth) {
    if (root == NULL) return;

    printf("%s\n", root->data.name);

    // Print left child
    if (root->left) {
        for (int i = 0; i < depth + 1; i++) {
            printf(" ");
        }
        printf("l:");
        print_helper(root->left, depth + 1);
    }

    // Print right child
    if (root->right) {
        for (int i = 0; i < depth + 1; i++) {
            printf(" ");
        }
        printf("r:");
        print_helper(root->right, depth + 1);
    }
}

void print(struct tree_node* root) {
    print_helper(root, 0); // Start with depth 0
}

void printSorted(struct tree_node* root) {
    if (root == NULL) return;
    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
}

