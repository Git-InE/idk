#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tablero.h"
#include "Cartas.h"

// Declaraciones de estructuras y funciones

extern void *** tablero ;

typedef void *(*CartaFunc)(int, int);

typedef struct Mano {
    CartaFunc *carta;
    int disponibles;
} Mano;

Mano Cartas;

void inicializarTablero(int tamano);
void mostrarTablero();
void liberarTablero(int tamano);
void inicializarMano();
void mostrarMano();
void usarCarta();

// Funciones de disparo
void *disparoSimple(int x, int y);
void *disparoGrande(int x, int y);
// (Declaraciones de otras funciones de disparo aquí...)

int main() {
    int tamano, opcion;
    srand(time(NULL)); // Inicializar semilla para números aleatorios

    printf("Selecciona la Dificultad:\n");
    printf("1. Facil -> 11 X 11, 5 Barcos\n");
    printf("2. Medio -> 17 X 17, 7 Barcos\n");
    printf("3. Dificil -> 21 X 21, 9 Barcos\n");
    printf("Ingrese un numero: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            tamano = 11;
            // Configurar tablero y barcos para dificultad fácil
            break;
        case 2:
            tamano = 17;
            // Configurar tablero y barcos para dificultad media
            break;
        case 3:
            tamano = 21;
            // Configurar tablero y barcos para dificultad difícil
            break;
        default:
            printf("Opción no válida.\n");
            return 1;
    }

    inicializarTablero(tamano);
    inicializarMano();

    int turnos = 0;
    int max_turnos = (opcion == 1) ? 30 : (opcion == 2) ? 25 : 15;
    while (turnos < max_turnos) {
        printf("Turno %d\n", turnos + 1);
        mostrarTablero();
        mostrarMano();
        usarCarta();
        turnos++;
        // Verificar si todos los barcos han sido hundidos
    }

    // Mostrar resultado final
    mostrarTablero();
    liberarTablero(tamano);
    return 0;
}

// Implementación de funciones


void inicializarMano() {
    Cartas.carta = (CartaFunc *)malloc(5 * sizeof(CartaFunc));
    for (int i = 0; i < 5; i++) {
        Cartas.carta[i] = disparoSimple; // Inicializar con disparo simple
    }
    Cartas.disponibles = 5;
}
// ***
// ***
// Inicializa la mano con 5 cartas de disparo simple.
// ***

void mostrarMano() {
    printf("Cartas:\n");
    for (int i = 0; i < Cartas.disponibles; i++) {
        printf("Simple | "); // Mostrar el tipo de carta
    }
    printf("\n");
}
// ***
// ***
// Muestra por pantalla las cartas disponibles en la mano.
// ***

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
// ***
// ***
// Permite seleccionar y usar una carta de la mano. Ejecuta la función de disparo
// correspondiente según las coordenadas seleccionadas.
// ***

void *disparoSimple(int x, int y) {
    // Código para disparo simple
    printf("Disparo simple en (%d, %d)\n", x, y);
    // Retornar la próxima carta aleatoriamente
    return disparoSimple;
}
// ***
// Parametro 1 : int x
// Parametro 2 : int y
// Retorno : void *
// ***
// Dispara un misil con área de efecto de 1x1 celdas en las coordenadas (x,y).
// Retorna la próxima carta que se usará en la mano.
// ***

void *disparoGrande(int x, int y) {
    // Código para disparo grande
    printf("Disparo grande en (%d, %d)\n", x, y);
    // Retornar la próxima carta aleatoriamente
    return disparoSimple;
}
// ***
// Parametro 1 : int x
// Parametro 2 : int y
// Retorno : void *
// ***
// Dispara un gran misil con área de efecto de 3x3 celdas con centro en las coordenadas (x,y).
// Retorna la próxima carta que se usará en la mano.
// ***

// (Otras funciones de disparo irían aquí...)