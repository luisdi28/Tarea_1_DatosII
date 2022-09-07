#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<random>
#include<fstream>
#include <string>
#include <bitset>

#define PAGE_SIZE 256

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

        ofstream outfile ("Archivo_Desordenado"+ std::to_string(cont) +".txt");

        for (int cantidad = 0; cantidad < 256*multiplicador; cantidad++) {
            int valor;
            std::random_device rd;
            std::mt19937 eng(rd());
            std::uniform_int_distribution<int> dist(0, 120);
            valor = dist(eng);
            outfile << valor << ", ";

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

void printPage(int* page, int pageSize){
    for (int i = 0; i < pageSize; i++){
        cout << page[i] << endl;
    }
}

void printFile(FILE *fp){
    int page[PAGE_SIZE];
    int readBytes = fread(&page, sizeof(int), PAGE_SIZE, fp);
    while (readBytes > 0) {
        cout << "Reading page" << endl;
        printPage((int *) &page, PAGE_SIZE),
                readBytes = fread(&page, sizeof(int), PAGE_SIZE, fp);
    }
}

int main() {
    FILE *fp = fopen("binary.bin","rb");
    if (fp == nullptr){
        cout << "Unexpected error" << endl;
        return 1;
    }
    printFile(fp);
    fclose(fp);
    return 0;
    crear_paginas();
}