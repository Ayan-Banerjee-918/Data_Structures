#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedList
{
    int data;
    struct LinkedList* link;
}list;

list* topNode, * front, * rear;
int createCheck = 0;

list* createStack(list*);
list* createQueue(list*);
bool isEmptyStack();
bool isEmptyQueue();
list* pushStack(list*, int);
list* enQueue(list*, int);
list* popStack(list*);
list* deQueue(list*);
void peekStack(list*);
void peekQueue(list*);
void displayStack(list*);
void displayQueue(list*);
list* freeStack(list*);
void freeQueue(list*);
int queueMenu();
int stackMenu();

list* createStack(list* temp) {
    temp = (list*)malloc(sizeof(list));
    temp->link = NULL;
    topNode = NULL;
    system("cls");
    printf("Stack created!\n");
    return temp;
}

list* createQueue(list* temp) {
    temp = (list*)malloc(sizeof(list));
    temp->link = NULL;
    front = NULL;
    rear = NULL;
    system("cls");
    printf("Queue created!\n");
    return temp;
}

bool isEmptyStack() {
    if (topNode == NULL) {
        return true;
    }
    return false;
}

bool isEmptyQueue() {
    if (front == NULL) {
        return true;
    }
    return false;
}

list* pushStack(list* temp, int val) {
    if (isEmptyStack()) {
        temp->data = val;
    }
    else {
        list* newNode = (list*)malloc(sizeof(list));
        newNode->data = val;
        newNode->link = temp;
        temp = newNode;
    }
    topNode = temp;
    system("cls");
    printf("%d pushed into stack\n", val);
    return temp;
}

list* enQueue(list* temp, int val) {
    list* node = (list*)malloc(sizeof(list));
    node->data = val;
    node->link = NULL;
    if (isEmptyQueue()) {
        rear = front = temp = node;
        system("cls");
        printf("%d pushed into queue\n", val);
        return temp;
    }
    rear->link = node;
    rear = node;
    system("cls");
    printf("%d pushed into queue\n", val);
    return temp;
}

list* popStack(list* temp) {
    list* node;
    if (isEmptyStack()) {
        system("cls");
        printf("Stack is Empty\n");
    }
    else {
        system("cls");
        printf("%d popped from stack\n", temp->data);
        node = temp;
        temp = temp->link;
        free(node);
        topNode = temp;
    }
    return temp;
}

list* deQueue(list* temp) {
    if (isEmptyQueue()) {
        system("cls");
        printf("Queue is Empty\n");
    }
    else {
        system("cls");
        printf("%d removed from queue\n", front->data);
        front = front->link;
        temp = temp->link;
    }
    return temp;
}

void peekStack(list* temp) {
    if (isEmptyStack()) {
        system("cls");
        printf("Stack is Empty\n");
    }
    else {
        system("cls");
        printf("%d is at top of stack\n", temp->data);
    }
}

void peekQueue(list* temp) {
    if (isEmptyQueue()) {
        system("cls");
        printf("Queue is Empty\n");
    }
    else {
        system("cls");
        printf("%d is at front of queue\n", front->data);
    }
}

void displayStack(list* temp) {
    list* traverseNode;
    if (isEmptyStack()) {
        system("cls");
        printf("Stack is Empty\n");
    }
    else {
        traverseNode = temp;
        system("cls");
        printf("Stack Elements are:\n");
        while (traverseNode != NULL) {
            printf("%d\n", traverseNode->data);
            traverseNode = traverseNode->link;
        }
    }
}

void displayQueue(list* temp) {
    list* traverseNode;
    if (isEmptyQueue()) {
        system("cls");
        printf("Queue is Empty\n");
    }
    else {
        traverseNode = temp;
        system("cls");
        printf("Queue Elements are:\n");
        while (traverseNode != NULL) {
            printf("%d ", traverseNode->data);
            traverseNode = traverseNode->link;
        }
        printf("\n");
    }
}

list* freeStack(list* temp) {
    temp = NULL;
    system("cls");
    printf("Stack Freed!\n");
    return temp;
}

void freeQueue(list* temp) {
    temp = NULL;
    front = NULL;
    rear = NULL;
    system("cls");
    printf("Queue Freed!\n");
}

int stackMenu() {
    list* newStack = NULL;
    int choice, element = 0;
start:
    printf("\n__STACK__\n");
    printf("1. Create Stack\n");
    printf("2. Push into Stack\n");
    printf("3. Pop from Stack\n");
    printf("4. Peek Stack\n");
    printf("5. Display Stack\n");
    printf("6. Free Stack\n");
    printf("7. Return Back to Main Menu\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        if (newStack == NULL && createCheck == 0) {
            newStack = createStack(newStack);
            createCheck = 1;
            goto start;
        }
        else {
            system("cls");
            printf("Stack has already been created\n");
            goto start;
        }
    case 2:
        if (createCheck != 0) {
            if (newStack == NULL) {
                newStack = createStack(newStack);
            }
            printf("Enter element to be pushed into stack:");
            scanf("%d", &element);
            newStack = pushStack(newStack, element);
            goto start;
        }
        else {
            system("cls");
            printf("Stack has not been created\n");
            goto start;
        }
    case 3:
        if (createCheck != 0) {
            if (newStack == NULL) {
                newStack = createStack(newStack);
            }
            newStack = popStack(newStack);
            goto start;
        }
        else {
            system("cls");
            printf("Stack has not been created\n");
            goto start;
        }
    case 4:
        if (createCheck != 0) {
            if (newStack == NULL) {
                newStack = createStack(newStack);
            }
            peekStack(newStack);
            goto start;
        }
        else {
            system("cls");
            printf("Stack has not been created\n");
            goto start;
        }
    case 5:
        if (createCheck != 0) {
            if (newStack == NULL) {
                newStack = createStack(newStack);
            }
            displayStack(newStack);
            goto start;
        }
        else {
            system("cls");
            printf("Stack has not been created\n");
            goto start;
        }
    case 6:
        if (createCheck != 0) {
            if (newStack == NULL) {
                newStack = createStack(newStack);
            }
            newStack = freeStack(newStack);
            createCheck = 0;
            goto start;
        }
        else {
            system("cls");
            printf("Stack has not been created\n");
            goto start;
        }
    case 7:
        freeStack(newStack);
        createCheck = 0;
        system("cls");
        break;
    default:
        system("cls");
        printf("Invalid Choice!Please enter between 1 and 7\n");
        goto start;
    }
    return 0;
}

int queueMenu() {
    list* newQueue = NULL;
    int choice, element = 0;
start:
    printf("\n__QUEUE__\n");
    printf("1. Initialize Queue\n");
    printf("2. Add to Queue\n");
    printf("3. Delete from Queue\n");
    printf("4. Peek Queue\n");
    printf("5. Display Queue\n");
    printf("6. Free Queue\n");
    printf("7. Return Back to Main Menu\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        if (newQueue == NULL && createCheck==0) {
            newQueue = createQueue(newQueue);
            createCheck = 1;
            goto start;
        }
        else {
            system("cls");
            printf("Queue has already been created\n");
            goto start;
        }
    case 2:
        if (createCheck != 0) {
            if (newQueue == NULL) {
                newQueue = createQueue(newQueue);
            }
            printf("Enter element to be added to Queue:");
            scanf("%d", &element);
            newQueue = enQueue(newQueue, element);
            goto start;
        }
        else {
            system("cls");
            printf("Queue has not been created\n");
            goto start;
        }
    case 3:
        if (createCheck != 0) {
            if (newQueue == NULL) {
                newQueue = createQueue(newQueue);
            }
            newQueue = deQueue(newQueue);
            goto start;
            
        }
        else {
            system("cls");
            printf("Queue has not been created\n");
            goto start;
        }
    case 4:
        if (createCheck != 0) {
            if (newQueue == NULL) {
                newQueue = createQueue(newQueue);
            }
            peekQueue(newQueue);
            goto start;
        }
        else {
            system("cls");
            printf("Queue has not been created\n");
            goto start;
        }
    case 5:
        if (createCheck != 0) {
            if (newQueue == NULL) {
                newQueue = createQueue(newQueue);
            }
            displayQueue(newQueue);
            goto start;
        }
        else {
            system("cls");
            printf("Queue has not been created\n");
            goto start;
        }
    case 6:
        if (createCheck != 0) {
            if (newQueue == NULL) {
                newQueue = createQueue(newQueue);
            }
            freeQueue(newQueue);
            createCheck = 0;
            goto start;
            
        }
        else {
            system("cls");
            printf("Queue has not been created\n");
            goto start;
        }
    case 7:
        freeQueue(newQueue);
        createCheck = 0;
        system("cls");
        break;
    default:
        system("cls");
        printf("Invalid Choice!Please enter between 1 and 7\n");
        goto start;
    }
    return 0;
}

int main() {
    int choice;
menu:
    printf("LINKED LIST IMPLEMENTATION:\n");
    printf("1. STACK\n");
    printf("2. QUEUE\n");
    printf("3. EXIT\n");
    printf("Enter Choice:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        system("cls");
        stackMenu();
        system("cls");
        goto menu;
        break;
    case 2:
        system("cls");
        queueMenu();
        system("cls");
        goto menu;
        break;
    case 3:
        system("cls");
        printf("Exiting...");
        exit(0);
    default:
        system("cls");
        printf("Please enter choice between 1 and 3\n\n");
        goto menu;
    }
    return 0;
}