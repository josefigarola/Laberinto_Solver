// Jose Miguel Figarola Prado
// A01632557
// 30 sept 2021
// Laberynth Solver using backtracking

#include <iostream>
#include <fstream>
using namespace std;

int m;
int n;
const int N = 4;
string laberinto[N][N];
string current_pos[0][0];

void printLab(string tablero[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tablero[i][j];
        }
        cout << endl;
    }
}

bool isSafe(string board[N][N], int row, int col){
    // Checar los casos de movimiento

    // Si es cero no se puede mover
    if(board[row+1][col] == "0"){
        return false; // No se puede mover
    }
    // Checar derecha
    if(board[row][col+1] == "0"){
        return false; // No se puede mover
    }
    // Checar izquierda
    if(board[row][col-1] == "0"){
       return false; // No se puede mover
    }
    if(board[row-1][col] == "0"){
        return false; // No se puede mover
    }

    return true;
}

bool solveUtil(string tablero[N][N], int x, int y){

    // Mejor de los casos
    if(current_pos[x][y] == tablero[N-1][N-1] ){ // La posición inicial es el final
        cout << "Tablero completado" << endl;
        return true; // Ya esta resuelto el problema
    }

    // APLICAR LA RECURSIVIDAD
    while(current_pos[x][y] != tablero[N-1][N-1]){
        if(isSafe(laberinto,x,y)){
            current_pos[x][y] = "1";
            // Recursividad posiciones
            if(solveUtil(laberinto,x,y)){
                return true;
            }
            else{
                laberinto[x][y] = "0";
            }
        }
    }

    return false; // No se puede mover
}


// Utilizar solveUtil (recursiva)
// True = tiene solucion y se imprime
// False = no tiene solucion
bool solve(string board[N][N]){

    if(!solveUtil(laberinto,0,0)){ // Si no tiene solucion el tablero o hay un error
        cout << "No hay solución" << endl; // Algo salio mal
        return false;
    }
    printLab(laberinto); // El tablero si tiene solucion y se imprime
    return true;
}

int main() {
    ifstream file;
    file.open("4x4.txt");

    if (file.fail()) {
        cerr << "File not created!" << endl;
        exit(1);
    }
    else{
        cout << "File opened correctly" << endl;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            file >> laberinto[i][j];
        }
    }

    file.close();

    cout << "Initial board" << endl;
    printLab(laberinto);

    solve(laberinto);

    cout << "Path founded" << endl;
    printLab(laberinto);

    return 0;
}
