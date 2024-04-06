// Importante: utilizar este tipo de comentario para las funciones, si no quitan 5 pts 
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
* tipoParámetro NombreParámetro : Descripción Parámetro
* .......
******
* Returns:
* TipoRetorno, Descripción retorno
*****/

#include <iostream>
#include <string>
#include <fstream> 

using namespace std;
// Structs
struct Pieza
{
	char simbolo;
	int x, y;
	
};

struct Tablero
{
	Pieza* piezas_tablero;
};


char BuscarPieza(int cantidadPiezas, Tablero tablero, int x, int y)
{
	for (int i = 0; i < cantidadPiezas; i++)
	{
		if (tablero.piezas_tablero[i].x == x && tablero.piezas_tablero[i].y == y)
		{
			return tablero.piezas_tablero[i].simbolo;
		}
	}
	return '.';
}

Pieza* ArregloPosRey(int cantidadPiezas, int indice, Tablero tablero)
{
	Pieza* posRey = new Pieza[9];
	int posReyX = tablero.piezas_tablero[indice].x	;
	int posReyY = tablero.piezas_tablero[indice].y	;
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
				posRey[contador].x = adjX;
				posRey[contador].y = adjY;
				posRey[contador].simbolo = BuscarPieza(cantidadPiezas, tablero, adjX, adjY);
				contador++;
			}

		}
	}
	return posRey;
}



// Main
int main()
{
	int cantidadPiezas;
	int posY = 0;
	int indice = 0;
	int reyIndice = 0;
	Pieza* posRey;
	fstream tab;
	string linea;
	Tablero tablero;

	tab.open("tablero.txt", ios::in);

	tab >> cantidadPiezas;

	tablero.piezas_tablero = new Pieza[cantidadPiezas];

	if (tab.is_open())
	{
		while (getline(tab, linea))
		{
			for (int i = 0; i < int(linea.size()); i++)
			{
				if (linea[i] != '.')
				{
					tablero.piezas_tablero[indice].simbolo = linea[i];
					tablero.piezas_tablero[indice].x = i + 1;
					tablero.piezas_tablero[indice].y = posY;
					if (linea[i] == 'X')
					{
						reyIndice = indice;
					}
					indice++;
				}
			}
			posY++;
		}
		
		posRey = ArregloPosRey(cantidadPiezas,reyIndice, tablero);
		posY = 0;

		delete[] posRey;
	}
	else
	{
		cout << "Error al abrir el Archivo" << endl;
	}
	tab.close();
	delete[] tablero.piezas_tablero;
	
	return 0;
}