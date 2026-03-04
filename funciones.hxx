/*
Juego: Tres en línea (Tic-Tac-Toe)

Reglas:
1. Gana el jugador que logre ocupar 3 posiciones en línea,
   ya sea vertical, horizontal o diagonalmente.
2. Puede haber empate si ningún jugador logra formar una línea
   y todas las posiciones del tablero están ocupadas.
3. Debe jugar un jugador por turno (no se permiten jugadas consecutivas).

Resultados:
1. Ganar:
   1.1. Victoria vertical
   1.2. Victoria horizontal
   1.3. Victoria diagonal
2. Empate

Objetivo:
Obtener tres símbolos consecutivos en línea antes que el oponente.

Esfuerzo del jugador:
Cada jugador debe analizar el estado actual del tablero y tomar
decisiones estratégicas, ya que cada movimiento afecta el estado
del juego y las posibilidades de victoria o empate.
*/

#include "funciones.h"

// Función para mostrar el tablero
void mostrarTablero(char** tablero) {
    cout << "\n  1   2   3" << endl;
    cout << "  +---+---+---+" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " | " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << " |" << endl;
        cout << "  +---+---+---+" << endl;
    }
}

// Función para verificar si hay un ganador
char verificarGanador(char** tablero) {
    // Verificar filas
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
            return tablero[i][0];
        }
    }
    
    // Verificar columnas
    for (int j = 0; j < 3; j++) {
        if (tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j]) {
            return tablero[0][j];
        }
    }
    
    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
        return tablero[0][0];
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
        return tablero[0][2];
    }
    
    return ' ';
}

// Función para verificar si hay empate
bool verificarEmpate(char** tablero) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

char** copiarTableroDinamicamente(char tablero[3][3]) {

    char** copia = new char*[3];

    for (int i = 0; i < 3; i++) {
        copia[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            copia[i][j] = tablero[i][j];
        }
    }

    return copia;
}

void liberarTablero(char** tablero){
    for(int i = 0; i < 3; i++){
        delete[] tablero[i];
    }
    delete[] tablero;
}

// Función para generar el espacio de estados (Árbol con todos los estados posibles)
// Si el turno es verdadero significa que juega la IA
template< class T >
void funcionSucesor(NodoGeneral<T>* tableroActual, bool turno){

    //Caso base: si ya no se hay más jugadas, devolverse al nodo anterior para verificar si puede crear más posibilidades de juego
    if( pruebaTerminal( tableroActual->obtenerDato() ) ){
        return;
    }

    //Acercarse al problema: Llegar a un estado terminal del juego en una rama
    // Como no se ha llegado a un estado terminal (ganar o empatar) crear todas las jugadas posibles para ese nodo
    vector< pair<int,int> > posiblesJugadas = obtenerJugadas(tableroActual->obtenerDato());

    // Verificar si se va a construir las jugadas posibles de la IA o el jugador
    // Dependiendo el caso se contruyen los nuevos tableros y se llama recursivamente a la función para que para todos los hijos creados se creen también sus respectivos tableros 
    for (size_t i = 0; i < posiblesJugadas.size(); ++i){

        // Copiar el tablero actual
        T original = tableroActual->obtenerDato();
        T nuevo = new char*[3];

        for (int f = 0; f < 3; f++) {
            nuevo[f] = new char[3];

            for (int c = 0; c < 3; c++) {
                nuevo[f][c] = original[f][c];
            }
        }

        int fila = posiblesJugadas[i].first;
        int columna = posiblesJugadas[i].second;

        // Aplicar jugada dependiendo si es el turno de la IA o el jugador
        nuevo[fila][columna] = (turno ? 'X' : 'O');

        // Crear hijo
        tableroActual->adicionarDesc(nuevo);

        // Obtener el último hijo creado
        NodoGeneral<T>* hijo = tableroActual->obtenerDesc().back();
        hijo->fijarJugada({fila, columna});

        // Llamada recursiva cambiando turno
        funcionSucesor(hijo, !turno);
    }
}

template< class T >
vector< pair<int,int> > obtenerJugadas(T tableroActual){
    // Para todo espacio vacio en el tablero hay una jugada posible
    // Se quiere obtener las posiciones del tablero en que la IA o el jugador puede poner su ficha

    vector< pair<int,int> > posiblesJugadas;

    for (int fila = 0; fila < 3; fila++) {
        for (int columna = 0; columna < 3; columna++) {

            if (tableroActual[fila][columna] == ' ') {
                posiblesJugadas.push_back({fila, columna});
            }
        }
    }

    return posiblesJugadas;
}

 bool pruebaTerminal(char** tablero){
    if( (verificarGanador(tablero) != ' ') || verificarEmpate(tablero)) return true;

    return false;
 }

// La funcion utilidad da un valor numérico a una configuración final del juego
// Evalúa el estado desde el punto de vista de la IA ('X')
template< class T >
int funcionUtilidad(T tableroActual){

    // Verificar si alguien ganó
    char ganador = verificarGanador(tableroActual);

    if(ganador == 'X'){
        return 1;   // La IA gana
    }
    else if(ganador == 'O'){
        return -1;  // El jugador humano gana
    }

    return 0;   // Si nadie gana, hay empate
}

template<class T>
int minimaxRecursivo(NodoGeneral<T>* nodo, bool turnoIA, int alfa, int beta){

    // Si es hoja → evaluar utilidad
    if(nodo->esHoja()){
        return funcionUtilidad(nodo->obtenerDato());
    }

    if(turnoIA){ // MAX

        int mejorValor = -1000;

        typename std::list< NodoGeneral<T>* >::iterator it;
        for(it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); ++it){

            int valor = minimaxRecursivo(*it, false, alfa, beta);
            mejorValor = max(mejorValor, valor);

            alfa = max(alfa, mejorValor);

            if(beta <= alfa)
                break; // PODA
        }

        return mejorValor;
    }
    else{ // MIN

        int peorValor = 1000;

        typename std::list< NodoGeneral<T>* >::iterator it;
        for(it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); ++it){

            int valor = minimaxRecursivo(*it, true, alfa, beta);
            peorValor = min(peorValor, valor);

            beta = min(beta, peorValor);

            if(beta <= alfa)
                break; // PODA
        }

        return peorValor;
    }
}

template< class T >
std::pair<int,int> minimaxPodaAlfaBeta(ArbolGeneral<T>& arbolDeJuego, bool turnoIA){

    NodoGeneral<T>* raiz = arbolDeJuego.obtenerRaiz();

    int alfa = -1000;
    int beta = 1000;

    int mejorValor = -1000;
    std::pair<int,int> mejorJugada = {-1, -1};

    // Evaluar cada hijo de la raíz
    typename std::list< NodoGeneral<T>* >::iterator it;
    for(it = raiz->obtenerDesc().begin(); it != raiz->obtenerDesc().end(); ++it){

        int valor = minimaxRecursivo(*it, false, alfa, beta);

        if(valor > mejorValor){
            mejorValor = valor;
            mejorJugada = (*it)->obtenerJugada(); 
        }

        alfa = std::max(alfa, mejorValor);

        if(beta <= alfa)
            break;
    }

    return mejorJugada;
}
