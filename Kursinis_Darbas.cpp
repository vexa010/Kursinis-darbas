#include <iostream>
#include <vector>
#include <chrono> // Tikslesniam laikui
#include <iomanip>
#include <cstdlib>
#include <functional>

using namespace std;

// Globalūs kintamieji statistikai
long long comparisons = 0;
long long swaps = 0;

// --- 1. Įterpimo rikiavimas (Insertion Sort) ---
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// --- 2. Sąlajinis rikiavimas (Merge Sort) ---
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            swaps++;
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Profesionalus testavimo wrapper'is
void runTest(string algoName, function<void(vector<int>&)> sortFunc, vector<int> data) {
    comparisons = 0;
    swaps = 0;

    auto start = chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << left << setw(15) << algoName << " | Laikas: " << setw(10) << duration
         << " us | Palyginimai: " << setw(10) << comparisons
         << " | Sukeitimai: " << setw(10) << swaps << endl;
}

int main() {
    int sizes[] = {5000, 10000, 50000};

    for (int size : sizes) {
        vector<int> data(size);
        for(int i = 0; i < size; i++) data[i] = rand() % size;

        cout << "\n--- Dydis: " << size << " ---" << endl;

        // Testuojame Insertion Sort
        runTest("Insertion Sort", insertionSort, data);

        // Testuojame Merge Sort (naudojame lambda funkciją, kad atitiktų formatą)
        runTest("Merge Sort", [](vector<int>& v) { 
            mergeSort(v, 0, v.size() - 1); 
        }, data);
    }
    return 0;
}
