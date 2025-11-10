//
// Created by Pablo Montoro on 26/10/2025.
//

#ifndef P3_FARMACIA_H
#define P3_FARMACIA_H
#include <iostream>
#include <stdexcept>
#include <string>
#include <set>
#include <list>
#include <vector>

#include "PA_Medicamento.h"
#include "Stock.h"
class MediExpress;
class Farmacia {
public:
    Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
             const std::string &nombre, const std::string &direccion, const std::string &codPostal,
             MediExpress *linkMed);

private:
    std::string _Cif,_Provincia,_Localidad,_Nombre,_Direccion,_CodPostal;
    std::set<Stock> _order;
    MediExpress *linkMed;

    int buscaMedicamID(int _id_num);


public:

    const std::string &getCodPostal() const;

    Farmacia();
    void pedidoMedicam(int _id_Num);


    const std::string &getCif() const;
    void dispensaMed(PA_Medicamento *pa);

    void setCif(const std::string &cif);


    const std::string &getProvincia() const;
    std::vector<PA_Medicamento*> buscarMedicamNombre(const std::string &nombreMedicam);


    void setProvincia(const std::string &provincia);

    const std::string &getLocalidad() const;

    void setLocalidad(const std::string &localidad);

    const std::string &getNombre() const;


    void setNombre(const std::string &nombre);
    void setLinkMed(MediExpress *linkMed);

    const std::string &getDireccion() const;
    MediExpress *getLinkMed() const;



    void setCodPostal(const std::string &codPostal);
    void setDireccion(const std::string &direccion);

    int comparMedicam(int _idNum, int numAComprar, PA_Medicamento &result);
};


#endif //P3_FARMACIA_H
