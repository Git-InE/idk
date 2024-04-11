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

struct Pieza {
    char simbolo; 
    int x, y;
};

struct Tablero {
	int cantidad_piezas;
	Pieza *piezas_tablero;
};

char BuscarPieza( Tablero tablero, int x, int y){
	for (int i = 0; i < tablero.cantidad_piezas; i++){
		if (tablero.piezas_tablero[i].x == x && tablero.piezas_tablero[i].y == y){
			return tablero.piezas_tablero[i].simbolo;
		}
	}
	return '.';
}


bool jaquePeon(int cantidad_piezas, int indiceRey, Tablero tablero)
{
	int posXRey = tablero.piezas_tablero[indiceRey].x;
	int posYRey = tablero.piezas_tablero[indiceRey].y;
	
	for (int i = 0; i < cantidad_piezas; i++)
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

bool jaqueTorre(int cantidad_piezas, int indiceRey, Tablero& tablero){
	int posXRey = tablero.piezas_tablero[indiceRey].x;
	int posYRey = tablero.piezas_tablero[indiceRey].y;
	int contador = 0;
	
	for (int x = posXRey + 1; x < 8 - posXRey; x++)
	{
		if (BuscarPieza(tablero, x, posYRey) != 'T')
		{
			contador++;
		}
		else {
			cout << "Jaque" << endl;
			return true;
		}

	}

	for (int x = posXRey - 1; x >= 0; x--)
	{
		if (BuscarPieza(tablero, x, posYRey) != 'T')
		{
			contador++;
		}
		else {
			cout << "Jaque" << endl;
			return true;
		}
	}

	for (int y = posYRey + 1; y < 8 - posYRey; y++)
	{
		if (BuscarPieza(tablero, posXRey, y) != 'T')
		{
			contador++;
		}
		else {
			cout << "Jaque" << endl;
			return true;
		}
	}

	for (int y = posYRey - 1; y >= 0; y--)
	{
		if (BuscarPieza(tablero, posXRey, y) != 'T')
		{
			contador++;
		}
		
		else {

			cout << "Jaque" << endl;
			return true;
		}
	}

	if (contador < 4)
	{
		cout << "No hay jaque por Torre" << endl;
		return true;
	}

	return false;
}

Pieza expandirRey(Tablero tab, int reyindice){
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
	for (int i = 0; i < 9; i++)
	{
		cout << posRey[i].x << ' ' << posRey[i].y << ' ' << posRey[i].simbolo << endl;
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
	int i, j, reyindice = 0;
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
	Pieza reyexpand = expandirRey(*tab, reyindice);
	
	// solo para ver si funciona las funciones
	bool jaque_peon = jaquePeon(tab->cantidad_piezas, reyindice, *tab);
	bool jaque_torre = jaqueTorre(tab->cantidad_piezas, reyindice, *tab);


    bool jaque_mate = tableroEnJaqueMate(tablero);
    tableroEnJaqueMate ? cout << "si" << endl : cout << "no" << endl;

	delete[] tablero.piezas_tablero;
	archivo.close();
    return 0;
};
