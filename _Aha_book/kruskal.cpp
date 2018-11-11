#include "../common.h"
#include <vector>
#include <algorithm>

const int map[][3] = {  //已按权重小到大排序
        1, 2, 1,    1, 3, 2,    4, 6, 3,    5, 6, 4,    2, 3, 6,
        4, 5, 7,    3, 4, 9,    2, 4, 11,   3, 5, 13
}, Nodes = 6, Edges = 9;
int merge_arr[Nodes + 1] {-1};

typedef pair<int, int> pii;
typedef pair<pii, int> piipi;
typedef vector<piipi> vpipii;
vpipii circle, min_circle;

void init() {
    //并查集数组
    for (int i = 1; i <= Nodes; ++i) merge_arr[i] = i;
    //边放入队列
    for (int i = 0; i < Edges; ++i)
        circle.push_back(piipi(pii(map[i][0], map[i][1]), map[i][2]));
}

int get_boss_(int n) {  //通过递归实现
    if(merge_arr[n] == n) return n;
    return get_boss_(merge_arr[n]);
}

int get_boss(int n) {  //通过循环实现
    while(merge_arr[n] != n) n = merge_arr[n];
    return n;
}

bool same_boss(int n1, int n2) {
    int t1 = get_boss(n1);
    int t2 = get_boss(n2);
    if(t1 == t2) return true;
    else {
        merge_arr[t2] = t1;
        return false;
    }
}



int main() {
    /*图的最小生成树，基于并查集实现*/
    init();
    piipi tmp;
    //小到大开始取边，最多n-1条
    while(true) {
        //弹出最小值
        tmp = circle.front(), circle.erase(circle.begin(), circle.begin() + 1);
        //通过并查集判断是否是回路（两个点的祖先节点相同）
        if(!same_boss(tmp.first.first, tmp.first.second))
            min_circle.push_back(tmp);
        if(min_circle.size() == Nodes - 1) break;
    }
    for_each(min_circle.begin(), min_circle.end(), [](const piipi& pp){
        cout << pp.first.first << "->" << pp.first.second << ":" << pp.second << "; ";
    });

    return 0;
}