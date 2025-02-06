#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "market.h"

typedef enum {
    OPT_EXIT = 0,
    OPT_NEW_CUSTOMER = 1,
    OPT_SERVE_CUSTOMER = 2,
    OPT_OPEN_TILL = 3,
    OPT_CLOSE_TILL = 4,
    OPT_PRINT_TILLS = 5,
    // OPT_TILLS_STATUS = 6,
} option_t;

const char* DASHED_LINE = "========================================\n";

int main() {
    till_t tills[TILL_COUNT];
    option_t opt;

    till_init(tills);

    do {
        printf("MENU\n"
               "1) Cadastrar cliente\n"
               "2) Atender um cliente\n"
               "3) Abrir caixa\n"
               "4) Fechar caixa\n"
               "5) Imprimir os caixas\n"
               // "5) Imprimir a lista de clientes em espera\n"
               // "6) Imprimir o status dos caixas\n"
               "0) Sair do programa\n"
               "Digite um comando: ");
        scanf("%u%*c", &opt);
        printf("%s", DASHED_LINE);

        switch (opt) {
            case OPT_NEW_CUSTOMER:
                mkt_new_customer(tills);
                break;

            case OPT_SERVE_CUSTOMER:
                mkt_serve_customer(tills);
                break;

            case OPT_OPEN_TILL:
                mkt_open_till(tills);
                break;

            case OPT_CLOSE_TILL:
                mkt_close_till(tills);
                break;

            case OPT_PRINT_TILLS:
                mkt_print_tills(tills);
                break;

            // case OPT_TILLS_STATUS:
            //     for (int i = 0; i < TILL_COUNT; i++) {
            //         printf("O caixa número %d está %s e tem %d clientes\n",
            //                tills[i].id,
            //                tills[i].is_available ? "aberto" : "fechado",
            //                tills[i].queue.len);
            //     }
            //     break;

            case OPT_EXIT:
                printf("Saindo...\n");
                break;

            default:
                printf("Comando não definido!\n");
                break;
        }

        printf("%s", DASHED_LINE);

        if (till_any_open(tills) == false) {
            printf("Nenhum caixa aberto. Fechando mercado\n");
            break;
        }

    } while (opt != OPT_EXIT);

    till_deinit(tills);

    return 0;
}
