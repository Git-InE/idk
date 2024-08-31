#ifndef CARTAS_H
#define CARTAS_H

typedef void *(*CartaFunc)(int, int);

typedef struct Mano {
    CartaFunc *carta;
    int disponibles;
} Mano;

extern Mano Cartas;

void inicializarMano();
void mostrarMano();
void usarCarta();
void *disparoSimple(int x, int y);
void *disparoGrande(int x, int y);

#endif