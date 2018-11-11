#include "../common.h"
#include <list>
#include <stack>
#include <algorithm>

/*AOE网关键路径邻接表结构*/
typedef pair<int, int> pii;
typedef list<pii> list_pii;
typedef pair<string, string> pss;
typedef pair<pss, int> ppssi;
typedef list<ppssi> list_ppssi;
template <typename T>
struct AOENode {
    T name;
    int in_edges;  //入度
    list_pii adj_list;  //出边顶点索引->边权值
};

int main() {
    /*AOE网的关键路径*/
    //初始化
    const int map[][3] = {0,2,4, 0,1,3, 1,4,6, 1,3,5, 2,5,7, 2,3,8, 3,4,3, 4,7,4, 4,6,9, 5,7,6, 6,9,2, 7,8,5, 8,9,3},
        Vertexes = 10, Edges = 13;
    const string names[] = {"V0", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8", "V9"};
    int book[Vertexes] {}, earliest_cost[Vertexes] {}, latest_cost[Vertexes], top_index;
    AOENode<string> aoe[Vertexes];
    stack<int> v_stack, pre_v_stack;
    list_ppssi critical_path;
    for (int i = 0; i < Vertexes; ++i) aoe[i].in_edges = 0, aoe[i].name = names[i];
    for (int j = 0; j < Edges; ++j) {
        aoe[map[j][1]].in_edges = ++book[map[j][1]];
        aoe[map[j][0]].adj_list.push_back(pii(map[j][1], map[j][2]));
    }
    //源点开始拓扑排序
    v_stack.push(0);  //源点入栈
    while (!v_stack.empty()) {
        top_index = v_stack.top(), v_stack.pop(), pre_v_stack.push(top_index);
        for_each(aoe[top_index].adj_list.begin(), aoe[top_index].adj_list.end(), [&](const pii& p){
            if(--aoe[p.first].in_edges == 0) v_stack.push(p.first);
            if(earliest_cost[p.first] < earliest_cost[top_index] + p.second)
                earliest_cost[p.first] = earliest_cost[top_index] + p.second;  //计算顶点最早权值
        });
    }
    //for(auto x: earliest_cost) cout << x << " ";
    //倒拓扑排序计算最晚权值
    for(auto& x: latest_cost) x = earliest_cost[Vertexes - 1];  //初始化
    while (!pre_v_stack.empty()) {
        top_index = pre_v_stack.top(), pre_v_stack.pop();
        for_each(aoe[top_index].adj_list.begin(), aoe[top_index].adj_list.end(), [&](const pii& p){
            if(latest_cost[top_index] > latest_cost[p.first] - p.second)
                latest_cost[top_index] = latest_cost[p.first] - p.second;  //计算顶点最晚权值
        });
    }
    //cout << endl; for(auto x: latest_cost) cout << x << " ";
    //关键路径（顶点最早权值 == 顶点最晚权值）
    for (int k = 0, flag; k < Vertexes; ++k) {
        flag = earliest_cost[k] == latest_cost[k];
        for_each(aoe[k].adj_list.begin(), aoe[k].adj_list.end(), [&](const pii& p){
            if(flag && earliest_cost[p.first] == latest_cost[p.first])
                critical_path.push_back(ppssi(pss(names[k], names[p.first]), p.second));
        });
    }
    //展示
    for_each(critical_path.begin(), critical_path.end(), [&](const ppssi& pp){
        cout << pp.first.first << "->" << pp.first.second << ":" << pp.second << "; ";
    });

    return 0;
}