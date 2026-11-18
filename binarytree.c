#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *left, *right;
};                           
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}
int searchBST(struct Node* root, int key, int *accesses) {
    *accesses = 0;
    struct Node* current = root;
    while (current != NULL) {
        (*accesses)++;
        if (key == current->data) {
            return 1;
        } else if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return 0;
}
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
int main() {
    struct Node* root = NULL;
    int n, data, key, accesses;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter node value: ");
        scanf("%d", &data);
        root = insertNode(root, data);
    }
    printf("Inorder Traversal: ");
    inOrder(root);
    printf("\nPreorder Traversal: ");
    preorder(root);
    printf("\nPostorder Traversal: ");
    postorder(root);
    printf("\nEnter key to search: ");
    scanf("%d", &key);
    if (searchBST(root, key, &accesses)) {
        printf("Key %d found with %d accesses.\n", key, accesses);
    } else {
        printf("Key %d not found with %d accesses.\n", key, accesses);
    }

    freeTree(root);
    return 0;
}