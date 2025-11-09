//
// Created by Pablo Montoro on 26/10/2025.
//

#ifndef P3_FARMACIA_H
#define P3_FARMACIA_H
#include <iostream>
#include <stdexcept>
#include <string>
#include "PA_Medicamento.h"
#include "ListaSimplementeEnlazada.h"
class MediExpress;
class Farmacia {
public:
    Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
             const std::string &nombre, const std::string &direccion, const std::string &codPostal,
             MediExpress *linkMed);

private:
    std::string _Cif,_Provincia,_Localidad,_Nombre,_Direccion,_CodPostal;
    ListaSimplementeEnlazada<PA_Medicamento*> dispense;
    MediExpress *linkMed;


public:

    const std::string &getCodPostal() const;

    Farmacia();
    void pedidoMedicam(int _id_Num);


    const std::string &getCif() const;
    void dispensaMed(PA_Medicamento *pa);

    void setCif(const std::string &cif);
    PA_Medicamento* buscaMedicam(int _id_num);


    const std::string &getProvincia() const;
    ListaSimplementeEnlazada<Laboratorio*> buscarMedicam(const std::string &nombreMedicam);


    void setProvincia(const std::string &provincia);
    bool operator<(const Farmacia &rhs) const;

    const std::string &getLocalidad() const;
    bool operator>(const Farmacia &rhs) const;

    void setLocalidad(const std::string &localidad);
    bool operator<=(const Farmacia &rhs) const;

    const std::string &getNombre() const;
    bool operator>=(const Farmacia &rhs) const;


    void setNombre(const std::string &nombre);
    void setLinkMed(MediExpress *linkMed);

    const std::string &getDireccion() const;
    MediExpress *getLinkMed() const;



    void setCodPostal(const std::string &codPostal);
    void setDireccion(const std::string &direccion);


};


#endif //P3_FARMACIA_H
