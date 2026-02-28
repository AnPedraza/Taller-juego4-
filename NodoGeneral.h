#ifndef __NODOGENERAL_H__
#define __NODOGENERAL_H__

#include <list>
#include <vector>

template< class T >
class NodoGeneral{
  protected:
    T dato;
    std::list< NodoGeneral<T>* > desc;
  public:
    NodoGeneral();
    ~NodoGeneral();
    T& obtenerDato();
    void fijarDato(T& val);
    std::list< NodoGeneral<T>* >& obtenerDesc(); 
    void fijarDesc(std::list< NodoGeneral<T>* >& ndesc);
    void limpiarLista();
    void adicionarDesc(T& nval);
    bool eliminarDesc(T& val);
    bool esHoja();
    int altura();
    void preOrden();
    void posOrden();
    bool insertarNodo(T padre, T n);
    bool eliminarNodo(T n); 
    bool buscar(T n);
    void tamano(unsigned int &tamanio);
    bool camino(T dato,std::vector<NodoGeneral<T>*> &vector);
};

#include "NodoGeneral.hxx"

#endif

