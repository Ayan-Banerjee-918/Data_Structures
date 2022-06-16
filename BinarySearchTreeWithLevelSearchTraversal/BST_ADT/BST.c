#include<stdio.h>
#include<stdlib.h>
//#include<Practice/DataStructures/BinaryTree/PrintingBTs/printBinaryTree.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}BST;

typedef struct BQueue{
    BST *elements;
    struct BQueue *link;
} queue;

//Queue Functions for BFS
void initQueue(queue **);
void enqueue(queue **, queue **, queue **, BST *);
BST* dequeue(queue **);

//BST Functions
void initNode(BST **);
void insertChild(BST **, int);
void deleteChild(BST **, int);
BST *findMinimum(BST *);
BST *findMaximum(BST *);
void levelOrderTraversal(BST *);

//QUEUE
void initQueue(queue **temp){
    *temp = (queue*)malloc(sizeof(queue));
    (*temp)->elements = NULL;
    (*temp)->link = NULL;
}

void enqueue(queue **temp,queue **front,queue **rear,BST* newNode){
    queue *newQueueNode = (queue *)malloc(sizeof(queue));
    newQueueNode->elements = newNode;
    newQueueNode->link = NULL;
    if(*front==NULL){
        *rear = *front = *temp = newQueueNode;
    }
    else{
        (*rear)->link = newQueueNode;
        *rear = (*rear)->link;
    }
}

BST* dequeue(queue **front){
    BST *tmp = (*front)->elements;
    if(!((*front)==NULL)){
        *front = (*front)->link;
    }
    return tmp;
}

//if BST==NULL Sir boleche error check korte
//BST
void initNode(BST **temp){
    *temp = (BST *)malloc(sizeof(BST));
    (*temp)->left = (*temp)->right = NULL;
}

void insertChild(BST **temp,int data){
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

BST* findMinimum(BST* temp){
    while(temp && temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

BST* findMaximum(BST* temp){
    while(temp && temp->right!=NULL){
        temp = temp->right;
    }
    return temp;
}

void deleteChild(BST** temp,int data){
    if(*temp==NULL){
        return;
    }
    else if(data<(*temp)->data){
        deleteChild(&((*temp)->left), data);
    }
    else if(data>(*temp)->data){
        deleteChild(&((*temp)->right), data);
    }
    else{
        if((*temp)->left==NULL && (*temp)->right==NULL){
            (*temp) = NULL;
        }
        else if((*temp)->left==NULL){
            (*temp) = (*temp)->right;
        }
        else if((*temp)->right==NULL){
            (*temp) = (*temp)->left;
        }
        else{
            BST *tmpNode = findMinimum((*temp)->right);
            (*temp)->data = tmpNode->data;
            deleteChild (&((*temp)->right), tmpNode->data);
        }
    }
}

void levelOrderTraversal(BST* temp){
    queue *front , *rear;
    queue *currentNode;
    initQueue(&currentNode);
    front = rear = NULL;
    enqueue(&currentNode, &front, &rear, temp);
    while(front){
        temp = dequeue(&front);
        printf("%d ", temp->data);
        if(temp->left){
            enqueue(&currentNode, &front, &rear, temp->left);
        }
        if(temp->right){
            enqueue(&currentNode, &front, &rear, temp->right);
        } 
    }
    printf("\n");
}

void printInOrderRange(BST* t,int x,int y) {
    if (t == NULL){
        return;
    }
    if(t->data>x && t->left!=NULL){
        printInOrderRange(t->left, x, y);
    }
    if(t->data>=x && t->data<=y){
        printf("%d ", t->data);
    }
    if(t->data<y && t->right!=NULL){
        printInOrderRange(t->right, x, y);
    }
}

void main(){
    BST *binaryTree = NULL;
    // insertChild(&binaryTree, 10);
    // insertChild(&binaryTree, 29);
    // insertChild(&binaryTree, 13);
    // insertChild(&binaryTree, 54);
    // insertChild(&binaryTree, 3);
    // insertChild(&binaryTree, 32);
    // insertChild(&binaryTree, 6);
    // insertChild(&binaryTree, 55);
    // insertChild(&binaryTree, 7);
    // insertChild(&binaryTree, 27);
    // insertChild(&binaryTree, 23);
    // insertChild(&binaryTree, 14);
    // insertChild(&binaryTree, 21);
    // insertChild(&binaryTree, 10);
    // insertChild(&binaryTree, 9);
    // insertChild(&binaryTree, 33);
    // insertChild(&binaryTree, 17);
    // insertChild(&binaryTree, 11);
    // insertChild(&binaryTree, 43);
    // insertChild(&binaryTree, 29);
    // insertChild(&binaryTree, 22);
    // insertChild(&binaryTree, 5);
    // insertChild(&binaryTree, 15);
    // insertChild(&binaryTree, 19);
    // insertChild(&binaryTree, 28);
    // insertChild(&binaryTree, 36);
    insertChild(&binaryTree, 10);
    insertChild(&binaryTree, 8);
    insertChild(&binaryTree, 9);
    insertChild(&binaryTree, 13);
    insertChild(&binaryTree, 11);
    insertChild(&binaryTree, 14);
    // levelOrderTraversal(binaryTree);
    // printf("\n");
    // print_ascii_tree(binaryTree);
    // printf("\n");
    // deleteChild (&binaryTree, 7);
    // levelOrderTraversal(binaryTree);
    // printf("\n");
    // print_ascii_tree(binaryTree);
    // printf("\n");
    // deleteChild (&binaryTree, 13);
    levelOrderTraversal(binaryTree);
    printf("Minimum Value in BST: %d\n", (findMinimum(binaryTree))->data);
    printf("Maximum Value in BST: %d\n", (findMaximum(binaryTree))->data);
    printf("\n");
    //print_ascii_tree(binaryTree);
    printInOrderRange(binaryTree,8,11);
    printf("\n");
    system("pause");
}
