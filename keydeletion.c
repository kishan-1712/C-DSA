#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};
struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void insert(struct Node** head, int data)
{
    struct Node* newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}
void display(struct Node* head)
{
    struct Node* temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void deleteNode(struct Node** head, int key)
{
    struct Node* temp = *head;
    while (temp != NULL && temp->data != key)
        temp = temp->next;
    if (temp == NULL)
        return;
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        *head = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    free(temp);
    printf("Node deleted successfully\n");
}
int main(){
    struct Node *head = NULL;
    int value, key;
    printf("enter 10 node values\n");
    for(int i=0;i<10;i++){
        scanf("%d",&value);
        insert(&head,value);
    }
    printf("\n Doubly linked list: ");
    display(head);
    printf("Enter the key to delete: ");
    scanf("%d",&key);
    deleteNode(&head,key);
    printf("\nDoubly linked list after deletion: ");
    display(head);
    return 0;
}