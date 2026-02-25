#include <iostream>
#include <string>


// Test
//test4//Juego de Tres en Linea (Tic-Tac-Toe) en C++
using namespace std;
//Creacion de codigo//
// Función para mostrar el tablero
void mostrarTablero(char tablero[3][3]) {
    cout << "\n  1   2   3" << endl;
    cout << "  +---+---+---+" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " | " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << " |" << endl;
        cout << "  +---+---+---+" << endl;
    }
}

// Función para verificar si hay un ganador
char verificarGanador(char tablero[3][3]) {
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

// Función para verificar si hayempate
bool verificarEmpate(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

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
