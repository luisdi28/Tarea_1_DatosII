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

int* a;

int crear_paginas(){

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

            a = &valor;

            FILE *fp;
            fp = fopen("binary.bin", "wb+");
            if (fp != nullptr){
                for (int i = 0; i < 256; i++){
                    fwrite (a, sizeof(int),1,fp);
                }
                fseek(fp,0,SEEK_SET);
                int buffer[256];
                int readBytes = fread(&buffer, sizeof(int), 256,fp);
                cout << "Bytes read:" << readBytes << endl;

                fclose(fp);
                if (readBytes <= 0){
                    return 1;
                }
                for (int i = 0; i < 256; i++){
                    cout << buffer[i] << endl;
                }
            }
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

void printFile(FILE *fp) {
    int page[PAGE_SIZE];
    int readBytes = fread(&page, sizeof(int), PAGE_SIZE, fp);
    while (readBytes > 0) {
        cout << "Reading page" << endl;
        printPage((int *) &page, PAGE_SIZE);
        readBytes = fread(&page, sizeof(int), PAGE_SIZE, fp);
    }
}

int main() {
    crear_paginas();
}