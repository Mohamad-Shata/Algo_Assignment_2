#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

int divisionMethod(int key, int tableSize) {
    return key % tableSize;
}

int multiplicationMethod(int key, int tableSize) {
    const double A = 0.6180339887;
    double fractionalPart = key * A - int(key * A);
    return int(tableSize * fractionalPart);
}

int midSquareMethod(int key, int tableSize) {
    int square = key * key;
    int mid = (square / 100) % 100;
    return mid % tableSize;
}

int foldingMethod(int key, int tableSize) {
    int part1 = key / 1000;
    int part2 = key % 1000;
    int sum = part1 + part2;
    return sum % tableSize;
}

void chainingMethod(vector<list<int>>& hashTable, int key, int tableSize) {
    int index = divisionMethod(key, tableSize);
    hashTable[index].push_back(key);
}

void openAddressingMethod(vector<int>& hashTable, int key, int tableSize) {
    int index = divisionMethod(key, tableSize);
    while (hashTable[index] != -1) {
        index = (index + 1) % tableSize;
    }
    hashTable[index] = key;
}

int secondaryHash(int key, int tableSize) {
    return 7 - (key % 7);
}

void doubleHashing(vector<int>& hashTable, int key, int tableSize) {
    int index = divisionMethod(key, tableSize);
    int stepSize = secondaryHash(key, tableSize);
    while (hashTable[index] != -1) {
        index = (index + stepSize) % tableSize;
    }
    hashTable[index] = key;
}

void printChainTable(const vector<list<int>>& chainTable) {
    for (int i = 0; i < chainTable.size(); ++i) {
        cout << "Bucket " << i << ": ";
        for (int key : chainTable[i]) {
            cout << key << " -> ";
        }
        cout << "null" << endl;
    }
}

void printHashTable(const vector<int>& hashTable, const string& tableName) {
    cout << "Contents of the " << tableName << ":" << endl;
    for (int i = 0; i < hashTable.size(); ++i) {
        cout << "Index " << i << ": ";
        if (hashTable[i] == -1) {
            cout << "null";
        } else {
            cout << hashTable[i];
        }
        cout << endl;
    }
}


int main() {
    int tableSize = 10;

    vector<list<int>> chainTable(tableSize);
    chainingMethod(chainTable, 25, tableSize);
    chainingMethod(chainTable, 35, tableSize);

    vector<int> openAddressTable(tableSize, -1);
    openAddressingMethod(openAddressTable, 25, tableSize);
    openAddressingMethod(openAddressTable, 35, tableSize);

    vector<int> doubleHashTable(tableSize, -1);
    doubleHashing(doubleHashTable, 25, tableSize);
    doubleHashing(doubleHashTable, 35, tableSize);

    printChainTable(chainTable);

    printHashTable(openAddressTable , "Open Addressing Table");

    printHashTable(doubleHashTable,  "Double Hashing Table");
    

    return 0;
}
