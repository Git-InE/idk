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

Pieza expandirRey(Tablero tab, int reyindice){
	Pieza posRey[9];
	int i, j = 0;
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
				cout << adjX << ' '<< adjY << ' ' << posRey[contador].simbolo << endl;
				
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
	/*solo pa comprobar*/
	int k;
	for (k = 0; k< tablero.cantidad_piezas; k++){
		cout << tablero.piezas_tablero[k].simbolo << ':' << tablero.piezas_tablero[k].x << ',' << tablero.piezas_tablero[k].y << endl;
	}
    bool jaque_mate = tableroEnJaqueMate(tablero);
    tableroEnJaqueMate ? cout << "si" << endl : cout << "no" << endl;

	delete[] tablero.piezas_tablero;
	archivo.close();
    return 0;
};

