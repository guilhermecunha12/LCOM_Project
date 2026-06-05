#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#define QUEUE_SIZE 16

typedef struct {
    uint8_t data[QUEUE_SIZE];
    int head;
    int tail;
    int count;
} Queue;

Queue create_queue();
int enqueue(Queue *queue, uint8_t data);
int dequeue(Queue *queue, uint8_t *data);
int is_queue_full(Queue *queue);
int is_queue_empty(Queue *queue);

#endif /* QUEUE_H */
