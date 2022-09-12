#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <bitset>
#include <cstring>

#define PAGE_SIZE 256

using namespace std;

int partition(int arr[], int start, int end){

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(int arr[], int start, int end) {

    if (start >= end)
        return;

    int p = partition(arr, start, end);

    quickSort(arr, start, p - 1);

    quickSort(arr, p + 1, end);

    FILE *regularFile = fopen("Archivo_ordenado_QS.txt", "w+");
    for (int i = 0; i < 256; i++) {
        std::string newValueOrdered = to_string(arr[i]).append(",");
        fwrite(newValueOrdered.data(), newValueOrdered.length(), 1, regularFile);
    }
    fclose(regularFile);

}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        if(min_idx!=i)
            swap(&arr[min_idx], &arr[i]);
    }
    FILE *regularFile = fopen("Archivo_ordenado_SS.txt", "w+");
    for (int i = 0; i < 256; i++) {
        std::string newValueOrdered = to_string(arr[i]).append(",");
        fwrite(newValueOrdered.data(), newValueOrdered.length(), 1, regularFile);
    }
    fclose(regularFile);
}

void insertionSort(int arr[], int nElements)
{
    int x, key, y;
    for (x = 1; x < nElements; x++)
    {
        key = arr[x];
        y = x - 1;
        while (y >= 0 && arr[y] > key)
        {
            arr[y + 1] = arr[y];
            y = y - 1;
        }
        arr[y + 1] = key;
    }
    FILE *regularFile = fopen("Archivo_ordenado_IS.txt", "w+");
    for (int i = 0; i < 256; i++) {
        std::string newValueOrdered = to_string(arr[i]).append(",");
        fwrite(newValueOrdered.data(), newValueOrdered.length(), 1, regularFile);
    }
    fclose(regularFile);
}

void initRandomGenerator() {
    srand(time(0));
}
int* generateFile() {

    static int arr[256];
    for (int cantidad = 0; cantidad < 256; cantidad++) {
        FILE *binaryFile = fopen("Archivo_binario.bin", "wb+");
        FILE *regularFile = fopen("Archivo_desordenado.txt", "w+");

        for (int i = 0; i < 256; i++) {
            int newValue = rand();
            std::string newValueStr = to_string(newValue).append(",");
            fwrite(&newValue, sizeof(int), 1, binaryFile);
            fwrite(newValueStr.data(), newValueStr.length(), 1, regularFile);

            arr[cantidad] = newValue;

        }
        fclose(regularFile);
        fclose(binaryFile);
    }
    return arr;

}


int main(int argc, char ** argv) {

    initRandomGenerator();
    if ( strcmp(argv[1], "QS") == 0 ){
        int* ptr = generateFile();
        quickSort(ptr,0,255);
    }
    else if ( strcmp(argv[1], "SS") == 0 ){
        int* ptr = generateFile();
        selectionSort(ptr,256);
    }
    else{
        int* ptr = generateFile();
        insertionSort(ptr,256);
    }
    return 0;
}