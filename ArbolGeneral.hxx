#include "ArbolGeneral.h"
#include <queue>
#include <list>

template <class T>
ArbolGeneral<T>::ArbolGeneral() {
    this->raiz = NULL;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T val) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>;
    nodo->fijarDato(val);
    this->raiz = nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
    delete this->raiz;
    this->raiz = NULL;
}

template <class T>
bool ArbolGeneral<T>::esVacio() {
    return this->raiz == NULL;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
    return this->raiz;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
    this->raiz = nraiz;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(T padre, T n) {
    if (this->esVacio()) {
	NodoGeneral <T>* nodo = new NodoGeneral<T>;
        nodo->fijarDato(n);
        this->fijarRaiz(nodo); 
        return true;
    }else{
        return (this->raiz)->insertarNodo(padre,n);
    }
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(T n) {
    if (this->esVacio()) {
	return false;
    } else if((this->raiz->obtenerDato()) == n) {
	delete this->raiz;
	this->raiz = NULL;
	return true;
    } else {
	return (this -> raiz -> eliminarNodo(n));
    }
}

template <class T>
bool ArbolGeneral<T>::buscar(T n) {
    if (this->esVacio()) {
	return false;
    }else{
	return (this -> raiz -> buscar(n));
    }
}

template <class T>
int ArbolGeneral<T>::altura() {
    if (this->esVacio()) {
      return -1;
    } else {
      return (this->raiz)->altura();
    }
}

template <class T>
unsigned int ArbolGeneral<T>::tamano() {
    if (this->esVacio()) {
	return 0;
    }else{
	unsigned int tamanio = 0;
	this->raiz->tamano(tamanio);
	return tamanio;
    }
}

template <class T>
void ArbolGeneral<T>::preOrden() {
    if (!this->esVacio()){
        (this->raiz)->preOrden();
    }
}

template <class T>
void ArbolGeneral<T>::posOrden() {
    if(!this->esVacio()){
	(this->raiz)->posOrden();
    }
}

template <class T>
void ArbolGeneral<T>::nivelOrden() {
    if (this->esVacio()) return;

    std::queue<NodoGeneral<T>* > nivel;
    nivel.push(this->raiz);

    while(!nivel.empty()){
	NodoGeneral<T> *nodo = nivel.front();
	nivel.pop();
	std::cout <<nodo -> obtenerDato() << " ";
	    
	std::list< NodoGeneral<T>* > hijos = nodo->obtenerDesc();
	typename std::list< NodoGeneral<T>* >::iterator it;
	for (it = hijos.begin(); it != hijos.end(); it++){
	    nivel.push(*it);
	}
    }
}

template <class T>
bool ArbolGeneral<T>::camino(T dato,std::vector<NodoGeneral<T>*> &vector){
    if(!this->esVacio()){
	return (this->raiz)->camino(dato,vector);
    }
    return false;
}

template <class T>
int ArbolGeneral<T>::ancho() {
    if (this->esVacio()) return 0;

    int ancho = 0;

    std::queue<NodoGeneral<T>* > nivel;
    nivel.push(this->raiz);

    while(!nivel.empty()){

	int actual = (int)nivel.size();
	if(actual > ancho) ancho = actual;

	for(int i = 0; i < actual; ++i) {
	
	    NodoGeneral<T> *nodo = nivel.front();
	    nivel.pop();
	    
	    std::list< NodoGeneral<T>* > hijos = nodo->obtenerDesc();
	    typename std::list< NodoGeneral<T>* >::iterator it;
	    for (it = hijos.begin(); it != hijos.end(); it++){
	        nivel.push(*it);
	    }
	}
    }

    return ancho;
}