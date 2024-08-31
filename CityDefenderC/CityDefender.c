#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tablero.h"
#include "Cartas.h"

int main() {
    int tamano, opcion;
    int barcosFacil[] = {2, 3, 4, 5}; // Ejemplo para fácil
    int barcosMedio[] = {2, 2, 3, 3, 4, 5};
    int barcosDificil[] = {2, 2, 3, 3, 4, 4, 5, 5};
    
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
            inicializarTablero(tamano);
            colocarBarcos(tamano, 4, barcosFacil);
            break;
        case 2:
            tamano = 17;
            inicializarTablero(tamano);
            colocarBarcos(tamano, 6, barcosMedio);
            break;
        case 3:
            tamano = 21;
            inicializarTablero(tamano);
            colocarBarcos(tamano, 8, barcosDificil);
            break;
        default:
            printf("Opción no válida.\n");
            return 1;
    }

    inicializarMano();

    int turnos = 0;
    int max_turnos = (opcion == 1) ? 30 : (opcion == 2) ? 25 : 15;
    while (turnos < max_turnos) {
        printf("Turno %d\n", turnos + 1);
        mostrarTablero(tamano);
        mostrarMano();
        usarCarta();
        turnos++;
        // Verificar si todos los barcos han sido hundidos
    }

    // Mostrar resultado final
    mostrarTablero(tamano);
    liberarTablero(tamano);
    return 0;
}