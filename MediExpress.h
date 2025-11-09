//
// Created by Lazaro Ruiz on 08/10/2025.
//

#ifndef P2_MEDIEXPRESS_H
#define P2_MEDIEXPRESS_H

#include "VectorDinamico.h"
#include "ListaSimplementeEnlazada.h"
#include "PA_Medicamento.h"
#include "Laboratorio.h"
#include "Farmacia.h"
#include "ArbolAVL.h"

class MediExpress {
private:
    VectorDinamico<PA_Medicamento> _medicamentos;
    ListaSimplementeEnlazada<Laboratorio> _labs;
    ArbolAVL<Farmacia> _pharmacy;

public:
    VectorDinamico<Laboratorio*> buscarLabs(const std::string &nombrePa);

    void _cargarMedicamentosDesdeFichero(const std::string& _ficheroMedicamentos);
    void asignarParesYVerificar();

    void _cargarFarmaciasDesdeFichero(const std::string& _ficheroFarmacias);
    MediExpress(const std::string &_ficheroMedicamentos, const std::string &_ficheroLaboratorios, const std::string &_ficheroFarmacias);


    VectorDinamico<PA_Medicamento*> getMedicamentosSinLab();
    Laboratorio* buscarLab(const std::string &nombreLab);

    void eliminarLaboratorio(const std::string& localidad, int& contador);
    void suministrarMed(PA_Medicamento *pa, Laboratorio *l);

    VectorDinamico<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    Farmacia* buscarFarmacia(const std::string &cif);




    void suministrarFarmacia(Farmacia *f, int id_num);
    PA_Medicamento* buscarCompuesto(int id_num);


    void asignarLabsMadridAMedicamentosSinAsignar();
    void _cargarLaboratoriosDesdeFichero(const std::string& _ficheroLaboratorios);

    };


#endif //P2_MEDIEXPRESS_H
