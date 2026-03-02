#include <iostream>
#include <string>
#include "ArbolGeneral.h"

using namespace std;

//test4//Juego de Tres en Linea (Tic-Tac-Toe) en C++

// La IA siempre jugará con 'X' y el jugador con 'O'
// No me acuerdo si debiamos hacer que empezara la IA o el jugador...

int main() {
    char tablero[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    char jugadorActual = 'X';
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
        jugadorActual = 'X';
        
        // Ciclo principal del juego
        while (true) {
            mostrarTablero(tablero);
            cout << "\nTurno del jugador " << jugadorActual << endl;
            
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
            tablero[fila - 1][columna - 1] = jugadorActual;
            movimientos++;
            
            // Verificar ganador
            char ganador = verificarGanador(tablero);
            if (ganador != ' ') {
                mostrarTablero(tablero);
                cout << "\n**********************************" << endl;
                cout << "   FELICIDADES! Jugador " <<ganador << " GANA!   " << endl;
                cout << "**********************************" << endl;
                break;
            }
            
            // Verificar empate
            if (verificarEmpate(tablero)) {
                mostrarTablero(tablero);
                cout << "\n**********************************" << endl;
                cout << "         ES UN EMPATE!            " << endl;
                cout << "**********************************" << endl;
                break;
            }
            
            // Cambiar jugador
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
        }
        
        // Preguntar si queremojugar de nuevo
        cout << "\nDesea jugar de nuevo? (S/N): ";
        cin >> jugarAgain;
        
    } while (jugarAgain == 'S' || jugarAgain == 's');
    
    cout << "\nGracias por jugar. Hasta luego!" << endl;
    
    return 0;
}

