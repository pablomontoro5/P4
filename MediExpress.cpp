//
// Created by Lazaro Ruiz on 08/10/2025.
//

#include "MediExpress.h"

#include <fstream>
#include <sstream>
/**
 * @brief Asigna medicamentos a laboratorios por pares y muestra las asignaciones realizadas.
 * @post Cada laboratorio recibe dos medicamentos consecutivos; se muestran por consola los resultados.
 */
void MediExpress::asignarParesYVerificar() {
    ListaSimplementeEnlazada<Laboratorio>::Iterador<Laboratorio> it4=_labs._elIterador();

    int i = 0;
    while (i < _medicamentos._getTamanio() && !it4._esFinal()) {
        suministrarMed(&_medicamentos[i], &it4._verDato());
        suministrarMed(&_medicamentos[i + 1], &it4._verDato());
        i += 2;
        it4._esSiguiente();
    }

    int _contadorAuxiliar=0;

    int i2=0;
    while(i2 < _medicamentos._getTamanio()){
        if (_medicamentos[i].servidoPor()) {
            std::cout << "*** Id del principio activo del medicamento : *** " << _medicamentos[i].getIdNum() <<
                      " *** Id del laboratorio : *** " << _medicamentos[i].servidoPor()->getId() << std::endl;
        }else{
            ++_contadorAuxiliar;
        }
        ++i2;
    }

    std::cout << " *** Este es el numero de medicamentos que no se han asignado : *** " << _contadorAuxiliar << std:: endl;
}
/**
 * @brief Busca los laboratorios que suministran medicamentos cuyo nombre contenga una subcadena dada.
 * @param nombrePa Subcadena a buscar dentro del nombre del medicamento.
 * @return Vector dinámico con punteros a laboratorios (puede contener duplicados o punteros nulos).
 */
VectorDinamico<Laboratorio *> MediExpress::buscarLabs(const std::string &nombrePa) {
    VectorDinamico<Laboratorio*> toRet;
    int i=0;
    while(i < _medicamentos._getTamanio()) {
        if (_medicamentos[i].getNombre().find(nombrePa) != std::string::npos) {
            toRet.inserta(_medicamentos[i].servidoPor());
        }
        ++i;
    }
    return toRet;
}

/**
 * @brief Carga las farmacias desde un fichero CSV y las inserta en el árbol AVL.
 * @param _ficheroFarmacias Ruta del fichero CSV/semicolon con farmacias.
 * @post El árbol AVL de farmacias queda poblado con las farmacias leídas del fichero.
 */

void MediExpress::_cargarFarmaciasDesdeFichero(const std::string &_ficheroFarmacias) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;
    std::string nuevoCif = "";
    std::string nuevaProvincia = "";
    std::string nuevaLocalidad = "";
    std::string nuevoNombre = "";
    std::string nuevaDireccion = "";
    std::string nuevoCodigoPostal = "";
    is.open(_ficheroFarmacias);
    if(is.good()){
        while(getline(is,fila)){
            if(fila!= ""){
                columnas.str(fila);
                getline(columnas,nuevoCif,';');
                getline(columnas,nuevaProvincia,';');
                getline(columnas,nuevaLocalidad,';');
                getline(columnas,nuevoNombre,';');
                getline(columnas,nuevaDireccion,';');
                getline(columnas,nuevoCodigoPostal,'\r');
                fila = "";
                columnas.clear();
                Farmacia datoFarmaceutico(nuevoCif,nuevaProvincia,nuevaLocalidad,nuevoNombre,nuevaDireccion,nuevoCodigoPostal,this);
                _pharmacy.inserta(datoFarmaceutico);
            }
        }
        is.close();
    }else{
        std::cout << " *** Error de apertura del fichero de farmacias ***" << std::endl;
    }

}
/**
 * @brief Obtiene todos los medicamentos que actualmente no están servidos por ningún laboratorio.
 * @return Vector dinámico con punteros a medicamentos sin laboratorio (posiblemente vacío).
 */
VectorDinamico<PA_Medicamento *> MediExpress::getMedicamentosSinLab() {
    VectorDinamico<PA_Medicamento*> toRet;
    int i=0;
    while(i < _medicamentos._getTamanio()){
        if(_medicamentos[i].servidoPor() == nullptr){
            toRet.inserta(&_medicamentos[i]);
        }
        ++i;
    }

    return toRet;
}

/**
 * @brief Asigna laboratorios de Madrid a los medicamentos que no tienen laboratorio asignado.
 * @post Cada medicamento sin laboratorio pasa a estar servido por un laboratorio de Madrid (si hay suficientes).
 * @note La asignación se realiza por orden de aparición en las listas internas.
 */
void MediExpress::asignarLabsMadridAMedicamentosSinAsignar() {
    VectorDinamico<Laboratorio*> _Madrid = buscarLabCiudad("Madrid");
    VectorDinamico<PA_Medicamento*> sin = getMedicamentosSinLab();
    int i=0;
    while(i < _Madrid._getTamanio() && i < sin._getTamanio()){
        suministrarMed(sin[i], _Madrid[i]);
        if(sin[i]->servidoPor()==0){
            std::cout << i << std::endl;
        }
        std::cout <<  " *** ID : *** " << sin[i]->getIdNum() << " *** , Id del laboratorio :  *** " << sin[i]->servidoPor()->getId() << std::endl;
        ++i;
    }


}

/**
 * @brief Carga la información de los medicamentos desde un fichero CSV.
 * @param _ficheroMedicamentos Ruta del fichero CSV/semicolon con medicamentos.
 * @post El vector interno de medicamentos queda poblado.
 */
void MediExpress::_cargarMedicamentosDesdeFichero(const std::string &_ficheroMedicamentos) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string _numeroDeId = "";
    std::string _idAlpha="";
    std::string _nombre="";

    int _idNum=0;


    is.open(_ficheroMedicamentos);
    if ( is.good() ) {


        while ( getline(is, fila ) ) {

            if (fila!="") {

                columnas.str(fila);

                getline(columnas, _numeroDeId, ';');
                getline(columnas, _idAlpha, ';');
                getline(columnas, _nombre, ';');
                _idNum = std::stoi(_numeroDeId);
                fila="";
                columnas.clear();

                PA_Medicamento _unMedicamento(_idNum, _idAlpha, _nombre);
                _medicamentos.inserta(_unMedicamento);



            }
        }
        is.close();

    } else {
        std::cout << "***Ha ocurrido un error de apertura en el archivo de medicamentos ***" <<  std::endl;
    }
}
/**
 * @brief Carga medicamentos, laboratorios y farmacias desde sus respectivos ficheros y realiza asignaciones iniciales.
 * @param _ficheroMedicamentos Ruta del fichero CSV/semicolon con medicamentos.
 * @param _ficheroLaboratorios Ruta del fichero CSV/semicolon con laboratorios.
 * @param _ficheroFarmacias Ruta del fichero CSV/semicolon con farmacias.
 * @post Los contenedores internos quedan cargados; se realiza una primera asignación entre medicamentos, laboratorios y farmacias.
 */

MediExpress::MediExpress(const std::string &_ficheroMedicamentos, const std::string &_ficheroLaboratorios, const std::string &_ficheroFarmacias) {
    _cargarMedicamentosDesdeFichero(_ficheroMedicamentos);

    _cargarLaboratoriosDesdeFichero(_ficheroLaboratorios);

    _cargarFarmaciasDesdeFichero(_ficheroFarmacias);
    std::cout << " *** Muestro lista de laboratorios :  *** " << std::endl;
    ListaSimplementeEnlazada<Laboratorio>::Iterador<Laboratorio> it = _labs._elIterador();
    while (!it._esFinal() ){
        std::cout << " *** Id del laboratorio : *** " << it._verDato().getId() << std::endl;
        it._esSiguiente();
    }
    std::cout << " *** Total de numero de laboratorios : *** " << _labs._getTamanio() << std::endl;


    asignarParesYVerificar();

    //Asociar los 152 medicamentos sin laboratorio a laboratorios de Madrid
    asignarLabsMadridAMedicamentosSinAsignar();

    //Leemos la segunda lectura del tercer fichero
    VectorDinamico<std::string> _vectorDeCifsDeFarmacias;
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador =0;
    std::string _nuevoCif = "";
    is.open(_ficheroFarmacias);
    if(is.good()){
        while(getline(is,fila)){
            if(fila != ""){
                columnas.str(fila);
                getline(columnas, _nuevoCif, ';');
                fila = "";
                columnas.clear();
                _vectorDeCifsDeFarmacias.inserta(_nuevoCif);

            }
        }
        is.close();
    }else{
        std::cout << "*** Error de apertura en archivo de medicamentos *** " << std::endl;
    }

    //Asociamos PaMedicamentos a cada farmacia del AVL, a patir del vector de cifs
    int j = 0;
    int i = 0;

    while (i < _vectorDeCifsDeFarmacias._getTamanio()) {
        Farmacia *f = buscarFarmacia(_vectorDeCifsDeFarmacias[i]);
        int c = 0;

        for ( c=0; c < 100; ++c) {
            suministrarFarmacia(f, _medicamentos[j].getIdNum());
            if (j == _medicamentos._getTamanio() - 1) {
                j = 0;
            } else {
                ++j;
            }
        }

        ++i;
    }

}

/**
 * @brief Carga la información de los laboratorios desde un fichero CSV.
 * @param _ficheroLaboratorios Ruta del fichero CSV/semicolon con laboratorios.
 * @post La lista interna de laboratorios queda poblada y ordenada por ID.
 */
void MediExpress::_cargarLaboratoriosDesdeFichero(const std::string &_ficheroLaboratorios) {
    std::ifstream is2;
    std::stringstream  columnas2;
    std::string fila2;
    int contador2=0;

    std::string _numeroDeId = "";
    std::string _nombreLab = "";
    std::string _direccion = "";
    std::string _cp = "";
    std::string _localidad = "";
    int _idNumLab=0;


    is2.open(_ficheroLaboratorios);
    if ( is2.good() ) {
        while ( getline(is2, fila2 ) ) {
            if (fila2!="") {
                columnas2.str(fila2);
                getline(columnas2, _numeroDeId, ';');
                getline(columnas2, _nombreLab, ';');
                getline(columnas2, _direccion, ';');
                getline(columnas2, _cp, ';');
                getline(columnas2, _localidad, '\r');
                _idNumLab = std::stoi(_numeroDeId);
                fila2="";
                columnas2.clear();

                Laboratorio _unLab(_idNumLab,_nombreLab,_direccion,_cp,_localidad);
                ListaSimplementeEnlazada<Laboratorio>::Iterador<Laboratorio> it = _labs._elIterador();
                while(!it._esFinal() && it._verDato().getId() < _idNumLab){
                    it._esSiguiente();

                }
                _labs._insertarPorElFinal(_unLab);


            }
        }
        is2.close();

    } else {
        std::cout << "***Ha ocurrido un error de apertura en el archivo de laboratorios ***" <<  std::endl;
    }
}
/**
 * @brief Devuelve los laboratorios cuya localidad contenga el texto dado.
 * @param nombreCiudad Subcadena a buscar dentro del campo localidad.
 * @return Vector dinámico con punteros a los laboratorios que coinciden (puede estar vacío).
 * @note La coincidencia es por subcadena y sensible a mayúsculas/minúsculas.
 */
VectorDinamico<Laboratorio *> MediExpress::buscarLabCiudad(const std::string &nombreCiudad) {
    VectorDinamico<Laboratorio*> toRet;
    ListaSimplementeEnlazada<Laboratorio>::Iterador<Laboratorio> it6 = _labs._elIterador();
    while(!it6._esFinal()){
        if(it6._verDato().getLocalidad().find(nombreCiudad) != std::string::npos){
            toRet.inserta(&(it6._verDato()));
        }
        it6._esSiguiente();
    }
    return toRet;
}

/**
 * @brief Busca un medicamento por su identificador numérico.
 * @param id_num Identificador numérico del medicamento.
 * @return Puntero al medicamento encontrado o nullptr si no existe.
 */
PA_Medicamento* MediExpress::buscarCompuesto(const int id_num) {
    PA_Medicamento *aux = nullptr;
    int i =0;
    while(i < _medicamentos._getTamanio()){
        if(_medicamentos[i].getIdNum()==id_num){
            aux =  (&(_medicamentos[i]));
        }
        ++i;
    }

    return aux;
}

/**
 * @brief Asigna un laboratorio a un principio activo (medicamento).
 * @param pa Puntero al medicamento (principio activo) a asignar.
 * @param l Puntero al laboratorio que suministra el medicamento.
 * @pre Ambos punteros deben ser válidos (no nulos) para que la asignación se aplique.
 * @post El medicamento queda marcado como servido por el laboratorio indicado.
 */
void MediExpress::suministrarMed(PA_Medicamento *pa, Laboratorio *l) {
    if(l && pa){
        pa->servidoPor(l);
    }
}
/**
 * @brief Asigna un medicamento a una farmacia, según su identificador.
 * @param f Puntero a la farmacia receptora.
 * @param id_num Identificador del medicamento a dispensar.
 * @post Si el medicamento existe, se añade al inventario de la farmacia; en caso contrario, se inserta nulo.
 */
void MediExpress::suministrarFarmacia(Farmacia *f, int id_num) {
    PA_Medicamento* medicamento = buscarCompuesto(id_num);
    if(medicamento){
        f->dispensaMed(medicamento);
    }else{
        f->dispensaMed(0);

    }
}


/**
 * @brief Busca una farmacia en el árbol por su CIF.
 * @param cif Identificador CIF de la farmacia a buscar.
 * @return Puntero a la farmacia encontrada o nullptr si no existe.
 * @throws std::invalid_argument Si el CIF está vacío.
 */
Farmacia *MediExpress::buscarFarmacia(const std::string &cif) {
    if(cif == " "){
        throw std::invalid_argument("*** El cif esta vacio *** ");
    }
    Farmacia _farmaAux;
    _farmaAux.setCif(cif);
    return _pharmacy.busquedaIterativa(_farmaAux);
}
/**
 * @brief Busca un laboratorio cuyo nombre contenga el texto dado.
 * @param nombreLab Subcadena a buscar dentro del nombre del laboratorio.
 * @return Puntero al primer laboratorio cuyo nombre contenga @p nombreLab, o nullptr si no se encuentra.
 * @note La búsqueda es por subcadena (std::string::find), sensible a mayúsculas/minúsculas.
 */
Laboratorio *MediExpress::buscarLab(const std::string &nombreLab) {
    ListaSimplementeEnlazada<Laboratorio>::Iterador<Laboratorio> it5 = _labs._elIterador();
    while(!it5._esFinal()){
        if(it5._verDato().getNombreLab().find(nombreLab) != std::string::npos){
            return (&(it5._verDato()));
        }
        it5._esSiguiente();
    }
    return nullptr;
}
/**
 * @brief Elimina los laboratorios de una localidad y desasigna los medicamentos servidos por ellos.
 * @param localidad Subcadena a buscar dentro del campo localidad de los laboratorios a eliminar.
 * @param contador (IN/OUT) Número acumulado de laboratorios eliminados; se incrementa con los borrados de esta llamada.
 * @post Los medicamentos quedan con puntero a laboratorio nulo si eran servidos por laboratorios eliminados.
 * @note La coincidencia por localidad es por subcadena (sensible a mayúsculas/minúsculas).
 * @warning El iterador interno se invalida al borrar; se usa un iterador auxiliar para continuar de forma segura.
 */
void MediExpress::eliminarLaboratorio(const std::string& localidad, int& contador){

    int i=0;
    while(i < _medicamentos._getTamanio()){
        if (_medicamentos[i].servidoPor() != nullptr &&
            _medicamentos[i].servidoPor()->getLocalidad().find(localidad) != std::string::npos) {
            _medicamentos[i].servidoPor(nullptr);
        }
        ++i;
    }


    ListaSimplementeEnlazada<Laboratorio>::Iterador<Laboratorio> it7 = _labs._elIterador();
    ListaSimplementeEnlazada<Laboratorio>::Iterador<Laboratorio> _iteradorAuxiliar;

    while (!it7._esFinal()) {
        if (it7._verDato().getLocalidad().find(localidad) != std::string::npos) {
            _iteradorAuxiliar = it7;
            _iteradorAuxiliar._esSiguiente();
            _labs._borrarPorElMedio(it7);
            it7 = _iteradorAuxiliar;
            ++contador;
        } else {
            it7._esSiguiente();
        }
    }
}