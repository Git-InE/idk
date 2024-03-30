#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Pieza {
    char simbolo; 
    int x, y;
};
// transformar lineas en arrays y utilizar el index con .find//
struct Tablero {
    Pieza* piezas_tablero[8][8];
};
bool *tableroEnJaqueMate(Tablero &tablero){
    bool amenaza;
    bool jaque;
    Pieza Rey;
    char simbolo;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if (tablero.piezas_tablero[i][j]->simbolo == 'X'){
            Rey = {'X', i, j};
            }
        }
    }
};
int main(){
    ifstream archivo;
     std::ifstream archivo("tablero.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }
    Tablero tablero;
    int cantidad_piezas; /*obtener primera linea del .txt*/
    archivo >> cantidad_piezas;
    /*asignar cada letra o punto a una posicion dentro del tablero y sus coordenadas*/
    for(int i=0; i<cantidad_piezas; i++){
        char simbolo;
        int x, y;
        for(int j=0; j<8; j++){
            archivo >> simbolo >> x >> y;
            tablero.piezas_tablero[i][j]->simbolo = simbolo;
            tablero.piezas_tablero[i][j]->x = i;
            tablero.piezas_tablero[i][j]->y = j;
    }
    /*llamar funcion tablerojaquemate*/
    bool jaque_mate = tableroEnJaqueMate(tablero);
    tableroEnJaqueMate ? cout << "si" << endl : cout << "no" << endl;
    return 0;
}