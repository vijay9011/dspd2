#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};


struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}


struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}


struct Node* deleteLeaf(struct Node* root, int key, int* deleted) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteLeaf(root->left, key, deleted);
    else if (key > root->key)
        root->right = deleteLeaf(root->right, key, deleted);
    else {
        
        if (root->left == NULL && root->right == NULL) {
            free(root);
            *deleted = 1;
            return NULL;
        }
    }
    return root;
}


int main() {
    struct Node* root = NULL;
    int choice, key, deleted;

    while (1) {
        printf("\n1. Search an element in BST\n");
        printf("2. Insert an element in BST\n");
        printf("3. Delete leaf element in BST\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to search: ");
                scanf("%d", &key);
                struct Node* result = search(root, key);
                if (result == NULL) {
                    printf("NULL\n");
                } else {
                    printf("Found\n");
                }
                break;

            case 2:
                printf("Enter the element to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Element inserted\n");
                break;

            case 3:
                printf("Enter the leaf element to delete: ");
                scanf("%d", &key);
                deleted = 0;
                root = deleteLeaf(root, key, &deleted);
                if (deleted) {
                    printf("Leaf node with value %d deleted.\n", key);
                } else {
                    printf("Node with value %d is not a leaf or not found.\n", key);
                }
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}