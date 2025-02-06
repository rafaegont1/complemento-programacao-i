#ifndef MARKET_H
#define MARKET_H

#include "till.h"

void mkt_new_customer(till_p tills);
void mkt_serve_customer(till_p tills);
void mkt_open_till(till_p tills);
void mkt_close_till(till_p tills);
// void mkt_open_close_till(till_p tills);
void mkt_print_tills(till_p tills);

#endif // MARKET_H
