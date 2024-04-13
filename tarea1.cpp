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

int reyindice = 0;

/*****
* char BuscarPieza
******
* Resumen Función
*
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
* bool jaquePeon
******
* Resumen Función
* Primero busca en el arreglo de piezas si hay un peon existente,
* en caso de que exista, busca si el rey está en jaque desde la posición del peon
* dado que el peon solo puede atacar en diagonal con 1 "unidad", se busca si el rey está en diagonal de 1 "unidad"
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns:
* bool, true si el rey está en jaque, false si no lo está
*****/

bool jaquePeon(Tablero tablero)
{
    int posXRey = tablero.piezas_tablero[reyindice].x;
    int posYRey = tablero.piezas_tablero[reyindice].y;

    for (int i = 0; i < tablero.cantidad_piezas; i++)
    {
        if (tablero.piezas_tablero[i].simbolo == 'P')
        {
            if (tablero.piezas_tablero[i].x == posXRey + 1 && tablero.piezas_tablero[i].y == posYRey + 1)
            {
                cout << "Jaque" << endl;
                return true;
            }
            else if (tablero.piezas_tablero[i].x == posXRey - 1 && tablero.piezas_tablero[i].y == posYRey + 1)
            {
                cout << "Jaque" << endl;
                return true;
            }
        }
    }
    return false;
}
/*****
* bool jaqueAlfil
******
* Resumen Función
* Crea dos arreglos, uno para las piezas adyacentes y otro para las posiciones con un "."
* despues de eso inicia un ciclo for, en el cual guarda las piezas adyacentes en el arreglo adj
* si la pieza adyacente es un alfil y la cantidad de posiciones vacias es igual a i-1, entonces el rey está en jaque
* en caso de que no se cumpla, agregará 1 al contador de piezas adyacentes y si la pieza adyacente es distinta de "."
* entonces agregará 1 al contador de piezas adyacentes
* si la cantidad de piezas adyacentes es igual a 4, entonces retornará false
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns:
* bool, true si el rey está en jaque, false si no lo está
*****/

bool jaqueAlfil(Tablero tablero){
    int posXRey = tablero.piezas_tablero[reyindice].x;
    int posYRey = tablero.piezas_tablero[reyindice].y;
    char adj[4];
    int vacios[4] = {0, 0, 0, 0};
    int numOtras;
    for (int i = 1; i < 8; i++)
    {
        numOtras = 0;
        adj[0] = BuscarPieza(tablero, posXRey + i, posYRey + i);
        adj[1] = BuscarPieza(tablero, posXRey + i, posYRey - i);
        adj[2] = BuscarPieza(tablero, posXRey - i, posYRey + i);
        adj[3] = BuscarPieza(tablero, posXRey - i, posYRey - i);

        for (int j = 0; j < 4; j++)
        {
            if ((adj[j] == 'A')&&(vacios[j]==i-1)){
                cout << "Jaque" << endl;
                return true;
            } 
            if (adj[j] != '.') numOtras++;
            if (adj[j] == '.') vacios[j]++;
        }

        if (numOtras==4) return false;

    }
    return false;
}
/*****
* bool jaqueReina
******
* Resumen Función
* Esta funcion es una mezcla de las funciones jaqueAlfil y jaqueTorre
* la cual basicamente crea 4 arreglos 2 "horizontales" y 2 "verticales",
* en los cuales se guardan las piezas adyacentes y las posiciones vacias, 1 arreglo para cada tipo de movimiento de la reina
* despues de eso inicia un ciclo for, en el cual guarda las piezas adyacentes en el arreglo adj
* si la pieza adyacente es un reina y la cantidad de posiciones vacias es igual a i-1, entonces el rey está en jaque
* en caso de que no se cumpla, agregará 1 al contador de piezas adyacentes y si la pieza adyacente es distinta de "."
* entonces agregará 1 al contador de piezas adyacentes
* si la cantidad de piezas adyacentes es igual a 4, entonces retornará false
******
* Input:
* Tablero tablero, tablero con las piezas
******
* Returns:
* bool, true si el rey está en jaque, false si no lo está
*****/
bool jaqueReina(Tablero tablero){
	int posXRey = tablero.piezas_tablero[reyindice].x;
	int posYRey = tablero.piezas_tablero[reyindice].y;
	
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
            if ((adjT[j] == 'R')&&(vaciosT[j]==i-1)){
                cout << "Jaque" << endl;
                return true;
            } 
            if (adjT[j] != '.') numOtrasT++;
            if (adjT[j] == '.') vaciosT[j]++;
        }

        if (numOtrasT==4) return false;

    }
	char adjA[4];
    int vaciosA[4] = {0, 0, 0, 0};
    int numOtrasA;
    for (int i = 1; i < 8; i++)
    {
        numOtrasA = 0;
        adjA[0] = BuscarPieza(tablero, posXRey + i, posYRey + i);
        adjA[1] = BuscarPieza(tablero, posXRey + i, posYRey - i);
        adjA[2] = BuscarPieza(tablero, posXRey - i, posYRey + i);
        adjA[3] = BuscarPieza(tablero, posXRey - i, posYRey - i);

        for (int j = 0; j < 4; j++)
        {
            if ((adjA[j] == 'A')&&(vaciosA[j]== i - 1)){
                cout << "Jaque" << endl;
                return true;
            } 
            if (adjA[j] != '.') numOtrasA++;
            if (adjA[j] == '.') vaciosA[j]++;
        }

        if (numOtrasA == 4) return false;

    }

    return false;
}

/*****
* bool jaqueTorre
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
* bool, true si el rey está en jaque, false si no lo está
*****/

bool jaqueTorre(Tablero& tablero){
	int posXRey = tablero.piezas_tablero[reyindice].x;
    int posYRey = tablero.piezas_tablero[reyindice].y;
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
            if ((adj[j] == 'T')&&(vacios[j]==i-1)){
                cout << "Jaque" << endl;
                return true;
            } 
            if (adj[j] != '.') numOtras++;
            if (adj[j] == '.') vacios[j]++;
        }

        if (numOtras==4) return false;

    }

    return false;
}

/*****
* bool jaqueCaballo
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
* Returns:
* bool, true si el rey está en jaque, false si no lo está
*****/

bool jaqueCaballo(Tablero tablero){
	int posXRey = tablero.piezas_tablero[reyindice].x;
	int posYRey = tablero.piezas_tablero[reyindice].y;
	
	if (BuscarPieza(tablero, posXRey + 1, posYRey + 2) == 'C')
	{
		cout << "Jaque" << endl;
		return true;
	}
	else if (BuscarPieza(tablero, posXRey + 1, posYRey - 2) == 'C')
	{
		cout << "Jaque" << endl;
		return true;
	}
	else if (BuscarPieza(tablero, posXRey - 1, posYRey + 2) == 'C')
	{
		cout << "Jaque" << endl;
		return true;
	}
	else if (BuscarPieza(tablero, posXRey - 1, posYRey - 2) == 'C')
	{
		cout << "Jaque" << endl;
		return true;
	}
	else if (BuscarPieza(tablero, posXRey + 2, posYRey + 1) == 'C')
	{
		cout << "Jaque" << endl;
		return true;
	}
	else if (BuscarPieza(tablero, posXRey + 2, posYRey - 1) == 'C')
	{
		cout << "Jaque" << endl;
		return true;
	}
	else if (BuscarPieza(tablero, posXRey - 2, posYRey + 1) == 'C')
	{
		cout << "Jaque" << endl;
		return true;
	}
	else if (BuscarPieza(tablero, posXRey - 2, posYRey - 1) == 'C')
	{
		cout << "Jaque" << endl;
		return true;
	}
	return false;
}

Pieza expandirRey(Tablero tab){
	Pieza posRey[9];
	int indice = reyindice;
	int posReyX = tab.piezas_tablero[indice].x;
	int posReyY = tab.piezas_tablero[indice].y;
	cout << "rey: " << posReyX << ',' << posReyY << endl;
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
				posRey[contador].simbolo = BuscarPieza(tab, adjX, adjY);
				posRey[contador].x = adjX;
				posRey[contador].y = adjY;
				contador++;
			}			
		}
	}
	return *posRey;
}

bool tableroEnJaqueMate(Tablero tablero){
    int contador;
	/*terminar*/
    return true;
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
	Tablero *tab = &tablero;
	Pieza reyexpand = expandirRey(*tab);
	
	// solo para ver si funciona las funciones
	bool jaque_peon = jaquePeon(*tab);
	bool jaque_torre = jaqueTorre(*tab);
	bool jaque_caballo = jaqueCaballo(*tab);
	bool jaque_alfil = jaqueAlfil(*tab);
	bool jaque_reina = jaqueReina(*tab);


    bool jaque_mate = tableroEnJaqueMate(tablero);
    tableroEnJaqueMate ? cout << "si" << endl : cout << "no" << endl;

	delete[] tablero.piezas_tablero;
	archivo.close();
    return 0;
};