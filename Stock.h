//
// Created by USUARIO on 10/11/2025.
//

#ifndef P4_STOCK_H
#define P4_STOCK_H

#include "PA_Medicamento.h"

class Stock {
private:
    int id_PaMed; ///< Debe de coincidir siempre con el _idNumero de PA_Medicamento
    unsigned int num_stock; ///< Numero de medicamentos que hay en la farmacia
    PA_Medicamento* number;

public:
    Stock();
    Stock(int idPaMed, unsigned int numStock, PA_Medicamento *number);
    Stock(const Stock &_unaCopia);

    PA_Medicamento *getNumber() const;

    void setNumber(PA_Medicamento *number);

    virtual ~Stock();

    void decrementa(int n);
    void incrementa(int n);

    int getIdPaMed() const;
    void setIdPaMed(int idPaMed);
    unsigned int getNumStock() const;
    void setNumStock(unsigned int numStock);

    bool operator<(const Stock &rhs) const;
    bool operator>(const Stock &rhs) const;
    bool operator<=(const Stock &rhs) const;
    bool operator>=(const Stock &rhs) const;
};


#endif //P4_STOCK_H
