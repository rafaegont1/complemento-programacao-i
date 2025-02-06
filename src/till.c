#include "till.h"

#include <stdlib.h>
#include "queue.h"

void till_init(till_p tills) {
    for (int i = 0; i < TILL_COUNT; i++) {
        tills[i] = (till_t) {
            .id = i + 1,
            .queue = queue_init(),
            .is_available = true
        };
    }
}

void till_deinit(till_p tills) {
    for (int i = 0; i < TILL_COUNT; i++) {
        queue_deinit(&tills[i].queue);
    }
}

till_p till_find(const till_p tills, const int id) {
    till_p till = NULL;

    for (int i = 0; i < TILL_COUNT; i++) {
        if (tills[i].id == id) {
            till = &tills[i];
            break;
        }
    }

    return till;
}

bool till_any_open(const till_p tills) {
    for (int i = 0; i < TILL_COUNT; i++) {
        if (tills[i].is_available == true) {
            return true;
        }
    }

    return false;
}

int till_count_open(const till_p tills) {
    int count = 0;

    for (int i = 0; i < TILL_COUNT; i++) {
        if (tills[i].is_available == true) {
            count++;
        }
    }

    return count;
}
