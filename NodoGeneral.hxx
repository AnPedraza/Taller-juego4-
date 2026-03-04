#include "NodoGeneral.h"
#include <list>

template<class T>
NodoGeneral<T>::NodoGeneral() {
    this->desc.clear();
    this->dato = nullptr;
}

template<class T>
NodoGeneral<T>::~NodoGeneral() {

    for (auto hijo : this->desc)
        delete hijo;

    this->desc.clear();

    if (this->dato != nullptr) {
        for (int i = 0; i < 3; ++i) {
            delete[] this->dato[i];
        }

        delete[] this->dato;
    }
}

template< class T >
T& NodoGeneral<T>::obtenerDato() {
    return this->dato;
}

template<class T>
void NodoGeneral<T>::fijarDato(T& val) {
    this->dato = new char*[3];
    for (int i = 0; i < 3; ++i) {
        this->dato[i] = new char[3];
        for (int j = 0; j < 3; ++j) {
            this->dato[i][j] = val[i][j];
        }
    }
}

template< class T >
void NodoGeneral<T>::fijarJugada(std::pair<int,int> jug){
    this->jugada = jug;
}

template< class T >
std::pair<int,int> NodoGeneral<T>::obtenerJugada(){
    return this->jugada;
}

template< class T >
typename std::list< NodoGeneral<T>* >& NodoGeneral<T>::obtenerDesc(){
    return this->desc;
}

template< class T >
void NodoGeneral<T>::fijarDesc(std::list< NodoGeneral<T>* >& ndesc){
    this->desc = ndesc;
}

template< class T >
void NodoGeneral<T>::limpiarLista() {
    this->desc.clear();
}

template< class T >
void NodoGeneral<T>::adicionarDesc(T& nval) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>;
    
    nodo->fijarDato(nval);
    this->desc.push_back(nodo);
}

template< class T >
bool NodoGeneral<T>::eliminarDesc(T& val) {
    // buscar el nodo con el valor dado
    typename std::list< NodoGeneral<T>* >::iterator it;
    NodoGeneral<T> *aux;
    bool eliminado = false;

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        aux = *it;
        if (aux->obtenerDato() == val)
            break;
    }

    // si lo encontramos, eliminarlo
    if (it != this->desc.end()) {
        delete *it;
        this->desc.erase(it);
        eliminado = true;
    }

    return eliminado;
}

template< class T >
bool NodoGeneral<T>::esHoja() {
  return this->desc.size() == 0;
}

template< class T >
int NodoGeneral<T>::altura() {
  int alt = -1;

  if (this->esHoja()) {
    alt = 0;
  } else {
    int alth;
    typename std::list< NodoGeneral<T>* >::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
      alth = (*it)->altura();
      if (alt < alth+1)
        alt = alth+1;
    }
  }

  return alt;
}

template< class T >
void NodoGeneral<T>::preOrden() {
  std::cout << this->dato << " ";
  typename std::list< NodoGeneral<T>* >::iterator it;
  for (it = this->desc.begin(); it != this->desc.end(); it++) {
    (*it)->preOrden();
  }
}

template< class T >
void NodoGeneral<T>::posOrden() {
    typename std::list< NodoGeneral<T>* >::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
      (*it)->posOrden();
    }
    std::cout << this->dato << " ";
}

template< class T >
bool NodoGeneral<T>::insertarNodo(T padre, T n) {
    if(this->obtenerDato() == padre){
	this->adicionarDesc(n);
        return true;
    }else{
	typename std::list< NodoGeneral<T>* >::iterator it;
        for (it = this->desc.begin(); it != this->desc.end(); it++){
	    if((*it)->insertarNodo(padre,n)){
		return true;
	    }
	}
	return false;
    }
}

template< class T >
bool NodoGeneral<T>::eliminarNodo(T n) {
    typename std::list< NodoGeneral<T>* >::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++){
	if((*it)->obtenerDato() == n){
	    NodoGeneral<T>* nodo = *it;
	    this -> desc.erase(it);
	    delete nodo;
	    return true;
	}else{
	    if((*it)->eliminarNodo(n)){
		return true;
	    }
	}
    }
    return false;
}

template< class T >
bool NodoGeneral<T>::buscar(T n) {
    if(this->obtenerDato() == n){
        return true;
    }else{
	typename std::list< NodoGeneral<T>* >::iterator it;
        for (it = this->desc.begin(); it != this->desc.end(); it++){
	    if((*it)->buscar(n)){
		return true;
	    }
	}
	return false;
    }
}

template <class T>
void NodoGeneral<T>::tamano(unsigned int &tamanio) {
    tamanio ++;
    typename std::list< NodoGeneral<T>* >::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++){
	(*it) -> tamano(tamanio);
    }
}

template <class T>
bool NodoGeneral<T>::camino(T dato,std::vector<NodoGeneral<T>*> &vector){
    
    if(this->obtenerDato() == dato){
	vector.push_back(this);
	return true;
    }

    typename std::list<NodoGeneral<T>*>::iterator it;
    for(it=this->desc.begin(); it!= this->desc.end();it++){
	if((*it)->camino(dato,vector)){
	    vector.push_back(this);
	    return true;
	}
    }

    return false;
}
