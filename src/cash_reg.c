#include "cash_reg.h"

#include "queue.h"

cash_reg_t cr_init(int id)
{
    return (cash_reg_t) {
        .id = id,
        .queue = queue_init(),
        .is_available = true
    };
}

void cr_deinit(cash_reg_t* cash_reg)
{
    queue_deinit(&cash_reg->queue);
}
