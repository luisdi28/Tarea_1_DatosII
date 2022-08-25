#include<iostream>
#include<stdlib.h>
#include<random>
#include<fstream>

using std::cout;
using std::endl;
using std::string;

using namespace std;

int valor = 0;

void crear_paginas(){
    int co = 6;
    for (int i = 1; i <= co; i++)
    {
        ofstream file;
        file.open (std::to_string(i) + ".txt");

        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<int> dist(0, 5000);

        for (size_t i = 0; i < 256; i++) {
            valor = dist(eng);
            cout << to_string(valor) << ", ";
            file << to_string(valor) << ", ";
        }

        file.close();
    }
}

int main() {
    crear_paginas();
}