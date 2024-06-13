#include <stdio.h>
#include <stdlib.h>


struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};


int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}


struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // New node is initially added at leaf
    return(node);
}


struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = height(y->left) > height(y->right) ? height(y->left) + 1 : height(y->right) + 1;
    x->height = height(x->left) > height(x->right) ? height(x->left) + 1 : height(x->right) + 1;

    return x;
}


struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    
    y->left = x;
    x->right = T2;

  
    x->height = height(x->left) > height(x->right) ? height(x->left) + 1 : height(x->right) + 1;
    y->height = height(y->left) > height(y->right) ? height(y->left) + 1 : height(y->right) + 1;

    
    return y;
}


int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


struct Node* insert(struct Node* node, int key) {
    
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node;

    node->height = height(node->left) > height(node->right) ? height(node->left) + 1 : height(node->right) + 1;

    
    int balance = getBalance(node);

  
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    
    return node;
}


void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d (Balance Factor: %d)\n", root->key, getBalance(root));
        preOrder(root->left);
        preOrder(root->right);
    }
}


int main() {
    struct Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    
    printf("Pre-order traversal of the AVL tree is:\n");
    preOrder(root);

    return 0;
}