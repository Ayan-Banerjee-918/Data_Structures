#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 20

typedef struct StackArrayADT
{
    int top;
    int *arr;
}stack;

stack* create(stack*);
bool isFull(stack*);
bool isEmpty(stack*);
void push(stack*,int);
void pop(stack*);
void peek(stack*);
void display(stack*);
stack* freeStack(stack*);

stack* create(stack* temp){
    temp = (stack*)malloc(sizeof(stack));
    temp->top = -1;
    temp->arr = (int *)malloc(sizeof(int) * MAXSIZE);
    system("cls");
    printf("Stack created!\n");
    return temp;
}

bool isFull(stack* temp){
    if(temp->top==MAXSIZE-1){
        return true;
    }
    return false;
}

bool isEmpty(stack* temp){
    if(temp->top==-1){
        return true;
    }
    return false;
}

void push(stack* temp,int val){
    if(isFull(temp)==true){
        system("cls");
        printf("Stack is Full\n");
    }
    else{
        ++temp->top;
        temp->arr[temp->top] = val;
        system("cls");
        printf("%d pushed into stack\n",val);
    }
}

void pop(stack* temp){
    if(isEmpty(temp)){
        system("cls");
        printf("Stack is Empty\n");
    }
    else{
        system("cls");
        printf("%d popped from stack\n",temp->arr[temp->top]);
        temp->top--;
    }
}

void peek(stack* temp){
    if(isEmpty(temp)){
        system("cls");
        printf("Stack is Empty\n");
    }
    else{
        system("cls");
        printf("%d is at top of stack\n",temp->arr[temp->top]);
    }
}

void display(stack* temp){
    if(isEmpty(temp)){
        system("cls");
        printf("Stack is Empty\n");
    }
    else{
        int i = temp->top;
        system("cls");
        printf("Stack Elements are:\n");
        for (; i >=0 ;i--){
            printf("%d\n", temp->arr[i]);
        }
    }
}

stack* freeStack(stack* temp){
    temp = NULL;
    system("cls");
    printf("Stack Freed!\n");
    return temp;
}

int main(){
    stack* newStack = NULL;
    int choice,element = 0;
start:
    printf("\n__STACK__\n");
    printf("1. Create Stack\n");
    printf("2. Push into Stack\n");
    printf("3. Pop from Stack\n");
    printf("4. Peek Stack\n");
    printf("5. Display Stack\n");
    printf("6. Free Stack\n");
    printf("7. Exit\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            if(newStack==NULL){
                newStack=create(newStack);
                goto start;
            }
            else{
                system("cls");
                printf("Stack has already been created\n");
                goto start;
            }
        case 2:
            if(newStack!=NULL){
                printf("Enter element to be pushed into stack:");
                scanf("%d", &element);
                push(newStack, element);
                goto start;
            }
            else{
                system("cls");
                printf("Stack has not been created\n");
                goto start;
            }
        case 3:
            if(newStack!=NULL){
                pop(newStack);
                goto start;
            }
            else{
                system("cls");
                printf("Stack has not been created\n");
                goto start;
            }
        case 4:
            if(newStack!=NULL){
                peek(newStack);
                goto start;
            }
            else{
                system("cls");
                printf("Stack has not been created\n");
                goto start;
            }
        case 5:
            if(newStack!=NULL){
                display(newStack);
                goto start;
            }
            else{
                system("cls");
                printf("Stack has not been created\n");
                goto start;
            }
        case 6:
           if(newStack!=NULL){
                newStack=freeStack(newStack);
                goto start;
            }
            else{
                system("cls");
                printf("Stack has not been created\n");
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