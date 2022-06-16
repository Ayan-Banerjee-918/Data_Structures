#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct HashTable{
    int *arr;
    int full;
    int size;
    int crntFull;
} hash;

hash* createHashTable(int size,hash* table){
    table->size = size;
    table->arr = (int *)malloc(size*sizeof(int));
    if(!table->arr){
        printf("Memory Allocation Error.");
        exit(0);
    }
    while(size>0){
        table->arr[size - 1] = -9999;
        size--;
    }
    table->full = 0;
    table->crntFull = 0;
    return table;
}

int hashFunction(int num){
    return (num % 10);
}

int collisionDetectInsert(hash* table,int pos){
    int count = 0;
    int i = table->size - 1;
    while(count!=i){
        if(pos==-1){
            pos = i;
        }
        if(table->arr[pos]==-9999){
            return pos;
        }
        else{
            count = count + 1;
            pos--;
        }
    }
    if(count==i){
        return -1234;
    }
}

int collisionDetectDelete(hash* table,int data,int pos){
    int count = 0;
    int i = table->size - 1;
    while(count!=i){
        if(pos==-1){
            pos = i;
        }
        if(table->arr[pos]==data){
            return pos;
        }
        else{
            count = count + 1;
            pos--;
        }
    }
    if(count==i){
        return -1234;
    }
}

int collisionDetect(hash* table,int pos,int data,int check){
    if(check==0){
        return collisionDetectInsert(table, pos);
    }
    else{
        return collisionDetectDelete(table, data, pos);
    }
}

hash* insertItem(int data,hash* table){
    int hashedVal = hashFunction(data);
    int correctedPos = -1;
    if(table->arr[hashedVal]!=-9999){
        correctedPos = collisionDetect(table, hashedVal - 1, data, 0);
        if(correctedPos==-1234){
            printf("Hash Table Full\n");
            return table;
        }
        table->arr[correctedPos] = data;
        table->crntFull++;
    }
    else{
        table->arr[hashedVal] = data;
        table->crntFull++;
    }
    if (table->crntFull == table->size) {
        table->full = 1;
    }
    return table;
}

hash* deleteItem(int data,hash* table){
    int hashedPos = hashFunction(data);
    int correctedPos = -1;
    if(table->arr[hashedPos]!=data){
        correctedPos = collisionDetect(table, hashedPos - 1, data, 1);
        if(correctedPos==-1234){
            printf("%d not present in hash table\n", data);
            return table;
        }
        table->arr[correctedPos] = -9999;
    }
    else{
        table->arr[hashedPos] = -9999;
    }
    if(table->full==1){
        table->full = 0;
    }
    table->crntFull--;
    printf("%d deleted from Hash Table\n", data);
    return table;
}

void searchItem(int data,hash* table){
    int hashedPos = hashFunction(data);
    int correctedPos = -1;
    if(table->arr[hashedPos]==data){
        printf("%d present in Hash Table at %d position\n", data, (hashedPos+1));
    }
    else{
        correctedPos = collisionDetectDelete(table, data, hashedPos - 1);
        if(correctedPos==-1234){
            printf("%d not present in hash table\n", data);
        }
        else{
            printf("%d present in Hash Table at %d position\n", data, (correctedPos+1));
        }
    }
}

void displayHashTable(hash* table){
    printf("Hash Table:\n");
    for (int i = 0; i < table->size; i++){
        if(table->arr[i]==-9999){
            printf("X ");
        }
        else{
            printf("%d ", table->arr[i]);
        }
    }
    printf("\n");
}

int main(){
    hash *table = (hash*)malloc(sizeof(hash));
    int size = -1;
    int choice = 0;
    int data = 0;
    printf("Enter size of hash table:");
    scanf("%d", &size);
    while(size<1 || size>10){
        printf("Invalid size Entered.Please enter a size between 1 and 10.\n");
        printf("Enter size:");
        scanf("%d", &size);
    }
    table = createHashTable(size, table);
    system("cls");
    while(1){
        printf("\n__HASH TABLE__\n");
        printf("1. Insert into Hash Table\n");
        printf("2. Delete from Hash Table\n");
        printf("3. Search Hash Table\n");
        printf("4. Display Hash Table\n");
        printf("5. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                if(table->full==1){
                    system("cls");
                    printf("Hash Table Full\n");
                    break;
                }
                printf("Enter data to be inserted into Hash Table (Ones place of data should be less than %d):", size);
                scanf("%d", &data);
                if(data%10>=size){
                    system("cls");
                    printf("Data with ones place greater than %d cannot be inserted into the Hash Table of size %d\n",size-1,size);
                    break;
                }
                system("cls");
                table = insertItem(data, table);
                printf("%d inserted into Hash Table\n",data);
                break;
            case 2:
                printf("Enter data to be deleted from Hash Table (Ones place of data should be less than %d):", size);
                scanf("%d", &data);
                if(data%10>=size){
                    system("cls");
                    printf("Data with ones place greater than %d cannot be present in the Hash Table of size %d\n",size-1,size);
                    break;
                }
                system("cls");
                table = deleteItem(data, table);
                break;
            case 3:
                printf("Enter data to search in Hash Table (Ones place of data should be less than %d):", size);
                scanf("%d", &data);
                if(data%10>=size){
                    system("cls");
                    printf("Data with ones place greater than %d cannot be present in the Hash Table of size %d\n",size-1,size);
                    break;
                }
                system("cls");
                searchItem(data, table);
                break;
            case 4:
                system("cls");
                displayHashTable(table);
                break;
            case 5:
                exit(0);
            default:
                system("cls");
                printf("Incorrect choice entered! Please enter between 1 and 5\n");
        }
    }
    return 0;
}