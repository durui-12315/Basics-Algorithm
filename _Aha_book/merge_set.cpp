#include "../common.h"
#include <iomanip>

const int merge[][2] = {
        1, 2,   3, 4,   5, 2,   4, 6,   2, 6,
        8, 7,   9, 7,   1, 6,   2, 4
}, Members = 10, Merges = 9;
int merge_set[Members + 1] {-1};

void init() {
    for (int i = 1; i <= Members ; ++i) merge_set[i] = i;
}

void show(int loop) {
    cout << left << setw(2) << loop << setw(2) << ":";
    for (int i = 1; i <= Members; ++i) cout << setw(2) << merge_set[i] << " ";
    cout << endl << setw(2) << "" << setw(2) << "";
    for (int i = 1; i <= Members; ++i) cout << setw(2) << i << " ";
    NHR;
}

int get_boss(int i) {
    if(merge_set[i] == i) return i;
    return get_boss(merge_set[i]);
    //return merge_set[i] = get_boss(merge_set[i]);  //压缩路径
}

void set_merge(int a, int b, int loop) { //先找到两点的祖先节点，判断是否相同，不相同则执行“靠左原则”
    int t1 = get_boss(a);
    int t2 = get_boss(b);
    if(t1 != t2) merge_set[t2] = t1;
    show(loop);
}

int main() {
    /*并查集*/
    init();
    for (int i = 0; i < Merges; ++i)
        set_merge(merge[i][0], merge[i][1], i + 1);
    return 0;
}