#ifndef MARKET_H
#define MARKET_H

#include "cash_reg.h"

#define MKT_CASH_REG_COUNT 5

void mkt_init(cash_reg_t* mkt);
void mkt_deinit(cash_reg_t* mkt);
int mkt_count_open_cash_reg(const cash_reg_t* mkt);
bool mkt_any_cash_reg_open(const cash_reg_t* mkt);
void mkt_new_customer(cash_reg_t* mkt);
void mkt_serve_customer(cash_reg_t* mkt);
void mkt_toggle_cash_reg(cash_reg_t* mkt);
void mkt_print_cash_regs(const cash_reg_t* mkt);
void mkt_cash_regs_status(const cash_reg_t* mkt);

#endif // MARKET_H
