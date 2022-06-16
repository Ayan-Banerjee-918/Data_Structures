#include <stdio.h>
#include <stdlib.h>

typedef struct circularSinglyLL {
    int data;
    struct circularSinglyLL* next;
} node;

node* initialize(node* last){
    last = (node *)malloc(sizeof(node));
    last->next = NULL;
    return last;
}

node* addNodeFront(node* last,int val){
    if (last==NULL){
        last = initialize(last);
        last->next = last;
    }
    node* newNode = (node*)malloc(sizeof(node));
    if(last->next==NULL){
        last->data = val;
        last->next = last;
        return last;
    }
    newNode->data = val;
    newNode->next = last->next;
    last->next = newNode;
    return last;
}

node* addNodeEnd(node* last,int val){
    if (last==NULL){
        last = initialize(last);
        return addNodeFront(last, val);
    }
    node* newNode = (node*)malloc(sizeof(node));
    if (last->next == NULL) {
        last->data = val;
        last->next = last;
        return last;
    }
    newNode->data = val;
    newNode->next = last->next;
    last->next = newNode;
    last = newNode;
    return last;
}

node* addNodeMiddle(node* last,int pos,int val){
    if (last==NULL){
        last = initialize(last);
        return addNodeFront(last, val);
    }
    node *newNode = (node*)malloc(sizeof(node));
    node* tempNode = last->next;
    node* lastNode = NULL;
    int cnt = 0, flag = 0;
    if (pos < 0) {
        printf("Invalid Position Entered.\n");
        return last;
    }
    if (last->next == NULL) {
        if (pos != 0) {
            printf("Invalid Position! List is Empty!\n");
            return last;
        }
        printf("%d has been inserted into list at position %d.\n", val, pos + 1);
        last->data = val;
        last->next = last;
        return last;
    }
    if(pos==0){
        last = addNodeFront(last, val);
        printf("%d has been inserted into list at position %d.\n", val,pos+1);
        return last;
    }
    do{
        if(cnt==pos){
            flag = 1;
            if(tempNode->next==last->next){
                last = addNodeEnd(last, val);
                printf("%d has been inserted into list at position %d.\n", val,pos+1);
                return last;
            }
            newNode->data = val;
            newNode->next = tempNode;
            lastNode->next = newNode;
            printf("%d has been inserted into list at position %d.\n", val,pos+1);
            return last;
        }
        cnt += 1;
        lastNode = tempNode;
        tempNode = tempNode->next;
    }while(tempNode!=last->next);
    if(flag==0){
        printf("Invalid Position Entered.\n");
        return last;
    }
    return last;
}

node* deleteNode(node* last,int pos){
    node* tempNode;
    node *lastNode = NULL;
    if(last==NULL){
        printf("List is empty.\n");
        return last;
    }
    tempNode = last->next;
    if(pos<0){
        printf("Invalid Deletion Position.\n");
        return last;
    }
    int cnt = -1,flag=0;
    do{
        cnt++;
        if(cnt==pos){
            flag = 1;
            if(last->next==last){
                printf("%d has been deleted.\n", last->data);
                last = NULL;
                return last;
            }
            if(pos==0){
                printf("%d has been deleted.\n", tempNode->data);
                last->next = tempNode->next;
                return last;
            }
            if(tempNode->next==last->next){
                printf("%d has been deleted.\n", tempNode->data);
                lastNode->next = last->next;
                last = lastNode;
                return last;
            }
            printf("%d has been deleted.\n", tempNode->data);
            lastNode->next = tempNode->next;
            return last;
        }
        lastNode = tempNode;
        tempNode = tempNode->next;
    }while(tempNode!=last->next);
    if(flag==0){
        printf("Invalid Deletion Position.\n");
    }
    return last;
}

void searchElement(node* last, int val) {
    int pos = -1;
    if (last == NULL) {
        printf("List is Empty.\n");
        last = initialize(last);
        last->next = last;
        return;
    }
    node* tempNode = last->next;
    if (tempNode == NULL) {
        printf("List is Empty.\n");
        return;
    }
    do {
        pos++;
        if (tempNode->data == val) {
            printf("Element %d found at position %d\n", val, pos+1);
            return;
        }
        tempNode = tempNode->next;
    } while (tempNode != last->next);
    printf("Element %d not found in list\n", val);
}

void freeList(node* last) {
    if(last!=NULL)
        free(last);
    last = NULL;
    printf("List Memory Deallocated.\n");
}

void display(node* last)
{
    if (last == NULL) {
        printf("List is Empty.\n");
        last = initialize(last);
        last->next = last;
        return;
    }
    node* tempNode = last->next;
    if(tempNode==NULL){
        printf("List is Empty.\n");
        return;
    }
    printf("Values in List:\n");
    do{
        printf("%d ", tempNode->data);
        tempNode = tempNode->next;
    }while(tempNode!=last->next);
    printf("\n");
}

void main(){
    node *last = NULL;
    int choice = 0, data = 0, pos = 0;
    node *temp;
    int flag = 0;
    start:
    printf("\n__CIRCULAR LINKED LIST__\n");
    printf("1. Initialize Linked List\n");
    printf("2. Insert into Linked List\n");
    printf("3. Delete from Linked List\n");
    printf("4. Search Item in Linked List\n");
    printf("5. Display Linked List\n");
    printf("6. Free Linked List\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            if (flag == 1) {
                system("cls");
                printf("List already initialized.\n");
                goto start;
            }
            system("cls");
            last = initialize(last);
            flag = 1;
            printf("List has been initialized.\n");
            goto start;
        case 2:
            if(flag!=1){
                system("cls");
                printf("List not initialized.\n");
                goto start;
            }
            system("cls");
            insert:
            printf("\n__LIST ITEM INSERTION__\n");
            printf("1. Insert at Front\n");
            printf("2. Insert at Rear\n");
            printf("3. Insert at Middle\n");
            printf("4. Display List\n");
            printf("5. Back\n");
            printf("Enter your choice:");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                printf("Enter number to be inserted at front of linked list:");
                scanf("%d", &data);
                last = addNodeFront(last, data);
                system("cls");
                printf("%d has been inserted into list at front.\n", data);
                goto insert;
            case 2:
                printf("Enter number to be inserted at rear of linked list:");
                scanf("%d", &data);
                last = addNodeEnd(last, data);
                system("cls");
                printf("%d has been inserted into list at rear.\n", data);
                goto insert;
            case 3:
                printf("Enter number to be inserted at middle of linked list:");
                scanf("%d", &data);
                printf("Enter position(starts from 1) to be inserted at:");
                scanf("%d", &pos);
                system("cls");
                last = addNodeMiddle(last, pos-1, data);
                goto insert;
            case 4:
                system("cls");
                display(last);
                goto insert;
            case 5:
                system("cls");
                goto start;
            default:
                system("cls");
                printf("Invalid Option.Enter between 1 and 5.\n");
                goto insert;
            }
        case 3:
            if(flag!=1){
                system("cls");
                printf("List not initialized.\n");
                goto start;
            }
            system("cls");
            delete:
            printf("\n__LIST ITEM DELETION__\n");
            printf("1. Delete from Front\n");
            printf("2. Delete from Rear\n");
            printf("3. Delete from Middle\n");
            printf("4. Display List\n");
            printf("5. Back\n");
            printf("Enter your choice:");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                system("cls");
                last = deleteNode(last, 0);
                goto delete;
            case 2:
                system("cls");
                temp = last->next;
                pos = -1;
                do{
                    pos++;
                    temp = temp->next;
                } while (temp != last->next);
                last = deleteNode(last, pos);
                goto delete;
            case 3:
                printf("Enter position(starts from 1) to be deleted from the list:");
                scanf("%d", &pos);
                system("cls");
                last = deleteNode(last, pos-1);
                goto delete;
            case 4:
                system("cls");
                display(last);
                goto delete;
            case 5:
                system("cls");
                goto start;
            default:
                system("cls");
                printf("Invalid Option.Enter between 1 and 5.\n");
                goto insert;
            }
        case 4:
            if (flag != 1) {
                system("cls");
                printf("List not initialized.\n");
                goto start;
            }
            printf("Enter element to be searched for in the list:");
            scanf("%d", &data);
            system("cls");
            searchElement(last,data);
            goto start;
        case 5:
            if(flag!=1){
                system("cls");
                printf("List not initialized.\n");
                goto start;
            }
            system("cls");
            display(last);
            goto start;
        case 6:
            system("cls");
            flag = 0;
            freeList(last);
            goto start;
        case 7:
            exit(0);
        default:
            system("cls");
            printf("Invalid Option.Enter between 1 and 7.\n");
            goto start;
    }
}