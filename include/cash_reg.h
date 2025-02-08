#ifndef CASH_REG_H
#define CASH_REG_H

#include "queue.h"

typedef struct {
    int id;
    queue_t queue;
    bool is_available;
} cash_reg_t;

cash_reg_t cr_init(int id);
void cr_deinit(cash_reg_t* cash_reg);

#endif // CASH_REG_H
