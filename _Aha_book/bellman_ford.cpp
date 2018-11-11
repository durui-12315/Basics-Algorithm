#include "../common.h"
#include <memory>

const int map[][3] = {
        2, 3, 2,    1, 2, -3,   1, 5, 5,    4, 5, 2,    3, 4, 3
}, Nodes = 5, Circles = 5, Inf = INT_MAX / 2;

typedef unique_ptr<int[]> upi;

upi init(int node) {
    --node;
    upi dis(new int[Nodes]);
    for(int i = 0; i < Nodes; ++i) dis[i] = i == node ? 0 : Inf;
    return dis;
}

upi bellman_ford(const int node, bool& is_negative) {
    //初始化
    upi dis = init(node);
    //对指定点进行最多n-1轮松弛
    for (int i = 0, check; i < Nodes - 1; ++i) {
        check = 1;
        //每一轮松弛
        for (int j = 0; j < Circles; ++j)
            if(dis[map[j][1] - 1] > dis[map[j][0] - 1] + map[j][2])
                dis[map[j][1] - 1] = dis[map[j][0] - 1] + map[j][2], check = 0;
        if(check) break;  //提前退出
    }
    //检测负权边
    for(int i = 0; i < Circles; ++i)
        if(dis[map[i][1] - 1] > dis[map[i][0]] + map[i][2]) is_negative = false;
    return dis;
}

int main() {
    /*初稿*/
    bool flag = true;
    upi dis = bellman_ford(1, flag);
    for (int i = 0; i < Nodes; ++i) cout << dis[i] << " ";
    cout << endl << (flag ? "" : "This map has negative weight edge.");

    return 0;
}