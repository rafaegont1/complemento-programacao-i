#include "queue.h"

#include <stdlib.h>
#include <stdbool.h>

queue_t queue_init()
{
    return (queue_t) {
        .first = NULL,
        .len = 0
    };
}

void queue_deinit(queue_t* q)
{
    node_t* it = q->first;

    while (it != NULL) {
        node_t* rm = it;
        it = it->next;
        free(rm);
    }
}

void queue_set(queue_t* q, const customer_t* new_customer)
{
    node_t* new_node = (node_t*) malloc(sizeof(node_t));

    new_node->customer = *new_customer;

    if ((queue_empty(q) == true) ||
        (new_customer->priority < q->first->customer.priority)) {
        new_node->next = q->first;
        q->first = new_node;
    } else {
        node_t* it = q->first;

        while ((it->next != NULL) &&
               (it->next->customer.priority <= new_node->customer.priority)) {
            it = it->next;
        }

        new_node->next = it->next;
        it->next = new_node;
    }

    q->len++;
}

customer_t queue_pop(queue_t* q)
{
    customer_t customer;
    node_t* rm = q->first;

    q->first = rm->next;
    customer = rm->customer;
    free(rm);
    q->len--;

    return customer;
}

void queue_merge(queue_t* dst, queue_t* src)
{
    customer_t customer;

    while (queue_empty(src) == false) {
        customer = queue_pop(src);
        queue_set(dst, &customer);
    }
}

int queue_length(const queue_t* q)
{
    int len = 0;

    for (node_t* it = q->first; it != NULL; it = it->next) {
        len++;
    }

    return len;
}

bool queue_empty(const queue_t* q)
{
    return q->first == NULL;
}
