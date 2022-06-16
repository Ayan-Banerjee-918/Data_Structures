#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct StackLLAdt
{
    int data;
    struct StackLLAdt* link;
}stack;

stack* create(stack*,stack**);
bool isEmpty(stack*,stack**);
stack* push(stack*, int, stack**);
int pop(stack**,stack**);

stack* create(stack* temp,stack** topNode) {
    temp = (stack*)malloc(sizeof(stack));
    temp->link = NULL;
    *topNode = NULL;
    return temp;
}

bool isEmpty(stack* temp,stack** topNode) {
    if ((*topNode) == NULL) {
        return true;
    }
    return false;
}

stack* push(stack* temp, int val,stack** topNode) {
    if ((*topNode) == NULL) {
        temp->data = val;
    }
    else {
        stack* newNode = (stack*)malloc(sizeof(stack));
        newNode->data = val;
        newNode->link = temp;
        temp = newNode;
    }
    (*topNode) = temp;
    return temp;
}

int pop(stack** temp,stack** topNode) {
    stack* node;
    int data = 0;
    if (isEmpty((*temp),topNode)) {
        system("cls");
        printf("Stack is Empty\n");
    }
    else {
        data = (*temp)->data;
        node = (*temp);
        *temp = (*temp)->link;
        free(node);
        *topNode = *temp;
    }
    return data;
}

int main(){
    int num = 0, numcopy = 0, revnum = 0 , i = 0;
    stack* topNode;
    stack* newStack = create(newStack,&topNode);
    printf("Enter Number to be reversed with Stack:");
    scanf("%d", &num);
    numcopy = num;
    while(numcopy>0){
        newStack = push(newStack, numcopy % 10, &topNode);
        numcopy /= 10;
    }
    for (i = 0; !isEmpty(newStack,&topNode);i++){
        revnum += (pop(&newStack,&topNode) * pow(10,i));
    }
    printf("The number %d reversed is %d.\n",num,revnum);
    system("pause");
    return 0;
}