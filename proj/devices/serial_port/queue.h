#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#define QUEUE_SIZE 16

/**
 * @brief Lightweight queue implementation for storing data received from the serial port.
 */
typedef struct {
    uint8_t data[QUEUE_SIZE];
    int head;
    int tail;
    int count;
} Queue;

/**
 * @brief Creates and initializes a new Queue instance.
 * @return Queue object initialized and ready to be used. 
 */
Queue create_queue();

/**
 * @brief Enqueues a byte of data into the queue. If the queue is full, it does not add the data and returns an error code.
 * @param queue The queue to which the data will be added.
 * @param data The data to be enqueued.
 * @return 0 if the data was successfully enqueued, -1 if the queue is full.
 */
int enqueue(Queue *queue, uint8_t data);

/**
 * @brief Dequeues a byte of data from the queue. If the queue is empty, it does not remove any data and returns an error code.
 * @param queue The queue from which the data will be removed.
 * @param data Pointer to the location where the dequeued data will be stored.
 * @return 0 if the data was successfully dequeued, -1 if the queue is empty.
 */
int dequeue(Queue *queue, uint8_t *data);

/**
 * @brief Checks if the queue is full.
 * @param queue The queue to check.
 * @return 1 if the queue is full, 0 otherwise.
 */
int is_queue_full(Queue *queue);

/**
 * @brief Checks if the queue is empty.
 * @param queue The queue to check.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int is_queue_empty(Queue *queue);

#endif /* QUEUE_H */
