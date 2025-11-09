//
// Created by Pablo Montoro on 22/09/2025.
//

#ifndef P1_VECTORDINAMICO_H
#define P1_VECTORDINAMICO_H

#include "iostream"
#include "cmath"
#include "climits"
#include "stdexcept"
#include "algorithm"

template<typename T>
class VectorDinamico{
    private:
        T *pV;
        unsigned int _tamanioLogico, _tamanioFisico;
        void cogerMemoria();
        void liberaMemoria();
        void tamanioEnBaseDos(unsigned long int &_elTamanio);
    public:
        VectorDinamico(const VectorDinamico<T> &_unaCopia, unsigned int _posicionInicial, unsigned int _totalElementos);
        VectorDinamico(unsigned int _unTamanio, T& _unDato);
        unsigned long int busquedaDicotomica(const T &dato);
        void ordenar();

        unsigned long int _getTamanio();
        T& borrar(unsigned int pos = UINT_MAX);
        T& operator[](unsigned long int posicion);
        VectorDinamico(const VectorDinamico<T> &_unaCopia);

        void inserta(const T& dato, unsigned int pos = UINT_MAX);
        VectorDinamico<T> &operator=(const VectorDinamico<T> &_unaAsignacion);
        virtual ~VectorDinamico();
        VectorDinamico();

};
/**
 * @brief Borra el último elemento o el de una posición dada y lo devuelve.
 * @tparam T Tipo de los elementos.
 * @param pos Posición a borrar; si es `UINT_MAX`, borra el último.
 * @return Copia del elemento borrado.
 * @throws std::out_of_range Si el vector está vacío o @pos ≥ tamaño lógico.
 * @post Disminuye el tamaño lógico en 1. Puede reducirse la capacidad si hay mucha holgura.
 */
template <typename T>
T &VectorDinamico<T>::borrar(unsigned int pos) {
    T _toRet;
    if(_tamanioLogico == 0){
        throw std::out_of_range("No hay nada para borrar");
    }
    if(pos==UINT_MAX){
        if(_tamanioLogico * 3 < _tamanioFisico){
            liberaMemoria();
        }
        _toRet = pV[_tamanioLogico - 1];
    }else{
        if(pos >= _tamanioLogico){
            throw std::out_of_range("No hay nada para borrar");
        }
        if(_tamanioLogico * 3 < _tamanioFisico){
            liberaMemoria();
        }
        _toRet = pV[pos];
        for(unsigned i = pos; i < _tamanioLogico - 1; ++i){
            pV[i] = pV[i+1];
        }
    }
    --_tamanioLogico;
    return (_toRet);
}
/**
 * @brief Ajusta un tamaño al siguiente valor que sea potencia de 2.
 * @tparam T Tipo de los elementos.
 * @param _elTamanio (entrada/salida) Tamaño a ajustar.
 * @post @_elTamanio toma un valor que es potencia de 2 y ≥ al original (o la siguiente si ya lo era).
 * @note Útil para dimensionar capacidad física.
 */
template <typename T>
void VectorDinamico<T>::tamanioEnBaseDos(unsigned long &_elTamanio) {
    if(log2(_elTamanio)==round(log2(_elTamanio))){
        ++_elTamanio;
    }
    while(log2(_elTamanio)!=round(log2(_elTamanio))){
        ++_elTamanio;
    }
}
/**
 * @brief Reduce a la mitad la capacidad física y conserva los primeros elementos.
 * @tparam T Tipo de los elementos.
 * @post La capacidad física se divide entre 2; se preservan los elementos válidos.
 * @note Debe usarse cuando exista holgura notable para ahorrar memoria.
 */
template <typename T>
void VectorDinamico<T>::liberaMemoria() {
    _tamanioFisico/=2;
    int *_numeroAux = new int[_tamanioFisico];
    for(unsigned i=0;i<_tamanioFisico;i++){
        _numeroAux[i]=pV[i];
    }
    delete[] pV;
    pV=_numeroAux;

    return pV[--_tamanioFisico];
}


/**
 * @brief Constructor por dado un tamaño logico inicial.
 * @tparam T Tipo de los elementos.
 * @param _unTamanio Tamaño logico.
 * @param _unDato Dato para rellenar el vector.
 * @post Crea un vector relleno con un _unDato hasta su tamaño logico, con capacidad física inicial potencia inmediatamente mayor que el tamaño logico.
 */
 template<typename T>
VectorDinamico<T>::VectorDinamico(unsigned int _unTamanio, T& _unDato):_tamanioLogico(_unTamanio) {
    int _nuevoTamanio = _unTamanio;
    tamanioEnBaseDos(_nuevoTamanio);
    _tamanioFisico = _nuevoTamanio;
    pV = new T[_tamanioFisico];
    for(int i=0;i<_tamanioLogico;++i){
        pV[i]=_unDato;
    }
}



/**
 * @brief Constructor de copia parcial (segmento).
 * @tparam T Tipo de los elementos.
 * @param _unaCopia Vector fuente.
 * @param _posicionInicial Índice inicial (incluido) del segmento en el vector fuente.
 * @param _totalElementos Número de elementos a copiar.
 * @throws std::range_error Si @_posicionInicial ≥ tamaño lógico del fuente.
 * @throws std::out_of_range Si @_posicionInicial + @_totalElementos excede el tamaño lógico del fuente.
 * @post Tamaño lógico = @_totalElementos. La capacidad física se ajusta a potencia de 2 suficiente.
 */
template<typename T>
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T> &_unaCopia, unsigned int _posicionInicial, unsigned int _totalElementos):_tamanioLogico(_totalElementos) {
    if(_posicionInicial >= _unaCopia._tamanioLogico){
        throw std::range_error("***El comienzo esta fuera del rango***");
    }
    if(_totalElementos + _posicionInicial > _unaCopia._tamanioLogico){
        throw std::out_of_range("***No hay tantos elementos***");
    }
    int _nuevoTamanio = _totalElementos;
    tamanioEnBaseDos(_nuevoTamanio);
    _tamanioFisico = _nuevoTamanio;
    pV = new T[_tamanioFisico];
    _tamanioLogico = _totalElementos;
    int j = 0;
    for(unsigned long int i=_posicionInicial; i < _posicionInicial + _totalElementos; ++i){
        pV[j++] = _unaCopia.pV[i];
    }
}

/**
 * @brief Constructor de copia.
 * @tparam T Tipo de los elementos.
 * @param _unaCopia Vector fuente.
 * @post Crea un nuevo vector exactamente igual a uno dado.
 */
template<typename T>
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T> &_unaCopia): _tamanioLogico(_unaCopia._tamanioLogico), _tamanioFisico(_unaCopia._tamanioFisico) {
    pV = new T[_tamanioFisico];
    for(int i=0; i < _tamanioLogico; ++i){
        pV[i] = _unaCopia.pV[i];
    }
}
/**
 * @brief Búsqueda binaria del elemento indicado.
 * @tparam T Tipo de los elementos (requiere `operator==` y `operator<`).
 * @param dato Elemento a localizar.
 * @return Índice del elemento si se encuentra; en caso contrario, un valor sentinela (p. ej., `-1` si el tipo de retorno lo permite).
 * @pre El contenedor debe estar ordenado ascendentemente según `operator<`.
 */
template <typename T>
unsigned long VectorDinamico<T>::busquedaDicotomica(const T &dato) {
    int inf = 0;
    int sup = _tamanioLogico - 1;
    int curIn;
    while (inf <= sup) {
        curIn = (inf + sup) / 2;
        if (pV[curIn] == dato) {
            return curIn;
        }else if(pV[curIn] < dato) {
            inf = curIn + 1;
        }else{
            sup = curIn - 1;
        }
    }
    return -1;
}
/**
 * @brief Destructor.
 * @tparam T Tipo de los elementos.
 */
template <typename T>
VectorDinamico<T>::~VectorDinamico(){
    if(pV != nullptr){
        delete []pV;
        pV = nullptr;
    }
}
/**
 * @brief Duplica la capacidad física y copia los elementos actuales.
 * @tparam T Tipo de los elementos.
 * @post La capacidad física se multiplica por 2 y se preserva el contenido.
 */
template <typename T>
void VectorDinamico<T>::cogerMemoria() {
    T* _vectorAuxiliar = new T[_tamanioFisico*=2];
    for(unsigned int i=0;i<_tamanioLogico;++i){
        _vectorAuxiliar[i]=pV[i];
    }
    delete []pV;
    pV = _vectorAuxiliar;
}

/**
 * @brief Ordena los elementos en el rango [0, _getTamanio()).
 * @tparam T Tipo de los elementos (requiere `operator<`).
 * @post El contenedor queda ordenado de menor a mayor según `operator<`.
 */
template <typename T>
void VectorDinamico<T>::ordenar() {
    std::sort(pV, pV + _tamanioLogico);
}
/**
 * @brief Acceso por índice (lectura/escritura).
 * @tparam T Tipo de los elementos.
 * @param posicion Índice lógico (0 .. _getTamanio()-1).
 * @return Referencia al elemento en @posicion.
 * @throws std::out_of_range Si @posicion es inválida.
 */
template <typename T>
T &VectorDinamico<T>::operator[](unsigned long posicion) {
    if(posicion >= _tamanioLogico){
        throw std::out_of_range("posicion no valida");
    }
    return pV[posicion];
}
/**
 * @brief Inserta un elemento al final o en la posición dada.
 * @tparam T Tipo de los elementos.
 * @param dato Elemento a insertar.
 * @param pos Posición de inserción; si es `UINT_MAX`, se insertarDato al final.
 * @throws std::out_of_range Si @pos es distinta de `UINT_MAX` y @pos ≥ tamaño lógico.
 * @post Aumenta el tamaño lógico en 1. Duplica capacidad si es necesario.
 * @warning Si se insertarDato en medio se realiza desplazamiento a la derecha de elementos.
 */
template <typename T>
void VectorDinamico<T>::inserta(const T &dato, unsigned int pos) {
    if(pos==UINT_MAX){
        if(_tamanioLogico == _tamanioFisico){
            cogerMemoria();
        }
        pV[_tamanioLogico]=dato;
    }else{
        if(pos >= _tamanioLogico){
            throw std::out_of_range("***Posicion fuera de rango ***");
        }
        if(_tamanioLogico == _tamanioFisico){
            cogerMemoria();
        }
        if(_tamanioLogico != 0){
            for(unsigned long int i= _tamanioLogico - 1; i >= pos; --i){
                pV[i+1]=pV[i];
            }
        }
        pV[pos]=dato;
    }
    ++_tamanioLogico;
}




/**
 * @brief Constructor por defecto.
 * @tparam T Tipo de los elementos.
 * @post Crea un vector vacío con capacidad física inicial 1.
 */
template<typename T>
VectorDinamico<T>::VectorDinamico(): _tamanioLogico(0), _tamanioFisico(1) {
    pV = new T[_tamanioFisico];
}
/**
 * @brief Getter del tamaño logico
 * @return Tamaño logico del vector
 */
template <typename T>
unsigned long VectorDinamico<T>::_getTamanio() {
    return _tamanioLogico;
}
/**
 * @brief Operador de asignacion.
 * @tparam T Tipo de los elementos.
 * @param _unaAsignacion Vector a asignar
 * @return Vector asignado
 */
template <typename T>
VectorDinamico<T> &VectorDinamico<T>::operator=(const VectorDinamico<T> &_unaAsignacion) {
    if(this!=&_unaAsignacion){
        delete [] pV;
        _tamanioLogico = _unaAsignacion._tamanioLogico;
        _tamanioFisico = _unaAsignacion._tamanioFisico;
        pV = new T [_tamanioFisico];
        for(unsigned long int c2 = 0; c2 < _tamanioLogico; ++c2){
            pV[c2] = _unaAsignacion.pV[c2];
        }
    }
    return (*this);
}
#endif //P1_VECTORDINAMICO_H
