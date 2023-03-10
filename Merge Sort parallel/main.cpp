#include <bits/stdc++.h>
using namespace std;

template<typename T>
void mergeArray(T arr[], int leftPos, int midPos, int rightPos) {
    int arrSize = rightPos - leftPos + 1;
    T* tempArr = new T[arrSize];
    for (int i = 0, leftId = leftPos, rightId = midPos + 1; i < arrSize; i++) {
        if (leftId > midPos)
            tempArr[i] = arr[rightId++];
        else if (rightId > rightPos)
            tempArr[i] = arr[leftId++];
        else if (arr[leftId] < arr[rightId])
            tempArr[i] = arr[leftId++];
        else 
            tempArr[i] = arr[rightId++];
    }
    for (int i = leftPos; i <= rightPos; i++)
        arr[i] = tempArr[i - leftPos];
    delete[] tempArr;
}

const int MIN_TO_THREAD = 1000;
template<typename T>
void mergeSort(T arr[], int leftPos, int rightPos) {
    if (leftPos == rightPos)
        return;

    int midPos = (rightPos + leftPos) / 2;
    // if (1 == 2) {
    if (rightPos - leftPos + 1 >= MIN_TO_THREAD) {
        std::thread left(mergeSort<T>,arr, leftPos, midPos);
        std::thread right(mergeSort<T>,arr, midPos + 1, rightPos);
        left.join();
        right.join();
    } else {
        mergeSort<T>(arr, leftPos, midPos);
        mergeSort<T>(arr, midPos + 1, rightPos);
    }

    mergeArray<T>(arr, leftPos, midPos, rightPos);
    if (rightPos - leftPos + 1 >= (MIN_TO_THREAD + 1) / 2)
        printf("THREAD FOR [%8.1d,%8.1d] RUNNING AT CORE %d WITH SIZE %d\n", leftPos, rightPos, sched_getcpu(), rightPos - leftPos + 1);
}

const int N = 10241024;
int main() {
    freopen("./Merge Sort parallel/Output_Parallel.txt", "w", stdout);
    srand(time(0));
    int* a = new int[N];
    for (int i = 0; i < N; i++) {
        a[i] = rand();
    }

    chrono::high_resolution_clock::time_point tStart = chrono::high_resolution_clock::now();
    mergeSort<int>(a, 0, N - 1);
    chrono::high_resolution_clock::time_point tEnd = chrono::high_resolution_clock::now();
    
    int tm_duration = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart).count();
    printf("TOOK %d microseconds\n", tm_duration);
    
    bool checkSorted = true;
    for (int i = 0; i + 1 < N; i++)
        if (a[i] > a[i + 1])
            checkSorted = false;
    cout << "CHECK SORTED: " << (checkSorted ? "TRUE":"FALSE");
    delete[] a;
}