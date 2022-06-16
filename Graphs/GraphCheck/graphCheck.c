//using Adjacency Matrix

#include <stdio.h>
#include <stdlib.h>

typedef struct linkedList{
    int data;
    struct linkedList *link;
} list;

list *front, *rear;

int isEmptyQueue() {
    if (front == NULL) {
        return 1;
    }
    return 0;
}

list* enQueue(list* temp, int val) {
    list* node = (list*)malloc(sizeof(list));
    node->data = val;
    node->link = NULL;
    if (isEmptyQueue()) {
        rear = front = temp = node;
        return temp;
    }
    rear->link = node;
    rear = node;
    return temp;
}

list* deQueue(list* temp) {
    if (!isEmptyQueue()) {
        front = front->link;
        temp = temp->link;
    }
    return temp;
}

int checkTreeOrNot(int *graph,int VertexCount){
    int *visited = (int*)malloc(VertexCount*sizeof(int));
    if(!visited){
        printf("Memory Allocation Error!");
        return;
    }
    int i = 0,j = 0,cnt = 0;
    for (i = 0; i < VertexCount; i++){
        visited[i] = 0;
    }
    list* queue = (list*)malloc(sizeof(list));
    queue->link = front = rear = NULL;
    for (i = 0; i < VertexCount; i++){
        if((queue==NULL)||(*((graph + i * VertexCount) + i) != 0)){
            return 0;
        }
        if (i == 0) {
            queue = enQueue(queue, i);
            visited[i]++;
        }
        for (j = 0; j < VertexCount;j++){
            if(*((graph + (front->data) * VertexCount) + j)==1){
                if (*((graph + (front->data) * VertexCount) + j) != (*((graph + j * VertexCount) + front->data))) {
                    return 0;
                }
                if(visited[j]==0){
                    queue = enQueue(queue, j);
                    visited[j]++;
                }
                else{
                    if(visited[j]>1){
                        cnt++;
                    }
                    if(cnt == 2){
                        return 0;
                    }
                }
            }
        }
        visited[front->data]++;
        queue = deQueue(queue);
        cnt = 0;
    }
    return 1;
}

void main(){
    int graph[4][4] = 
    { 
        {0, 1, 1, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 1},
        {0, 0, 1, 0}
    };
    printf("%d\n", checkTreeOrNot(*graph,sizeof(graph)/sizeof(graph[0])));
    system("pause");
}