#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define CUSTOMER_NAME_SIZE 100
#define CPF_SIZE 12

typedef enum {
    PRIORITY_HIGH   = 1,
    PRIORITY_MEDIUM = 2,
    PRIORITY_LOW    = 3
} priority_t;

typedef struct {
    char name[CUSTOMER_NAME_SIZE];
    char cpf[CPF_SIZE];
    priority_t priority;
    int items_qty;
} customer_t;

typedef struct node_s {
    customer_t customer;
    struct node_s* next;
} node_t;

typedef struct {
    node_t* first;
    int len;
} queue_t;

queue_t queue_init();
void queue_deinit(queue_t* q);
void queue_set(queue_t* q, const customer_t* new_customer);
customer_t queue_pop(queue_t* q);
bool queue_empty(const queue_t* q);

#endif // QUEUE_H
