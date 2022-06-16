/*Name:Ayan Banerjee
Roll:13000120019

1> Implement a list using array with following ADT(operation at least)
     - Insertion (default at the last available position otherwise as specified by user)
     - Deletion
     - Searching
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isListCreated(void*);
bool isListEmpty(void*);
void ReallocateList(void*);
int SearchElement(void*, int);
void CreateList(void*, int);
void InsertElements(void*, int);
void InsertAt(void*, int, int);
void DeleteElement(void*, int);
void DeleteAt(void*, int);
void DisplayList(void*);

typedef struct dynamicList {
    int totalSize;
    int usedSize;
    int* arr;
    void (*CreateList)(void*, int);
    void (*InsertElements)(void*, int);
    void (*InsertAt)(void*, int, int);
    void (*DeleteElement)(void*, int);
    void (*DeleteAt)(void*, int);
    int (*SearchElement)(void*, int);
    void (*DisplayList)(void*);
}DynamicList;

const DynamicList defaultList = { -1,-1,0,CreateList,InsertElements,InsertAt,DeleteElement,DeleteAt,SearchElement,DisplayList };

bool isListCreated(void* self) {
    DynamicList* temp = self;
    if (temp->totalSize == -1) {
        system("cls");
        printf("List Not Created\n");
        return false;
    }
    return true;
}

bool isListEmpty(void* self) {
    DynamicList* temp = self;
    if (temp->usedSize == 0) {
        system("cls");
        printf("Empty List of size %d\n", temp->totalSize);
        return true;
    }
    return false;
}

void ReallocateList(void* self) {
    DynamicList* temp = self;
    temp->totalSize += 10;
    temp->arr = realloc(temp->arr, temp->totalSize * sizeof(int));
}

int SearchElement(void* self, int element) {
    DynamicList* temp = self;
    int i = 0;
    for (i = 0; i < temp->usedSize; i++) {
        if (temp->arr[i] == element) {
            return i;
        }
    }
    return -1;
}

void CreateList(void* self, int size) {
    DynamicList* temp = self;
    temp->totalSize = size;
    temp->usedSize = 0;
    temp->arr = (int*)malloc(temp->totalSize * sizeof(int));
    printf("List Created\n");
}

void InsertElements(void* self, int element) {
    DynamicList* temp = self;
    if (temp->usedSize == temp->totalSize) {
        ReallocateList(temp);
    }
    temp->arr[temp->usedSize++] = element;
}

void InsertAt(void* self, int element, int index) {
    DynamicList* temp = self;
    int indexCopy;
    while (temp->totalSize < index) {
        ReallocateList(temp);
    }
    if (temp->usedSize == temp->totalSize) {
        ReallocateList(temp);
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
    DynamicList* temp = self;
    int i, j, count = 0;
    int Elementfound = SearchElement(temp, element);
    if (Elementfound > -1) {
        count = 1;
        j = Elementfound;
        i = Elementfound;
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
        printf("Element %d has been deleted from List\n", element);
    }
    else {
        system("cls");
        printf("Element %d does not exist in the List\n", element);
    }
}

void DeleteAt(void* self, int index) {
    DynamicList* temp = self;
    int i = 0;
    if (index <= temp->totalSize) {
        if (index > temp->usedSize) {
            system("cls");
            printf("The index is not filled in the List\n");
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
        system("cls");
        printf("Invalid Index : Index does not exist in List\n");
    }
}

void DisplayList(void* self) {
    DynamicList* temp = self;
    int i = 0;
    if (isListCreated(temp)) {
        if (isListEmpty(temp) == false) {
            printf("Elements in List:\n");
            for (; i < temp->usedSize; i++) {
                printf("%d ", (temp->arr)[i]);
            }
            printf("\n");
        }
    }
}

int main() {
    DynamicList arr1 = defaultList;
    int i, n, element, choice = 0;
    int index = arr1.usedSize;
start:
    printf("\n__DYNAMIC LIST ADT__\n");
    printf("1. Create List\n");
    printf("2. Insertion into List\n");
    printf("3. Deletion from List\n");
    printf("4. Search Element in List\n");
    printf("5. Display List\n");
    printf("6. Free List\n");
    printf("7. Exit\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        if (arr1.totalSize >= 0) {
            system("cls");
            printf("List has been already created.\n");
            goto start;
        }
        printf("Enter size of List to be created:");
        scanf("%d", &n);
        if(n < 0){
            system("cls");
            printf("Invalid Size\n");
            goto start;
        }
        system("cls");
        arr1.CreateList(&arr1, n);
        goto start;
    case 2:
        if (isListCreated(&arr1)) {
            system("cls");
        insert:
            printf("\nInsertion Options\n");
            printf("1. Insert Elements into List\n");
            printf("2. Insert Element at Index\n");
            printf("Enter choice:");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                printf("Enter no of elements to insert in List:");
                scanf("%d", &n);
                printf("Enter elements:");
                for (i = 0; i < n; i++) {
                    scanf("%d", &element);
                    arr1.InsertElements(&arr1, element);
                }
                system("cls");
                printf("Elements Inserted into List\n");
                break;
            case 2:
                printf("Enter element to be inserted:");
                scanf("%d", &element);
                printf("Enter index where element will be inserted:");
                scanf("%d", &index);
                if(index<1){
                    system("cls");
                    printf("Invalid index\n");
                    goto start;
                }
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
        if (isListCreated(&arr1)) {
            if (isListEmpty(&arr1) == false) {
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
                    if(index<1){
                        system("cls");
                        printf("Invalid index\n");
                        goto start;
                    }
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
        if (isListCreated(&arr1)) {
            if (isListEmpty(&arr1) == false) {
                printf("Enter element to be searched:");
                scanf("%d", &element);
                index = arr1.SearchElement(&arr1, element);
                if (index == -1) {
                    system("cls");
                    printf("Element %d does not exist in List\n", element);
                }
                else {
                    system("cls");
                    printf("Element %d exists in List at index %d \n", element, index + 1);
                }
                goto start;
            }
        }
    case 5:
        system("cls");
        arr1.DisplayList(&arr1);
        goto start;
    case 6:
        if (arr1.totalSize > -1) {
            free(arr1.arr);
            arr1.arr = NULL;
            arr1.usedSize = -1;
            arr1.totalSize = -1;
            system("cls");
            printf("List Memory Deallocated/Freed\n");
        }
        else {
            system("cls");
            printf("List not Allocated\n");
        }
        goto start;
    case 7:
        exit(0);
    default:
        system("cls");
        printf("Wrong input.Please enter between 1 and 7\n\n");
        goto start;
    }
    return 0;
}