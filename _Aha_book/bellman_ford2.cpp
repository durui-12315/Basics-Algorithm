#include "../common.h"
#include <vector>
#include <algorithm>

const int map[][3] = {
        1, 2, 2,    2, 3, 3,    1, 5, 10,   2, 5, 7,
        3, 4, 4,    5, 3, 6,    4, 5, 5
}, Nodes = 5, Circles = 7, Inf = INT_MAX / 2;
int book[Nodes] {}, dis[Nodes];

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;
vpii adja[Nodes];
vi queue;

void make_adjacency() {
    for (int i = 0; i < Circles; ++i)
        adja[map[i][0] - 1].push_back(pii(map[i][1], map[i][2]));
    /*for_each(adja[1].begin(), adja[1].end(), [](const pii& pr){
        cout << pr.first << " " << pr.second << " ";
    });*/
}

void init(int node) {  //距离数组初始化
    --node;
    for(int i = 0; i < Nodes; ++i) dis[i] = i == node ? 0 : Inf;
}

void enqueue(int node) {  //入列和标记
    queue.push_back(node);
    book[node - 1] = 1;
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
                if(book[it->first-1] == 0) enqueue(it->first);
            }
        dequeue();
    }
}

int main() {
    /*oop版队列优化*/
    make_adjacency();
    bellman_ford(1), cout << "Node" << 1 << ": ";
    for(const auto x: dis) cout << x << " ";
    cout << endl;

    return 0;
}

