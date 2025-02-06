#include "market.h"

#include <stdio.h>
#include "till.h"
#include "util.h"

void mkt_new_customer(till_p tills) {
    int id; // till id
    customer_t new_customer;
    till_p till;

    do {
        printf("Digite o número do caixa (1 a %d): ", TILL_COUNT);
    } while ((scanf("%d%*c", &id) != 1) &&
             (id < 1 || id > TILL_COUNT));

    till = till_find(tills, id);
    if (till->is_available == false) {
        printf("O caixa de número %d está fechado!\n", id);
        return;
    }

    printf("Digite o nome do cliente: ");
    read_line(new_customer.name);

    // printf("Digite o CPF do cliente: ");
    // scanf("%d%*c", &new_customer.cpf);

    // printf("Digite a prioridade do cliente (1 alta | 2 média | 3 baixa): ");
    // scanf("%u%*c", &new_customer.priority);

    // printf("Digite a quantidade de itens na compra do cliente: ");
    // scanf("%d%*c", &new_customer.items_qty);

    queue_set(&till->queue, &new_customer);
}

void mkt_serve_customer(till_p tills) {
    till_p till;
    customer_t customer;
    int id; // till id

    printf("Digite o número do caixa a ter cliente atendido: ");
    scanf("%d%*c", &id);

    till = till_find(tills, id);

    if (till->is_available == false) {
        printf("O caixa de número %d está fechado!\n", id);
        return;
    } else if (queue_empty(&till->queue)) {
        printf("O caixa de número %d está vazio!\n", id);
        return;
    }

    customer = queue_pop(&till->queue);
    printf("O cliente de nome %s foi antendido no caixa de número %d",
           customer.name, id);
}

static inline bool mkt_invalid_till_id(int id) {
    return (id < 1) || (id > TILL_COUNT);
}

void mkt_open_till(till_p tills) {
    till_p till;
    int id; // till id

    if (till_count_open(tills) == TILL_COUNT) {
        printf("Todos os caixas já estão abertos!\n");
        return;
    }

    do {
        printf("Selecione o número do caixa a ser aberto (digite 0 para voltar): ");
    } while ((scanf("%d%*c", &id) != 1) && mkt_invalid_till_id(id));

    if (id == 0) {
        printf("Retornando...\n");
        return;
    }

    till = till_find(tills, id);

    if (till->is_available == true) {
        printf("O caixa de ID %d já está aberto\n", till->id);
        return;
    }

    printf("Abrindo caixa número %d\n", till->id);
    till->is_available = true;
}

static void mkt_reallocate_customers(till_p tills, queue_p src) {
    while (src->len > 0) {
        int id = -1;
        queue_p dst = NULL;

        for (int i = 0; i < TILL_COUNT; i++) {
            queue_p iter = &tills[i].queue;
            if (iter == src) {
                continue;
            } else if (dst == NULL || iter->len < dst->len) {
                dst = iter;
                id = i + 1;
            }
        }

        customer_t customer = queue_pop(src);
        queue_set(dst, &customer);
        printf("Cliente %s realocado para o caixa de ID %d\n", customer.name, id);
    }
}

void mkt_close_till(till_p tills) {
    till_p till;
    int id; // till id

    do {
        printf("Selecione o número do caixa a ser fechado (digite 0 para voltar): ");
    } while ((scanf("%d%*c", &id) != 1) && mkt_invalid_till_id(id));

    if (id == 0) {
        printf("Retornando...\n");
        return;
    }

    till = till_find(tills, id);

    if (till->is_available == false) {
        printf("O caixa de ID %d já está fechado\n", till->id);
        return;
    }

    printf("Fechando o caixa número %d\n", till->id);
    till->is_available = false;
    mkt_reallocate_customers(tills, &till->queue);
}

void mkt_print_tills(till_p tills) {
    for (int i = 0; i < TILL_COUNT; i++) {
        queue_p q = &tills[i].queue;

        printf("Caixa número %d\n", tills[i].id);
        printf("%s\n", tills[i].is_available ? "ABERTO" : "FECHADO");

        for (node_p it = q->first; it != NULL; it = it->next) {
            customer_p c = &it->customer;
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
