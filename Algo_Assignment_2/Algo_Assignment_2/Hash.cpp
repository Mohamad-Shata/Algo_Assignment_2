#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

int divisionMethod(int key, int tableSize) {
    if (tableSize == 0) return 0;
    return abs(key) % tableSize;
}


int multiplicationMethod(int key, int tableSize) {
    if (tableSize == 0) return 0;
    const double A = 0.6180339887;
    double fractionalPart = fmod(abs(key) * A, 1);
    return static_cast<int>(tableSize * fractionalPart);
}

int midSquareMethod(int key, int tableSize) {
    if (tableSize == 0) return 0;

    long long square = static_cast<long long>(key) * key;
    int numDigits = floor(log10(square)) + 1;

    int digitsNeeded = floor(log10(tableSize - 1)) + 1;
    int middlePosition = numDigits / 2;

    long long divisor = pow(10, middlePosition - (digitsNeeded / 2));
    int middleDigits = (square / divisor) % static_cast<int>(pow(10, digitsNeeded));

    return middleDigits % tableSize;
}

int foldingMethod(int key, int tableSize) {
    if (tableSize == 0) return 0;

    key = abs(key);
    int sum = 0;

    int partSize = floor(log10(tableSize)) + 1;
    while (key > 0) {
        sum += key % static_cast<int>(pow(10, partSize));
        key /= static_cast<int>(pow(10, partSize));
    }

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

    // int keys[] = {123, 4567, 8910, 111213, -1415}; // Sample keys
    // int tableSizes[] = {10, 50, 100, 1000};       // Different table sizes

    // for (int tableSize : tableSizes) {
    //     cout << "\nTable Size: " << tableSize << endl;

    //     for (int key : keys) {
    //         cout << "Key: " << key << endl;
    //         cout << "Division Method: " << divisionMethod(key, tableSize) << endl;
    //         cout << "Multiplication Method: " << multiplicationMethod(key, tableSize) << endl;
    //         cout << "Mid-Square Method: " << midSquareMethod(key, tableSize) << endl;
    //         cout << "Folding Method: " << foldingMethod(key, tableSize) << endl;
    //         cout << "-----------------------------" << endl;
    //     }
    // }

    

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
