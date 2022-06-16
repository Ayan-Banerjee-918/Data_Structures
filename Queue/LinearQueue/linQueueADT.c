#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 3

typedef struct LinearQueueADT{
    int front, rear;
    int *arr;
} queue;

queue* initQueue(queue*);
bool isFull(queue*);
bool isEmpty(queue*);
void enQueue(queue*, int);
void deQueue(queue*);
void peek(queue*);
void display(queue*);
queue* freeQueue(queue*);

queue* initQueue(queue* temp){
    temp = (queue *)malloc(sizeof(queue));
    temp->front = 0;
    temp->rear = -1;
    temp->arr = (int *)malloc(sizeof(int) * MAXSIZE);
    system("cls");
    printf("Queue created!\n");
    return temp;
}

bool isFull(queue* temp){
    if(temp->rear==MAXSIZE-1){
        return true;
    }
    return false;
}

bool isEmpty(queue* temp){
    if(temp->front<0 || temp->front>temp->rear){
        return true;
    }
    return false;
}

void enQueue(queue* temp, int val){
    if(isFull(temp)==true){
        system("cls");
        printf("Queue is Full\n");
    }
    else{
        temp->arr[++temp->rear] = val;
        system("cls");
        printf("%d added to queue\n",val);
    }
}

void deQueue(queue* temp){
    if(isEmpty(temp)){
        system("cls");
        printf("Queue is Empty\n");
    }
    else{
        system("cls");
        printf("%d removed from queue\n",temp->arr[temp->front++]);
    }
}

void peek(queue* temp){
    if(isEmpty(temp)){
        system("cls");
        printf("Queue is Empty\n");
    }
    else{
        system("cls");
        printf("%d is at front of queue\n",temp->arr[temp->front]);
    }
}

void display(queue* temp){
    if(isEmpty(temp)){
        system("cls");
        printf("Queue is Empty\n");
    }
    else{
        int i;
        system("cls");
        printf("Queue Elements are:\n");
        for (i = temp->front; i <= temp->rear ;i++){
            printf("%d ", temp->arr[i]);
        }
        printf("\n");
    }
}

queue* freeQueue(queue* temp){
    temp = NULL;
    system("cls");
    printf("Queue Freed!\n");
    return temp;
}

int main(){
    queue* newQueue = NULL;
    int choice,element = 0;
start:
    printf("\n__QUEUE__\n");
    printf("1. Initialize Queue\n");
    printf("2. Add to Queue\n");
    printf("3. Delete from Queue\n");
    printf("4. Peek Queue\n");
    printf("5. Display Queue\n");
    printf("6. Free Queue\n");
    printf("7. Exit\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            if(newQueue==NULL){
                newQueue=initQueue(newQueue);
                goto start;
            }
            else{
                system("cls");
                printf("Queue has already been created\n");
                goto start;
            }
        case 2:
            if(newQueue!=NULL){
                printf("Enter element to be added to Queue:");
                scanf("%d", &element);
                enQueue(newQueue, element);
                goto start;
            }
            else{
                system("cls");
                printf("Queue has not been created\n");
                goto start;
            }
        case 3:
            if(newQueue!=NULL){
                deQueue(newQueue);
                goto start;
            }
            else{
                system("cls");
                printf("Queue has not been created\n");
                goto start;
            }
        case 4:
            if(newQueue!=NULL){
                peek(newQueue);
                goto start;
            }
            else{
                system("cls");
                printf("Queue has not been created\n");
                goto start;
            }
        case 5:
            if(newQueue!=NULL){
                display(newQueue);
                goto start;
            }
            else{
                system("cls");
                printf("Queue has not been created\n");
                goto start;
            }
        case 6:
           if(newQueue!=NULL){
                newQueue=freeQueue(newQueue);
                goto start;
            }
            else{
                system("cls");
                printf("Queue has not been created\n");
                goto start;
            } 
        case 7:
            system("cls");
            printf("Exiting...");
            exit(0);
        default:
            system("cls");
            printf("Invalid Choice!Please enter between 1 and 7\n");
            goto start;
    }
    return 0;
}