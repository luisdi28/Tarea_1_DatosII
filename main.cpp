#include<iostream>
#include<stdlib.h>
#include<random>
#include<fstream>
#include <string>
#include <bitset>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

using namespace std;

void crear_paginas(){

    int multiplicador = 1;

    int num1 = 4;
    int num2 = 1;

    for (int cont = 1; cont < 7; cont++){

        ofstream outfile ("Archivo"+ std::to_string(cont) +".txt");

        for (int cantidad = 0; cantidad < 256*multiplicador; cantidad++) {
            int valor;
            std::random_device rd;
            std::mt19937 eng(rd());
            std::uniform_int_distribution<int> dist(0, 255);
            valor = dist(eng);
            if (cantidad < 255){
                outfile << valor << ", ";
            }
            else{
                outfile << valor;
            }

            std::string binary = std::bitset<8>(valor).to_string(); //to binary
            std::cout<<binary<<",";

            unsigned long decimal = std::bitset<8>(binary).to_ulong();
            std::cout<<decimal<<"\n";

        }

        multiplicador = num2 * num1;
        if (num2 >= 3){
            num2+=3;
        }
        else{
            num2+=1;
        }

        outfile.close();

    }

}

int main() {

    crear_paginas();
}