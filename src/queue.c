#include "queue.h"

#include <stdlib.h>
#include <stdbool.h>
#include "malloc_dbg.h"

queue_t queue_init() {
    return (queue_t) { .first = NULL, .len = 0 };
}

void queue_deinit(queue_p q) {
    node_p it = q->first, rm;

    while (it != NULL) {
        rm = it;
        it = it->next;
        free(rm);
    }
}

void queue_set(queue_p q, const customer_p new_customer) {
    node_p new_node = (node_p) malloc(sizeof(node_t));

    new_node->customer = *new_customer;

    if ((queue_empty(q) == true) ||
        (new_customer->priority < q->first->customer.priority)) {
        new_node->next = q->first;
        q->first = new_node;
    } else {
        node_p it = q->first;

        while (it->next != NULL &&
               it->next->customer.priority <= new_node->customer.priority) {
            it = it->next;
        }

        new_node->next = it->next;
        it->next = new_node;
    }

    q->len++;
}

customer_t queue_pop(queue_p q) {
    customer_t customer;
    node_p rm = q->first;

    q->first = rm->next;
    customer = rm->customer;
    free(rm);
    q->len--;

    return customer;
}

void queue_merge(queue_p dest, queue_p src) {
    customer_t customer;

    while (queue_empty(src) == false) {
        customer = queue_pop(src);
        queue_set(dest, &customer);
    }
}

int queue_length(const queue_p q) {
    int len = 0;

    for (node_p it = q->first; it != NULL; it = it->next) {
        len++;
    }

    return len;
}

bool queue_empty(const queue_p q) {
    return q->first == NULL;
}
