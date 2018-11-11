#include "../common.h"
#include <ctime>
#include <cstdlib>

template <typename T>
void selection_sort(T* pt, const int n) {
    T tmp, max;
    for (int i = n, ti; i > 1; --i) {
        max = pt[0], ti = 0;
        for (int j = 1; j < i; ++j)
            if(max < pt[j]) max = pt[j], ti = j;
        tmp = max, pt[ti] = pt[i - 1], pt[i - 1] = tmp;
    }
}

int box_div(int width, int height) {  //田地分割最大正方体
    int bigger, smaller, mod;
    if(width >= height)
        bigger = width, smaller = height;
    else
        bigger = height, smaller = width;
    mod = bigger % smaller;
    if(mod == 0)
        return smaller;
    else
        box_div(mod, smaller);
}

int box_div_(int width, int height) {
    while(width != height) {
        if(width > height)
            width -= height;
        else
            height -= width;
    }
    return width;
}

int main() {
    /*选择排序*/
    /*const int Len = 40;
    int arr[Len];
    srand(time(0));
    for(int& x: arr) x = rand() % 10000;
    selection_sort(arr, Len);
    for(const int x: arr) cout << x << " ";*/

    /*递归分治思想*/
    int width = 200, height = 120, box;
    box = box_div(width, height);  //公约数
    cout << box << " " << width * height / box / box << endl;

    /*循环解决公约数问题*/
    box = box_div_(width, height);
    cout << box << " " << width * height / box / box << endl;

    return 0;
}