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
int book[Nodes] {}, dis[Nodes];

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;
typedef pair<vi, int> pvii;
vpii vp[Nodes];
pvii result[Nodes];

void make_adjacency() {
    for (int i = 0; i < Circles; ++i)
        vp[map_[i][0] - 1].push_back(pii(map_[i][1], map_[i][2]));
}

void reset_dis(int node) {
    --node;
    for(int i = 0; i < Nodes; ++i) {
        dis[i] = i == node ? 0 : Inf, book[i] = 0;
        result[i] = pvii(vi({node + 1, i + 1}), i == node ? 0 : Inf);
    }
    for_each(vp[node].begin(), vp[node].end(), [&](const pii& pr){
       dis[pr.first - 1] = pr.second;
       result[pr.first - 1].second = pr.second;
    }), book[node] = 1;
}

int min_dis_index() {
    int index;
    for(int i = 0, min = Inf; i < Nodes; ++i)
        if(book[i] == 0 && min > dis[i]) min = dis[i], index = i;
    book[index] = 1;
    return index;
}

void dijkstra(int node) {
    for (int i = 0, min_index; i < Nodes; ++i) {
        //得到与指定点距离最短的节点
        min_index = min_dis_index();
        //更新指定节点经过最小距离节点到其它节点的距离
        for_each(vp[min_index].begin(), vp[min_index].end(), [&](const pii& pr){
           if(dis[pr.first - 1] > dis[min_index] + pr.second) {
               dis[pr.first - 1] = dis[min_index] + pr.second;
               result[pr.first - 1].first = result[min_index].first;
               result[pr.first - 1].first.push_back(pr.first);
               result[pr.first - 1].second = dis[pr.first - 1];
           }
        });
    }
}

void route_show(int node) {
    cout << "Node" << node << ": ";
    for (int i = 0, j; i < Nodes; ++i) {
        j = 0, cout << "{";
        for_each(result[i].first.begin(), result[i].first.end(), [&j](const int& i){
            cout << (j++ == 0 ? "" : "->") << i;
        }), cout << "}:" << result[i].second << "; ";
    }
    cout << endl;
}

int main() {
    /*优化*/
    make_adjacency();  //组建邻接链表
    for (int i = 1; i <= Nodes; ++i) {
        reset_dis(i);
        dijkstra(i);  //单源最短路径
        route_show(i);  //显示具体路径
        break;
    }
    return 0;
}