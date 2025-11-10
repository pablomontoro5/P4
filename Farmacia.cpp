//
// Created by Pablo Montoro on 26/10/2025.
//

#include "Farmacia.h"
#include "MediExpress.h"
#include "Stock.h"

/**
 * @brief Busca medicamentos por nombre (parcialmente) dentro de la farmacia y devuelve sus laboratorios.
 * @param nombreMedicam Subcadena a buscar dentro del nombre del medicamento.
 * @return Lista simplemente enlazada con punteros a laboratorios que suministran los medicamentos encontrados.
 * @note La búsqueda es sensible a mayúsculas/minúsculas y devuelve duplicados si se repiten laboratorios.
 */
ListaSimplementeEnlazada<Laboratorio *> Farmacia::buscarMedicamNombre(const std::string &nombreMedicam) {
    ListaSimplementeEnlazada<Laboratorio*> toRet;
    ListaSimplementeEnlazada<PA_Medicamento*>::Iterador<PA_Medicamento*> it = dispense._elIterador();
    while(!it._esFinal()){
        if(it._verDato()->getNombre().find(nombreMedicam)!=std::string::npos){
            toRet._insertarPorElFinal(it._verDato()->servidoPor());
        }
        it._esSiguiente();
    }
    return toRet;
}

/**
 * @brief Obtiene el código CIF de la farmacia.
 * @return Referencia constante al CIF.
 */
const std::string &Farmacia::getCif() const {
    return _Cif;
}
/**
 * @brief Establece el código CIF de la farmacia.
 * @param cif Nuevo código CIF.
 */
void Farmacia::setCif(const std::string &cif) {
    _Cif = cif;
}
/**
 * @brief Operador menor que, compara farmacias por su CIF.
 * @param rhs Farmacia con la que se compara.
 * @return true si el CIF de esta farmacia es menor que el de rhs.
 */
bool Farmacia::operator<(const Farmacia &rhs) const {
    return _Cif < rhs._Cif;
}
/**
 * @brief Obtiene la provincia donde se encuentra la farmacia.
 * @return Referencia constante a la provincia.
 */
const std::string &Farmacia::getProvincia() const {
    return _Provincia;
}
/**
 * @brief Establece la provincia de la farmacia.
 * @param provincia Nueva provincia.
 */
void Farmacia::setProvincia(const std::string &provincia) {
    _Provincia = provincia;
}
/**
 * @brief Operador menor o igual que, compara farmacias por su CIF.
 * @param rhs Farmacia con la que se compara.
 * @return true si el CIF de esta farmacia es menor o igual que el de rhs.
 */
bool Farmacia::operator<=(const Farmacia &rhs) const {
    return !(rhs < *this);
}
/**
 * @brief Obtiene la localidad de la farmacia.
 * @return Referencia constante a la localidad.
 */
const std::string &Farmacia::getLocalidad() const {
    return _Localidad;
}
/**
 * @brief Establece la localidad de la farmacia.
 * @param localidad Nueva localidad.
 */
void Farmacia::setLocalidad(const std::string &localidad) {
    _Localidad = localidad;
}
/**
 * @brief Obtiene el nombre de la farmacia.
 * @return Referencia constante al nombre.
 */
const std::string &Farmacia::getNombre() const {
    return _Nombre;
}
/**
 * @brief Operador mayor que, compara farmacias por su CIF.
 * @param rhs Farmacia con la que se compara.
 * @return true si el CIF de esta farmacia es mayor que el de rhs.
 */
bool Farmacia::operator>(const Farmacia &rhs) const {
    return rhs < *this;
}
/**
 * @brief Establece el nombre de la farmacia.
 * @param nombre Nuevo nombre.
 */
void Farmacia::setNombre(const std::string &nombre) {
    _Nombre = nombre;
}
/**
 * @brief Obtiene la dirección de la farmacia.
 * @return Referencia constante a la dirección.
 */
const std::string &Farmacia::getDireccion() const {
    return _Direccion;
}
/**
 * @brief Establece la dirección de la farmacia.
 * @param direccion Nueva dirección.
 */
void Farmacia::setDireccion(const std::string &direccion) {
    _Direccion = direccion;
}
/*
* @brief Obtiene el código postal de la farmacia.
* @return Referencia constante al código postal.
*/
const std::string &Farmacia::getCodPostal() const {
    return _CodPostal;
}
/**
 * @brief Establece el código postal de la farmacia.
 * @param codPostal Nuevo código postal.
 */
void Farmacia::setCodPostal(const std::string &codPostal) {
    _CodPostal = codPostal;
}
/**
 * @brief Obtiene el puntero al objeto MediExpress asociado a la farmacia.
 * @return Puntero al objeto MediExpress.
 */
MediExpress *Farmacia::getLinkMed() const {
    return linkMed;
}
/**
 * @brief Establece el puntero al objeto MediExpress asociado a la farmacia.
 * @param linkMed Nuevo puntero a MediExpress.
 */
void Farmacia::setLinkMed(MediExpress *linkMed) {
    Farmacia::linkMed = linkMed;
}
/**
 * @brief Constructor parametrizado de la clase Farmacia.
 * @param cif Código CIF de la farmacia.
 * @param provincia Provincia donde se ubica la farmacia.
 * @param localidad Localidad de la farmacia.
 * @param nombre Nombre comercial de la farmacia.
 * @param direccion Dirección física de la farmacia.
 * @param codPostal Código postal de la farmacia.
 * @param linkMed Puntero al objeto MediExpress asociado.
 */
Farmacia::Farmacia(const std::string &cif, const std::string &provincia, const std::string &localidad,
                   const std::string &nombre, const std::string &direccion, const std::string &codPostal,
                   MediExpress *linkMed) : _Cif(cif), _Provincia(provincia), _Localidad(localidad), _Nombre(nombre),
                                           _Direccion(direccion), _CodPostal(codPostal), linkMed(linkMed),_order() {

}



/**
 * @brief Operador mayor o igual que, compara farmacias por su CIF.
 * @param rhs Farmacia con la que se compara.
 * @return true si el CIF de esta farmacia es mayor o igual que el de rhs.
 */
bool Farmacia::operator>=(const Farmacia &rhs) const {
    return !(*this < rhs);
}
/**
* @brief Busca un medicamento en la farmacia por su identificador numérico.
* @param _id_num Identificador numérico del medicamento.
* @return Puntero al medicamento encontrado o nullptr si no está en la farmacia.
*/
int Farmacia::buscaMedicamID(int _id_num) {
    Stock auxiliar;
    auxiliar.setIdPaMed(_id_num);
    std::set<Stock>::iterator i = _order.find(auxiliar);
    if(i != _order.end()){
        return i->getNumStock();
    }
    return 0;
}
/**
 * @brief Solicita un medicamento al sistema MediExpress.
 * @param _id_Num Identificador numérico del medicamento solicitado.
 * @pre La farmacia debe tener un puntero válido a MediExpress.
 */
void Farmacia::pedidoMedicam(int _id_Num) {
    if(linkMed){
        linkMed->suministrarFarmacia(this,_id_Num);
    }
}
/**
 * @brief Añade un medicamento al inventario (lista de dispensación) de la farmacia.
 * @param pa Puntero al medicamento a insertar.
 */
void Farmacia::dispensaMed(PA_Medicamento *pa) {
    dispense._insertarPorElFinal(pa);
}


/**
 * @brief Constructor por defecto de la clase Farmacia.
 * Inicializa todos los campos con valores por defecto ("---") y punteros a nullptr.
 */
Farmacia::Farmacia() :_Cif("---"),_Provincia("---"),_Localidad("---"),_Nombre("---"),_Direccion("---"),_CodPostal("---"),linkMed(
        nullptr),_order()
{

}

int Farmacia::comparMedicam(int _idNum, int numAComprar, PA_Medicamento &result) {
    Stock auxiliar;
    auxiliar.setIdPaMed(_idNum);
    std::set<Stock>::iterator iterador = _order.find(auxiliar);
    if(buscaMedicamID(_idNum) >= numAComprar){

    }
}