// Jose Miguel Figarola Prado
// A01632557
// 30 sept 2021
// Laberynth Solver using backtracking
// Es programa resuelve un laberinto nxm
// Utilizando backtracking
// Complejidad de O(n^2)

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

string pm; // parametro de m
string pn; // parametro de n
int m; // m a entero
int n; // n a entero
string line;
int cont = 0;
const int N = 4;
int posx, posy = 0; // Posicion x,y

string laberinto[N][N];
string ejercicio; // Eleccion de archivo

// Esta funcion imprime el laberitno
void printLab(string tablero[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tablero[i][j];
        }
        cout << endl;
    }
}

// En esta funcion se checan los parametros
// x,y no se salgan de la matriz
bool isSafe(string board[N][N], int x, int y){
    // Si la posicion (x,y) se sale de la matriz
    if (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == "1"){
        return true;
    }

    return false;

}

bool solveUtil(string tablero[N][N], int x, int y){

    // Mejor de los casos
    if(x == N - 1 && y == N - 1 && tablero[x][y] == "1"){ // La posición inicial es la final
        tablero[x][y] = "x";
        return true; // Ya esta resuelto el problema
    }

    // APLICAR LA RECURSIVIDAD
    // Checar la pos (x,y) sea valida
    if (isSafe(tablero, x, y)) {
        // El actual es parte de la solucion
        if (tablero[x][y] == "x"){
            return false;
        }

        // (x,y) son parte de la solucion
        // Se marca con x por ahora
        tablero[x][y] = "x";

        // Mover se en x (derecha)
        if (solveUtil(tablero, x + 1, y)) {
            return true; // Se puede mover por ahi
        }

        // Moverse en y (abajo)
        if (solveUtil(tablero, x, y + 1)){
            return true; // Se puede mover por ahi
        }

        // No es solucion en ese camino
        // Entonces se regresa
        tablero[x][y] = "1";
        return false;
    }

    return false; // No se puede mover
}


// Utilizar solveUtil (recursiva)
// True = tiene solucion y se imprime
// False = no tiene solucion
bool solve(string board[N][N]){

    if(!solveUtil(board,posx,posy)){ // Si no tiene solucion el tablero o hay un error
        cout << "There's no solution" << endl; // Algo salio mal
        exit(1);
    }
    return true;
}

void Iniciar(const string& archivo){


    ifstream file;
    file.open(archivo);

    if (file.fail()) {
        cerr << "File not created!" << endl;
        exit(1);
    }
    else{
        cout << "File opened correctly" << endl;
    }

    // OBTENER PARAMETROS PARA MxN
    while(file >> line) {
        cout << line;
    }
    cout << endl;

    // FOR SIN MxN EL ACTUAL
    /*for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            file >> laberinto[i][j];
        }
    }*/

    file.close();

    cout << "Initial board" << endl;
    printLab(laberinto);

    solve(laberinto);

    cout << "Path founded" << endl;
    printLab(laberinto);
}

int main() {

    cout << "Which board you want to solve: ";
    cin >> ejercicio;
    cout<<endl;

    Iniciar(ejercicio);

    return 0;
}
