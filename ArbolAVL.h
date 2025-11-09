//
// Created by monto on 22/10/2025.
//
/**
 * @file ArbolAVL.h
 * @brief Definición de la clase plantilla ArbolAVL, que implementa un árbol de búsqueda auto-balanceado (AVL).
 * @date 22/10/2025
 */

#ifndef P3_ARBOLAVL_H
#define P3_ARBOLAVL_H
#include <iostream>
#include "NodoArbolAVL.h"
#include "VectorDinamico.h"
/**
 * @class ArbolAVL
 * @brief Clase plantilla que representa un árbol binario de búsqueda balanceado (AVL).
 *
 * Proporciona inserción, búsqueda (recursiva e iterativa), recorrido inorden y gestión de memoria
 * (copiado, destrucción y cálculo de altura). Mantiene el equilibrio mediante rotaciones simples.
 *
 * @tparam T Tipo de dato almacenado en los nodos del árbol.
 */
template <typename T>
class ArbolAVL{
    NodoArbolAVL<T> *_elRaiz;///< Puntero al nodo raíz del árbol.
    unsigned int _elTamanio; ///< Número total de elementos en el árbol.
/**
     * @brief Realiza una rotación simple a la derecha en el subárbol dado.
     * @param p Referencia al puntero del nodo donde se aplica la rotación.
     */
    void rotacionDerecha(NodoArbolAVL<T>*& p);
    /**
     * @brief Realiza una rotación simple a la izquierda en el subárbol dado.
     * @param p Referencia al puntero del nodo donde se aplica la rotación.
     */
    void rotacionIzquierda(NodoArbolAVL<T>*& p);
    /**
     * @brief Copia recursivamente los nodos de otro árbol AVL.
     * @param qNodo Referencia al puntero destino donde se insertarán los nodos copiados.
     * @param pNodo Puntero al nodo origen desde el que se copiarán los datos.
     */
    void copioAVL(NodoArbolAVL<T>*& qNodo, NodoArbolAVL<T>* pNodo);
    /**
     * @brief Recorre el árbol en orden (izquierda-raíz-derecha) y almacena punteros a los datos.
     * @param p Nodo actual.
     * @param v Vector dinámico donde se almacenan los punteros a los datos.
     */
    void inorden(NodoArbolAVL<T> *p,VectorDinamico<T*> &v);
    /**
     * @brief Busca un nodo en el árbol de forma recursiva a partir de una clave.
     * @param dato Clave a buscar.
     * @param pNodo Nodo desde el cual se realiza la búsqueda.
     * @return Puntero al nodo encontrado, o nullptr si no existe.
     */
    NodoArbolAVL<T>* buscoClave(const T& dato, NodoArbolAVL<T>* pNodo);
    /**
     * @brief Inserta un nuevo dato en el árbol manteniendo las propiedades del AVL.
     * @param xNodo Referencia al puntero de nodo donde se inserta.
     * @param dato Dato a insertar.
     * @return 1 si el subárbol ha aumentado de altura, 0 en caso contrario.
     */
    int insertoDato(NodoArbolAVL<T>*& xNodo, const T& dato);
    /**
     * @brief Calcula la altura del subárbol cuyo nodo raíz es p.
     * @param p Nodo raíz del subárbol.
     * @return Altura del subárbol.
     */
    unsigned alturaPrivada(NodoArbolAVL<T>* p);
public:
    /**
     * @brief Constructor por defecto. Inicializa un árbol vacío.
     */
    ArbolAVL(): _elRaiz(nullptr),_elTamanio(0){

    }
    /**
     * @brief Destructor del árbol AVL.
     * Libera toda la memoria asociada a los nodos del árbol.
     */
    ~ArbolAVL(){
        destruyeArbol(_elRaiz);
    }
    /**
     * @brief Constructor de copia. Crea un nuevo árbol a partir de otro existente.
     * @param copia Árbol AVL a copiar.
     */
    ArbolAVL(const ArbolAVL<T>& copia);
    /**
     * @brief Operador de asignación. Copia el contenido de otro árbol AVL.
     * @param copia Árbol a copiar.
     * @return Referencia al árbol actual (*this).
     */
    ArbolAVL<T>& operator=(const ArbolAVL<T> &copia);
    /**
     * @brief Busca un elemento de manera recursiva en el árbol.
     * @param dato Dato a buscar.
     * @return Puntero al dato si se encuentra, nullptr si no existe.
     */
    T* busquedaRecursiva(const T& dato);
    /**
     * @brief Busca un elemento de manera iterativa en el árbol.
     * @param dato Dato a buscar.
     * @return Puntero al dato si se encuentra, nullptr si no existe.
     */
    T* busquedaIterativa(const T &dato);
    /**
     * @brief Recorre el árbol en orden (izquierda-raíz-derecha) y devuelve un vector con los datos.
     * @return Vector dinámico de punteros a los elementos del árbol en orden.
     */
    VectorDinamico<T*> _recorrerInorden(){
        VectorDinamico<T*> _toRet;
        inorden(_elRaiz,_toRet);
        return _toRet;
    }
    /**
     * @brief Inserta un nuevo elemento en el árbol, manteniendo su balanceo.
     * @param dato Elemento a insertar.
     * @return true si la inserción fue exitosa, false si el dato ya existía.
     */
    bool inserta(const T &dato);
    /**
     * @brief Destruye recursivamente todos los nodos del árbol.
     * @param p Referencia al puntero del nodo raíz a eliminar.
     * @post El árbol queda vacío.
     */
    void destruyeArbol(NodoArbolAVL<T>* &p);
    /**
     * @brief Devuelve el número total de elementos del árbol.
     * @return Número de elementos.
     */
    unsigned int _getNumeroDeElementos();
    /**
     * @brief Calcula y devuelve la altura del árbol.
     * @return Altura del árbol (0 si está vacío).
     */
    unsigned int _getAltura();
};

template <typename T>
int ArbolAVL<T>::insertoDato(NodoArbolAVL<T> *&xNodo, const T &dato) {
    NodoArbolAVL<T>* pNodo = xNodo;
    int d = 0;
    if (!pNodo) {
        pNodo = new NodoArbolAVL<T>(dato);
        xNodo = pNodo;
        d = 1;
    } else if (pNodo->_unDato < dato) {
        if (insertoDato(pNodo->_derecha, dato)) {
            pNodo->_elBalanceo--;
            if (pNodo->_elBalanceo == -1) {
                d = 1;
            }else if (pNodo->_elBalanceo == -2) {
                if (pNodo->_derecha->_elBalanceo == 1) {
                    rotacionDerecha(pNodo->_derecha);
                }
                rotacionIzquierda(xNodo);
            }
        }
    } else if (dato < pNodo->_unDato) {
        if (insertoDato(pNodo->_izquierda, dato)) {
            pNodo->_elBalanceo++;
            if (pNodo->_elBalanceo == 1) {
                d = 1;
            }else if (pNodo->_elBalanceo == 2) {
                if (pNodo->_izquierda->_elBalanceo == -1) {
                    rotacionIzquierda(pNodo->_izquierda);
                }
                rotacionDerecha(xNodo);
            }
        }
    }
    return d;
}
template <typename T>
bool ArbolAVL<T>::inserta(const T &dato) {
    if(buscoClave(dato, _elRaiz)){
        return false;
    }
    insertoDato(_elRaiz, dato);
    ++_elTamanio;
    return true;

}
template <typename T>
ArbolAVL<T>::ArbolAVL(const ArbolAVL<T> &copia): _elTamanio(copia._elTamanio) {
    copioAVL(_elRaiz,copia._elRaiz);
}

template <typename T>
void ArbolAVL<T>::rotacionIzquierda(NodoArbolAVL<T> *&p) {
    NodoArbolAVL<T>* _nodoQ = p;
    NodoArbolAVL<T>* _nodoR = _nodoQ->_derecha;
    p = _nodoR;
    _nodoQ->_derecha = _nodoR->_izquierda;
    _nodoR->_izquierda = _nodoQ;
    _nodoQ->_elBalanceo++;
    if (_nodoR->_elBalanceo < 0) {
        _nodoQ->_elBalanceo += -_nodoR->_elBalanceo;
    }
    _nodoR->_elBalanceo++;
    if (_nodoQ->_elBalanceo > 0) {
        _nodoR->_elBalanceo += _nodoQ->_elBalanceo;
    }
}

template <typename T>
void ArbolAVL<T>::inorden(NodoArbolAVL<T> *p, VectorDinamico<T *> &v) {
    if(p){
        inorden(p->_izquierda,v);
        v.inserta(&(p->_unDato));
        inorden(p->_derecha,v);
    }
}

template <typename T>
NodoArbolAVL<T> *ArbolAVL<T>::buscoClave(const T &dato, NodoArbolAVL<T> *pNodo) {
    if(!pNodo){
        return nullptr;
    }
    if(dato < pNodo->_unDato){
        return buscoClave(dato,pNodo->_izquierda);
    }else if(pNodo->_unDato < dato){
        return buscoClave(dato,pNodo->_derecha);
    }else{
        return pNodo;
    }
}
template <typename T>
T *ArbolAVL<T>::busquedaRecursiva(const T &dato) {
    NodoArbolAVL<T> *p = buscoClave(dato,_elRaiz);
    T* result;
    if(p){
        result = (&(p->_unDato));
        return result;
    }
    return nullptr;
}
template <typename T>
T* ArbolAVL<T>::busquedaIterativa(const T &dato) {
    NodoArbolAVL<T> *p = _elRaiz;

    while (p) {
        if (dato < p->_unDato) {
            p = p->_izquierda;
        } else if (p->_unDato < dato) {
            p = p->_derecha;
        } else {
            return &(p->_unDato);
        }
    }
    return nullptr;
}

template <typename T>
void ArbolAVL<T>::destruyeArbol(NodoArbolAVL<T> *&p) {
    if(p){
        destruyeArbol(p->_izquierda);
        destruyeArbol(p->_derecha);
        delete p;
        p = nullptr;
    }
}

template <typename T>
unsigned int ArbolAVL<T>::_getNumeroDeElementos() {
    return _elTamanio;
}
template <typename T>
unsigned int ArbolAVL<T>::alturaPrivada(NodoArbolAVL<T> *p) {
    if(!p){
        return 0;
    }
    int _alturaIzquireda = alturaPrivada(p->_izquierda);
    int _alturaDerecha = alturaPrivada(p->_derecha);
    if(_alturaIzquireda > _alturaDerecha){
        return _alturaIzquireda+1;
    }else{
        return _alturaDerecha+1;
    }
}
template <typename T>
unsigned int ArbolAVL<T>::_getAltura() {
    if(_elRaiz){
        return alturaPrivada(_elRaiz)-1;
    }else{
        return 0;
    }
}

template <typename T>
void ArbolAVL<T>::copioAVL(NodoArbolAVL<T> *&qNodo, NodoArbolAVL<T> *pNodo) {
    if(!pNodo){
        qNodo = nullptr;
        return;
    }
    qNodo = new Nodo<T>(pNodo->_unDato);
    qNodo->_elBalanceo = pNodo->_elBalanceo;
    copioAVL(qNodo->_izquierda,pNodo->_izquierda);
    copioAVL(qNodo->_derecha,pNodo->_derecha);



}
template <typename T>
void ArbolAVL<T>::rotacionDerecha(NodoArbolAVL<T> *&p) {
    NodoArbolAVL<T>* _qNodo2 = p;
    NodoArbolAVL<T>* _lNodo = _qNodo2->_izquierda;
    p = _lNodo;
    _qNodo2->_izquierda = _lNodo->_derecha;
    _lNodo->_derecha = _qNodo2;
    _qNodo2->_elBalanceo--;
    if (_lNodo->_elBalanceo > 0) {
        _qNodo2->_elBalanceo -= _lNodo->_elBalanceo;
    }
    _lNodo->_elBalanceo--;
    if (_qNodo2->_elBalanceo < 0) {
        _lNodo->_elBalanceo -= -_qNodo2->_elBalanceo;
    }
}
template <typename T>
ArbolAVL<T> &ArbolAVL<T>::operator=(const ArbolAVL<T> &copia) {
    if(this!=&copia){
        destruyeArbol(_elRaiz);
        copioAVL(_elRaiz,copia._elRaiz);
        _elTamanio = copia._elTamanio;
    }
    return (*this);
}
#endif //P3_ARBOLAVL_H
