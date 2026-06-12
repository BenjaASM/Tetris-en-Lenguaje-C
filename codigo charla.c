#include <stdio.h>
#include <stdbool.h>

#define FILAS 20
#define COLUMNAS 10

// Representación del tablero (0 = vacío, 1 = ocupado)
int tablero[FILAS][COLUMNAS] = {0};

// Estructura para simular una pieza simple (por ejemplo, un bloque de 1x2 horizontal)
typedef struct {
    int ancho;
    int alto;
} Pieza;

// Función para verificar si una pieza cabe en una posición específica
bool esMovimientoValido(int fila, int col, Pieza p) {
    if (col + p.ancho > COLUMNAS || fila + p.alto > FILAS) return false;
    
    // Verificar colisiones con bloques ya existentes
    for (int i = 0; i < p.alto; i++) {
        for (int j = 0; j < p.ancho; j++) {
            if (tablero[fila + i][col + j] == 1) return false;
        }
    }
    return true;
}

// DFS con Backtracking para buscar la profundidad máxima donde colocar la pieza
void buscarMejorPosicionDFS(int fila, int col, Pieza p, int* maxFila) {
    // Concepto transversal: Recursividad
    // Si ya no es válido el movimiento hacia abajo, llegamos al fondo en esta columna
    if (!esMovimientoValido(fila + 1, col, p)) {
        if (fila > *maxFila) {
            *maxFila = fila; // Registramos la posición más profunda encontrada
        }
        return; 
    }

    // Colocamos provisionalmente la pieza (Simulación en el Grafo de Estados)
    for (int i = 0; i < p.alto; i++)
        for (int j = 0; j < p.ancho; j++) tablero[fila + i][col + j] = 1;

    // Profundizamos en el siguiente nivel (Mover hacia abajo)
    buscarMejorPosicionDFS(fila + 1, col, p, maxFila);

    // Concepto transversal: Backtracking (Limpiamos el tablero al regresar)
    for (int i = 0; i < p.alto; i++)
        for (int j = 0; j < p.ancho; j++) tablero[fila + i][col + j] = 0;
}

int main() {
    Pieza bloque = {2, 1}; // Pieza de 2x1 de ancho/alto
    int mejorFila = 0;

    // Colocamos un obstáculo artificial en la fila 15
    tablero[15][3] = 1;

    printf("Iniciando DFS para encontrar la mejor jugada en la columna 3...\n");
    buscarMejorPosicionDFS(0, 3, bloque, &mejorFila);

    printf("Resultado DFS: La pieza puede descender de forma segura hasta la fila: %d\n", mejorFila);
    return 0;
}