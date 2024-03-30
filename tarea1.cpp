#include <iostream>
#include <iostream>
using namespace std;
struct Pieza {
    char simbolo; 
    int x, y;
};
// transformar lineas en arrays y utilizar el index con .find//
struct Tablero {
    Pieza* piezas_tablero[8][8];
};

int main(){
    int tablero[8][8];
    for (int i = 0; i < 8; i++){
        for (int j= 0; j<8; j++){
            tablero[j] = j;
            cout << tablero;
        }
    }
    return 0;
}