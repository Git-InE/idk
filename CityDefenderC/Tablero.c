#include <stdio.h>
#include <stdlib.h>
#include "Tablero.h"

#define INVISIBLE (void *)1
#define HIT (void *)2
#define MISS (void *)3
void ***tablero;

void inicializarTablero(int tamano) {
    tablero = (void ***)malloc(tamano * sizeof(void **));
    for (int i = 0; i < tamano; i++) {
        tablero[i] = (void **)malloc(tamano * sizeof(void *));
        for (int j = 0; j < tamano; j++) {
            tablero[i][j] = NULL; // Inicializar cada celda a NULL
        }
    }
}

void mostrarTablero(int tamano) {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (tablero[j][i] == NULL) {
                printf("| "); // Celda no disparada
            } else if (tablero[j][i] == INVISIBLE) {
                printf("|B"); // Barco no visible, pero no se muestra
            } else if (tablero[j][i] == HIT) {
                printf("|X"); // Acierto
            } else if (tablero[j][i] == MISS) {
                printf("|O"); // Fallo
            }
        }
        printf("\n");
    }
}

void liberarTablero(int tamano) {
    for (int i = 0; i < tamano; i++) {
        free(tablero[i]);
    }
    free(tablero);
}

void colocarBarcos(int tamano, int numBarcos, int barcos[]) {
    for (int i = 0; i < numBarcos; i++) {
        int colocado = 0;
        while (!colocado) {
            int orientacion = rand() % 2; // 0 = horizontal, 1 = vertical
            int x = rand() % tamano;
            int y = rand() % tamano;
            int puedeColocar = 1;

            // Verificar si el barco cabe en la posición
            if (orientacion == 0) {
                if (y + barcos[i] >= tamano) continue;
                for (int j = 0; j < barcos[i]; j++) {
                    if (tablero[x][y + j] != NULL) {
                        puedeColocar = 0;
                        break;
                    }
                }
            } else {
                if (x + barcos[i] >= tamano) continue;
                for (int j = 0; j < barcos[i]; j++) {
                    if (tablero[x + j][y] != NULL) {
                        puedeColocar = 0;
                        break;
                    }
                }
            }

            // Colocar el barco
            if (puedeColocar) {
                for (int j = 0; j < barcos[i]; j++) {
                    if (orientacion == 0) {
                        tablero[x][y + j] = INVISIBLE; // Representar barco invisible con 1
                    } else {
                        tablero[x + j][y] = INVISIBLE; // Representar barco invisible con 1
                    }
                }
                colocado = 1;
            }
        }
    }
}