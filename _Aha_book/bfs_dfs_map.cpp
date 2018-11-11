#include "../common.h"
#include <vector>
#include <array>
#include <algorithm>
#include <iomanip>
#include "../Map_list.h"

/*无向图标量*/
const int Nodes = 8, map[Nodes][Nodes] {  //邻接矩阵存储无向图
    0, 1, 1, -1, 1, -1, -1, -1,
    1, 0, -1, 1, -1, -1, -1, -1,
    1, -1, 0, 1,  -1, -1, -1, -1,
    -1, 1, 1, 0, -1, -1, 1, -1,
    1, -1, -1, -1, 0, 1, -1, -1,
    -1, -1, -1, -1, 1, 0, -1, 1,
    -1, -1, -1, 1, -1, -1, 0, -1,
    -1, -1, -1, -1, -1, 1, -1, 0
};
int book[Nodes] {1}, num = 0;  //从第一点开始遍历

vector<int> v;
Map_list<int, int> ml(1, 1);

void dfs(int cur = 0) {
    ++num, v.push_back(cur + 1);
    if(num == Nodes) return;
    for (int i = 0; i < Nodes; ++i) {
        if(map[cur][i] == 1 && book[i] == 0) {
            book[i] = 1;
            dfs(i);
        }
    }
}

void bfs() {
    int book[Nodes] {1}, num = 1;
    auto it = ml.begin();
    while(it != ml.end()) {
        for (int i = 0; i < Nodes; ++i) {
            if(map[(*it).second - 1][i] == 1 && book[i] == 0) {
                book[i] = 1;
                ml.push_back(++num, i + 1);
            }
        }
        if(num == Nodes) break;
        ++it;
    }
}

/*有向图标量*/
const int Citys = 5, map_city[Citys][Citys] {  //邻接矩阵存储有向图
    0, 2, 4, -1, 10,
    -1, 0, 3, -1, 7,
    4, -1, 0, 4, 3,
    -1, -1, -1, 0, 5,
    -1, -1, 3, -1, 0
};
int book_city[Citys] {}, sum = 0;

vector<pair<vector<int>, int>> vc;
vector<int> vc_tmp;

void dfs(int cur, const int dst) {
    if(cur == dst) {
        vc.push_back(pair<vector<int>, int>(vc_tmp, sum));
        return;
    }
    for (int i = 0; i < Citys; ++i) {
        if(map_city[cur - 1][i] > 0 && book_city[i] == 0) {
            book_city[i] = 1, sum += map_city[cur - 1][i], vc_tmp.push_back(i + 1);
            dfs(i + 1, dst);
            book_city[i] = 0, sum -= map_city[cur - 1][i], vc_tmp.pop_back();
        }
    }
}

/*权值相等的有向图标量*/
const int Addrs = 7, map_addr[Addrs][Addrs] {
    0, -1, -1, -1, 1, -1, -1,
    1, 0, -1, 1, 1, -1, -1,
    1, -1, 0, -1, 1, 1, 1,
    -1, 1, -1, 0, -1, -1, 1,
    1, 1, 1, -1, 0, -1, -1,
    -1, -1, 1, -1, -1, 0, -1,
    -1, -1, 1, 1, 1, 1, 0
};
int book_addr[Addrs] {};

Map_list<int, int> vas;

void bfs(const int src, const int dst) {
    book_addr[src - 1] = 1, vas.push_back(src, 0);
    auto it = vas.begin();
    int flag = 0;
    while(it != vas.end()) {
        for(int i = 0; i < Addrs; ++i) {
            if(map_addr[(*it).first - 1][i] == 1 && book_addr[i] == 0) {
                book_addr[i] = 1;
                vas.push_back(i + 1, (*it).second + 1);
                if(i + 1 == dst) {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag) break;
        ++it;
    }
}

int main() {
    /*深度优先遍历无向图*/
    dfs();
    for_each(v.begin(), v.end(), [](int c){cout << c << " ";});
    NHR;

    /*广度优先遍历无向图*/
    bfs();
    for_each(ml.begin(), ml.end(), [](const pair<int, int>& pr){
        cout << pr.first << ":" << pr.second << "; ";
    }), NHR;

    /*深度优先遍历有向图*/
    const int src = 3, dst = 5;
    book_city[src - 1] = 1, vc_tmp.push_back(src);
    dfs(src, dst);
    for_each(vc.begin(), vc.end(), [](const pair<vector<int>, int>& pr){
        for_each(pr.first.begin(), pr.first.end(), [](const int n){
            cout << n << "->";
        });
        cout << ":" << pr.second << "; ";
    }), NHR;

    /*广度优先遍历等权有向图*/
    const int src_addr = 1, dst_addr = 7;
    bfs(src_addr, dst_addr);
    for_each(vas.begin(), vas.end(), [](const pair<int, int> n){
        cout << n.first << "->" << n.second << "; ";
    });

    return 0;
}
