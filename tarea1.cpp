#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Pieza {
    char simbolo; 
    int x, y;
};

struct Tablero {
	int cantidad_piezas;
	Pieza *piezas_tablero;
};

struct PiezaRey {
    int x, y;
    char simbolo; 
	bool amenaza;
};

PiezaRey arreglorey[9];
int reyindice, espacios_validos = 0;

/*****
* char BuscarPieza
******
* Resumen Función
*busca el simbolo de la pieza en la posicion (x,y)
******
* Input:
* Tablero tablero, tablero con las piezas
* int x, coordenada x de la pieza
* int y, coordenada y de la pieza
******
* Returns:
* char, simbolo de la pieza en la posicion x, y
* si no hay pieza en esa posicion retorna '.'
*****/

char BuscarPieza( Tablero tablero, int x, int y){
	for (int i = 0; i < tablero.cantidad_piezas; i++){
		if (tablero.piezas_tablero[i].x == x && tablero.piezas_tablero[i].y == y){
			return tablero.piezas_tablero[i].simbolo;
		}
	}
	return '.';
}
/*****
* void bloqueoReyEnemigo
******
* Resumen Función
* realiza una busqueda alrededor de todas las casillas posibles que pueden ser amenazadas por el rey enemigo
* en caso de encontrar al rey enemigo que amenace una de estas casillas, marca la amenaza a la casilla señalada a true
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns: void
*****/
void bloqueoReyEnemigo(Tablero tablero){
    for (int indice = 0; indice < espacios_validos; indice++)
    {
        int posXRey = arreglorey[indice].x;
        int posYRey = arreglorey[indice].y;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    char pieza = BuscarPieza(tablero, posXRey + i, posYRey + j);
                    if (pieza == 'K')
                    {
                        arreglorey[indice].amenaza = true;
                    }
                }
            }
        }
    }
}
/*****
* void jaquePeon
******
* Resumen Función
* Primero busca en el arreglo de piezas si hay un peon existente,
* en caso de que exista, busca si el rey está en jaque desde la posición del peon
* dado que el peon solo puede atacar en diagonal con 1 "unidad", se busca si el rey está en diagonal de 1 "unidad"
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns: void
*****/

void jaquePeon(Tablero tablero)
{
	int indice = 0;
	for (int indice = 0; indice < espacios_validos; indice++)
	{
		int posXRey = arreglorey[indice].x;
    	int posYRey = arreglorey[indice].y;
			for (int i = 0; i < tablero.cantidad_piezas; i++)
			{
				if (tablero.piezas_tablero[i].simbolo == 'P')
				{
					if (tablero.piezas_tablero[i].x == posXRey + 1 && tablero.piezas_tablero[i].y == posYRey + 1)
					{
						arreglorey[indice].amenaza = true;
					}
					else if (tablero.piezas_tablero[i].x == posXRey - 1 && tablero.piezas_tablero[i].y == posYRey + 1)
					{
						arreglorey[indice].amenaza = true;
					}
				}
			}

	}
    return;
}
/*****
* void jaqueAlfil
******
* Resumen Función
* La función entra en un bucle que recorre las cuatro direcciones diagonales alrededor del rey. 
* En cada iteración del bucle, la función busca la pieza en la posición diagonal correspondiente y la almacena en el arreglo adj.
* Después de obtener la pieza adyacente, la función verifica si esta pieza es un alfil.
* Si es así, y si no hay otras piezas bloqueando el camino entre el alfil y el rey, la función marca al rey como en jaque en esa dirección.
* Si la pieza adyacente no es un alfil, la función verifica si la posición está vacía o bloqueada por otra pieza.
* Si la posición está vacía, la función incrementa el contador de posiciones vacías en esa dirección.
* Si la posición está bloqueada por otra pieza, la función marca esa dirección como bloqueada.
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns:void
*****/

void jaqueAlfil(Tablero tablero){
    for (int indice = 0; indice < espacios_validos; indice++)
    {
        int posXRey = arreglorey[indice].x;
        int posYRey = arreglorey[indice].y;
        char adj[4];
        bool amenaza[4] = {false, false, false, false};
        bool bloqueado[4] = {false, false, false, false};

        for (int i = 1; i < 8; i++)
        {
            adj[0] = BuscarPieza(tablero, posXRey + i, posYRey + i);
            adj[1] = BuscarPieza(tablero, posXRey + i, posYRey - i);
            adj[2] = BuscarPieza(tablero, posXRey - i, posYRey + i);
            adj[3] = BuscarPieza(tablero, posXRey - i, posYRey - i);

            for (int j = 0; j < 4; j++)
            {
                if (!amenaza[j] && !bloqueado[j]) {
                    if (adj[j] == 'A') {
                        arreglorey[indice].amenaza = true;
                        amenaza[j] = true;
                    } else if (adj[j] != '.') {
                        bloqueado[j] = true;
                    }
                }
            }
        }
    }
    return;
}
/*****
* void jaqueReina
******
* Resumen Función
* Esta funcion es una mezcla de las funciones jaqueAlfil y jaqueTorre
* la cual basicamente crea 4 arreglos 2 "horizontales" y 2 "verticales",
* en los cuales se guardan las piezas adyacentes y las posiciones vacias, 1 arreglo para cada tipo de movimiento de la reina
* despues de eso inicia un ciclo for, en el cual guarda las piezas adyacentes en el arreglo adj
* si la pieza adyacente es un reina y la cantidad de posiciones vacias es igual a i-1, entonces el rey está en jaque
* en caso de que no se cumpla, agregará 1 al contador de piezas adyacentes y si la pieza adyacente es distinta de "."
* entonces agregará 1 al contador de piezas adyacentes
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns: void
*****/
void jaqueReina(Tablero tablero){
    for (int indice = 0;indice < espacios_validos; indice++)
    {        
        int posXRey = arreglorey[indice].x;
        int posYRey = arreglorey[indice].y;
	    char adjT[4];
        int vaciosT[4] = {0, 0, 0, 0};
        int numOtrasT;
        for (int i = 1; i < 8; i++)
        {
            numOtrasT = 0;
            adjT[0] = BuscarPieza(tablero, posXRey + i, posYRey);
            adjT[1] = BuscarPieza(tablero, posXRey - i, posYRey);
            adjT[2] = BuscarPieza(tablero, posXRey, posYRey + i);
            adjT[3] = BuscarPieza(tablero, posXRey, posYRey - i);

            for (int j = 0; j < 4; j++)
            {
                if ((adjT[j] == 'R')&&(vaciosT[j] == i - 1)){
                    arreglorey[indice].amenaza = true;
                } 
                if (adjT[j] != '.') numOtrasT++;
                if ((adjT[j] == '.') || (adjT[j] == 'X')) vaciosT[j]++;
            }
        }
        char adjA[4];
        bool amenaza[4] = {false, false, false, false};
        bool bloqueado[4] = {false, false, false, false};

        for (int i = 1; i < 8; i++)
        {
            adjA[0] = BuscarPieza(tablero, posXRey + i, posYRey + i);
            adjA[1] = BuscarPieza(tablero, posXRey + i, posYRey - i);
            adjA[2] = BuscarPieza(tablero, posXRey - i, posYRey + i);
            adjA[3] = BuscarPieza(tablero, posXRey - i, posYRey - i);

            for (int j = 0; j < 4; j++)
            {
                if (!amenaza[j] && !bloqueado[j]) {
                    if (adjA[j] == 'A') {
                        arreglorey[indice].amenaza = true;
                        amenaza[j] = true;
                    } else if (adjA[j] != '.') {
                        bloqueado[j] = true;
                    }
                }
            }
        }
    }
    return;
}

/*****
* void jaqueTorre
******
* Resumen Función
* Crea dos arreglos, uno para las piezas adyacentes y otro para las posiciones con un "."
* despues de eso inicia un ciclo for, en el cual guarda las piezas adyacentes en el arreglo adj
* si la pieza adyacente es un torre y la cantidad de posiciones vacias es igual a i-1, entonces el rey está en jaque
* en caso de que no se cumpla, agregará 1 al contador de piezas adyacentes y si la pieza adyacente es distinta de "."
* entonces agregará 1 al contador de piezas adyacentes
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns:
* void
*****/

void jaqueTorre(Tablero& tablero){
    for (int indice = 0; indice < espacios_validos; indice++)
    {
        int posXRey = arreglorey[indice].x;
    	int posYRey = arreglorey[indice].y;
        char adj[4];
        int vacios[4] = {0, 0, 0, 0};
        int numOtras;
        for (int i = 1; i < 8; i++)
        {
            numOtras = 0;
            adj[0] = BuscarPieza(tablero, posXRey + i, posYRey);
            adj[1] = BuscarPieza(tablero, posXRey - i, posYRey);
            adj[2] = BuscarPieza(tablero, posXRey, posYRey + i);
            adj[3] = BuscarPieza(tablero, posXRey, posYRey - i);
            for (int j = 0; j < 4; j++)
            {
                if ((adj[j] == 'T') && (vacios[j] == i - 1)){
                    arreglorey[indice].amenaza = true;
                } 
                if (adj[j] != '.') numOtras++;
                if ((adj[j] == '.') || (adj[j] == 'X')) vacios[j]++;
            }
        }
    }
    return;
}

/*****
* void jaqueCaballo
******
* Resumen Función
* utilizando la posicion del rey, se busca si existe un caballo en las 8 posibles posiciones
* en caso de que exista un caballo en alguna de las posiciones, entonces el rey está en jaque
* en este caso no se necesita buscar si hay una pieza entre el rey y el caballo, ya que el caballo puede saltar 
* por las reglas del ajedrez
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns: void
*****/

void jaqueCaballo(Tablero tablero){
    for (int indice = 0; indice < espacios_validos; indice++)
    {
        int posXRey = arreglorey[indice].x;
    	int posYRey = arreglorey[indice].y;
        for (int i = 0; i < tablero.cantidad_piezas; i++)
        {
            if (tablero.piezas_tablero[i].simbolo == 'C')
            {
                if ((tablero.piezas_tablero[i].x == posXRey + 2 && tablero.piezas_tablero[i].y == posYRey + 1) ||
                    (tablero.piezas_tablero[i].x == posXRey + 2 && tablero.piezas_tablero[i].y == posYRey - 1) ||
                    (tablero.piezas_tablero[i].x == posXRey - 2 && tablero.piezas_tablero[i].y == posYRey + 1) ||
                    (tablero.piezas_tablero[i].x == posXRey - 2 && tablero.piezas_tablero[i].y == posYRey - 1) ||
                    (tablero.piezas_tablero[i].x == posXRey + 1 && tablero.piezas_tablero[i].y == posYRey + 2) ||
                    (tablero.piezas_tablero[i].x == posXRey + 1 && tablero.piezas_tablero[i].y == posYRey - 2) ||
                    (tablero.piezas_tablero[i].x == posXRey - 1 && tablero.piezas_tablero[i].y == posYRey + 2) ||
                    (tablero.piezas_tablero[i].x == posXRey - 1 && tablero.piezas_tablero[i].y == posYRey - 2))
                {
                    arreglorey[indice].amenaza = true;
                }
            }
        }
    }
    return;
}
/*****
* void expandirRey
******
* Resumen Función
* expandirRey se encarga de generar un arreglo global de las casillas adyacentes al rey,
* siendo un cuadrado 3x3 donde se le agrega adicionalmente una variable booleana de "amenaza"
* que no posee el struct Pieza, con este arreglo se podra determinar si el rey tiene
* movimientos posibles o se encuentra en jaquemate
******
* Input:
* Tablero tab, el tablero que guarda las piezas
* .......
******
* Returns: void
*****/
void expandirRey(Tablero tab){
	int indice = reyindice;
	int posReyX = tab.piezas_tablero[indice].x;
	int posReyY = tab.piezas_tablero[indice].y;
	int adjX,adjY;
	int contador = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			adjX = posReyX + i;
			adjY = posReyY + j;
			if (adjX >= 0 && adjX < 8 && adjY >= 0 && adjY < 8)
			{	
				arreglorey[contador].simbolo = BuscarPieza(tab, adjX, adjY);
				arreglorey[contador].x = adjX;
				arreglorey[contador].y = adjY;
				arreglorey[contador].amenaza = false;
				contador++;
			}			
		}
	}
	espacios_validos = contador;

	return;
}
/*****
* bool tableroEnJaqueMate
******
* Resumen Función
* Esta funcion se encarga de ejecutar todas las funciones void anteriormente
* definidas, luego itera sobre el arreglo para buscar todas las casillas que
* se encuentran amenazadas del rey (su circulo cercano 3x3) descartando las
* posiciones que puedan estar fuera del tablero, si el contador coincide con
* todos los movimientos posibles del rey, este se encuentra en jaque mate
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns:
* Booleano, True si el rey esta en jaque mate y False si aun tiene movimientos disponibles
*****/

bool tableroEnJaqueMate(Tablero tablero){
    int contador=0;
    expandirRey(tablero);
    jaquePeon(tablero);
	jaqueTorre(tablero);
	jaqueCaballo(tablero);
	jaqueAlfil(tablero);
    jaqueReina(tablero);
    bloqueoReyEnemigo(tablero);
    for (int i=0; i < espacios_validos; i++)
    {
        if (arreglorey[i].amenaza){
            contador++;
        }
    }
    if (contador == espacios_validos){
        return true;
    }
    else{
        return false;
    }
	}

int main(){
    ifstream archivo;
	archivo.open("tablero.txt", ios::in);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
	}
	Tablero tablero;
	char simbolo;
	int i, j;
	int  indice = 0;
	string linea;
    cout << endl;
	archivo >> tablero.cantidad_piezas;
	tablero.piezas_tablero = new Pieza[tablero.cantidad_piezas];
	for (j=0; j<8; j++){
		archivo >> linea;
		for (i=0; i<8; i++){
			simbolo = linea[i];
			if (simbolo != '.'){
				if(simbolo == 'X'){
					reyindice = indice;
				}
				tablero.piezas_tablero[indice].x = i;
				tablero.piezas_tablero[indice].y = j;
				tablero.piezas_tablero[indice].simbolo = simbolo;
				indice++;
			}
		}
	}
    bool jaque_mate = tableroEnJaqueMate(tablero);
    jaque_mate ? cout << "si" << endl : cout << "no" << endl;
	delete[] tablero.piezas_tablero;
	archivo.close();
    return 0;
};