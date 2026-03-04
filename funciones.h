#ifndef __FUNCIONES__H__
#define __FUNCIONES__H__

#include <iostream>
#include <string>
#include "ArbolGeneral.h"
#include <utility>
#include <vector>
#include "NodoGeneral.h"

using namespace std;

void mostrarTablero(char** tablero);
char verificarGanador(char** tablero);
bool verificarEmpate(char** tablero);
char** copiarTableroDinamicamente(char tablero[3][3]);
void liberarTablero(char** tablero);

template< class T >
void funcionSucesor(NodoGeneral<T>* tableroActual, bool turno);

template< class T >
vector< pair<int,int> > obtenerJugadas(T tableroActual);

bool pruebaTerminal(char** tablero);

template< class T >
int funcionUtilidad(T tableroActual);

template<class T>
int minimaxRecursivo(NodoGeneral<T>* nodo, bool turnoIA, int alfa, int beta);

template< class T >
std::pair<int,int> minimaxPodaAlfaBeta(ArbolGeneral<T>& arbolDeJuego, bool turnoIA);

#include "funciones.hxx"

#endif // __FUNCIONES__H__

// eof - funciones.h