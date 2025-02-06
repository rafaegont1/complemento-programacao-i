#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef enum {
    PRIORITY_HIGH   = 1,
    PRIORITY_MEDIUM = 2,
    PRIORITY_LOW    = 3
} priority_t;

typedef struct {
    char name[100];
    int cpf;
    priority_t priority;
    int items_qty;
} customer_t, *customer_p;

typedef struct node_s {
    customer_t customer;
    struct node_s* next;
} node_t, *node_p;

typedef struct {
    node_p first;
    int len;
} queue_t, *queue_p;

queue_t queue_init();
void queue_deinit(queue_p q);
void queue_set(queue_p q, const customer_p new_customer);
customer_t queue_pop(queue_p q);
void queue_merge(queue_p dst, queue_p src);
int queue_length(const queue_p q);
bool queue_empty(const queue_p q);

#endif // QUEUE_H
