#include "../common.h"
#include <memory>
#include <algorithm>
#include "../Map_list.h"

/*初稿标量*/
const int Nodes = 6, Inf = INT_MAX / 2, map[][Nodes] {  //邻接矩阵存储
    0, 1, 12, Inf, Inf, Inf,
    Inf, 0, 9, 3, Inf, Inf,
    Inf, Inf, 0, Inf, 5, Inf,
    Inf, Inf, 4, 0, 13, 15,
    Inf, Inf, Inf, Inf, 0, 4,
    Inf, Inf, Inf, Inf, Inf, 0
};
int book[Nodes] {};
vector<pair<int, unique_ptr<int[]>>> v;

unique_ptr<int[]> dis_arr(int node) {
    for(auto& x: book) x = 0;
    unique_ptr<int[]> pt(new int[node]);
    for(int i = 0; i < Nodes; ++i) pt[i] = map[node - 1][i];
    book[node - 1] = 1;
    return pt;
}

unique_ptr<int[]> dijkstra(int node) {
    //指定节点到其它点原始距离
    unique_ptr<int[]> dis = dis_arr(node);
    //遍历每个节点
    for (int i = 0, min, node_index; i < Nodes; ++i) {
        //找出最小距离的节点
        min = Inf;
        for (int j = 0; j < Nodes; ++j)
            if(book[j] == 0 && dis[j] < min) min = dis[j], node_index = j;
        book[node_index] = 1;
        //更新指定节点经过最小距离节点到其它节点的距离
        for (int k = 0; k < Nodes; ++k) {
            if(map[node_index][k] < Inf && dis[k] > dis[node_index] + map[node_index][k])
                dis[k] = dis[node_index] + map[node_index][k];
        }
    }
    return dis;
}

int main() {
    /*初稿*/
    for(int i = 1; i <= Nodes; ++i)
        v.push_back(pair<int, unique_ptr<int[]>>(i, dijkstra(i)));
    for_each(v.begin(), v.end(), [](const pair<int, unique_ptr<int[]>>& pr){
        cout << pr.first << ": ";
        for(int i = 0; i < Nodes; ++i) cout << pr.second[i] << " ";
        cout << endl;
    }), HR;

    return 0;
}