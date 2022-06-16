/*Name:Ayan Banerjee
Roll:13000120019

2. Define a self referential structure to store a polynomial and do the below set of operation
    - addition/subtraction of  polynomials
    - Implements the Horner's Rule to evaluate the value of polynomial as mentioned below by recursion.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    float coeff;
    int exp;
    int termCount;
    struct node* link;
} Polynomial;

Polynomial* polyInsert(Polynomial*, float, int);
Polynomial* createPolynomial(Polynomial*);
void displayPolynomial(Polynomial*);
void addPolynomial(Polynomial*, Polynomial*);
void subPolynomial(Polynomial*, Polynomial*);
float HornersRule(float*, int, int);

Polynomial* polyInsert(Polynomial* head, float coefficient, int exponent) {
    Polynomial* temp;
    Polynomial* newNode = malloc(sizeof(Polynomial));
    newNode->coeff = coefficient;
    newNode->exp = exponent;
    newNode->link = NULL;

    if (head == NULL || newNode->exp > head->exp) {
        newNode->link = head;
        head = newNode;
    }
    else {
        temp = head;
        while (temp->link != NULL && temp->link->exp > newNode->exp) {
            temp = temp->link;
        }
        newNode->link = temp->link;
        temp->link = newNode;
    }
    return head;
}

Polynomial* createPolynomial(Polynomial* head) {
    int termCount, i, exponent = 0;
    float coefficient = 0.0f;
    printf("Enter the number of terms for polynomial to be created:");
    scanf("%d", &termCount);
    printf("\n");
    for (i = 0; i < termCount; i++) {
        printf("Enter the coefficient for term %d : ", i + 1);
        scanf("%f", &coefficient);
        printf("Enter the exponent for term %d : ", i + 1);
        scanf("%d", &exponent);
        printf("\n");
        head = polyInsert(head, coefficient, exponent);
    }
    head->termCount = termCount;
    return head;
}

void displayPolynomial(Polynomial* head) {
    if (head == NULL) {
        printf("Polynomial does not exist.\n");
    }
    else {
        Polynomial* temp = head;
        while (temp != NULL) {
            printf("( %.1fx^%d )", temp->coeff, temp->exp);
            temp = temp->link;
            if (temp != NULL) {
                printf(" + ");
            }
            else {
                printf("\n");
            }
        }
    }
}

void addPolynomial(Polynomial* head1, Polynomial* head2) {
    Polynomial* temp1 = head1;
    Polynomial* temp2 = head2;
    Polynomial* head3 = NULL;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->exp == temp2->exp) {
            head3 = polyInsert(head3, temp1->coeff + temp2->coeff, temp1->exp);
            temp1 = temp1->link;
            temp2 = temp2->link;
        }
        else if (temp1->exp > temp2->exp) {
            head3 = polyInsert(head3, temp1->coeff, temp1->exp);
            temp1 = temp1->link;
        }
        else if (temp1->exp < temp2->exp) {
            head3 = polyInsert(head3, temp2->coeff, temp2->exp);
            temp2 = temp2->link;
        }
    }
    while (temp1 != NULL)
    {
        head3 = polyInsert(head3, temp1->coeff, temp1->exp);
        temp1 = temp1->link;
    }
    while (temp2 != NULL) {
        head3 = polyInsert(head3, temp2->coeff, temp2->exp);
        temp2 = temp2->link;
    }
    system("cls");
    printf("Added Result:\n");
    displayPolynomial(head3);
}

void subPolynomial(Polynomial* head1, Polynomial* head2) {
    Polynomial* temp1 = head1;
    Polynomial* temp2 = head2;
    Polynomial* head3 = NULL;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->exp == temp2->exp) {
            head3 = polyInsert(head3, temp1->coeff - temp2->coeff, temp1->exp);
            temp1 = temp1->link;
            temp2 = temp2->link;
        }
        else if (temp1->exp > temp2->exp) {
            head3 = polyInsert(head3, temp1->coeff, temp1->exp);
            temp1 = temp1->link;
        }
        else if (temp1->exp < temp2->exp) {
            head3 = polyInsert(head3, -temp2->coeff, temp2->exp);
            temp2 = temp2->link;
        }
    }
    while (temp1 != NULL)
    {
        head3 = polyInsert(head3, temp1->coeff, temp1->exp);
        temp1 = temp1->link;
    }
    while (temp2 != NULL) {
        head3 = polyInsert(head3, -temp2->coeff, temp2->exp);
        temp2 = temp2->link;
    }
    system("cls");
    printf("Subtracted Result:\n");
    displayPolynomial(head3);
}

float HornersRule(float* coeff, int degree, int x)
{
    if (degree == 0)
    {
        return coeff[0];
    }
    return HornersRule(coeff, degree - 1, x) * x + coeff[degree];
}

int main() {
    Polynomial* polynomial1 = NULL;
    Polynomial* polynomial2 = NULL;
    Polynomial* HornerPolynomial = NULL;
    int i, x, size, choice = 0;
    float HornerResult = 0.0f;
start:
    printf("\n__POLYNOMIALS__\n");
    printf("1. Create Polynomial\n");
    printf("2. Add Polynomial\n");
    printf("3. Subtract Polynomial\n");
    printf("4. Horner's Rule\n");
    printf("5. Display Polynomial\n");
    printf("6. Free Polynomials\n");
    printf("7. Exit\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        if (polynomial1 == NULL && polynomial2 == NULL) {
            system("cls");
            printf("Polynomial Creation\n");
            printf("Polynomial 1\n");
            polynomial1 = createPolynomial(polynomial1);
            printf("Polynomial 2\n");
            polynomial2 = createPolynomial(polynomial2);
            system("cls");
            printf("Polynomials Created\n");
            goto start;
        }
        else {
            system("cls");
            printf("Polynomials already Created.\n");
            goto start;
        }
    case 2:
        if (polynomial1 != NULL && polynomial2 != NULL) {
            addPolynomial(polynomial1, polynomial2);
            goto start;
        }
        else {
            system("cls");
            printf("Polynomials not created\n");
            goto start;
        }
    case 3:
        if (polynomial1 != NULL && polynomial2 != NULL) {
            system("cls");
            printf("Polynomial subtraction\n");
            printf("1.Do polynomial 1 - polynomial 2\n");
            printf("2.Do polynomial 2 - polynomial 1\n");
            printf("Enter choice:");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                subPolynomial(polynomial1, polynomial2);
                break;
            case 2:
                subPolynomial(polynomial2, polynomial1);
                break;
            default:
                system("cls");
                printf("Incorrect Choice!\n");
            }
            goto start;
        }
        else {
            system("cls");
            printf("Polynomials not created\n");
            goto start;
        }
    case 4:
        system("cls");
        printf("Horner's Rule\n");
        Polynomial* temp = NULL;
        HornerPolynomial = NULL;
        i = 0;
        HornerPolynomial = createPolynomial(HornerPolynomial);
        size = HornerPolynomial->termCount;
        float* coeff = (float*)malloc(size * sizeof(float));
        temp = HornerPolynomial;
        while (temp != NULL) {
            coeff[i++] = temp->coeff;
            temp = temp->link;
        }
        printf("Enter value for x to be evaluated in the polynomial :");
        scanf("%d", &x);
        HornerResult = HornersRule(coeff, HornerPolynomial->termCount-1, x);
        system("cls");
        printf("\nPolynomial Entered is\n");
        displayPolynomial(HornerPolynomial);
        printf("\nValue of x entered is %d\n",x);
        printf("\nValue of polynomial by Horner's rule is %.1f \n", HornerResult);
        goto start;
    case 5:
        if (polynomial1 != NULL && polynomial2 != NULL) {
            system("cls");
            printf("Polynomial 1\n");
            displayPolynomial(polynomial1);
            printf("Polynomial 2\n");
            displayPolynomial(polynomial2);
            goto start;
        }
        else {
            system("cls");
            printf("Polynomials not created\n");
            goto start;
        }
    case 6:
        if(polynomial1==NULL && polynomial2==NULL){
            system("cls");
            printf("Polynomials not created\n");
            goto start;
        }
        else{
            system("cls");
            polynomial1 = NULL;
            polynomial2 = NULL;
            printf("Memory for polynomials has been deallocated.\n");
            goto start;
        }
    case 7:
        exit(0);
    default:
        system("cls");
        printf("Incorrect Choice!Enter between 1 and 7!");
        goto start;
    }
    return 0;
}