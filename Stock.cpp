//
// Created by USUARIO on 10/11/2025.
//

#include "Stock.h"


void Stock::decrementa(int n) {
    num_stock-=n;
}

void Stock::incrementa(int n) {
    num_stock+=n;
}

int Stock::getIdPaMed() const {
    return id_PaMed;
}

void Stock::setIdPaMed(int idPaMed) {
    id_PaMed = idPaMed;
}

unsigned int Stock::getNumStock() const {
    return num_stock;
}

void Stock::setNumStock(unsigned int numStock) {
    num_stock = numStock;
}

Stock::Stock():id_PaMed(0),num_stock(0),number(nullptr) {}

Stock::~Stock() {

}

Stock::Stock(int idPaMed, unsigned int numStock, PA_Medicamento *number) : id_PaMed(idPaMed), num_stock(numStock),
                                                                           number(number) {}
Stock::Stock(const Stock &_unaCopia):id_PaMed(_unaCopia.id_PaMed), num_stock(_unaCopia.num_stock), number(_unaCopia.number) {}

bool Stock::operator<(const Stock &rhs) const {
    return id_PaMed < rhs.id_PaMed;
}

bool Stock::operator>(const Stock &rhs) const {
    return rhs < *this;
}

bool Stock::operator<=(const Stock &rhs) const {
    return !(rhs < *this);
}

bool Stock::operator>=(const Stock &rhs) const {
    return !(*this < rhs);
}

PA_Medicamento *Stock::getNumber() const {
    return number;
}

void Stock::setNumber(PA_Medicamento *number) {
    Stock::number = number;
}
