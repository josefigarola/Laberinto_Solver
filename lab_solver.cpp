// Jose Miguel Figarola Prado
// A01632557
// 30 sept 2021
// Laberynth Solver using backtracking

#include <iostream>
#include <fstream>
using namespace std;

const int N = 4;

int main() {
    ifstream laberinto;
    laberinto.open("4x4.txt");

    if (laberinto.fail()) {
        cerr << "File not created!" << endl;
        exit(1);
    }
    else{
        cout << "Todo bien" << endl;
    }

    laberinto.close();
    return 0;
}
