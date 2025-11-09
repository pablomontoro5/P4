//
// Created by Pablo Montoro on 07/10/2025.
//

#ifndef P2_LISTASIMPLEMENTEENLAZADA_H
#define P2_LISTASIMPLEMENTEENLAZADA_H
#include <iostream>
#include <stdexcept>
#include <string>
/**
 * @brief Nodo de una lista simplemente enlazada.
 * @tparam W Tipo del _unDato almacenado en el nodo.
 */
template <typename W>
class Nodo{
private:
public:
    W _elDato; ///< Dato almacenado en el nodo.
    Nodo *_siguienteNodo; ///< Puntero al siguiente nodo (o nullptr si es el último).
    /**
     * @brief Constructor que crea un nodo con un _unDato y opcionalmente enlazado a otro nodo.
     * @param _unDato Valor a almacenar en el nodo.
     * @param _elSiguiente Puntero al siguiente nodo; por defecto nullptr.
     */
    Nodo(const W &_unDato, Nodo *_elSiguiente= nullptr): _elDato(_unDato),_siguienteNodo(_elSiguiente){

    }
    /**
     * @brief Destructor del nodo.
     * @note No elimina en cascada la cadena de nodos; sólo el nodo actual.
     */
    ~Nodo(){

    }

};
/**
 * @brief Implementación genérica de una lista simplemente enlazada.
 * @tparam T Tipo de los elementos almacenados en la lista.
 */
template <typename T>
class ListaSimplementeEnlazada{
private:

//private:
    Nodo<T> *_punteroCabecera; ///< Puntero al primer nodo de la lista.
    Nodo<T> *_punteroCola; ///< Puntero al ultimo nodo de la lista.
    unsigned _elTamanio; ///< Numero de elementos en la lista.
    void _destruirLista();
public:
    /**
     * @brief Iterador simple para recorrer la lista.
     * @tparam A Tipo del elemento apuntado por el iterador.
     */
    template <typename A>
    class Iterador{
    //private:
        Nodo<A> *_unNodo; ///< Nodo actual sobre el que se posiciona el iterador.
    public:
        friend class ListaSimplementeEnlazada<T>;
        /**
         * @brief Construye un iterador opcionalmente posicionado sobre un nodo.
         * @param _aNode Puntero al nodo inicial o nullptr para fin.
         */
        Iterador(Nodo<A> *_aNode = nullptr): _unNodo(_aNode){

        }
        /**
         * @brief Indica si el iterador está en la posición final (nullptr).
         * @return true si ha alcanzado el final; false en caso contrario.
         */
        bool _esFinal(){
            return _unNodo== nullptr;
        }
        /**
         * @brief Avanza el iterador al siguiente nodo.
         * @pre El iterador no debe estar en el final.
         */
        void _esSiguiente(){
            _unNodo = _unNodo->_siguienteNodo;
        }
        /**
         * @brief Devuelve una referencia al _unDato del nodo actual.
         * @return Referencia modificable al _unDato.
         * @pre El iterador no debe estar en el final.
         */
        A& _verDato(){
            return _unNodo->_elDato;
        }
        /**
         * @brief Destructor del iterador.
         */
        ~Iterador(){

        }
    };
public:

    void _insertarPorElFinal(const T &_unDato);
    /**
     * @brief Devuelve el número de elementos de la lista.
     * @return Tamaño de la lista.
     */
    int _getTamanio(){
        return _elTamanio;
    }
    void _insertarPorDetras(Iterador<T> &_iterador, const T &_unDato);

    /**
     * @brief Accede al _unDato almacenado en el último elemento.
     * @return Referencia modificable al _unDato de la cola.
     * @throws std::invalid_argument Si la lista está vacía.
     */
    T& _elFinal(){
        if(!_punteroCola){
            throw std::invalid_argument(" *** Elemento no existente ***");
        }
        return _punteroCola->_elDato;
    }

    ListaSimplementeEnlazada(const ListaSimplementeEnlazada<T> &_unaLista);




    void _insertarPorDelante(Iterador<T> &_iterador, const T &_unDato);
    void _borrarPorElPrincipio();

    T& _elInicio(){
        if(!_punteroCabecera){
            throw std::invalid_argument(" *** Elemento no existente ***");
        }
        return _punteroCabecera->_elDato;
    }
    Iterador<T> _elIterador() const;
    void _borrarPorElFinal();

    ListaSimplementeEnlazada<T> & concatena(const ListaSimplementeEnlazada<T> &_unaLista);
    void _borrarPorElMedio(Iterador<T> &_it);


    ~ListaSimplementeEnlazada();
    ListaSimplementeEnlazada& operator=(const ListaSimplementeEnlazada<T> &_unaLista);


    /**
     * @brief Crea una lista vacía.
     */
    ListaSimplementeEnlazada(): _punteroCabecera(nullptr),_punteroCola(nullptr),_elTamanio(0){

    }

    ListaSimplementeEnlazada<T> operator+(const ListaSimplementeEnlazada<T> &_unaLista);
    /**
     * @brief Accede al _unDato almacenado en el primer elemento.
     * @return Referencia modificable al _unDato de la cabecera.
     * @throws std::invalid_argument Si la lista está vacía.
     */
    void _insertarPorElPrincipio(const T &_unDato);
};

/**
 * @brief Inserta un elemento al final.
 * @param _unDato Dato a insertar.
 */
template <typename T>
void ListaSimplementeEnlazada<T>::_insertarPorElFinal(const T &_unDato) {
    Nodo<T> *_nuevoNodo=new Nodo<T>(_unDato,nullptr);
    if(_punteroCola!=nullptr){
        _punteroCola->_siguienteNodo = _nuevoNodo;
    }
    if(_punteroCabecera== nullptr){
        _punteroCabecera = _nuevoNodo;
    }
    _punteroCola = _nuevoNodo;
    ++_elTamanio;
}
/**
 * @brief Elimina el primer elemento.
 */
template <typename T>
void ListaSimplementeEnlazada<T>::_borrarPorElPrincipio() {
    if(_punteroCabecera!= nullptr){
        --_elTamanio;
        Nodo<T> *_borrarNodo= _punteroCabecera;
        _punteroCabecera = _punteroCabecera->_siguienteNodo;
        delete _borrarNodo;
        if(_punteroCabecera== nullptr){
            _punteroCola = nullptr;
        }
    }
}
/**
 * @brief Destructor: destruye la lista completa.
 */
template <typename T>
ListaSimplementeEnlazada<T>::~ListaSimplementeEnlazada() {
    _destruirLista();
}

/**
 * @brief Elimina el último elemento.
 */
template <typename T>
void ListaSimplementeEnlazada<T>::_borrarPorElFinal() {
    Nodo<T> *_anteriorNodo = nullptr;
    if(_punteroCabecera!=_punteroCola){
        --_elTamanio;
        _anteriorNodo = _punteroCabecera;
        while(_anteriorNodo->_siguienteNodo!=_punteroCola){
            _anteriorNodo = _anteriorNodo->_siguienteNodo;
        }
        delete _punteroCola;
        _punteroCola = _anteriorNodo;
        _anteriorNodo->_siguienteNodo = nullptr;
    }else{
        if(_punteroCabecera!= nullptr){
            delete _punteroCabecera;
            _punteroCabecera = nullptr;
            _punteroCola = nullptr;
            _elTamanio = 0;
        }
    }
}
/**
 * @brief Inserta después del nodo señalado por el iterador.
 * @param _iterador Iterador de referencia.
 * @param _unDato Dato a insertar.
 */
template <typename T>
void ListaSimplementeEnlazada<T>::_insertarPorDetras(ListaSimplementeEnlazada::Iterador<T> &_iterador, const T &_unDato) {
    if(!_iterador._esFinal()){
        ++_elTamanio;
        Nodo<T> *_nuevoNodo = new Nodo<T>(_unDato,_iterador._unNodo->_siguienteNodo);
        _iterador._unNodo->_siguienteNodo = _nuevoNodo;
        if(_iterador._unNodo==_punteroCola){
            _punteroCola = _nuevoNodo;
        }
    }
}
/**
 * @brief Operador de asignación: libera el contenido actual y copia otra lista.
 * @param _unaLista Lista origen.
 * @return Referencia a *this.
 */
template <typename T>
ListaSimplementeEnlazada<T> &ListaSimplementeEnlazada<T>::operator=(const ListaSimplementeEnlazada<T> &_unaLista) {
    if(this!=&_unaLista){
        _destruirLista();
        if(_punteroCabecera){
            Nodo<T> *_borrarAux = _punteroCabecera;
            while(_borrarAux!= nullptr){
                _punteroCabecera = _punteroCabecera->_siguienteNodo;
                delete _borrarAux;
                _borrarAux = _punteroCabecera;
            }
            _punteroCola = nullptr;
        }
        Nodo<T> *i = _unaLista._punteroCabecera;
        _punteroCabecera = _punteroCola = 0;
        _elTamanio = _unaLista._elTamanio;
        while(i){
            Nodo<T> *nuevo = new Nodo<T>(i->_elDato, nullptr);
            if(_punteroCola!= nullptr){
                _punteroCola->_siguienteNodo = nuevo;
            }
            if(_punteroCabecera== nullptr){
                _punteroCabecera=nuevo;
            }
            _punteroCola = nuevo;
            i = i->_siguienteNodo;
        }
    }
    return (*this);
}
/**
 * @brief Libera todos los nodos y deja la lista vacía.
 */
template <typename T>
void ListaSimplementeEnlazada<T>::_destruirLista() {
    if(_punteroCabecera!= nullptr){
        Nodo<T> *_borrarNodo= _punteroCabecera;
        while(_borrarNodo!= nullptr){
            _punteroCabecera = _punteroCabecera->_siguienteNodo;
            delete _borrarNodo;
            _borrarNodo = _punteroCabecera;
        }
        _punteroCola = nullptr;
        _elTamanio = 0;
    }
}




/**
 * @brief Inserta antes del nodo señalado por el iterador.
 * @param _iterador Iterador de referencia.
 * @param _unDato Dato a insertar.
 */
template <typename T>
void ListaSimplementeEnlazada<T>::_insertarPorDelante(ListaSimplementeEnlazada::Iterador<T> &_iterador, const T &_unDato) {
    if(_iterador._esFinal()){
        _insertarPorElFinal(_unDato);
    }else{
        if(_iterador._unNodo==_punteroCabecera){
            _insertarPorElPrincipio(_unDato);
            return ;
        }
        ++_elTamanio;
        Nodo<T> *_elAnterior = nullptr;
        _elAnterior = _punteroCabecera;
        while(_elAnterior->_siguienteNodo!=_iterador._unNodo){
            _elAnterior = _elAnterior->_siguienteNodo;
        }
        Nodo<T> *_nuevoNodo= new Nodo<T>(_unDato,_iterador._unNodo);
        _elAnterior->_siguienteNodo = _nuevoNodo;
    }
}


/**
 * @brief Elimina el elemento apuntado por el iterador (caso general).
 * @param _it Iterador posicionado sobre el elemento a borrar.
 */
template <typename T>
void ListaSimplementeEnlazada<T>::_borrarPorElMedio(ListaSimplementeEnlazada::Iterador<T> &_it) {
    Nodo<T> *_anteriorNodo;
    if(!_it._esFinal()){
        --_elTamanio;
        if(_it._unNodo==_punteroCabecera){
            _borrarPorElPrincipio();
            return ;
        }
        if(_it._unNodo==_punteroCola){
            _borrarPorElFinal();
            return ;
        }
        _anteriorNodo = _punteroCabecera;
        while(_anteriorNodo->_siguienteNodo!=_it._unNodo){
            _anteriorNodo = _anteriorNodo->_siguienteNodo;
        }
        _anteriorNodo->_siguienteNodo = _it._unNodo->_siguienteNodo;
        delete _it._unNodo;
    }
}

/**
 * @brief Concatena los elementos de otra lista al final de la lista actual.
 *
 * Inserta, en orden, todos los elementos de la lista pasada como parámetro
 * al final de la lista actual. La lista origen no se modifica.
 *
 * @tparam T Tipo de los elementos almacenados en la lista.
 * @param _unaLista Lista cuyos elementos se añadirán al final de la lista actual.
 * @return Referencia a la lista actual después de la concatenación (*this).
 */

template <typename T>
ListaSimplementeEnlazada<T> &ListaSimplementeEnlazada<T>::concatena(const ListaSimplementeEnlazada<T> &_unaLista) {
    Nodo<T>* actual = _unaLista._punteroCabecera;
    while (actual) {
        _insertarPorElFinal(actual->_elDato);
        actual = actual->_siguienteNodo;
    }
    return *this;
}

/**
 * @brief Constructor de copia: crea una lista con los mismos elementos y orden que otra.
 * @param _unaLista Lista a copiar.
 */
template <typename T>
ListaSimplementeEnlazada<T>::ListaSimplementeEnlazada(const ListaSimplementeEnlazada<T> &_unaLista) {
    Nodo<T> *i = _unaLista._punteroCabecera;
    _punteroCabecera = _punteroCola = 0;
    _elTamanio = _unaLista._elTamanio;
    while(i){
        Nodo<T> *nuevo = new Nodo<T>(i->_elDato, nullptr);
        if(_punteroCola!= nullptr){
            _punteroCola->_siguienteNodo = nuevo;
        }
        if(_punteroCabecera== nullptr){
            _punteroCabecera=nuevo;
        }
        _punteroCola = nuevo;
        i = i->_siguienteNodo;
    }
}
/**
 * @brief Devuelve un iterador posicionado al inicio de la lista.
 * @return Iterador al primer nodo o iterador final si está vacía.
 */
template <typename T>
ListaSimplementeEnlazada<T>::Iterador<T> ListaSimplementeEnlazada<T>::_elIterador() const {
    return Iterador(_punteroCabecera);
}

/**
 * @brief Operador +: devuelve una nueva lista con la concatenación de ambas.
 * @param _unaLista Lista a añadir al final.
 * @return Nueva lista con los elementos de *this seguidos de los de _unaLista.
 */
template <typename T>
ListaSimplementeEnlazada<T> ListaSimplementeEnlazada<T>::operator+(const ListaSimplementeEnlazada<T> &_unaLista) {
    return this->concatena();
}
/**
 * @brief Inserta un elemento al principio.
 * @param _unDato Dato a insertar.
 */
template <typename T>
void ListaSimplementeEnlazada<T>::_insertarPorElPrincipio(const T &_unDato) {
    Nodo<T> *_nuevoNodo=new Nodo<T>(_unDato,_punteroCabecera);
    if(_punteroCola==nullptr){
        _punteroCola = _nuevoNodo;
    }
    _punteroCabecera = _nuevoNodo;
    ++_elTamanio;
}
#endif //P2_LISTASIMPLEMENTEENLAZADA_H
