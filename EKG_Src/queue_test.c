#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_QUEUE_SIZE 10000
#define BUF_SIZE 1024

typedef char element;

element buf[BUF_SIZE];

typedef struct QueueType {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void init(QueueType *Q) {
    Q->front = Q->rear = 0;
}

QueueType *create_queue(void) {
    QueueType *new_queue = (QueueType *)malloc(sizeof(QueueType));
    if ( new_queue == NULL ) {
        perror("malloc error");
    } else {
        init(new_queue);
        return new_queue;
    }
}

int is_empty(QueueType *Q) {
    return (Q->front == Q->rear);
}

int is_full(QueueType *Q) {
    return ((Q->front)%MAX_QUEUE_SIZE == (Q->rear+1)%MAX_QUEUE_SIZE);
}

void enqueue(QueueType *Q, element item) {
    if ( is_full(Q) ) {
        perror("error");
    } else {
        Q->rear = (Q->rear+1)%MAX_QUEUE_SIZE;
        Q->queue[Q->rear] = item;
    }
}

element dequeue(QueueType *Q) {
    if ( is_empty(Q) ) {
        perror("error");
    } else {
        Q->front = (Q->front+1)%MAX_QUEUE_SIZE;
        return Q->queue[Q->front];
    }
}

element peek(QueueType *Q) {
    if ( is_empty(Q) ) {
        perror("error");
    } else {
        return Q->queue[(Q->front+1)%MAX_QUEUE_SIZE];
    }
}

void display(QueueType *Q) {
    printf("f<-[ ");
    if ( Q->front > Q->rear ) {
        for ( int i=(Q->front+1); i<MAX_QUEUE_SIZE; i++ ) {
            printf("%c ", Q->queue[i]);
        }
        for ( int i=0; i<=(Q->rear); i++ ) {
            printf("%c ", Q->queue[i]);
        }
    } else {
        for ( int i=(Q->front+1); i<=Q->rear; i++ ) {
            printf("%c ", Q->queue[i]);
        }
    }
    printf("]<-r\n");
}

void push_data(QueueType *Q, char *str) {
	while ( *str != '\0' ) {
		enqueue(Q, *str);
		*str++;
	} 
}

void pop_data(QueueType *Q) {
    int i=0, cnt=0;
    element e;
    memset(buf, '\0', BUF_SIZE);
    while ( cnt < 10 ) {
        e = dequeue(Q);
        if ( e == '/' ) {
            cnt++;
        }
        buf[i++] = e;
    }
}

int main(void) {
    QueueType *queue = create_queue();
	char s[30][100];
    int i;
    for ( i=0; i<30; i++ ) {
        sprintf(s[i], "abc%d", i);
    }
    char *delimeter = "/";
	for ( i=0; i<30; i++ ) {
        push_data(queue, s[i]);
        push_data(queue, delimeter);
    }
	display(queue);
    printf("%d %d\n", queue->front, queue->rear);

    pop_data(queue);
	display(queue);
    printf("%d %d\n", queue->front, queue->rear);
    printf("%s\n", buf);

    pop_data(queue);
	display(queue);
    printf("%d %d\n", queue->front, queue->rear);
    printf("%s\n", buf);
    return 0;
}
