
#include <stdio.h>
#include <stdlib.h>3
struct Node {
    int coeff, x, y, z;
    struct Node *next;
};
struct Node* createNode(int c, int a, int b, int d) {
    struct Node *newNode =
        (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = c;
    newNode->x = a;
    newNode->y = b;
    newNode->z = d;
    newNode->next = NULL;
    return newNode;
}
void insert(struct Node **head, int c, int a, int b, int d) {
    struct Node *newNode = createNode(c, a, b, d);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}
void readPolynomial(struct Node **head) {
    int n, c, a, b, d;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponents of x, y, z: ");
        scanf("%d %d %d %d", &c, &a, &b, &d);
        insert(head, c, a, b, d);
    }
}
struct Node* add(struct Node *p1, struct Node *p2) {
    struct Node *result = NULL;
    while (p1 != NULL) {
        insert(&result, p1->coeff,
               p1->x, p1->y, p1->z);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        struct Node *temp = result;
        while (temp != NULL) {
            if (temp->x == p2->x &&
                temp->y == p2->y &&
                temp->z == p2->z) {
                temp->coeff += p2->coeff;
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL) {
            insert(&result, p2->coeff,
                   p2->x, p2->y, p2->z);
        }
        p2 = p2->next;
    }
    return result;
}
void display(struct Node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    while (head != NULL) {
        printf("%dx^%dy^%dz^%d",
               head->coeff,
               head->x, head->y, head->z);
        head = head->next;
        if (head != NULL)
            printf(" + ");
    }
    printf("\n");
}
int main() {
    struct Node *p1 = NULL;
    struct Node *p2 = NULL;
    struct Node *sum = NULL;
    printf("\nEnter First Polynomial:\n");
    readPolynomial(&p1);
    printf("\nEnter Second Polynomial:\n");
    readPolynomial(&p2);
    printf("\nFirst Polynomial: ");
    display(p1);
    printf("Second Polynomial: ");
    display(p2);
    sum = add(p1, p2);
    printf("\nAddition of Polynomials: ");
    display(sum);
    return 0;
}
