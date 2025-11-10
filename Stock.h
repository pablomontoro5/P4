//
// Created by USUARIO on 10/11/2025.
//

#ifndef P4_STOCK_H
#define P4_STOCK_H

#include "PA_Medicamento.h"

class Stock {
private:
    int id_PaMed;
    int num_stock;
    PA_Medicamento* number;

public:
    int decrementa(int n);
    int incrementa(int n);
};


#endif //P4_STOCK_H
