#include <bits/stdc++.h>
using namespace std;
const int MIN_TO_THREAD = 1000;

template<typename T>
void mergeSort(T arr[], int leftPos, int rightPos);

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

template<typename T>
void mergeSort(T arr[], int leftPos, int rightPos) {
    if (leftPos == rightPos)
        return;
    int midPos = (rightPos + leftPos) / 2;
    mergeSort<T>(arr, leftPos, midPos);
    mergeSort<T>(arr, midPos + 1, rightPos);
    mergeArray<T>(arr, leftPos, midPos, rightPos);
}

template<typename T>
void mergeSortParallel(T arr[], int leftPos, int rightPos) {
    if (leftPos == rightPos)
        return;

    int midPos = (rightPos + leftPos) / 2;
    // if (1 == 2) {
    if (rightPos - leftPos + 1 >= MIN_TO_THREAD) {
        std::thread left(mergeSortParallel<T>,arr, leftPos, midPos);
        std::thread right(mergeSortParallel<T>,arr, midPos + 1, rightPos);
        left.join();
        right.join();
    } else {
        mergeSort<T>(arr, leftPos, midPos);
        mergeSort<T>(arr, midPos + 1, rightPos);
    }

    mergeArray<T>(arr, leftPos, midPos, rightPos);
    // if (rightPos - leftPos + 1 >= (MIN_TO_THREAD + 1) / 2)
    //     printf("THREAD FOR [%8.1d,%8.1d] RUNNING AT CORE %d WITH SIZE %d\n", leftPos, rightPos, sched_getcpu(), rightPos - leftPos + 1);
}

const int N = 10241024;
string checkSorted(int a[]) {
    bool checkSorted = true;
    for (int i = 0; i + 1 < N; i++)
        if (a[i] > a[i + 1])
            checkSorted = false;
    return "CHECK SORTED: " + (string)(checkSorted ? "TRUE":"FALSE") + "\n";
}

int main() {
    freopen("./Merge Sort parallel/OutParallel.txt", "w", stdout);
    srand(time(0));
    int* temp = new int[N];
    int* a = new int[N];
    for (int i = 0; i < N; i++) {
        temp[i] = rand();
        a[i] = temp[i]; // array a used twice
    }
    cout << "WITH N = " << N << endl;
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    mergeSort<int>(a, 0, N - 1);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    cout << checkSorted(a);

    for (int i = 0; i < N; i++)
        a[i] = temp[i];

    chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
    mergeSortParallel<int>(a, 0, N - 1);
    chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
    cout << checkSorted(a);

    int duration_1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    int duration_2 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
    printf("NORMAL TOOK %d microseconds\n", duration_1);
    printf("PARALLEL TOOK %d microseconds\n", duration_2);

    // for (int i = 0; i < N; i++)
    //     cout << a[i] << " ";
    delete[] a;
    delete[] temp;
}