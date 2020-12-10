#include <stdio.h>
#include <stdlib.h>

typedef struct _tree_node{
    int data;
    struct _tree_node* left;
    struct _tree_node* right;
}tree_node;

void insert(tree_node** tree, int value){
    tree_node* temp = NULL;
    if (*tree == NULL){
        temp = malloc(sizeof(tree_node));
        temp->left = NULL;
        temp->right = NULL; 
        temp->data = value;
        *tree = temp;
        return;
    }

    if ((*tree)->data > value){
        insert(&(*tree)->left, value);
    }

    if ((*tree)->data < value){
        insert(&(*tree)->right, value);
    }    
}

void print_inorder(tree_node* tree){
    if (tree != NULL){
        print_inorder(tree->left);
        printf("%d\n",tree->data);
        print_inorder(tree->right);
    }
}

void delete_tree(tree_node* tree){
    if (tree != NULL){
        delete_tree(tree->left);
        delete_tree(tree->right);
        free(tree);
    }
}

tree_node* search(tree_node* node, int value){
    if(node == NULL) return NULL;
    if(value < node->data) return search(node->left, value);
    if(value > node->data) return search(node->right, value);
    if(value == node->data) return node;
    return NULL;
}

int main(int argc, char** argv){

    int count = 1000;
    if (argc > 1){
        count = atoi(argv[1]);
    }

    tree_node* root = NULL;
    for (size_t i = 0; i < count; i++){
        insert(&root, i);
    }

    printf("Searching for: %d\n", 0);
    tree_node* test = search(root, 0);
    printf("%p: %d\n", &test, test != NULL ? test->data : -1);

    printf("Searching for: %d\n", count/2);
    test = search(root, count/2);
    printf("%p: %d\n", &test, test != NULL ? test->data : -1);

    printf("Searching for: %d\n", count-1);
    test = search(root, count-1);
    printf("%p: %d\n", &test, test != NULL ? test->data : -1);

    delete_tree(root);
    return 0;
}