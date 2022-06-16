#include <stdio.h>
#include <stdlib.h>

typedef struct doublyLL {
    int data;
    struct doublyLL* next;
    struct doublyLL* prev;
} node;

node* insertFront(node* head, int data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;
    return head;
}

void insertBetween(node** prevNode, int data) {
    if ((*prevNode)->next == NULL && (*prevNode)->prev == NULL) {
        printf("Previous Node NULL");
        return;
    }
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = (*prevNode)->next;
    (*prevNode)->next = newNode;
    newNode->prev = *prevNode;
    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
}

node* insertEnd(node* head, int data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    node* temp;
    if (head->next == NULL && head->prev == NULL) {
        newNode->prev = NULL;
        head = newNode;
        return head;
    }
    temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

node* deleteNode(node* head, node* delNode) {
    if (head == NULL || delNode == NULL) {
        printf("No Nodes available to delete\n");
        return head;
    }
    if (head == delNode) {
        head = head->next;
    }
    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }
    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }
    delNode = NULL;
    return head;
}

void search(node* head,int val){
    node *temp = head;
    int pos = 0;
    int flag = 1;
    while(temp!=NULL){
        if(temp->data==val){
            printf("Element %d found at %d position in the linked list.",val,pos);
            flag = 0;
            break;
        }
        temp = temp->next;
        pos++;
    }
    if(flag==1){
        printf("Element not found in list.");
    }
}

void displayLL(node* head) {
    node* temp = head;
    printf("Values in list:\n");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    // initialize an empty node
    node* head = NULL;
    head = (node*)malloc(sizeof(node));
    head->prev = NULL;
    head->next = NULL;

    head = insertEnd(head, 5);
    head = insertFront(head, 1);
    head = insertFront(head, 6);
    head = insertEnd(head, 9);

    // insert 11 after head
    insertBetween(&head, 11);

    // insert 15 after the seond node
    insertBetween(&head->next, 15);

    displayLL(head);

    // delete the last node
    head = deleteNode(head, head->next->next);

    displayLL(head);
    system("pause");
    return 0;
}
