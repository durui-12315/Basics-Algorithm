#include "../common.h"
#include <vector>
#include <algorithm>

const int map_[][3] {  //邻接表存储原材料
        1, 2, 1,    1, 3, 12,
        2, 3, 9,    2, 4, 3,
        3, 5, 5,
        4, 3, 4,    4, 5, 13,   4, 6, 15,
        5, 6, 4
}, Circles = 9, Nodes = 6, Inf = INT_MAX / 2;

typedef vector<pair<int, int>> vpii;
typedef pair<int, int> pii;
typedef vector<pair<int, pair<int, int>>> vpipii;
typedef pair<int, pair<int, int>> pipii;

vpii vp[Nodes], result[Nodes];
vpipii vpp;

void make_adjacency() {
    for (int i = 0; i < Circles; ++i)
        vp[map_[i][0] - 1].push_back(pii(map_[i][1], map_[i][2]));
}

void make_simple_adjacency(int node) {
    for(auto it = vp[--node].begin(); it != vp[node].end(); ++it)
        vpp.push_back(pipii(0, pii(it->first, it->second)));
}

int get_dis_map(int node1, int node2) {
    if(node1 == node2) return 0;
    for(auto it = vp[node1 - 1].begin(); it != vp[node1 - 1].end(); ++it)
        if(it->first == node2) return it->second;
    return Inf;
}

auto get_dis(int node) {
    for(auto it = vpp.begin(); it != vpp.end(); ++it)
        if(it->second.first == node) return it;
    return vpp.end();
}

auto get_min_dis() {
    int min_dis = Inf;
    auto min_it = vpp.begin();
    for(auto it = vpp.begin(); it != vpp.end(); ++it)
        if(it->first == 0 && min_dis > it->second.second)
            min_dis = it->second.second, min_it = it;
    min_it->first = 1;
    return min_it;
}

void add_result(int node) {
    --node;
    for(auto it = vpp.begin(); it != vpp.end(); ++it)
        result[node].push_back(pii(it->second.first, it->second.second));
    vpp = vpipii();
}

void dijkstra(int node) {
    //组建指定点单独的邻接链表
    make_simple_adjacency(node);
    for (int i = 0, min_dis, min_node; i < Nodes; ++i) {
        //得到与指定点距离最短的节点
        auto min_it = get_min_dis();
        min_dis = min_it->second.second, min_node = min_it->second.first;
        //更新指定节点经过最小距离节点到其它节点的距离
        for (int j = 1, map_dis; j <= Nodes ; ++j) {
            if(min_node == j || j == node) continue;
            auto it_dis = get_dis(j);
            map_dis = get_dis_map(min_node, j);
            if(it_dis == vpp.end()) {
                if(Inf > min_dis + map_dis)
                    vpp.push_back(pipii(0, pii(j, min_dis + map_dis)));
            } else {
                if(it_dis->second.second > min_dis + map_dis)
                    it_dis->second.second = min_dis + map_dis;
            }
        }
    }
    add_result(node);
}

int main() {
    /*优化*/
    make_adjacency();  //组建邻接链表
    for (int i = 1; i <= Nodes; ++i) {
        dijkstra(i);  //单源最短路径
        cout << "Node" << i << ": ";
        for_each(result[i - 1].begin(), result[i - 1].end(), [](const pii& pr){
            cout << pr.first << "->" << pr.second << "; ";
        });
        cout << endl;
    }
    return 0;
}