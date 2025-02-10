#include "queue.h"

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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

    *q = queue_init();
}

void queue_set(queue_t* q, const customer_t* new_customer)
{
    node_t* new_node = (node_t*) malloc(sizeof(node_t));

    new_node->customer = *new_customer;

    if ((queue_empty(q)) || (new_customer->priority < q->first->customer.priority)) {
        new_node->next = q->first;
        q->first = new_node;
    } else {
        node_t* it = q->first;

        while ((it->next != NULL) && (it->next->customer.priority <= new_node->customer.priority)) {
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
    node_t* rm;

    assert(!queue_empty(q));

    rm = q->first;
    q->first = rm->next;
    customer = rm->customer;
    free(rm);
    q->len--;

    return customer;
}

bool queue_empty(const queue_t* q)
{
    return q->first == NULL;
}
