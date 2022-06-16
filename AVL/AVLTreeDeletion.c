#include <stdio.h>
#include <stdlib.h>

typedef struct AVLtreeNode
{
    int data;
    struct AVLtreeNode *left;
    struct AVLtreeNode *right;
    int height;
}node;

int maximum(int, int);
int getHeight(node *);
int getBalance(node *);
node *newNode(int);
node *leftRotate(node *);
node *rightRotate(node *);
node *insertNode(node *,int);
node *findMinimum(node *);
node *deleteNode(node *,int);
void traversePreOrder(node *);
void traverseInOrder(node *);

int maximum(int a, int b) {
  return (a > b) ? a : b;
}

int getHeight(node *tmp){
    if(tmp==NULL){
        return 0;
    }
    return tmp->height;
}

int getBalance(node* tmp){
    if(tmp==NULL){
        return 0;
    }
    return getHeight(tmp->left) - getHeight(tmp->right);
}

node* newNode(int data){
    node* tmp=(node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 1;
    return tmp;
}

node* leftRotate(node* x){
    node *y = x->right;
    node *tmp = y->left;
    y->left = x;
    x->right = tmp;
    x->height = maximum(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maximum(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

node* rightRotate(node* x){
    node* y = x->left;
    node *tmp = y->right;
    y->right = x;
    x->left = tmp;
    x->height = maximum(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maximum(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

node* insertNode(node *tmp,int data){
    if(tmp==NULL){
        return newNode(data);
    }
    if(data<tmp->data){
        tmp->left = insertNode(tmp->left, data);
    }
    else if(data>tmp->data){
        tmp->right = insertNode(tmp->right, data);
    }
    else{
        return tmp;
    }
    tmp->height = 1 + maximum(getHeight(tmp->left), getHeight(tmp->right));
    int balance = getBalance(tmp);
    if (balance > 1 && getBalance(tmp->left) >= 0){
        printf("Portion of tree to be rotated:\n");
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n\n");
        printf("Right Rotation\n\n");
        tmp = rightRotate(tmp);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        return tmp;
    }

    if (balance > 1 && getBalance(tmp->left) < 0) {
        printf("Portion of tree to be rotated:\n");
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n\n");
        printf("Left Right Rotation\n\n");
        printf("After left rotation.\n");
        tmp->left = leftRotate(tmp->left);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        printf("After right rotation.\n");
        tmp = rightRotate(tmp);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        return tmp;
    }

    if (balance < -1 && getBalance(tmp->right) <= 0){
        printf("Portion of tree to be rotated:\n");
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n\n");
        printf("Left Rotation\n\n");
        tmp = leftRotate(tmp);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        return tmp;
    }

    if (balance < -1 && getBalance(tmp->right) > 0) {
        printf("Portion of tree to be rotated:\n");
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n\n");
        printf("Right Left Rotation\n\n");
        printf("After right rotation.\n");
        tmp->right = rightRotate(tmp->right);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        printf("After left rotation.\n");
        tmp = leftRotate(tmp);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        return tmp;
    }
    return tmp;
}

node* findMinimum(node* temp){
    while(temp && temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

node* deleteNode(node* tmp,int data){
    if(tmp==NULL){
        return tmp;
    }
    if(data<tmp->data){
        tmp->left = deleteNode(tmp->left, data);
    }
    else if(data>tmp->data){
        tmp->right = deleteNode(tmp->right, data);
    }
    else{
        if((tmp->left == NULL) && (tmp->right == NULL)){
            tmp = NULL;
        }
        else if(tmp->left == NULL){
            tmp = tmp->right;
        }
        else if(tmp->right == NULL){
            tmp = tmp->left;
        }
        else{
            node *tmpNode = findMinimum(tmp->right);
            tmp->data = tmpNode->data;
            tmp->right = deleteNode (tmp->right, tmpNode->data);
        }
    }
    if(tmp==NULL){
        return tmp;
    }
    tmp->height = 1 + maximum(getHeight(tmp->left), getHeight(tmp->right));
    int balance = getBalance(tmp);
    if (balance > 1 && getBalance(tmp->left) >= 0){
        printf("Portion of tree to be rotated:\n");
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n\n");
        printf("Right Rotation\n\n");
        tmp = rightRotate(tmp);
        traversePreOrder(tmp);
        printf("\n");
        return tmp;
    }

    if (balance > 1 && getBalance(tmp->left) < 0) {
        printf("Portion of tree to be rotated:\n");
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n\n");
        printf("Left Right Rotation\n\n");
        printf("After left rotation.\n");
        tmp->left = leftRotate(tmp->left);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        printf("After right rotation.\n");
        tmp = rightRotate(tmp);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        return tmp;
    }

    if (balance < -1 && getBalance(tmp->right) <= 0){
        printf("Portion of tree to be rotated:\n");
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n\n");
        printf("Left Rotation\n\n");
        tmp = leftRotate(tmp);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        return tmp;
    }

    if (balance < -1 && getBalance(tmp->right) > 0) {
        printf("Portion of tree to be rotated:\n");
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n\n");
        printf("Right Left Rotation\n\n");
        printf("After right rotation.\n");
        tmp->right = rightRotate(tmp->right);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        printf("After left rotation.\n");
        tmp = leftRotate(tmp);
        printf("PreOrder:\n");
        traversePreOrder(tmp);
        printf("\n");
        printf("InOrder:\n");
        traverseInOrder(tmp);
        printf("\n");
        return tmp;
    }
    return tmp;
}

void traversePreOrder(node* tmp){
    if(tmp==NULL){
        return;
    }
    printf("%d ", tmp->data);
    traversePreOrder(tmp->left);
    traversePreOrder(tmp->right);
}

void traverseInOrder(node* tmp){
    if(tmp==NULL){
        return;
    }
    traverseInOrder(tmp->left);
    printf("%d ", tmp->data);
    traverseInOrder(tmp->right);
}

int main(){
    int choice = 0, value = 0;
    node *root = NULL;
start:
    printf("\n___AVLTree___\n");
    printf("1. Insert Value\n");
    printf("2. Delete Value\n");
    printf("3. Display Tree (Pre-Order and In-Order)\n");
    printf("4. Exit\n");
    printf("Enter your choice:\n");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            printf("Enter a value to be inserted into tree:");
            scanf("%d", &value);
            system("cls");
            root = insertNode(root, value);
            printf("%d has been inserted into tree.\n",value);
            goto start;
        case 2:
            printf("Enter value to be deleted from tree:");
            scanf("%d", &value);
            system("cls");
            printf("Tree PreOrder before Deletion:\n");
            traversePreOrder(root);
            printf("\n");
            printf("Tree InOrder before Deletion:\n");
            traverseInOrder(root);
            printf("\n\n");
            printf("Deleting %d from tree.\n\n",value);
            root = deleteNode(root, value);
            goto start;
        case 3:
            system("cls");
            printf("Tree Traversal in PreOrder:\n");
            traversePreOrder(root);
            printf("\n");
            printf("Tree Traversal in InOrder:\n");
            traverseInOrder(root);
            printf("\n");
            goto start;
        case 4:
            exit(0);
        default:
            printf("Invalid choice! Enter between 1 and 4.");
    }
    system("pause");
    return 0;
}