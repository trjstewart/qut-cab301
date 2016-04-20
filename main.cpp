#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

// Constants
const int ARRAY_MIN = 0;
const int ARRAY_MAX = 1000;
const int ARRAY_INC = 100;
const string resultsPath = "C:\\projects\\qut-cab301\\results\\";
int testSets[][3] = {
        {0, 1000, 10},
        {0, 2000, 10},
        {0, 4000, 10},
        {0, 8000, 10},
        {0, 10000, 100},
        {0, 20000, 100},
        {0, 40000, 100},
        {0, 60000, 1000},
        {0, 80000, 1000},
        {0, 100000, 1000}
};

// Globals
bool debug = false;

// Function Definitions
unsigned int *populateRandomArray(const int size);
unsigned long long BubbleSort(unsigned int toSort[], int arraySize);
void TestSortingAlgorithm(int setMin, int setMax, int setInc);
void MultiTestSortingAlgorithm(int tests[][3], int numTests);

int main() {
    //TestSortingAlgorithm(ARRAY_MIN, ARRAY_MAX, ARRAY_INC);
    MultiTestSortingAlgorithm(testSets, (sizeof(testSets) / 3) / sizeof(int));
    return 0;
}

void MultiTestSortingAlgorithm(int tests[][3], int numTests) {
    for (int i = 0; i < numTests; i++) {
        TestSortingAlgorithm(tests[i][0], tests[i][1], tests[i][2]);
        cout << "Completed Test Set: " << tests[i][0] << " through " << tests[i][1] << " in increments of " << tests[i][2] << "." << endl << endl;
    }
}

void TestSortingAlgorithm(int setMin, int setMax, int setInc) {
    cout << "Starting Test Set: " << setMin << " through " << setMax << " in increments of " << setInc << "." << endl;

    clock_t timer;

    ofstream outputCSV(resultsPath + to_string(setMin) + "x" + to_string(setMax) + "x" + to_string(setInc) + ".csv");
    outputCSV << "N,Time(s),Operations"<<endl;

    for (int i = setMin; i <= setMax; i += setInc) {
        unsigned int *randomArray = populateRandomArray(i);

        timer = clock();
        unsigned int operations = BubbleSort(randomArray, i);
        timer = clock() - timer;

        outputCSV << i << "," << ((float)timer) / CLOCKS_PER_SEC << "," << operations << endl;
    }

    outputCSV.close();
}

unsigned int *populateRandomArray(const int size) {
    static unsigned int array[100000000];

    srand( (unsigned)time( NULL ) );
    for (int i = 0; i < size; i++) array[i] = (unsigned int)rand();

    if (debug) {
        cout << "Generated Array..." << endl;
        for (int i = 0; i < size; i++) (i == size - 1) ? cout << array[i] << endl << endl : cout << array[i] << ", ";
    }

    return array;
}

unsigned long long BubbleSort(unsigned int array[], int arraySize) {
    bool swap = true;
    unsigned long long operations = 0;

    while (swap) {
        swap = false;

        for (int i = 0; i < arraySize - 1; i++) {
            if (array[i + 1] < array[i]) {
                int nextPos = i + 1;
                unsigned int temp;

                temp = array[i];
                array[i] = array[nextPos];
                array[nextPos] = temp;

                operations++;
                swap = true;
            }
        }
    }

    if (debug) {
        cout << "Sorted Array..." << endl;
        for (int i = 0; i < arraySize; i++) (i == arraySize - 1) ? cout << array[i] << endl << endl : cout << array[i] << ", ";
    }

    return operations;
}