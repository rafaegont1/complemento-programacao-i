#include <stdio.h>
#include <stdbool.h>
#include "market.h"

typedef enum {
    OPT_EXIT = 0,
    OPT_NEW_CUSTOMER = 1,
    OPT_SERVE_CUSTOMER = 2,
    OPT_TOGGLE_CASH_REG = 3,
    OPT_PRINT_CASH_REGS = 4,
    OPT_CASH_REGS_STATUS = 5,
} option_t;

static const char* DASHED_LINE = "========================================\n";

int main()
{
    cash_reg_t mkt[MKT_CASH_REG_COUNT];
    option_t opt;

    mkt_init(mkt);

    do {
        printf("MENU\n"
               "1) Cadastrar cliente\n"
               "2) Atender um cliente\n"
               "3) Abrir ou fechar um caixa\n"
               "4) Imprimir a lista de clientes em espera\n"
               "5) Imprimir o status dos caixas\n"
               "0) Sair do programa\n"
               "Digite um comando: ");
        scanf("%u%*c", &opt);
        printf("%s", DASHED_LINE);

        switch (opt) {
            case OPT_NEW_CUSTOMER:
                mkt_new_customer(mkt);
                break;

            case OPT_SERVE_CUSTOMER:
                mkt_serve_customer(mkt);
                break;

            case OPT_TOGGLE_CASH_REG:
                mkt_toggle_cash_reg(mkt);
                break;

            case OPT_PRINT_CASH_REGS:
                mkt_print_cash_regs(mkt);
                break;

            case OPT_CASH_REGS_STATUS:
                mkt_cash_regs_status(mkt);
                break;

            case OPT_EXIT:
                printf("Saindo...\n");
                break;

            default:
                printf("Comando não definido!\n");
                break;
        }

        printf("%s", DASHED_LINE);

        if (mkt_any_cash_reg_open(mkt) == false) {
            printf("Nenhum caixa aberto; Fechando mercado\n");
            break;
        }

    } while (opt != OPT_EXIT);

    mkt_deinit(mkt);

    return 0;
}
