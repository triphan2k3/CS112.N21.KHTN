#include <bits/stdc++.h>
#define TASK ""
#define pb push_back
#define F first
#define S second
#define FOR(i, a, b) for (int i=a; i<=b; i++)
#define FOr(i, a, b) for (int i=a; i<b ; i++)
#define FOD(i, a, b) for (int i=a; i>=b; i--)
#define FOd(i, a, b) for (int i=a; i>b ; i--)
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;


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

const int MIN_TO_THREAD = 100;
template<typename T>
void mergeSort(T arr[], int leftPos, int rightPos) {
    if (leftPos == rightPos)
        return;

    int midPos = (rightPos + leftPos) / 2; 
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
        printf("THREAD FOR [%7.1d,%7.1d]\tDONE! WITH SIZE %d\n", leftPos, rightPos, rightPos - leftPos + 1);
}

const int N = 1024102;
int main() {
    freopen("OutputMergeSortWithOutThread.txt", "w", stdout);
    srand(time(0));
    int* a = new int[N];
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 10;
        // std::cout << a[i] << " ";
    }
    // cout << endl;

    mergeSort<int>(a, 0, N - 1);
    // for (int i = 0; i < N; i++) 
        // std::cout << a[i] << " ";
    delete[] a;
}