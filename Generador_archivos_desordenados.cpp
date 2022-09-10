#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PAGE_SIZE 256

using namespace std;

void printPage(int* page, int pageSize) {
    for (int i = 0; i < pageSize; i++) {
        cout << page[i] << endl;
    }
}
void printFile(FILE *fp) {
    int page[PAGE_SIZE];
    int readBytes = fread(&page, sizeof(int), PAGE_SIZE, fp);
    while (readBytes > 0) {
        cout << "Reading page..." << endl;
        printPage(page, PAGE_SIZE);
        readBytes = fread(&page, sizeof(int), PAGE_SIZE, fp);
    }
}

void initRandomGenerator() {
    srand(time(0));
}
void generateFile(int size) {

    int multiplicador = 1;

    int num1 = 4;
    int num2 = 1;

    for (int cont = 1; cont < 7; cont++) {
        for (int cantidad = 0; cantidad < 256 * multiplicador; cantidad++) {
            FILE *binaryFile = fopen("binary.bin", "wb+");
            FILE *regularFile = fopen("regular.txt", "w+");
            int intCount = size / sizeof(int);
            for (int i = 0; i < intCount; i++) {
                int newValue = rand();
                std::string newValueStr = to_string(newValue).append(",");
                fwrite(&newValue, sizeof(int), 1, binaryFile);
                fwrite(newValueStr.data(), newValueStr.length(), 1, regularFile);
            }

            fclose(regularFile);
            fclose(binaryFile);

        }
        multiplicador = num2 * num1;
        if (num2 >= 3) {
            num2 += 3;
        } else {
            num2 += 1;
        }
    }
}

int partition(int page[], int start, int end){

    int pivot = page[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (page[i] <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    swap(page[pivotIndex], page[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (page[i] <= pivot) {
            i++;
        }

        while (page[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(page[i++], page[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(int page[], int start, int end)
{

    if (start >= end)
        return;

    int p = partition(page, start, end);

    quickSort(page, start, p - 1);

    quickSort(page, p + 1, end);
}

int main() {
    initRandomGenerator();
    //quitar esto cuando se solucione lo del nombre del archivo
    generateFile(1024);
    FILE *fp = fopen("binary.bin", "rb+");
    if (fp == nullptr){
        cout << "Unexpected error" << endl;
        return 1;
    }
    printFile(fp);
    return 0;
}