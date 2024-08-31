#include <stdio.h>
#include <stdlib.h>
#include "Cartas.h"
#include "Tablero.h"

#define INVISIBLE (void *)1
#define HIT (void *)2
#define MISS (void *)3
Mano Cartas;

void inicializarMano() {
    Cartas.carta = (CartaFunc *)malloc(5 * sizeof(CartaFunc));
    for (int i = 0; i < 5; i++) {
        Cartas.carta[i] = disparoSimple; // Inicializar con disparo simple
    }
    Cartas.disponibles = 5;
}

void mostrarMano() {
    printf("Cartas:\n");
    for (int i = 0; i < Cartas.disponibles; i++) {
        printf("Simple | "); // Mostrar el tipo de carta
    }
    printf("\n");
}

void usarCarta() {
    int carta, x, y;
    printf("Selecciona una Carta: ");
    scanf("%d", &carta);
    printf("Selecciona Coordenadas\nX : ");
    scanf("%d", &x);
    printf("Y : ");
    scanf("%d", &y);
    Cartas.carta[carta](x, y); // Usar la carta seleccionada
}

void *disparoSimple(int x, int y) {
    if (tablero[x][y] == INVISIBLE) {
        tablero[x][y] = HIT; // Marcar acierto
        printf("HIT en (%d, %d)!\n", x, y);
    } else if (tablero[x][y] == NULL) {
        tablero[x][y] = MISS; // Marcar fallo
        printf("MISS en (%d, %d)!\n", x, y);
    } else if (tablero[x][y] == MISS) {
        printf("FALLO anterior en (%d, %d)!\n", x, y);
    } else if (tablero[x][y] == HIT) {
        printf("ACIERTO anterior en (%d, %d)!\n", x, y);
    }
    return disparoSimple;
}

void *disparoGrande(int x, int y) {
    // Código para disparo grande, similar a disparoSimple pero afectando un área mayor
    return disparoSimple;
}