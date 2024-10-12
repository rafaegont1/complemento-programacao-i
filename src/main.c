#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "malloc_dbg.h"
#include "till.h"

static int read_line(char *str);
static void new_customer(till_p tills);
static void serve_customer(till_p tills);
static void open_close_till(till_p tills);
static void print_customers(till_p tills);

int main() {
    till_t tills[TILL_COUNT];
    char op;

    till_init(tills);

    do {
        printf("MENU\n"
               "1) Cadastrar cliente\n"
               "2) Atender um cliente\n"
               "3) Abrir ou fechar caixa\n"
               "4) Imprimir a lista de clientes em espera\n"
               "5) Imprimir o status dos caixas\n"
               "Digite um comando: ");
        scanf("%c%*c", &op);

        switch (op) {
            case '1': // -- Cadastrar cliente --
                // Solicitar nome, CPF, prioridade, e número de itens no
                // carrinho. Adicionar o cliente à fila de acordo com a sua
                // prioridade e o caixa escolhido.
                new_customer(tills);
                break;

            case '2': // -- Atender um cliente --
                // Remover o cliente da fila com maior prioridade para ser
                // atendido no caixa especificado.
                serve_customer(tills);
                break;

            case '3': // -- Abrir ou fechar caixa --
                // Permitir ao usuário abrir ou fechar um dos 5 caixas
                // disponíveis. Se o caixa estiver fechado, os clientes na fila
                // desse caixa devem ser realocados para outro caixa aberto.
                open_close_till(tills);
                break;

            case '4': // -- Imprimir a lista de clientes em espera --
                // Exibir os dados dos clientes em espera em cada caixa,
                // organizados por prioridade.
                print_customers(tills);
                break;

            case '5': // -- Imprimir o status dos caixas --
                // Exibir o estado (aberto ou fechado) de cada caixa e o número
                // de clientes em espera.
                for (int i = 0; i < TILL_COUNT; i++) {
                    printf("O caixa número %d está %s e tem %d clientes\n",
                           tills[i].id,
                           tills[i].available ? "aberto" : "fechado",
                           tills[i].queue.len);
                }
                break;

            case '0': // Ao digitar 0, o programa deve terminar.
                printf("Saindo...\n");
                break;

            default:
                printf("Comando não definido!\n");
                break;
        }

    } while (op != '0');

    till_deinit(tills);

    return 0;
}

int read_line(char *str) {
    char tmp[256];

    if (fgets(tmp, sizeof(tmp), stdin) == NULL) {
        fprintf(stderr, "fgets() falhou\n");
        str[0] = '\0';
        return 1;
    }

    tmp[strcspn(tmp, "\n")] = '\0';

    return 0;
}

static void new_customer(till_p tills) {
    int till_id;
    customer_t new_customer;
    till_p till;

    do {
        printf("Digite o número do caixa (1 a %d): ", TILL_COUNT);
    } while (scanf("%d%*c", &till_id) != 1 &&
             (till_id < 0 || till_id > TILL_COUNT));

    till = till_find(tills, till_id);
    if (till->available == false) {
        printf("O caixa de número %d está fechado!\n", till_id);
        return;
    }

    printf("Digite o nome do cliente: ");
    read_line(new_customer.name);

    printf("Digite o CPF do cliente: ");
    scanf("%d%*c", &new_customer.cpf);

    printf("Digite a prioridade do cliente (1 alta | 2 média | 3 baixa): ");
    scanf("%d%*c", &new_customer.priority);

    printf("Digite a quantidade de itens na compra do cliente: ");
    scanf("%d%*c", &new_customer.items_qty);

    queue_set(&till->queue, &new_customer);
}

static void serve_customer(till_p tills) {
    int till_id;
    till_p till;
    customer_t customer;

    printf("Digite o número do caixa a ter cliente atendido: ");
    scanf("%d%*c", &till_id);

    till = till_find(tills, till_id);
    if (till->available == false) {
        printf("O caixa de número %d está fechado!\n", till_id);
        return;
    } else if (queue_empty(&till->queue)) {
        printf("O caixa de número %d está vazio!\n", till_id);
        return;
    }

    customer = queue_pop(&till->queue);
    printf("O cliente de nome %s foi antendido no caixa de número %d",
           customer.name, till_id);
}

static void open_close_till(till_p tills) {
    int till_id;
    till_p till;
    char op;

    do {
        printf("Selecione o número do caixa a ser aberto/fechado: ");
    } while (scanf("%d%*c", &till_id) != 1 &&
             (till_id < 0 || till_id > TILL_COUNT));

    till = till_find(tills, till_id);

    do {
        if (till->available == true) {
            printf("O caixa está aberto. quer fechá-lo? (s ou n): ");
        } else {
            printf("O caixa está fechado. quer abri-lo? (s ou n): ");
        }
    } while (scanf("%c%*c", &op) != 1 &&
             op != 's' && op != 'n' && op != 'S' && op != 'N');

    if (op == 's' || op == 'S') {
        till->available = !till->available;
    }

    // TODO: passar todos os clientes do caixa fechado para algum caixa aberto
}

static void print_customers(till_p tills) {
    for (int i = 0; i < TILL_COUNT; i++) {
        queue_p q = &tills[i].queue;

        printf("Caixa número %d\n", tills[i].id);

        if (queue_empty(q)) {
            printf("A fila está vazia!\n");
            continue;
        }

        for (node_p it = q->first; it != NULL; it = it->next) {
            customer_p c = &it->customer;
            const char *priority = c->priority == 1 ? "alta" :
                                   c->priority == 2 ? "média" :
                                   c->priority == 3 ? "baixa" :
                                   "undefined";

            printf("\tNome: %s\n"
                   "\tCPF: %d\n"
                   "\tPrioridade: %s\n"
                   "\tQuantidade de itens: %d\n",
                   c->name, c->cpf, priority, c->items_qty);
        }
    }
}
