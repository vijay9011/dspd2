#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct BTreeNode {
    int val[MAX + 1], count;
    struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *root;


struct BTreeNode *createNode(int val, struct BTreeNode *child) {
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}


void insertNode(int val, int pos, struct BTreeNode *node, struct BTreeNode *child) {
    int j = node->count;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}


void splitNode(int val, int *pval, int pos, struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newNode) {
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        insertNode(val, pos, node, child);
    } else {
        insertNode(val, pos - median, *newNode, child);
    }
    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

int setValue(int val, int *pval, struct BTreeNode *node, struct BTreeNode **child) {
    int pos;
    if (!node) {
        *pval = val;
        *child = NULL;
        return 1;
    }

    if (val < node->val[1]) {
        pos = 0;
    } else {
        for (pos = node->count; (val < node->val[pos] && pos > 1); pos--);
        if (val == node->val[pos]) {
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (setValue(val, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            insertNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

void insert(int val) {
    int flag, i;
    struct BTreeNode *child;

    flag = setValue(val, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}


void search(int val, int *pos, struct BTreeNode *node) {
    if (!node) {
        return;
    }

    if (val < node->val[1]) {
        *pos = 0;
    } else {
        for (*pos = node->count; (val < node->val[*pos] && *pos > 1); (*pos)--);
        if (val == node->val[*pos]) {
            printf("Found %d\n", val);
            return;
        }
    }
    search(val, pos, node->link[*pos]);
    return;
}


void traverse(struct BTreeNode *node) {
    int i;
    if (node) {
        for (i = 0; i < node->count; i++) {
            traverse(node->link[i]);
            printf("%d ", node->val[i + 1]);
        }
        traverse(node->link[i]);
    }
}

int main() {
    int val, ch;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Search\n");
        printf("3. Traverse\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &val);
                insert(val);
                break;
            case 2:
                printf("Enter the value to search: ");
                scanf("%d", &val);
                search(val, &ch, root);
                break;
            case 3:
                traverse(root);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}