#include "../common.h"
#include <iomanip>
#include <vector>
#include <algorithm>

const int adjacency[][3] {
    2, 4, 11,   3, 5, 13,   4, 6, 3,    5, 6, 4,    2, 3, 6,
    4, 5, 7,    1, 2, 1,    3, 4, 9,    1, 3, 2
}, Nodes = 6, Edges = 9, Inf = INT_MAX / 2;
int book[Nodes] {}, map[Nodes][Nodes] {}, dis[Nodes], node[Nodes], counts = 0, sum = 0;

typedef pair<int, int> pii;
typedef pair<pii, int> ppiii;
typedef vector<ppiii> vppiii;
vppiii result;

void make_map() {
    for(int i = 0; i < Nodes; ++i)
        for (int j = 0; j < Nodes; ++j) if(i != j) map[i][j] = map[j][i] = Inf;
    for(int i = 0, j, k; i < Edges; ++i) {
        j = adjacency[i][0] - 1, k = adjacency[i][1] - 1;
        map[j][k] = map[k][j] = adjacency[i][2];
    }
    /*cout << left;
    for(int i = 0; i < Nodes; ++i) {
        for (int j = 0; j < Nodes; ++j) cout << setw(2) << map[i][j] << " ";
        cout << endl;
    }*/
}

void init(int first) {
    --first, ++counts;
    for(int i = 0; i < Nodes; ++i) dis[i] = map[first][i], node[i] = first;
    book[first] = 1;
}

void prim(int first) {
    init(first);
    int min, min_node_index;
    while(counts < Nodes) {
        //从dis中找出离生成树最短距离的点
        min = Inf;
        for(int i = 0; i < Nodes; i++)
            if(book[i] == 0 && dis[i] < min) min = dis[i], min_node_index = i;
        book[min_node_index] = 1, sum += min, ++counts;
        result.push_back(ppiii(pii(node[min_node_index] + 1, min_node_index + 1), min));
        //遍历该点，更新dis距离
        for(int i = 0; i < Nodes; ++i)
            if(book[i] == 0 && dis[i] > map[min_node_index][i])
                dis[i] = map[min_node_index][i], node[i] = min_node_index;
    }
}

int main() {
    /*最小生成树prim算法*/
    make_map();
    prim(1);
    for_each(result.begin(), result.end(), [](const ppiii& pp){
        cout << pp.first.first << "->" << pp.first.second << ":" << pp.second << "; ";
    });

    return 0;
}