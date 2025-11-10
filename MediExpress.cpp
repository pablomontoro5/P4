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
    std::list<Laboratorio>::iterator it1=_labs.begin();
    std::map<int,PA_Medicamento>::iterator iteradordeMedicamentos1 = _medicamentos.begin();
    while(iteradordeMedicamentos1!=_medicamentos.end() && it1!=_labs.end()){
        suministrarMed(&(iteradordeMedicamentos1->second),&(*it1));
        ++iteradordeMedicamentos1;
        iteradordeMedicamentos1->second.servidoPor(&(*it1)); //Probar con suministraMed
        ++it1;

    }


    int _contadorAuxiliar = 0;

    std::map<int, PA_Medicamento>::iterator itMed = _medicamentos.begin();
    while (itMed != _medicamentos.end()) {
        PA_Medicamento &med = itMed->second;

        if (med.servidoPor()) {
            std::cout << "*** Id del principio activo del medicamento : *** "
                      << med.getIdNum()
                      << " *** Id del laboratorio : *** "
                      << med.servidoPor()->getId()
                      << std::endl;
        } else {
            ++_contadorAuxiliar;
        }

        ++itMed;
    }


    std::cout << " *** Este es el numero de medicamentos que no se han asignado : *** " << _contadorAuxiliar << std:: endl;
}
/**
 * @brief Busca los laboratorios que suministran medicamentos cuyo nombre contenga una subcadena dada.
 * @param nombrePa Subcadena a buscar dentro del nombre del medicamento.
 * @return Vector dinámico con punteros a laboratorios (puede contener duplicados o punteros nulos).
 */
std::vector<Laboratorio *> MediExpress::buscarLabs(const std::string &nombrePa) {
    std::vector<Laboratorio*> toRet;
    int i=0;
    while(i < _medicamentos.size()) {
        if (_medicamentos[i].getNombre().find(nombrePa) != std::string::npos) {
            toRet.push_back(_medicamentos[i].servidoPor());
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
                _pharmacy.push_back(datoFarmaceutico);
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
std::vector<PA_Medicamento *> MediExpress::getMedicamentosSinLab() {
    std::vector<PA_Medicamento*> toRet;
    std::map<int,PA_Medicamento>::iterator it2 = _medicamentos.begin();
    while(it2!=_medicamentos.end()){
        if(!it2->second.servidoPor()){
            toRet.push_back(&(it2->second));
        }
        ++it2;
    }

    return toRet;
}
PA_Medicamento* MediExpress::buscarCompuesto(int _idDelNumero){
    PA_Medicamento *toRet = nullptr;
    std::map<int,PA_Medicamento>::iterator it7=_medicamentos.find(_idDelNumero);
    if (it7 != _medicamentos.end()){
        toRet =  &(it7->second);
    }else{
        return 0;
    }
    return toRet;
}
/**
 * @brief Asigna laboratorios de Madrid a los medicamentos que no tienen laboratorio asignado.
 * @post Cada medicamento sin laboratorio pasa a estar servido por un laboratorio de Madrid (si hay suficientes).
 * @note La asignación se realiza por orden de aparición en las listas internas.
 */
void MediExpress::asignarLabsMadridAMedicamentosSinAsignar() {
    std::vector<Laboratorio *> _Madrid = buscarLabCiudad("Madrid");
    std::vector<PA_Medicamento *> _sin = getMedicamentosSinLab();
    for (int i = 0; i < _Madrid.size() && i < _sin.size(); ++i) {
        suministrarMed(_sin[i], _Madrid[i]);
        std::cout << " *** ID : *** " << _sin[i]->getIdNum() << " *** , Id del laboratorio :  *** "
                  << _sin[i]->servidoPor()->getId() << std::endl;

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

                //Cambiar la forma de la inserción
                PA_Medicamento _unMedicamento(_idNum, _idAlpha, _nombre);
                _medicamentos.insert(std::pair<int,PA_Medicamento>(_idNum,_unMedicamento));




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
    std::list<Laboratorio>::iterator it = _labs.begin();
    while (it!=_labs.end()){
        std::cout << " *** Id del laboratorio : *** " << (*it).getId() << std::endl;
        ++it;
    }
    std::cout << " *** Total de numero de laboratorios : *** " << _labs.size() << std::endl;


    asignarParesYVerificar();

    //Asociar los 152 medicamentos sin laboratorio a laboratorios de Madrid
    asignarLabsMadridAMedicamentosSinAsignar();

    //Leemos la segunda lectura del tercer fichero
    std::vector<std::string> _vectorDeCifsDeFarmacias;
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
                _vectorDeCifsDeFarmacias.push_back(_nuevoCif);

            }
        }
        is.close();
    }else{
        std::cout << "*** Error de apertura en archivo de medicamentos *** " << std::endl;
    }

    std::map<int,PA_Medicamento>::iterator it3=_medicamentos.begin();
    for (int i=0; i<_vectorDeCifsDeFarmacias.size(); i++){
        Farmacia* f= buscarFarmacia(_vectorDeCifsDeFarmacias[i]);
        int c=0;
        while (c<100){
            suministrarFarmacia(f,it3->second.getIdNum(), 10); //Práctica 4

            if (it3==--_medicamentos.end()) {
                it3 = _medicamentos.begin();
            }else {
                it3++;
            }
            c++;
        }
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

                _labs.push_back(_unLab);


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
std::vector<Laboratorio *> MediExpress::buscarLabCiudad(const std::string &nombreCiudad) {
    std::vector<Laboratorio*> toRet;
    std::list<Laboratorio>::iterator it5 = _labs.begin();
    while(it5!=_labs.end()){
        if((*it5).getLocalidad().find(nombreCiudad)!=std::string::npos){
            toRet.push_back((&(*it5)));
        }
        ++it5;
    }
    return toRet;
}

/**
 * @brief Busca un medicamento por su identificador numérico.
 * @param id_num Identificador numérico del medicamento.
 * @return Puntero al medicamento encontrado o nullptr si no existe.
 */
std::vector<PA_Medicamento*> MediExpress::buscarCompuesto(const std::string &nombrePA) {
    std::vector<PA_Medicamento*> toRet;
    std::map<int,PA_Medicamento>::iterator it6 = _medicamentos.begin();
    for(; it6!=_medicamentos.end(); ++it6){
        if(it6->second.getNombre().find(nombrePA)!= std::string::npos){
            toRet.push_back((&(it6->second)));
        }
    }

    return toRet;
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
void MediExpress::suministrarFarmacia(Farmacia *f, int id_num, int n) {
    PA_Medicamento* medicamento = buscarCompuesto(id_num);
    if(medicamento){
        f->nuevoStock(medicamento,n);
    }else{
        //

    }
}


/**
 * @brief Busca una farmacia en el árbol por su CIF.
 * @param cif Identificador CIF de la farmacia a buscar.
 * @return Puntero a la farmacia encontrada o nullptr si no existe.
 * @throws std::invalid_argument Si el CIF está vacío.
 */
Farmacia *MediExpress::buscarFarmacia(const std::string &cif) {
    Farmacia *aux = nullptr;
    int i=0;
    while(i < _pharmacy.size()){
        if(_pharmacy[i].getCif()==cif){
            aux = (&(_pharmacy[i]));
        }
        ++i;
    }
    return aux;
}
/**
 * @brief Busca un laboratorio cuyo nombre contenga el texto dado.
 * @param nombreLab Subcadena a buscar dentro del nombre del laboratorio.
 * @return Puntero al primer laboratorio cuyo nombre contenga @p nombreLab, o nullptr si no se encuentra.
 * @note La búsqueda es por subcadena (std::string::find), sensible a mayúsculas/minúsculas.
 */
Laboratorio *MediExpress::buscarLab(const std::string &nombreLab) {
    std::list<Laboratorio>::iterator it4 = _labs.begin();
    while(it4!=_labs.end()){
        if((*it4).getNombreLab().find(nombreLab)!=std::string::npos){
            return (&(*it4));
        }
        ++it4;
    }
    return nullptr;
}
