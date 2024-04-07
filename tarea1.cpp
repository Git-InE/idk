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

char BuscarPieza(int cantidadPiezas, Tablero tablero, int x, int y){
	for (int i = 0; i < cantidadPiezas; i++){
		if (tablero.piezas_tablero[i].x == x && tablero.piezas_tablero[i].y == y){
			return tablero.piezas_tablero[i].simbolo;
		}
	}
	return '.';
}

Tablero expandirRey(int n, Tablero tab, int reyindice){
	Pieza* posRey = new Pieza[9];
	int i, j = 0;
	int indice = reyindice;
	int posReyX = tab.piezas_tablero[indice].x;
	int posReyY = tab.piezas_tablero[indice].y;
	cout << posReyX << ',' << posReyY << endl;
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
				posRey[contador].simbolo = BuscarPieza(n, tab, adjX, adjY);
				cout << adjX << ' '<< adjY << ' ' << posRey[contador].simbolo << endl;
				contador++;
			}

			
		}
	}
	return tab;
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
    int cantidad_piezas;
	int i, j, indice, reyindice = 0;
	string linea;
	archivo >> cantidad_piezas;
	tablero.piezas_tablero = new Pieza[cantidad_piezas];
	for (j=0; j<8; j++){
		archivo >> linea;
		for (i=0; i<8; i++){
			simbolo = linea[i];
			if (simbolo != '.'){
				if(simbolo == 'X'){
					reyindice = indice;
				}
				tablero.piezas_tablero[indice].simbolo = simbolo;
				tablero.piezas_tablero[indice].x = i;
				tablero.piezas_tablero[indice].y = j;
				indice++;
			}
		}
	}
	Tablero *tab = &tablero;
	expandirRey(cantidad_piezas, *tab, reyindice);
	/*solo pa comprobar*/
	for (int k=0; k < cantidad_piezas; k++){
		cout << tablero.piezas_tablero[k].simbolo << ':' << tablero.piezas_tablero[k].x << ',' << tablero.piezas_tablero[k].y << endl;
	}
    bool jaque_mate = tableroEnJaqueMate(tablero);
    tableroEnJaqueMate ? cout << "si" << endl : cout << "no" << endl;
	delete[] tablero.piezas_tablero;
	archivo.close();
    return 0;
};

