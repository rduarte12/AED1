#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue Queue;

Queue* create_queue();
int is_empty(const Queue *q);
int is_full(const Queue *q);
int enqueue(Queue *q, int value);
int dequeue(Queue *q, int *value);
int front(const Queue *q, int *value);
int size(const Queue *q);
void free_queue(Queue **q);

#endif
