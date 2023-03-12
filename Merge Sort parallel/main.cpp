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

template<typename T> 
void parallelMergeAux(T A[], int p1, int r1, int p2, int r2, T B[], int p3) {
    if (p1 > r1 && p2 > r2)
        return;
    if (r1 - p1 < r2 - p2) {
        swap(r1, r2);
        swap(p1, p2);
    }
    int q1 = (r1 + p1) >> 1;
    T x = A[q1];
    int q2 = findPosition(A, p2, r2, x);
    int q3 = p3 + (q1 - p1) + (q2 - p2);
    std::thread left(parallelMergeAux<T>, A, p1, q1 - 1, p2, q2 - 1, B, p3);
    B[q3] = x;
    std::thread right(parallelMergeAux<T>, A, q1 + 1, r1, q2, r2, B, q3 + 1);
    left.join();
    right.join();
}

const int MIN_TO_THREAD = 1000;
template<typename T>
void mergeParallel(T arr[], int leftPos, int midPos, int rightPos) {
    if (rightPos - leftPos + 1 >= MIN_TO_THREAD) {
        T B = new T[rightPos - leftPos + 1];
        parallelMergeAux<T>(A, leftPos, midPos, midPos + 1, rightPos, B, 0);
        delete[] B;
    } else 
        mergeArray(arr[], leftPos, midPos, rightPos);

}

template<typename T>
void mergeSortParallel(T arr[], int leftPos, int rightPos) {
    if (leftPos == rightPos)
        return;

    int midPos = (rightPos + leftPos) / 2;
    if (rightPos - leftPos + 1 >= MIN_TO_THREAD) {
        std::thread left(mergeSortParallel<T>,arr, leftPos, midPos);
        std::thread right(mergeSortParallel<T>,arr, midPos + 1, rightPos);
        left.join();
        right.join();
    } else {
        mergeSort<T>(arr, leftPos, midPos);
        mergeSort<T>(arr, midPos + 1, rightPos);
    }
    
    mergeParallel<T>(arr, leftPos, midPos, rightPos);
    // if (rightPos - leftPos + 1 >= (MIN_TO_THREAD + 1) / 2)
    //     printf("THREAD FOR [%8.1d,%8.1d] RUNNING AT CORE %d WITH SIZE %d\n", leftPos, rightPos, sched_getcpu(), rightPos - leftPos + 1);
}


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
    int* temp = new int[N];
    int* a = new int[N];
    for (int i = 0; i < N; i++) {
        temp[i] = rand();
        a[i] = temp[i]; // array a used twice
    }



    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    mergeSort<int>(a, 0, N - 1);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    mergeSortParallel<int>(a, 0, N - 1);
    int duration_1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("TOOK %d microseconds\n", duration_1);
    
    bool checkSorted = true;
    for (int i = 0; i + 1 < N; i++)
        if (a[i] > a[i + 1])
            checkSorted = false;
    cout << "CHECK SORTED: " << (checkSorted ? "TRUE":"FALSE");
    delete[] a;
}