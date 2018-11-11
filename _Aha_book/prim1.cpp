#include "../common.h"
#include <vector>
#include <algorithm>

const int adjacency[][3] {
        2, 4, 11,   3, 5, 13,   4, 6, 3,    5, 6, 4,    2, 3, 6,
        4, 5, 7,    1, 2, 1,    3, 4, 9,    1, 3, 2
}, Nodes = 6, Edges = 9, Inf = INT_MAX / 2;
int book[Nodes] {}, dis[Nodes] {}, node[Nodes], counts = 0;

typedef pair<int, int> pii;
typedef pair<pii, int> ppiii;
typedef vector<ppiii> vppiii;
vppiii res, adj_list[Nodes];

void make_adjacency() {
    for (int i = 0, n1, n2, d; i < Edges; ++i) {
        n1 = adjacency[i][0], n2 = adjacency[i][1], d = adjacency[i][2];
        adj_list[n1 - 1].push_back(ppiii(pii(n1, n2), d));
        adj_list[n2 - 1].push_back(ppiii(pii(n2, n1), d));
    }
    for (int j = 0; j < Nodes; ++j) {
        cout << "Node" << j + 1 << ": ";
        for_each(adj_list[j].begin(), adj_list[j].end(), [](const ppiii &pp) {
            cout << pp.first.first << "->" << pp.first.second << ":" << pp.second << "; ";
        }), cout << endl;
    }
    HR;
}

void init(int first) {
    for(int i = 0; i < Nodes; ++i) {
        node[i] = first;
        if(i != first - 1) dis[i] = Inf;
    }
    for_each(adj_list[first-1].begin(), adj_list[first-1].end(), [&](const ppiii& pp){
        dis[pp.first.second - 1] = pp.second;
    }), book[first - 1] = 1, ++counts;
}

int min_dis_index() {  //可用最小堆优化获取最小值
    int min = Inf, min_index;
    for(int i = 0; i < Nodes; ++i)
        if(book[i] == 0 && min > dis[i]) min = dis[i], min_index = i;
    return min_index;
}

void prim(int first) {
    init(first);
    for(int counts = 0, min_index; counts < Nodes - 1; ++counts) {
        //从dis数组中获取非树节点到树的最小距离的节点
        min_index = min_dis_index(), book[min_index] = 1;
        res.push_back(ppiii(pii(node[min_index], min_index + 1), dis[min_index]));
        //通过该点到其它非树节点的距离来更新dis数组
        for_each(adj_list[min_index].begin(), adj_list[min_index].end(), [&](const ppiii& pp){
            int i = pp.first.second - 1;
            if(book[i] == 0 && dis[i] > pp.second) dis[i] = pp.second, node[i] = min_index + 1;
        });
    }
}

int main() {
    /*prim算法邻接表优化*/
    make_adjacency();
    prim(1);
    for_each(res.begin(), res.end(), [](const ppiii& pp){
        cout << pp.first.first << "->" << pp.first.second << ":" << pp.second << "; ";
    });

    return 0;
}