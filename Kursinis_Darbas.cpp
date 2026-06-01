#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Globalûs kintamieji statistikai
long long comparisons = 0;
long long swaps = 0;

// --- 1. Áterpimo rikiavimas (Insertion Sort) ---
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

// --- 2. Sàlajinis rikiavimas (Merge Sort) ---
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

// Testavimo funkcija
void runTest(string algoName, void (*sortFunc)(vector<int>&), vector<int> data) {
    comparisons = 0;
    swaps = 0;

    clock_t start = clock();
    sortFunc(data);
    clock_t stop = clock();

    double duration = (double)(stop - start) / CLOCKS_PER_SEC * 1000000;

    cout << left << setw(15) << algoName << " | Laikas: " << setw(10) << (long)duration
         << " us | Palyginimai: " << setw(10) << comparisons
         << " | Sukeitimai: " << setw(10) << swaps << endl;
}

int main() {
    int sizes[] = {5000, 10000, 50000};

    for (int size : sizes) {
        cout << "\n--- Dydis: " << size << " ---" << endl;
        vector<int> data(size);
        for(int i = 0; i < size; i++) data[i] = rand() % size;

        runTest("Insertion Sort", insertionSort, data);

        // Merge sort kvietimas
        comparisons = 0; swaps = 0;
        clock_t start = clock();
        mergeSort(data, 0, data.size() - 1);
        clock_t stop = clock();
        double duration = (double)(stop - start) / CLOCKS_PER_SEC * 1000000;

        cout << left << setw(15) << "Merge Sort" << " | Laikas: " << setw(10) << (long)duration
             << " us | Palyginimai: " << setw(10) << comparisons
             << " | Sukeitimai: " << setw(10) << swaps << endl;
    }
    return 0;
}
