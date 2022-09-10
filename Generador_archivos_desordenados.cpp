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

int main() {
    initRandomGenerator();
    generateFile(1024);
    return 0;
}