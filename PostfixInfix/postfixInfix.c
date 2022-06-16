#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int flag = 0;

typedef struct StackADT {
    int top;
    int capacity;
    double* arr;
} stack;

stack* create(int cap);
int isEmpty(stack* temp);
char peek(stack* temp);
double pop(stack* temp);
void push(stack* temp, double opr);
int isOperand(char ch);
int isNumber(char ch);
int isOperator(char ch);
int isRightAssociative(char ch);
int precedence(char ch);
char* infixPostfix(char* exp);
void evaluatePostfix(char* exp, int* expInt);

stack* create(int cap) {
    stack* temp = (stack*)malloc(sizeof(stack));
    if (!temp) {
        return NULL;
    }
    temp->top = -1;
    temp->capacity = cap;
    temp->arr = (double*)malloc(temp->capacity * sizeof(double));
    return temp;
}

int isEmpty(stack* temp) {
    return temp->top == -1;
}

char peek(stack* temp)
{
    return temp->arr[temp->top];
}

double pop(stack* temp)
{
    if (!isEmpty(temp))
        return temp->arr[temp->top--];
    return 0.0f;
}

void push(stack* temp, double opr) {
    temp->arr[++temp->top] = opr;
}

int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int isNumber(char ch) {
    return (ch >= '0' && ch <= '9');
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int isRightAssociative(char ch){
    return (ch == '^');
}

int precedence(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

char* infixPostfix(char* exp) {
    int i, k, bracketCnt = 0;
    char modifiedexp[100];
    int g = 0;
    stack* temp = create(strlen(exp));
    if (!temp) {
        return '\0';
    }
    for (i = 0, k = 0; exp[i]; i++) {
        if (isOperand(exp[i]) || isNumber(exp[i])) {
            if (isOperand(exp[i]) && isOperand(exp[i + 1])) {
                printf("\nInvalid expression.Please enter an operator between two operands.\n");
                return '\0';
            }
            exp[k] = exp[i];
            modifiedexp[g++] = exp[k++];
        }
        else if (exp[i] == '(') {
            bracketCnt++;
            push(temp, exp[i]);
        }
        else if (exp[i] == ')') {
            bracketCnt--;
            while (peek(temp) != '(' && !isEmpty(temp)) {
                exp[k] = pop(temp);
                modifiedexp[g++] = ' ';
                modifiedexp[g++] = exp[k++];
            }
            if (isEmpty(temp)) {
                printf("\nInvalid Expression\n");
                return '\0';
            }
            else {
                pop(temp);
            }
        }
        else {
            while (!isEmpty(temp) && precedence(exp[i]) <= precedence(peek(temp))) {
                if(isRightAssociative(exp[i])){
                    break;
                }
                exp[k] = pop(temp);
                modifiedexp[g++] = ' ';
                modifiedexp[g++] = exp[k++];
            }
            push(temp, exp[i]);
            modifiedexp[g++] = ' ';
        }
    }
    if (bracketCnt != 0) {
        printf("\nInvalid Expression\n");
        return '\0';
    }
    while (!isEmpty(temp)) {
        if (peek(temp) != '(' && peek(temp) != ')') {
            exp[k] = pop(temp);
            modifiedexp[g++] = ' ';
            modifiedexp[g++] = exp[k++];
        }
        else {
            pop(temp);
        }
    }
    exp[k++] = '\0';
    modifiedexp[g++] = '\0';
    printf("\nPostfix Expression: %s\n",modifiedexp);
    return exp;
}

void evaluatePostfix(char* exp, int* expInt) {
    int i, k, copy = 0;
    double top1, top2 = 0.0f;
    int count = 0;
    if (exp == NULL || *exp == '\0' || flag) {
        if (flag && exp != NULL) {
            for (i = 0,k=0; exp[i]; i++) {
                if (expInt[k] == '#') {
                    if (!isdigit(exp[i]) && !isOperator(exp[i])) {
                        printf("Enter value of %c:", exp[i]);
                        scanf("%d", &expInt[k++]);
                    }
                }
                else {
                    k++;
                }
            }
        }
        else {
            return;
        }
    }
    flag = 0;
    stack* temp = create(strlen(exp));
    for (i = 0, k = 0; exp[i]; i++) {
        count = 0;
        if (!isdigit(exp[i]) && !isOperand(exp[i])) {
            top1 = pop(temp);
            top2 = pop(temp);
            switch (exp[i]) {
            case '+':
                push(temp, top2 + top1);
                break;
            case '-':
                push(temp, top2 - top1);
                break;
            case '*':
                push(temp, top2 * top1);
                break;
            case '/':
                push(temp, top2 / top1);
                break;
            case '^':
                push(temp, pow(top2, top1));
                break;
            }
        }
        else {
            copy = expInt[k];
            while (copy > 0) {
                count += 1;
                copy /= 10;
            }
            push(temp, expInt[k++]);
            if (!isOperand(exp[i]))
                i += count - 1;
        }
    }
    printf("\nEvaluated Result: %.1lf\n\n", pop(temp));
}

int main() {
    char exp[100];
    static int num[100];
    int i, k = 0;
    int g = 0;
    printf("Enter infix expression: ");
    scanf("%s", exp);
    printf("\nInfix Expression: %s\n", exp);
    for (i = 0; exp[i]; i++) {
        if (!isdigit(exp[i]) && isOperator(exp[i])) {
            k++;
            continue;
        }
        else if (!isdigit(exp[i]) && (exp[i] == '(' || exp[i] == ')')) {
            continue;
        }
        else if (!isdigit(exp[i])) {
            flag = 1;
            num[k] = '#';
            continue;
        }
        else if (isdigit(exp[i])) {
            num[k] = (num[k] * 10) + (int)exp[i] - '0';
        }
    }
    evaluatePostfix(infixPostfix(exp), num);
    system("pause");
    return 0;
}