#ifndef TABLERO_H
#define TABLERO_H

extern void ***tablero;

void inicializarTablero(int tamano);
void mostrarTablero(int tamano);
void liberarTablero(int tamano);
void colocarBarcos(int tamano, int numBarcos, int barcos[]);

#endif