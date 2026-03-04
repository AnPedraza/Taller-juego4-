#include "funciones.h"

typedef char** T;

//test4//Juego de Tres en Linea (Tic-Tac-Toe) en C++

// La IA siempre jugará con 'X' y el jugador con 'O'
// Siempre empieza el jugador humano y establece el estado inicial

int main() {
    char tablero[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    char jugadorActual = 'O';
    int fila, columna;
    int movimientos = 0;
    char jugarAgain;
    
    cout << "========================================" << endl;
    cout << "       TRES EN LINEA (TIC-TAC-TOE)      " << endl;
    cout << "========================================" << endl;
    
    do {
        // Reiniciar el tablero
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                tablero[i][j] = ' ';
            }
        }
        movimientos = 0;
        jugadorActual = 'O'; // Siempre empieza el humano
        
        // Ciclo principal del juego
        while (true) {
            char** temp = copiarTableroDinamicamente(tablero);
            mostrarTablero(temp);
            liberarTablero(temp);

            cout << "\nTurno del jugador " << jugadorActual << endl;
            
            if (jugadorActual == 'O') {
                // Solicitar posición
                cout << "Ingrese fila (1-3): ";
                cin >> fila;
                cout << "Ingrese columna (1-3): ";
                cin >> columna;
                
                // Validar posición
                if (fila < 1 || fila > 3 || columna < 1 || columna > 3) {
                    cout << "\n!!! Posicion invalida. Intente de nuevo. !!!" << endl;
                    continue;
                }
                
                if (tablero[fila - 1][columna - 1] != ' ') {
                    cout << "\n!!! Esta posicion ya esta ocupada. Intente de nuevo. !!!" << endl;
                    continue;
                }
                
                // Realizar movimiento
                tablero[fila - 1][columna - 1] = 'O';
                movimientos++;
            }
            else { 
                // Turno de la IA
                ArbolGeneral<T> arbolDeBusqueda;

                NodoGeneral<T>* raiz = new NodoGeneral<T>;

                T tableroTemp = copiarTableroDinamicamente(tablero);
                raiz->fijarDato(tableroTemp);

                liberarTablero(tableroTemp);

                arbolDeBusqueda.fijarRaiz(raiz);

                // Generar espacio de estados desde el turno de la IA
                funcionSucesor(arbolDeBusqueda.obtenerRaiz(), true);

                // Obtener mejor jugada para la IA
                std::pair<int,int> mejorJugada = minimaxPodaAlfaBeta(arbolDeBusqueda,true);

                tablero[mejorJugada.first][mejorJugada.second] = 'X';
            }
            
            // Verificar ganador
            char** tempGanador = copiarTableroDinamicamente(tablero);
            char ganador = verificarGanador(tempGanador);
            liberarTablero(tempGanador);
            if (ganador != ' ') {
                char** tempMostrar = copiarTableroDinamicamente(tablero);
                mostrarTablero(tempMostrar);
                liberarTablero(tempMostrar);
                cout << "\n**********************************" << endl;
                cout << "   FELICIDADES! Jugador " << ganador << " GANA!   " << endl;
                cout << "**********************************" << endl;
                break;
            }
            
            // Verificar empate
            char** tempEmpate = copiarTableroDinamicamente(tablero);
            bool empate = verificarEmpate(tempEmpate);
            liberarTablero(tempEmpate);

            if(empate){
                char** tempMostrar = copiarTableroDinamicamente(tablero);
                mostrarTablero(tempMostrar);
                liberarTablero(tempMostrar);
                cout << "\n**********************************" << endl;
                cout << "         ES UN EMPATE!            " << endl;
                cout << "**********************************" << endl;
                break;
            }
            
            // Cambiar jugador
            jugadorActual = (jugadorActual == 'O') ? 'X' : 'O';
        }
        
        // Preguntar si queremojugar de nuevo
        cout << "\nDesea jugar de nuevo? (S/N): ";
        cin >> jugarAgain;
        
    } while (jugarAgain == 'S' || jugarAgain == 's');
    
    cout << "\nGracias por jugar. Hasta luego!" << endl;
    
    return 0;
}