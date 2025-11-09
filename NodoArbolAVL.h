//
// Created by monto on 26/10/2025.
//
/**
 * @file NodoArbolAVL.h
 * @brief Definición de la clase plantilla NodoArbolAVL, que representa un nodo individual de un árbol AVL.
 * @date 26/10/2025
 * @author Pablo Montoro
 */
#ifndef P3_NODOARBOLAVL_H
#define P3_NODOARBOLAVL_H

/**
 * @class NodoArbolAVL
 * @brief Nodo genérico para un árbol AVL.
 *
 * Esta clase plantilla representa un nodo en un árbol AVL, conteniendo un valor genérico,
 * punteros a los subárboles izquierdo y derecho, y un campo de balanceo que indica el equilibrio del nodo.
 *
 * @tparam W Tipo de dato almacenado en el nodo (por ejemplo, una clase o tipo primitivo).
 */
template <typename W>
class NodoArbolAVL{
public:
    /**
     * @brief Puntero al hijo izquierdo del nodo.
     * @details Puede ser nullptr si no hay subárbol izquierdo.
     */
    NodoArbolAVL<W> *_izquierda;
    /**
     * @brief Puntero al hijo derecho del nodo.
     * @details Puede ser nullptr si no hay subárbol derecho.
     */
    NodoArbolAVL<W> *_derecha;
    /**
     * @brief Factor de balanceo del nodo AVL.
     * @details Indica la diferencia de altura entre el subárbol izquierdo y el derecho:
     * -1, 0 o +1 en un árbol correctamente balanceado.
     */
    char _elBalanceo;
    /**
     * @brief Dato almacenado en el nodo.
     */
    W _unDato;
    /**
     * @brief Constructor que inicializa el nodo con un valor.
     * @param _unElemento Valor que se almacenará en el nodo.
     * @post Los punteros izquierdo y derecho se inicializan a nullptr, y el balanceo a 0.
     */
    NodoArbolAVL(const W &_unElemento): _izquierda(nullptr), _derecha(nullptr), _elBalanceo(0), _unDato(_unElemento){

    }
};
#endif //P3_NODOARBOLAVL_H
