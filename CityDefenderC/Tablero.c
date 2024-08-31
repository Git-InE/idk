#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ***tablero;
// ***
void inicializarTablero(int tamano) {
    tablero = (void ***)malloc(tamano * sizeof(void **));
    for (int i = 0; i < tamano; i++) {
        tablero[i] = (void **)malloc(tamano * sizeof(void *));
        for (int j = 0; j < tamano; j++) {
            tablero[i][j] = NULL; // Inicializar cada celda a NULL
        }
    }
}
// ***
// Parametro 1 : int tamano
// ***
// Inicializa el tablero cuadrado para un tamaño dado, asignando memoria para cada celda.
// ***

void mostrarTablero() {
    for (int i = 0; i < 11; i++) { // Ajustar según tamaño
        for (int j = 0; j < 11; j++) {
            // Mostrar estado de cada celda
            if (tablero[i][j] == NULL) {
                printf("|  ");
            } else if (tablero[i][j] == (void *)1) {
                printf("|X "); // Acierto
            } else {
                printf("|O "); // Fallo
            }
        }
        printf("\n");
    }
}
// ***
// ***
// Muestra el estado actual del tablero por pantalla. Las celdas pueden estar vacías,
// contener un acierto (X) o un fallo (O).
// ***

void liberarTablero(int tamano) {
    for (int i = 0; i < tamano; i++) {
        free(tablero[i]);
    }
    free(tablero);
}
// ***
// Parametro 1 : int tamano
// ***
// Libera la memoria asignada al tablero, evitando fugas de memoria.
// ***
