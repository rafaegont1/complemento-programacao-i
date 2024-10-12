#include "till.h"

#include <stdlib.h>
#include "queue.h"

void till_init(till_p tills) {
    for (int i = 0; i < TILL_COUNT; i++) {
        tills[i].id = i + 1;
        tills[i].queue = queue_init();
        tills[i].available = false;
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
