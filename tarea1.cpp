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
struct PiezaRey {
    char simbolo; 
    int x, y;
	bool amenaza;
};
struct Pieza {
    char simbolo; 
    int x, y;
};

struct Tablero {
	int cantidad_piezas;
	Pieza *piezas_tablero;
};
struct TableroRey {
	int espacios_validos;
	PiezaRey *piezas_tablero;
};
int reyindice, piezasvalidas = 0;

char BuscarPieza(Tablero tablero, int x, int y){
	for (int i = 0; i < tablero.cantidad_piezas; i++){
		if (tablero.piezas_tablero[i].x == x && tablero.piezas_tablero[i].y == y){
			return tablero.piezas_tablero[i].simbolo;
		}
	}
	return '.';
}

bool jaquePeon(Tablero tablero)
{
    int posXRey = tablero.piezas_tablero[reyindice].x;
    int posYRey = tablero.piezas_tablero[reyindice].y;
	for (int indice = 0;indice<piezasvalidas; indice++)
	{
		for (int i = 0; i < tablero.cantidad_piezas; i++)
		{
			if (tablero.piezas_tablero[i].simbolo == 'P')
			{
				if (tablero.piezas_tablero[i].x == posXRey + 1 && tablero.piezas_tablero[i].y == posYRey + 1)
				{
					cout << "Jaque" << endl;
				}
				else if (tablero.piezas_tablero[i].x == posXRey - 1 && tablero.piezas_tablero[i].y == posYRey + 1)
				{
					cout << "Jaque" << endl;
				}
			}
		}

	}
    return false;
}

bool jaqueTorre(Tablero& tablero){
	int posXRey = tablero.piezas_tablero[reyindice].x;
	int posYRey = tablero.piezas_tablero[reyindice].y;
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

bool jaqueAlfil(Tablero tablero){
	int posXRey = tablero.piezas_tablero[reyindice].x;
	int posYRey = tablero.piezas_tablero[reyindice].y;
	
	for (int RT = 1; RT < 8; RT++){
		if (BuscarPieza(tablero, posXRey + RT, posYRey + RT) == 'A'){
			cout << "Jaque" << endl;
			return true;
		}
	}
	for (int LT = 1; LT < 8; LT++){
		if (BuscarPieza(tablero, posXRey - LT, posYRey + LT) == 'A'){
			cout << "Jaque" << endl;
			return true;
		}
	}
	for (int RB = 1; RB < 8; RB++){
		if (BuscarPieza(tablero, posXRey + RB, posYRey - RB) == 'A'){
			cout << "Jaque" << endl;
			return true;
		}
	}
	for (int LB = 1; LB < 8; LB++){
		if (BuscarPieza(tablero, posXRey - LB, posYRey - LB) == 'A'){
			cout << "Jaque" << endl;
			return true;
		}
	}
	return false;
}

bool tableroEnJaqueMate(Tablero tablero){
    int contador;
	/*terminar*/
    return true;
	}
// No se si funciona porque falta la funcion jaqueAlfil
bool jaqueReina(Tablero tablero){
	int posXRey = tablero.piezas_tablero[reyindice].x;
	int posYRey = tablero.piezas_tablero[reyindice].y;

	if (jaqueTorre(tablero) || jaqueAlfil(tablero))
	{
		cout << "Jaque" << endl;
		return true;
	}
	return false;	
}

PiezaRey *expandirRey(Tablero tab){
	TableroRey posRey;
	posRey.piezas_tablero = new PiezaRey[9];
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
				posRey.piezas_tablero[contador].simbolo = BuscarPieza(tab, adjX, adjY);
				posRey.piezas_tablero[contador].x = adjX;
				posRey.piezas_tablero[contador].y = adjY;
				posRey.piezas_tablero[contador].amenaza = false;
				contador++;
			}			
		}
	}
	posRey.espacios_validos = contador;
	for (int i = 0; i < 9; i++)
	{
		cout << posRey.piezas_tablero[i].x << ' ' << posRey.piezas_tablero[i].y << ' ' << posRey.piezas_tablero[i].simbolo << endl;
	}
	return posRey.piezas_tablero;
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
	PiezaRey *Punt_Rey = expandirRey(*tab);
	
	// solo para ver si funciona las funciones
	bool jaque_peon = jaquePeon(*tab);
	bool jaque_torre = jaqueTorre(*tab);
	bool jaque_caballo = jaqueCaballo(*tab);
	bool jaque_alfil = jaqueAlfil(*tab);


    bool jaque_mate = tableroEnJaqueMate(tablero);
    tableroEnJaqueMate ? cout << "si" << endl : cout << "no" << endl;
	delete[] Punt_Rey;
	delete[] tablero.piezas_tablero;
	archivo.close();
    return 0;
};