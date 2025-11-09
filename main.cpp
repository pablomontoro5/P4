#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VectorDinamico.h"
#include "PA_Medicamento.h"
#include "ListaSimplementeEnlazada.h"
#include "Laboratorio.h"
#include "MediExpress.h"
#include "ArbolAVL.h"
#include "Farmacia.h"
/**  @author Pablo Javier Montoro Bermúdez pjmb0003@red.ujaen.es
      @author Lázaro Ruiz Fernández lrf00011@red.ujaen.es
*/


void cargarFarmacias(ArbolAVL<Farmacia> &af, VectorDinamico<Farmacia> &vf) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;
    int contador = 0;
    std::string nuevoCif = "";
    std::string nuevaProvincia = "";
    std::string nuevaLocalidad = "";
    std::string nuevoNombre = "";
    std::string nuevaDireccion = "";
    std::string nuevoCodigoPostal = "";
    is.open("../farmacias.csv");
    if(is.good()){
        while (getline(is, fila)) {
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, nuevoCif, ';');
                getline(columnas, nuevaProvincia, ';');
                getline(columnas, nuevaLocalidad, ';');
                getline(columnas, nuevoNombre, ';');
                getline(columnas, nuevaDireccion, ';');
                getline(columnas, nuevoCodigoPostal, '\r');
                fila = "";
                columnas.clear();
                Farmacia nuevaFarmacia(nuevoCif, nuevaProvincia, nuevaLocalidad, nuevoNombre, nuevaDireccion,
                                       nuevoCodigoPostal, nullptr);

                af.inserta(nuevaFarmacia);
                vf.inserta(nuevaFarmacia);
                std::cout << ++contador
                          << " *** Farma : cif = *** " << nuevoCif
                          << " *** provincia = *** " << nuevaProvincia << " *** localidad = *** " << nuevaLocalidad
                          << " *** nombre = *** " << nuevoNombre << " *** direccion = *** " << nuevaDireccion
                          << "***  codigo postal = *** " << nuevoCodigoPostal << std::endl;

            }
        }
    }else{
        std::cout << "***Error de apertura de archivo ***" << std::endl;
    }
}
int main(int argc, const char * argv[]) {

    try{
        std::cout << "***Programa de prueba I: probar la busqueda de medicamentos de forma eficiente ***" << std::endl;
        clock_t t_inicial;
        ArbolAVL<Farmacia> arbolDeFarmacias;
        VectorDinamico<Farmacia> vectorDeFarmacias;
        cargarFarmacias(arbolDeFarmacias, vectorDeFarmacias);
        VectorDinamico<std::string> auxiliar;

        std::cout << "*** Cargamos los cif de las primeras 500 farmacias directameante de vectorDeFarmacias *** " << std::endl;
        int i1 =0;
        while(i1 < vectorDeFarmacias._getTamanio() || i1 < 500){
            auxiliar.inserta(vectorDeFarmacias[i1].getCif());
            ++i1;
        }


        std::cout << "*** Calculamos el tiempo al buscar 500 farmacias en el AVL *** " << std::endl;
        Farmacia _unDatoAuxiliar;
        t_inicial = clock();
        int i2=0;
        while(i2 < auxiliar._getTamanio()){
            _unDatoAuxiliar.setCif(auxiliar[i2]);
            arbolDeFarmacias.busquedaRecursiva(_unDatoAuxiliar);
            ++i2;
        }

        std::cout << std::endl << "*** Tiempo (en segundos) al buscar 500 farmacias en el AVL : *** " << ((clock()-t_inicial) / (float) CLOCKS_PER_SEC*1000 ) <<  std::endl;

        std::cout << "***  Calculamos el tiempo al buscar 500 farmacias en el VectorDinamico *** " << std::endl;
        t_inicial = clock();
        int i3 =0;

        while(i3 < auxiliar._getTamanio()){
            bool enc = false;
            int j1 =0;
            while(j1 < vectorDeFarmacias._getTamanio() && !enc){
                if(auxiliar[i3] == vectorDeFarmacias[j1].getCif()){
                    enc = true;
                }
                ++j1;
            }
            ++i3;
        }

        std::cout << std::endl << "*** Tiempo (en segundos)  al buscar 500 farmacias en el VectorDinamico : *** " << ((clock()-t_inicial) / (float) CLOCKS_PER_SEC*1000 ) << std::endl;

        std::cout << "*** Altura del arbol de farmacias : *** " << arbolDeFarmacias._getAltura() << std::endl;

        std::cout << "***Recorremos en inorden y mostramos las 100 primeras *** " << std::endl;
        VectorDinamico<Farmacia*> v = arbolDeFarmacias._recorrerInorden();
        std::cout << "*** Muestro (el CIF) de las 100 primeras en inorden *** " << std::endl;

        for(int i=0; i< v._getTamanio() && i < 100; ++i){
            std::cout << v[i]->getCif() << std::endl;
        }

        std::cout << "***Programa de prueba II: probar la nueva funcionalidad de MediExpress ***" << std::endl;
        MediExpress medi("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv");

        std::cout << "*** Apartado 1 del Main 2 . Creamos un vector tipo buffer con los CIF del enunciado *** " << std::endl;
        std::string cif[27] = {"37656422V","46316032N", "77092934Q", "33961602D", "B62351861", "B62351861",
                               "B65828113", "46138599R", "35069965W", "37579913Y", "37682300C",
                               "37643742X", "46112335A", "47980171D", "38116138D", "46315600V",
                               "37640233C", "37931842N", "33964303L", "35022080A", "B66046640",
                               "E66748344", "47640201W", "B66621954", "46121385Z", "X6806622W",
                               "46046390E"};

        std::cout << "*** Apartado 2 del Main 2. Buscamos si alguna farmacia de las anteriormente mencionadas dispensa OXIDO DE MAGNESIO con id 3640 *** " << std::endl;
        int _idDelMedicamentoPedido =3640;
        Farmacia *_farmaciaAuxiliar = nullptr;
        int i5 =0;
        while(i5 < 27){
            _farmaciaAuxiliar = medi.buscarFarmacia(cif[i5]);
            if(!_farmaciaAuxiliar->buscaMedicam(_idDelMedicamentoPedido)){ //Si no está, hace el pedido del medicamento
                _farmaciaAuxiliar->pedidoMedicam(_idDelMedicamentoPedido);
            }
            ++i5;
        }

        std::cout << "*** Apartado 3 del Main 2. Buscamos y contamos todos los laboratorios que trabajen algun tipo de MAGNESIO *** " << std::endl;

        VectorDinamico<Laboratorio*> _laboratoriosQueTrabajenConMagnesio = medi.buscarLabs("MAGNESIO");
        std::cout << " *** Este es el numero de laboratios que trabajan con algun tipo de MAGNESIO: *** " << _laboratoriosQueTrabajenConMagnesio._getTamanio() << std::endl;

        std::cout << "*** Apartado Trabajo en Pareja *** " << std::endl;
        int cont2 = 0;
        int i6 =0;
        while(i6 < 27){
            _farmaciaAuxiliar = medi.buscarFarmacia(cif[i6]);
            if(_farmaciaAuxiliar){
                ListaSimplementeEnlazada<Laboratorio*> _listaDeLaboratoriosAuxiliar = _farmaciaAuxiliar->buscarMedicam("VIRUS");
                cont2+=_listaDeLaboratoriosAuxiliar._getTamanio();
            }
            ++i6;
        }


        std::cout << "*** Este es el numero de laboratorios que suministran a alguna de estas farmacias algun tipo de medicamento con VIRUS : *** " <<  cont2 << std::endl;
    }catch(std::runtime_error &rte){
        std::cerr << rte.what() << std::endl;
    }catch(std::out_of_range &oor){
        std::cerr << oor.what() << std::endl;
    }catch(std::bad_alloc &ba){
        std::cerr << ba.what() << std::endl;
    }catch(std::invalid_argument &inarg){
        std::cerr << inarg.what() << std::endl;
    }

    return 0;
}

