#include "../common.h"
#include <vector>
#include <algorithm>

const int map[][3] = {
        //1, 2, 2,    2, 3, 3,    1, 5, 10,   2, 5, 7,    3, 4, 4,    5, 3, 6,    4, 5, 5
        1, 2, 1,    1, 3, 12,
        2, 3, 9,    2, 4, 3,
        3, 5, 5,
        4, 3, 4,    4, 5, 13,   4, 6, 15,
        5, 6, 4
}, Nodes = 5, Circles = 7, Inf = INT_MAX / 2;
int book[Nodes], dis[Nodes];

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;
typedef pair<vi, int> pvii;
vpii adja[Nodes];
vi queue;
pvii result[Nodes];

void make_adjacency() {
    for (int i = 0; i < Circles; ++i)
        adja[map[i][0] - 1].push_back(pii(map[i][1], map[i][2]));
    /*for_each(adja[1].begin(), adja[1].end(), [](const pii& pr){
        cout << pr.first << " " << pr.second << " ";
    });*/
}

void init(int node) {  //距离数组初始化
    --node;
    for(int i = 0; i < Nodes; ++i) {
        dis[i] = i == node ? 0 : Inf, book[i] = 0;
        result[i] = pvii(vi(), i == node ? 0 : Inf);
    }
}

void enqueue(int node) {  //入列和标记、路径记录
    queue.push_back(node);
    book[node - 1] = 1;
    result[node - 1].first = result[queue.front() - 1].first;  //队列头节点路径覆盖入列节点的旧路径
    result[node - 1].first.push_back(node);
}

void dequeue() {  //出列和标记
    int node = queue.front();
    queue.erase(queue.begin(), queue.begin() + 1);  //第一出列
    book[node - 1] = 0;
}

void bellman_ford(int node) {
    init(node);
    enqueue(node);  //指定点先入列
    vector<pii>::const_iterator it;  //常量迭代器
    int pot_index;
    while(queue.size()) {
        pot_index = queue.front() - 1;
        for(it = adja[pot_index].begin(); it != adja[pot_index].end(); ++it)
            if(dis[it->first-1] > dis[pot_index] + it->second) {
                dis[it->first-1] = dis[pot_index] + it->second;
                result[it->first-1].second = dis[it->first-1];
                if(book[it->first-1] == 0)  //防止重复入列，避免重复出边计算
                    enqueue(it->first);
            }
        dequeue();
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
    /*oop版队列优化并显示路径*/
    make_adjacency();
    for (int i = 1; i <= Nodes; ++i) bellman_ford(i), route_show(i);
    return 0;
}

