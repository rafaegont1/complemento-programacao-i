#include "market.h"

#include <stdio.h>
#include "cash_reg.h"
#include "queue.h"
#include "util.h"

static inline int mkt_scanf_id(const char* msg)
{
    int id;

    do {
        printf("%s (1 a %d): ", msg, MKT_CASH_REG_COUNT);
    } while ((scanf("%d%*c", &id) != 1) && (id < 1 || id > MKT_CASH_REG_COUNT));

    return id;
}

static void mkt_reallocate_customers(cash_reg_t* cash_regs, cash_reg_t* src)
{
    while (src->queue.len > 0) {
        int id = -1;
        cash_reg_t* dst = NULL;

        for (int i = 0; i < MKT_CASH_REG_COUNT; i++) {
            cash_reg_t* iter = &cash_regs[i];
            if (iter == src || !iter->is_available) {
                continue;
            } else if (dst == NULL || iter->queue.len < dst->queue.len) {
                dst = iter;
                id = i + 1;
            }
        }

        customer_t customer = queue_pop(&src->queue);
        queue_set(&dst->queue, &customer);
        printf("Cliente %s realocado para o caixa de ID %d\n", customer.name, id);
    }
}

void mkt_init(cash_reg_t* mkt)
{
    for (int i = 0; i < MKT_CASH_REG_COUNT; i++) {
        mkt[i] = cr_init(i + 1);
    }
}

void mkt_deinit(cash_reg_t* mkt)
{
    for (int i = 0; i < MKT_CASH_REG_COUNT; i++) {
        cr_deinit(&mkt[i]);
    }
}

int mkt_count_open_cash_reg(const cash_reg_t* mkt)
{
    int count = 0;

    for (int i = 0; i < MKT_CASH_REG_COUNT; i++) {
        if (mkt[i].is_available) count++;
    }

    return count;
}

bool mkt_any_cash_reg_open(const cash_reg_t* mkt)
{
    for (int i = 0; i < MKT_CASH_REG_COUNT; i++) {
        if (mkt[i].is_available == true) return true;
    }

    return false;
}

void mkt_new_customer(cash_reg_t* mkt)
{
    customer_t customer;

    const int id = mkt_scanf_id("Digite o número do caixa");
    const int idx = id - 1;

    if (mkt[idx].is_available == false) {
        printf("O caixa de número %d está fechado!\n", id);
        return;
    }

    printf("Digite o nome do cliente: ");
    read_line(customer.name, CUSTOMER_NAME_SIZE);

    // printf("Digite o CPF do cliente: ");
    // scanf("%d%*c", &customer.cpf);

    // printf("Digite a prioridade do cliente (1 alta | 2 média | 3 baixa): ");
    // scanf("%u%*c", &customer.priority);

    // printf("Digite a quantidade de itens na compra do cliente: ");
    // scanf("%d%*c", &customer.items_qty);

    queue_set(&mkt[idx].queue, &customer);
}

void mkt_serve_customer(cash_reg_t* mkt)
{
    customer_t customer;

    const int id = mkt_scanf_id("Digite o número do caixa a ter cliente atendido");
    const int idx = id - 1;

    if (mkt[idx].is_available == false) {
        printf("O caixa de número %d está fechado!\n", id);
        return;
    } else if (queue_empty(&mkt[idx].queue)) {
        printf("O caixa de número %d está vazio!\n", id);
        return;
    }

    customer = queue_pop(&mkt[idx].queue);
    printf("O cliente de nome %s foi atendido no caixa de número %d\n", customer.name, id);
}

void mkt_toggle_cash_reg(cash_reg_t* mkt)
{
    const int id = mkt_scanf_id("Selecione o número do caixa a ser aberto/fechado");
    const int idx = id - 1;

    printf("%s caixa número %d\n", mkt[idx].is_available ? "Fechando" : "Abrindo", mkt[idx].id);

    // Realocar clientes se estiver fechando o caixa
    if (mkt[idx].is_available == true && mkt[idx].queue.len > 0) {
        // Se este for o único caixa aberto e ainda tem clientes, não tem como fechá-lo
        if (mkt_count_open_cash_reg(mkt) == 1) {
            printf("Não há como realocar clientes, pois os outros caixas estão fechados\n");
            return;
        }
        mkt_reallocate_customers(mkt, &mkt[idx]);
    }

    // Fechar ou abrir caixa
    mkt[idx].is_available = !mkt[idx].is_available;
}

void mkt_print_cash_regs(const cash_reg_t* mkt)
{
    for (int i = 0; i < MKT_CASH_REG_COUNT; i++) {
        const queue_t* queue = &mkt[i].queue;

        printf("Caixa número %d\n", mkt[i].id);

        if (queue_empty(queue)) {
            printf("\tA fila está vazia\n\n");
            continue;
        }

        for (node_t* it = queue->first; it != NULL; it = it->next) {
            const customer_t* c = &it->customer;
            const char* priority =
                c->priority == 1 ? "alta" :
                c->priority == 2 ? "média" :
                c->priority == 3 ? "baixa" :
                "indefinido";

            printf("\tNome: %s\n", c->name);
            printf("\tCPF: %d\n", c->cpf);
            printf("\tPrioridade: %s\n", priority);
            printf("\tQuantidade de itens: %d\n", c->items_qty);
            printf("\n");
        }
    }
}

void mkt_cash_regs_status(const cash_reg_t* mkt)
{
    for (int i = 0; i < MKT_CASH_REG_COUNT; i++) {
        printf("O caixa número %d está %s e tem %d clientes\n",
               mkt[i].id,
               mkt[i].is_available ? "aberto" : "fechado",
               mkt[i].queue.len);
    }
}
