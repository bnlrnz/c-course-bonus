#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int data;
    struct _node * next;
}node;

void print_list(node* node){
    while (node != NULL){
        printf("%d->", node->data);
        node = node->next;
        if(node == NULL) printf("NULL\n");
    }
}

void push_front(node** root, int data){
    node* new_node = malloc(sizeof(node));
    new_node->data = data;
    new_node->next = *root;
    *root = new_node;
}

void pop_front(node** root){
    if(*root == NULL) return;
    node* new_root = (*root)->next;
    free(*root);
    if(new_root == NULL) return;
    *root = new_root;
}

void push_back(node* root, int data){
    if(root == NULL) return;
    node* new_node = malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;

    while(root->next != NULL){
        root = root->next;
    }

    root->next = new_node;
}

void pop_back(node* root){
    if(root == NULL) return;
    node* prev;
    while (root->next != NULL){
        prev = root;
        root = root->next;
    }
    free(root);
    prev->next = NULL;
}

void insert_at_index(node** root, int index, int data){
    if(*root == NULL) return;

    if (index == 0){
        push_front(root, data);
        return;
    }

    node* prev;

    prev = *root;
    while (index > 1){
        if(prev->next == NULL) break;
        prev = prev->next;
        index--;
    }

    node* new_node = malloc(sizeof(node));
    new_node->data = data;

    if(prev->next != NULL){
        new_node->next = prev->next;
    }else{
        new_node->next = NULL;
    }

    prev->next = new_node;
}

void remove_at_index(node** root, int index){
    if(*root == NULL) return;

    if (index == 0){
        pop_front(root);
        return;
    }
    
    node* prev;
    node* current;
    node* next;

    prev = NULL;
    current = *root;
    next = current->next;

    while (index > 0 && next != NULL){
        prev = current;    
        current = current->next;
        next = next->next;
        index--;
    }

    if (next == NULL){
        pop_back(*root);
        return;
    }
    
    free(current);
    prev->next = next;
}

void delete_list(node* root){
    while(root != NULL){
        node* next = root->next;
        free(root);
        root = next;
    }
}

node* search_rec(node* root, int value){
    if(root->data == value) return root;
    if(root->next != NULL) return search_rec(root->next, value);
    return NULL;
}

node* search_iter(node* root, int value){
    while(root != NULL){
        if (root->data == value){
            return root;
        }
        root = root->next;
    }
    return NULL;
}

// int main(int argc, char** argv){
//     int count = 1000;
//     if (argc > 1){
//         count = atoi(argv[1]);
//     }

//     node* root = malloc(sizeof(node));
//     root->data = 0;
//     root->next = NULL;

//     for (size_t i = 1; i < count; i++){
//         push_back(root, i);
//     }
    
//     printf("Searching for: %d\n", 0);
//     node* test = search_rec(root, 0);
//     printf("%p: %d\n", &test, test != NULL ? test->data : -1);

//     printf("Searching for: %d\n", count/2);
//     test = search_rec(root, count/2);
//     printf("%p: %d\n", &test, test != NULL ? test->data : -1);

//     printf("Searching for: %d\n", count-1);
//     test = search_rec(root, count-1);
//     printf("%p: %d\n", &test, test != NULL ? test->data : -1);

//     delete_list(root);
//     return 0;
// }

int main(void){
    node* root = malloc(sizeof(node));
    root->data = 42;
    root->next = NULL;

    push_front(&root, 41);
    push_back(root, 43);

    insert_at_index(&root, 2, 100);

    print_list(root);
    delete_list(root);
    return 0;
}