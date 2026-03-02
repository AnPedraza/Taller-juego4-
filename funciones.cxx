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