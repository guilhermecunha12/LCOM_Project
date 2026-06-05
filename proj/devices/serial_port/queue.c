#include "queue.h"

Queue create_queue() {
    Queue queue;
    queue.head = 0;
    queue.tail = 0;
    queue.count = 0;
    return queue;
}

int is_queue_full(Queue *queue) {
    return queue->count == QUEUE_SIZE;
}

int is_queue_empty(Queue *queue) {
    return queue->count == 0;
}

int enqueue(Queue *queue, uint8_t data) {
    if (is_queue_full(queue)) return 1;

    queue->data[queue->tail] = data;
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;
    queue->count++;
    return 0;
}

int dequeue(Queue *queue, uint8_t *data) {
    if (is_queue_empty(queue)) return 1;

    *data = queue->data[queue->head];
    queue->head = (queue->head + 1) % QUEUE_SIZE;
    queue->count--;
    return 0;
}
