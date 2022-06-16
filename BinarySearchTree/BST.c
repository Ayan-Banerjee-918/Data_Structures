/*1. Create an binary tree with below functionality:
a) insertion an value
b) Search a value
c) Delete a value from tree.*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
} BST;

typedef struct linkedList{
    int data;
    struct linkedList *link;
} list;

static int flag = 0;

//Linked List Functions
list *addToList(list **, list**, int);

//BST Functions
void initNode(BST **);
list* readFile(char *location);
void generateBST(BST**,list*);
BST *findMinimum(BST *);
void insertChild(BST **, int);
void searchChild(BST *, int);
int deleteChild(BST **, int);
void displayInOrder(BST *);
void writeToFile(BST *, FILE **);

int maximum(int a,int b){
    return (a > b) ? a : b;
}

int getHeight(BST* tmp){
    if(tmp==NULL){
        return 0;
    }
    else{
        int left = getHeight(tmp->left);
        int right = getHeight(tmp->right);
        return maximum(left, right) + 1;
    }
}

//initialize node
void initNode(BST **temp){
    check:
    *temp = (BST *)malloc(sizeof(BST));
    if(*temp==NULL){
        goto check;
    }
    (*temp)->left = (*temp)->right = NULL;
}

//insert into List
list* addToList(list** temp, list** crntNode, int data){
    if(*temp==NULL){
        (*temp) = (list *)malloc(sizeof(list));
        (*temp)->data = data;
        (*temp)->link = NULL;
        return *temp;
    }
    else{
        list *newNode = NULL;
        while(newNode==NULL){
            newNode = (list *)malloc(sizeof(list));
        }
        newNode->data = data;
        newNode->link = NULL;
        (*crntNode)->link = newNode;
    }
    return (*crntNode)->link;
}

//read File and take input
list* readFile(char *location){
    int val = 0;
    list *numbers = NULL;
    list *currentNode = NULL;
    FILE* fptr;
    fptr = fopen(location, "r");
    if (fptr == NULL) {
        printf("Error in reading File.\n");
        exit(0);
    }
    while(fscanf(fptr,"%d",&val) == 1){
        currentNode=addToList(&numbers,&currentNode,val);
    }
    printf("File Read Completed Successfully\n");
    fclose(fptr);
    return numbers;
}

//generating BST from numbers read from File
void generateBST(BST** tmp ,list* numbers){
    while(numbers!=NULL){
        insertChild(&(*tmp), numbers->data);
        numbers = numbers->link;
    }
}

//insert a value to the tree
void insertChild(BST ** temp, int data){
    if((*temp)==NULL){
        initNode(&(*temp));
        (*temp)->data = data;
    }
    else{
        if(data<(*temp)->data){
            insertChild(&(*temp)->left, data);
        }
        else if(data>(*temp)->data){
            insertChild(&(*temp)->right, data);
        }
    }
}

//finds the node with minimum value of tree
BST* findMinimum(BST* temp){
    while(temp && temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

//deleting a value from th tree
int deleteChild(BST ** temp, int data){
    flag = 0;
    //for empty tree
    if(*temp==NULL){
        return flag;
    }
    //left subtree
    else if(data<(*temp)->data){
        deleteChild(&((*temp)->left), data);
    }
    //right subtree
    else if(data>(*temp)->data){
        deleteChild(&((*temp)->right), data);
    }
    else{
        flag = 1;
        //leaf node
        if((*temp)->left==NULL && (*temp)->right==NULL){
            (*temp) = NULL;
        }
        //only left child present
        else if((*temp)->left==NULL){
            (*temp) = (*temp)->right;
        }
        //only right child present
        else if((*temp)->right==NULL){
            (*temp) = (*temp)->left;
        }
        //both childs present
        else{
            BST *tmpNode = findMinimum((*temp)->right);
            (*temp)->data = tmpNode->data;
            deleteChild (&((*temp)->right), tmpNode->data);
        }
    }
    return flag;
}

//searches for value in the tree
void searchChild(BST *temp, int data){
    if(temp==NULL){
        printf("The value %d does not exist in the tree.\n",data);
        return;
    }
    else if(temp->data==data){
        printf("The value %d exists in the tree.\n", data);
        return;
    }
    else{
        if(data<temp->data){
            searchChild(temp->left, data);
        }
        else if(data>temp->data){
            searchChild(temp->right, data);
        }
    }
}

//displays tree
void displayInOrder(BST * tree){
    if (tree == NULL)
        return;
    displayInOrder(tree->left);
    printf("%d ", tree->data);
    displayInOrder(tree->right);
}

//write to file
void writeToFile(BST *tree, FILE** output){
    if (tree == NULL)
        return;
    writeToFile(tree->left,&(*output));
    fprintf(*output, "%d ", tree->data);
    writeToFile(tree->right,&(*output));
}

void main(){
    list *num = NULL;
    BST *tree = NULL;
    int choice = -1;
    int data = 0;
    FILE *output = fopen("output.txt", "w+");
    fprintf(output, "%s", "InOrder Traversal Of Tree:\n");
start:
    printf("\n__Binary Search Tree__\n\n");
    printf("0. Get Height\n");
    printf("1. Read File\n");
    printf("2. Generate Binary Search Tree\n");
    printf("3. Insert into Tree\n");
    printf("4. Search Tree\n");
    printf("5. Delete from Tree\n");
    printf("6. Display Tree InOrder\n");
    printf("7. Delete Tree and Clear File Buffer\n");
    printf("8. Exit\n");
    printf("\nEnter your choice:");
    scanf("%d", &choice);
    printf("\n");
    switch (choice)
    {
        case 0:
            printf("Height: %d\n", getHeight(tree));
            goto start;
        case 1:
            system("cls");
            num = readFile("input.txt");
            goto start;
        case 2:
            system("cls");
            generateBST(&tree, num);
            printf("Binary Search Tree Succesfully Generated.\n");
            goto start;
        case 3:
            printf("\nEnter number to be inserted into tree:");
            scanf("%d", &data);
            insertChild(&tree, data);
            system("cls");
            printf("%d succesfully inserted into tree\n",data);
            goto start;
        case 4:
            if(tree==NULL){
                system("cls");
                printf("Empty Tree\n");
                goto start;
            }
            printf("\nEnter number to be searched in tree:");
            scanf("%d", &data);
            system("cls");
            searchChild(tree, data);
            goto start;
        case 5:
            if(tree==NULL){
                system("cls");
                printf("Empty Tree\n");
                goto start;
            }
            printf("\nEnter number to be deleted from tree:");
            scanf("%d", &data);
            system("cls");
            if(deleteChild(&tree,data)){
                printf("%d succesfully deleted from tree.\n",data);
            }
            else{
                printf("%d not found in tree.\n",data);
            }
            goto start;
        case 6:
            if(tree==NULL){
                system("cls");
                printf("Empty Tree\n");
                goto start;
            }
            system("cls");
            printf("InOrder Traversal Of Tree:\n");
            displayInOrder(tree);
            printf("\n");
            goto start;
        case 7:
            system("cls");
            if(tree==NULL || num == NULL){
                if(tree == NULL){
                    printf("Tree Empty.\n");
                }
                else{
                    tree = NULL;
                    printf("Tree Deleted.\n");
                }
                if(num==NULL){
                    printf("File Buffer Empty.\n");
                }
                else{
                    num = NULL;
                    printf("File Buffer Cleared.\n");
                }
                goto start;
            }
            writeToFile(tree, &output);
            tree = NULL;
            num = NULL;
            printf("Tree Deleted and File Buffer cleared.\n");
            goto start;
        case 8:
            writeToFile(tree, &output);
            fclose(output);
            exit(0);
        default:
            system("cls");
            printf("Invalid Choice.Enter between 1 and 8.\n");
            goto start;
    }
}