#include "../common.h"
#include <cstdlib>
#include <ctime>
#include "../_/SimMatrix.h"

const int Size = 500;
int arr[Size + 1];

void set_data() {
    srand(time(0));
    arr[0] = -INT_MAX;
    for(int i = 1; i <= Size; ++i) arr[i] = rand() % 16384;
}

void show() {
    for(const auto x: arr) cout << x << " ";
}

void merge(int* src, int* dst, int start, int middle, int end) {
    int start_ = middle + 1, i = start;
    while(start <= middle && start_ <= end)
        dst[i++] = src[start] < src[start_] ? src[start++] : src[start_++];
    if(start > middle)
        while(start_ <= end) dst[i++] = src[start_++];
    else
        while(start <= middle) dst[i++] = src[start++];
}

void merge_pass(int* src, int* dst, const int unit, const int length) {
    int i = 1, end = length - 2 * unit + 1;
    while(i <= end) {
        merge(src, dst, i, i + unit - 1, i + 2 * unit - 1);
        i += 2 * unit;
    }
    if(length - i + 1 > unit)
        merge(src, dst, i, i + unit - 1, length);
    else
        while(i <= length) dst[i] = src[i], ++i;
}

template <typename T> void quick_sort(T* pa, int low, int high);

/*已学排序算法：桶排序、冒泡排序、比较排序、直接插入排序、希尔排序、堆排序、归并排序、快速排序*/
int main() {
    set_data();

    /*直接插入排序：在有序中把值插入合适的位置*/
    /*for (int i = 2, j; i <= Size; ++i){
        if(arr[i] < arr[i - 1]) {
            arr[0] = arr[i];
            for (j = i - 1; arr[j] > arr[0]; --j) arr[j + 1] = arr[j];
            arr[j + 1] = arr[0];
        }
    }*/

    /*希尔排序：优化版的直接插入排序（跳跃式比较）*/
    /*int i, j, increment = Size;
    do {
        increment = increment / 3 + 1;  //增量序列
        for(i = increment + 1; i <= Size; ++i)
            if(arr[i] < arr[i - increment]) {
                arr[0] = arr[i];
                for(j = i - increment; j > 0 && arr[j] > arr[0]; j -= increment)
                    arr[j + increment] = arr[j];
                arr[j + increment] = arr[0];
            }
    } while (increment > 1);*/

    /*归并排序*/
    /*int* tmp = new int[Size + 1];
    for (int u = 1; u < Size; u *= 2) {
        merge_pass(arr, tmp, u, Size);
        u *= 2;
        merge_pass(tmp, arr, u, Size);
    }
    delete [] tmp;*/

    /*快速排序优化版*/
    quick_sort(arr, 1, Size);

    show(); NHR;
    for(int i = 1; i < Size; ++i) cout << (arr[i + 1] - arr[i] >= 0 ? "" : "error ");

    return 0;
}

template <typename T>
void quick_sort(T* pa, int low, int high) {  //快速排序优化
    if(high - low > 7) {  //数组长度阈值
        //尾递归优化：循环代替高子表递归
        int middle, left, right, pivot;
        while(low < high) {
            middle = (low + high) / 2, left = low, right = high;
            //枢轴优化：三数取中
            if(pa[low] > pa[high]) swap(pa[low], pa[high]);
            if(pa[middle] > pa[high]) swap(pa[middle], pa[high]);
            if(pa[middle] > pa[low]) swap(pa[middle], pa[low]);
            pivot = pa[low];
            //交换优化：直接赋值代替
            pa[0] = pivot;
            while(left < right) {
                while(left < right && pa[right] >= pivot) right--;
                pa[left] = pa[right];
                while(left < right && pa[left] <= pivot) left++;
                pa[right] = pa[left];
            }
            pa[left] = pa[0];
            quick_sort(pa, low, left - 1);  //低子表递归排序
            low = right + 1;
        }
    } else
        //小数组优化：使用插入排序
        for (int i = low + 1, j; i <= high; ++i)
            if(arr[i] < arr[i - 1]) {
                arr[0] = arr[i];
                for (j = i - 1; arr[j] > arr[0]; --j) arr[j + 1] = arr[j];
                arr[j + 1] = arr[0];
            }
}