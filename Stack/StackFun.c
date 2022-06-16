#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int MAXSIZE=0;

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
void display(stack*);
stack* freeStack(stack*);

stack* create(stack* temp){
    temp = (stack*)malloc(sizeof(stack));
    temp->top = -1;
    temp->arr = (int *)malloc(sizeof(int) * (MAXSIZE+1));
    return temp;
}

bool isFull(stack* temp){
    if(temp->top==MAXSIZE){
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
    }
}

void pop(stack* temp){
    if(isEmpty(temp)){
        system("cls");
        printf("Stack is Empty\n");
    }
    else{
        temp->top--;
    }
}

void display(stack* temp){
    if(isEmpty(temp)){
        system("cls");
        printf("Stack is Empty\n");
    }
    else{
        int i = temp->top;
        for (; i >=0 ;i--){
            printf("%d\n", temp->arr[i]);
        }
    }
}

stack* freeStack(stack* temp){
    temp = NULL;
    return temp;
}

int main(){
    stack* newStackA = NULL;
    stack* newStackB = NULL;
    stack* newStackC = NULL;
    int choice,element,size,i = 0;
    printf("Enter maximum size of the 3 stacks:");
    scanf("%d",&MAXSIZE);
    system("cls");
start:
    printf("\n__STACK__\n");
    printf("1. Create Stack A\n");
    printf("2. Create Stack B\n");
    printf("3. Create Stack C\n");
    printf("4. Display Stacks\n");
    printf("5. Push into Stack\n");
    printf("6. Free Stacks\n");
    printf("7. Exit\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            if(newStackA==NULL){
                newStackA=create(newStackA);
            checkA:
                printf("Enter number of elements to be pushed into stack A:");
                scanf("%d", &size);
                if(size>MAXSIZE+1){
                    printf("Maximum size of each stack is %d\n", MAXSIZE+1);
                    goto checkA;
                }
                else{
                    printf("Enter elements:");
                    for (i = 0 ; i < size;i++){
                        scanf("%d", &element);
                        push(newStackA, element);
                    }
                }
                system("cls");
                printf("Elements have been pushed into stack A");
                goto start;
            }
            else{
                system("cls");
                printf("Stack A has already been created\n");
                goto start;
            }
        case 2:
            if(newStackB==NULL){
                newStackB=create(newStackB);
            checkB:
                printf("Enter number of elements to be pushed into stack B:");
                scanf("%d", &size);
                if(size>MAXSIZE+1){
                    printf("Maximum size of each stack is %d\n", MAXSIZE+1);
                    goto checkB;
                }
                else{
                    printf("Enter elements:");
                    for (i = 0 ; i < size;i++){
                        scanf("%d", &element);
                        push(newStackB, element);
                    }
                }
                system("cls");
                printf("Elements have been pushed into stack B");
                goto start;
            }
            else{
                system("cls");
                printf("Stack B has already been created\n");
                goto start;
            }
        case 3:
            if(newStackC==NULL){
                newStackC=create(newStackC);
            checkC:
                printf("Enter number of elements to be pushed into stack C:");
                scanf("%d", &size);
                if(size>MAXSIZE+1){
                    printf("Maximum size of each stack is %d\n", MAXSIZE+1);
                    goto checkC;
                }
                else{
                    printf("Enter elements:");
                    for (i = 0 ; i < size;i++){
                        scanf("%d", &element);
                        push(newStackC, element);
                    }
                }
                system("cls");
                printf("Elements have been pushed into stack C");
                goto start;
            }
            else{
                system("cls");
                printf("Stack C has already been created\n");
                goto start;
            }
        case 4:
            system("cls");
            if(newStackA!=NULL) {
                printf("Stack A:\n");
                display(newStackA);
            }
            else{
                printf("Stack A: NULL\n");
            }
            if(newStackB!=NULL){
                printf("Stack B:\n");
                display(newStackB);
            }
            else{
                printf("Stack B: NULL\n");
            }
            if(newStackC!=NULL){
                printf("Stack C:\n");
                display(newStackC);
                goto start;
            }
            else{
                printf("Stack C: NULL\n");
                goto start;
            }
        case 5:
            if(newStackA!=NULL && newStackB!=NULL && newStackC!=NULL){
                if(!isFull(newStackA)){
                    printf("Enter element to be pushed into stack:");
                    scanf("%d", &element);
                    push(newStackA, element);
                    system("cls");
                    printf("%d has been pushed into the stack\n",element);
                    goto start;
                }
                else if(isFull(newStackA)){
                    if(!isFull(newStackB)){
                        pop(newStackA);
                        push(newStackB, newStackA->arr[newStackA->top + 1]);
                        printf("Enter element to be pushed into stack:");
                        scanf("%d", &element);
                        push(newStackA, element);
                        system("cls");
                        printf("%d has been pushed into the stack\n",element);
                        goto start;
                    }
                    else if(!isFull(newStackC)){
                        pop(newStackB);
                        push(newStackC, newStackB->arr[newStackB->top + 1]);
                        pop(newStackA);
                        push(newStackB, newStackA->arr[newStackA->top + 1]);
                        printf("Enter element to be pushed into stack:");
                        scanf("%d", &element);
                        push(newStackA, element);
                        system("cls");
                        printf("%d has been pushed into the stack\n",element);
                        goto start;
                    }
                    else{
                        system("cls");
                        printf("Stacks are Full\n");
                        goto start;
                    }
                }
            }
            else{
                system("cls");
                printf("Please create all 3 stacks first\n");
                goto start;
            }
        case 6:
            system("cls");
            if(newStackA!=NULL){
                newStackA=freeStack(newStackA);
                printf("Stack A Freed!\n");
            }
            else{
                printf("Stack A hasn't been created\n");
            } 
            if(newStackB!=NULL){
                newStackB=freeStack(newStackB);
                printf("Stack B Freed!\n");
            }
            else{
                printf("Stack B hasn't been created\n");
            }
            if(newStackC!=NULL){
                newStackC=freeStack(newStackC);
                printf("Stack C Freed!\n");
            }
            else{
                printf("Stack C hasn't been created\n");
            }
            goto start;
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