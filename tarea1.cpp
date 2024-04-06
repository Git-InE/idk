#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Pieza {
    char simbolo; 
    int x, y;
};

struct Tablero {
    Pieza *piezas_tablero;
};
struct PosRey
{
	int x, y;
};


// Funciones
/*****
 * 
 * Funcion: ArregloPosRey
 * 
 * Resumen Funcion: Funcion que crea un arreglo de posiciones de rey + las 8 posiciones adyacentes
 * 
 * Input: 
 * int indice : indice de la pieza rey en el arreglo de piezas
 * Tablero tablero : tablero con las piezas
 * 
 * Returns:
 * PosRey*, arreglo de posiciones de rey
*****/
PosRey *ArregloPosRey(int indice, Tablero tablero)
{
	PosRey *posRey = new PosRey[9];
	int contador = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((posRey[contador].y = tablero.piezas_tablero[indice].y + i) > 8 || (posRey[contador].y = tablero.piezas_tablero[indice].y + i) < 0 
			|| (posRey[contador].y = tablero.piezas_tablero[indice].y + j) > 8 || (posRey[contador].y = tablero.piezas_tablero[indice].y + j) < 0)
			{
				posRey[contador].x = -1;
				posRey[contador].y = -1;
			}
			else
			{
				if (i == 0 && j == 0)
				{
					posRey[contador].x = tablero.piezas_tablero[indice].x;
					posRey[contador].y = tablero.piezas_tablero[indice].y;
					cout << "Posicion " << contador << " X: " << posRey[contador].x << " Y: " << posRey[contador].y << endl;
				}
				else
				{

				posRey[contador].x = tablero.piezas_tablero[indice].x + i;
				posRey[contador].y = tablero.piezas_tablero[indice].y + j;
				cout << "Posicion " << contador << " X: " << posRey[contador].x << " Y: " << posRey[contador].y << endl;
				}
			}
			contador++;
		}
	}
	return posRey;
}
bool tableroEnJaqueMate(Tablero tablero){
    Tablero mesa;
    int contador;
    
}
int main()
{
	int cantidadPiezas;
	int posY = 0;
	int indice = 0;
	fstream tab;
	string linea;
	Tablero tablero;        /*declarar variables*/

	tab.open("tablero.txt", ios::in);

	tab >> cantidadPiezas;
    
	tablero.piezas_tablero = new Pieza[cantidadPiezas];
    if (!tab.is_open()) {       /*checkear si el archivo abrio*/
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

	while (getline(tab, linea)) /*guardar piezas en tablero*/
	{
		for (int i = 0; i < linea.size(); i++)
		{
			if (linea[i] != '.')
			{
				tablero.piezas_tablero[indice].simbolo = linea[i];
				tablero.piezas_tablero[indice].x = i + 1;
				tablero.piezas_tablero[indice].y = posY;
			if (linea[i] == 'X')
			{
				ArregloPosRey(indice, tablero);
			}
			indice++;
    		}
    	}
    	posY++;
    }
	posY = 0;
    tab.close();
    bool jaque_mate = tableroEnJaqueMate(tablero);
    tableroEnJaqueMate ? cout << "si" << endl : cout << "no" << endl;
    return 0;
	delete[] tablero.piezas_tablero;
}

