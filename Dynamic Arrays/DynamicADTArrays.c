#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isArrayCreated(void*);
bool isArrayEmpty(void*);
void ReallocateArray(void*);
void CreateArray(void*, int);
void InsertElements(void*, int);
void InsertAt(void*, int, int);
void DeleteElement(void*, int);
void DeleteAt(void*, int);
void DisplayArray(void*);

typedef struct dynamicArray {
    int totalSize;
    int usedSize;
    int* arr;
    void (*CreateArray)(void*, int);
    void (*InsertElements)(void*, int);
    void (*InsertAt)(void*, int, int);
    void (*DeleteElement)(void*, int);
    void (*DeleteAt)(void*, int);
    void (*DisplayArray)(void*);
}DynamicArray;

const DynamicArray defaultArray = { -1,-1,0,CreateArray,InsertElements,InsertAt,DeleteElement,DeleteAt,DisplayArray };

bool isArrayCreated(void* self) {
    DynamicArray* temp = self;
    if (temp->totalSize == -1) {
        system("cls");
        printf("Array Not Created\n");
        return false;
    }
    return true;
}

bool isArrayEmpty(void* self) {
    DynamicArray* temp = self;
    if (temp->usedSize == 0) {
        system("cls");
        printf("Empty Array of size %d\n", temp->totalSize);
        return true;
    }
    return false;
}

void ReallocateArray(void* self) {
    DynamicArray* temp = self;
    temp->totalSize += 10;
    temp->arr = realloc(temp->arr, temp->totalSize * sizeof(int));
}

void CreateArray(void* self, int size) {
    DynamicArray* temp = self;
    temp->totalSize = size;
    temp->usedSize = 0;
    temp->arr = (int*)malloc(temp->totalSize * sizeof(int));
    printf("Array Created\n");
}

void InsertElements(void* self, int element) {
    DynamicArray* temp = self;
    if (temp->usedSize == temp->totalSize) {
        ReallocateArray(temp);
    }
    temp->arr[temp->usedSize++] = element;
}

void InsertAt(void* self, int element, int index) {
    DynamicArray* temp = self;
    int indexCopy;
    while (temp->totalSize < index) {
        ReallocateArray(temp);
    }
    if (temp->usedSize == temp->totalSize) {
        ReallocateArray(temp);
    }
    if (index <= temp->usedSize) {
        indexCopy = ++temp->usedSize;
        for (; indexCopy > index; indexCopy--) {
            temp->arr[indexCopy - 1] = temp->arr[indexCopy - 2];
        }
        temp->arr[index - 1] = element;
    }
    else if (index > temp->usedSize) {
        for (; temp->usedSize < index;) {
            temp->arr[temp->usedSize++] = 0;
        }
        temp->usedSize = index;
        temp->arr[index - 1] = element;
    }
}

void DeleteElement(void* self, int element) {
    DynamicArray* temp = self;
    int i, j, count, copyi = 0;
    bool Elementfound = false;
    for (i = 0; i < temp->usedSize; i++) {
        copyi = i;
        if (temp->arr[i] == element) {
            Elementfound = true;
            break;
        }
    }
    count = 1;
    j = i;
    if (Elementfound == true) {
        while (i < temp->usedSize - 1 && j < temp->usedSize - 1) {
        deleting:
            printf("%d %d\n", temp->arr[i], temp->arr[j + 1]);
            temp->arr[i] = temp->arr[j + 1];
            if (temp->arr[i] == element) {
                count++;
                j++;
                goto deleting;
            }
            i++;
            j++;
        }
        temp->usedSize -= count;
        system("cls");
        printf("Element %d has been deleted from array\n", element);
    }
    else {
        system("cls");
        printf("Element %d does not exist in the array\n", element);
    }
}

void DeleteAt(void* self, int index) {
    DynamicArray* temp = self;
    int i = 0;
    if (index < temp->totalSize) {
        if (index > temp->usedSize) {
            printf("The index is not filled in the array\n");
        }
        else {
            for (i = index - 1; i < temp->usedSize - 1; i++) {
                temp->arr[i] = temp->arr[i + 1];
            }
            temp->usedSize--;
            system("cls");
            printf("The element at index %d has been deleted\n", index);
        }
    }
    else {
        printf("Invalid Index : Index does not exist in array\n");
    }
}

void DisplayArray(void* self) {
    DynamicArray* temp = self;
    int i = 0;
    if (isArrayCreated(temp)) {
        if (isArrayEmpty(temp) == false) {
            printf("Elements in Array:\n");
            for (; i < temp->usedSize; i++) {
                printf("%d ", (temp->arr)[i]);
            }
            printf("\n");
        }
    }
}

int main() {
    DynamicArray arr1 = defaultArray;
    int i, n, element, choice = 0;
    int index = arr1.usedSize;
start:
    printf("\n__DYNAMIC ARRAY__\n");
    printf("1. Create Array\n");
    printf("2. Insertion into Array\n");
    printf("3. Deletion from Array\n");
    printf("4. Display Array\n");
    printf("5. Free Array\n");
    printf("6. Exit\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        if (arr1.totalSize >= 0) {
            system("cls");
            printf("Array has been already created.\n");
            goto start;
        }
        printf("Enter size of array to be created:");
        scanf("%d", &n);
        system("cls");
        arr1.CreateArray(&arr1, n);
        goto start;
    case 2:
        if (isArrayCreated(&arr1)) {
            system("cls");
        insert:
            printf("\nInsertion Options\n");
            printf("1. Insert Elements into Array\n");
            printf("2. Insert Element at Index\n");
            printf("Enter choice:");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                printf("Enter no of elements to insert in array:");
                scanf("%d", &n);
                printf("Enter elements:");
                for (i = 0; i < n; i++) {
                    scanf("%d", &element);
                    arr1.InsertElements(&arr1, element);
                }
                system("cls");
                printf("Elements Inserted into Array\n");
                break;
            case 2:
                printf("Enter element to be inserted:");
                scanf("%d", &element);
                printf("Enter index where element will be inserted:");
                scanf("%d", &index);
                system("cls");
                arr1.InsertAt(&arr1, element, index);
                printf("Element %d inserted at index %d\n", element, index);
                break;
            default:
                system("cls");
                printf("\n Please choose 1 or 2\n");
                goto insert;
            }
        }
        goto start;
    case 3:
        if (isArrayCreated(&arr1)) {
            if (isArrayEmpty(&arr1) == false) {
                system("cls");
                delete:
                printf("\nDeletion Options\n");
                printf("1. Delete element\n");
                printf("2. Delete index at which an element is present\n");
                printf("Enter choice:");
                scanf("%d", &choice);
                switch (choice) {
                case 1:
                    printf("Enter element:");
                    scanf("%d", &element);
                    arr1.DeleteElement(&arr1, element);
                    break;
                case 2:
                    printf("Enter index where element is to be deleted:");
                    scanf("%d", &index);
                    arr1.DeleteAt(&arr1, index);
                    break;
                default:
                    system("cls");
                    printf("\n Please choose 1 or 2\n");
                    goto delete;
                }
                goto start;
            }
        }
        goto start;
    case 4:
        system("cls");
        arr1.DisplayArray(&arr1);
        goto start;
    case 5:
        if (arr1.totalSize>-1) {
            free(arr1.arr);
            arr1.arr = NULL;
            arr1.usedSize = -1;
            arr1.totalSize = -1;
            system("cls");
            printf("Array Memory Deallocated/Freed\n");
        }
        else {
            system("cls");
            printf("Array not Allocated\n");
        }
        goto start;
    case 6:
        exit(0);
    default:
        system("cls");
        printf("Wrong input.Please enter between 1 and 6\n\n");
        goto start;
    }
    return 0;
}