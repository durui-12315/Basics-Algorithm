#include "../common.h"
#include <cstdlib>
#include <ctime>

template <typename T> int binary_search(const T&, const T*, const int&);
template <typename T> int binary_search_r(const T&, const T*, int, int);

int main() {
    /*二分查找法*/
    const int Len = 100000;
    int arr[Len];
    for(int i = 0, j = 100; i < Len; ++i, j+=7) arr[i] = j;
    int index = binary_search(877, arr, Len);
    HR;
    cout << index << endl;

    /*二分查找递归*/
    int index_ = binary_search_r(877, arr, 0, Len - 1);
    cout << index_;

    /*二分查找分块索引*/
    /*srand(time(0));
    const int Len = 100, N = rand() % 8000;
    int arr[Len], low = 0, high = Len, mid;
    for (int i = Len, j = 0; j < Len; i+=100,++j) arr[j] = i;
    //for(auto x: arr) cout << x << " "; NHR;
    while(low <= high) {
        mid = (low + high) / 2;
        if(N > arr[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    if(arr[mid] < N) ++mid;
    cout << N << " " << arr[mid];*/

    return 0;
}

template <typename T>
int binary_search(const T& val, const T* pa, const int& n) {
    int low = 0, high = n - 1, mid, guess;
    while(low <= high) {
        mid = (low + high) / 2, guess = pa[mid];
        cout << low << " " << mid << " " << high << endl;
        if(val > guess)
            low = mid + 1;
        else if(val < guess)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}

template <typename T>
int binary_search_r(const T& val, const T* pa, int low, int high) {
    if(low > high) return -1;
    int mid = (low + high) / 2, guess = pa[mid];
    if(guess < val)
        return binary_search_r(val, pa, mid + 1, high);
    else if(guess > val)
        return binary_search_r(val, pa, low, mid - 1);
    else
        return mid;
}