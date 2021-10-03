#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const int N = 12;
const int M = 8;

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