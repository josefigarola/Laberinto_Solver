// Author: Jose Miguel Figarola
// 30 sept 2021
// This programme solves a MxN maze
// Implemenenting backtracking
// bool solve and bool solveUtil functions use BT
// isSafe checks the range for it to be a save move
// printLab displays the Labrynth
// The complexity of the algorithm is O(n^2)

/*
CASES TO BE SOLVE
Case 1: 4x4
Maze
1 0 0 0
1 1 0 1
0 1 0 0
1 1 1 1
Solved Maze
x000
xx01
0x00
1xxx

Case 2: 5x6
Maze
1 1 0 1 0
1 1 1 1 0
1 0 0 0 0
1 1 1 1 1
1 0 0 0 1
Solved Maze
x1010
x1110
x0100
xxxxx
1010x
1010x

Case 3: 12x8
Maze
111100000111
100111000101
101101110101
101000010101
011111110101
010000000101
011111111101
000000000001
Solved Maze
xxxx00000xxx
100x11000x0x
10xx01110x0x
10x000010x0x
0xx111110x0x
0x0000000x0x
0xxxxxxxxx0x
00000000000x

Case 4: 21x21
Maze
110000000000000000000
111111011111011111110
010000010001010000010
011111110111110111010
010000000001010100000
010101011101011111110
000101000100000000010
011111111111111111010
000100010000000001010
011101110101111111110
000001010100010000010
011111011101010101110
010000010001000101010
010111011101110101010
010001010101000101000
011111010101111111110
010001000000000101000
010101110111010101110
010101000001010100000
010111111101111111110
000000000000000000011
Solved Maze
x10000000000000000000
xx11110xxxxx011111110
0x00000x000x010000010
0xxxxxxx011xxx0111010
0100000000010x0100000
0101010111010xxxxxxx0
0001010001000000000x0
0111111111111111110x0
0001000100000000010x0
0111011101011111111x0
0000010101000100000x0
01111101110101010xxx0
01000001000100010x010
01011101110111010x010
01000101010100010x000
011111010101111xxx110
010001000000000x01000
010101110111010x01110
010101000001010x00000
010111111101111xxxxx0
0000000000000000000xx

Case 5: 1x1
Maze
1
Solved Maze
x
Case 6: 5x5
Maze
10000
11000
01000
01110
00010
Solved Maze
No solution
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const int N = 5;
const int M = 6;

string laberinto[M][N];

// Esta funcion imprime el laberitno
void printLab(string tablero[M][N]){
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << tablero[i][j];
        }
        cout << endl;
    }
}

// En esta funcion se checan los parametros
// x,y no se salgan de la matriz
bool isSafe(string board[M][N], int x, int y){
    // Si la posicion (x,y) se sale de la matriz
    if (x >= 0 && x < M && y >= 0 && y < N && board[x][y] == "1"){
        return true;
    }

    return false;

}

bool solveUtil(string tablero[M][N], int x, int y){

    // Mejor de los casos
    if(x == M - 1 && y == N - 1 && tablero[x][y] == "1"){ // La posición inicial es la final
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
        // Mover se en x (izquierda)
        if (solveUtil(tablero, x - 1, y)) {
            return true; // Se puede mover por ahi
        }

        // Moverse en y (abajo)
        if (solveUtil(tablero, x, y + 1)){
            return true; // Se puede mover por ahi
        }
        // Moverse en y (arriba)
        if (solveUtil(tablero, x, y - 1)){
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
bool solve(string board[M][N]){

    if(!solveUtil(board,0,0)){ // Si no tiene solucion el tablero o hay un error
        cout << "There's no solution" << endl; // Algo salio mal
        exit(1);
    }
    return true;
}

int main() {

    ifstream file;
    int res = 0;

    cout << "Do NOT forget to change M y N values" << endl;
    // El primer caso de prueba tiene solución
    cout << "1 : 4x4" << endl;
    // El segundo caso de prueba tiene solucion
    cout << "2 : 5x6" << endl;
    // El tercer caso de prueba tiene solucion
    cout << "3 : 12x8" << endl;
    // El cuarto caso de prueba tiene solucion
    cout << "4 : 21x21" << endl;
    // El quinto caso de prueba tiene solucion inicial
    cout << "5 : 1x1" << endl;
    // El sexto caso de prueba no tiene solucion
    cout << "6 : 5x5" << endl;
    cout << "Cual laberinto quiere resolver?: " << endl;
    cin >> res;

    // Eleccion del archivo donde se encuentra el maze
    if(res == 1){ // Caso
        file.open("4x4.txt"); // Abrir el archivo
    }else if(res == 2){
        file.open("5x6.txt");
    }else if(res == 3){
        file.open("12x8.txt");
    }else if(res == 4){
        file.open("21x21.txt");
    }else if(res == 5){
        file.open("1x1.txt");
    }
    else if(res == 6){
        file.open("5x5.txt");
    }

    // Si no se puede abrur ek archivo se detiene el proceso
    if (file.fail()) {
        cerr << "File not created!" << endl;
        exit(1);
    }
    else{
        cout << "File opened correctly" << endl;
    }

    // Se guarda el archivo en una matriz MxN
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++) {
            file >> laberinto[i][j];
        }
    }

    file.close();

    // Inicia el proceso de solucion
    cout << "Initial board" << endl;
    printLab(laberinto);
    cout << endl;

    solve(laberinto);

    cout << "Path founded" << endl;
    printLab(laberinto);

    return 0;
}