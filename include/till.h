#ifndef TILL_H
#define TILL_H

#include "queue.h"

#define TILL_COUNT 5

typedef struct {
    int id;
    queue_t queue;
    bool available;
} till_t, *till_p;

void till_init(till_p tills);
void till_deinit(till_p tills);
till_p till_find(const till_p tills, const int id);

#endif // TILL_H
