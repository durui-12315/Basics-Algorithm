#include "../common.h"
#include <list>
#include <algorithm>
#include <stack>

/*邻接表C结构体存储*/
/*const int MaxVEX = 100;
struct EdgeNode {  //边表节点
    int adj_vex;  //顶点下标
    int weight;  //边权重
    EdgeNode* next;  //下一邻接点
};
template <typename T>
struct VertexNode {  //顶点表节点
    T vertex_name;  //顶点名
    EdgeNode* first_adj;  //边表头指针
};
template <typename T>
struct GraphAdjList {
    int num_vertexes;   //顶点数
    int num_edges;  //边数
    VertexNode<T> adj_list[MaxVEX];  //顶点数组
};*/

/*邻接表C++存储*/
/*template <typename T>
struct VertexEdge {  //顶点和边存储单元
    T vertex_name;  //顶点名
    list<pair<int, int>> adj_list;  //邻接队列，顶点下标->边权
};
template <typename T, int vertexNum, int edgeNum>
struct GraphAdjList {
    int num_vertexes = vertexNum;   //顶点数
    int num_edges = edgeNum;  //边数
    VertexEdge<T> adj_arr[vertexNum];  //顶点邻接数组
};*/

/*有向图邻接表C++对象存储(加入边)*/
/*template <typename T, int vertexNum, int edgeNum>
class Adjacency {
private:
    typedef pair<int, int> pii;
    typedef list<pii> list_pii;
    struct VertexEdge {
        T vertex_name;
        list_pii adj_in;  //节点出边
        list_pii adj_out;  //节点入边
    };
    int num_vertexes_ = vertexNum;
    int num_edges_ = edgeNum;
public:
    VertexEdge adjArray[vertexNum];
    Adjacency(const T v_name[], const int map[][3]) {
        for (int i = 0; i < num_vertexes_; ++i)
            adjArray[i].vertex_name = v_name[i];
        for (int j = 0; j < num_edges_; ++j) {
            adjArray[map[j][0]].adj_out.push_back(pii(map[j][1], map[j][2]));
            adjArray[map[j][1]].adj_in.push_back(pii(map[j][0], map[j][2]));
        }
    }
    int vertex_num() {return num_vertexes_;}
    int edge_num() {return num_edges_;}
};*/

/*template <typename T, int v, int e>
void DFS(const Adjacency<T, v, e>& adj, int index, int* book) {  //有向图邻接表的深度优先遍历
    book[index] = 1, cout << adj.adjArray[index].vertex_name;
    for_each(adj.adjArray[index].adj_out.begin(), adj.adjArray[index].adj_out.end(), [&](const pair<int, int>& pr){
        if(book[pr.first] == 0) DFS(adj, pr.first, book);
    });
}*/

/*AOV网拓扑排序所需邻接表结构*/
/*struct AOVNode {
    string name;
    int in_edge;  //顶点入度个数
    list<int> adj_list;
};*/

/*AOE网关键路径邻接表结构*/
typedef pair<int, int> pii;
typedef list<pii> list_pii;
template <typename T>
struct AOENode {
    T name;
    int in_edges;  //入度
    list_pii adj_list;  //出边顶点索引->边权值
};

int main() {
    /*邻接表C++存储*/
    /*GraphAdjList<char, 10, 20> adjList;
    for (int i = 0; i < adjList.num_vertexes; ++i) cout << &adjList.adj_arr[i] << " ";*/

    /*有向图邻接表C++对象存储(加入边)*/
    /*typedef pair<int, int> pii;
    const char vertex_name[] = {'A','B','C','D','E','F'};
    const int map[][3] = {0,1,5, 0,2,1, 2,1,2, 1,3,10, 3,2,10, 2,4,5, 4,3,20, 4,5,6, 3,5,15}, v_num = 6, e_num = 9;
    Adjacency<char, v_num, e_num> adjacency(vertex_name, map);
    for (int i = 0; i < adjacency.vertex_num(); ++i) {
        cout << "Vertex name:" << adjacency.adjArray[i].vertex_name << " => Edge out:";
        for_each(adjacency.adjArray[i].adj_out.begin(), adjacency.adjArray[i].adj_out.end(), [&](const pii& pr){
            cout << "->" << vertex_name[pr.first] << ":" << pr.second << "; ";
        }), cout << "Edge in:";
        for_each(adjacency.adjArray[i].adj_in.begin(), adjacency.adjArray[i].adj_in.end(), [&](const pii& pr){
            cout << "<-" << vertex_name[pr.first] << ":" << pr.second << "; ";
        }), cout << endl;
    } HR;*/

    /*有向图邻接表的深度优先遍历*/
    /*int book[v_num] {};
    DFS(adjacency, 0, book), NHR;  //从A开始*/

    /*有向图邻接表的广度优先遍历*/
    /*int visited[v_num] {1};  //标记A
    list<int> vname_list({0});  //从A开始
    for_each(vname_list.begin(), vname_list.end(), [&](const int& n){
        cout << vertex_name[n];
        for_each(adjacency.adjArray[n].adj_out.begin(), adjacency.adjArray[n].adj_out.end(), [&](const pii& pr){
           if(visited[pr.first] == 0) visited[pr.first] = 1, vname_list.push_back(pr.first);
        });
    });*/

    /*AOV网的拓扑排序*/
    /*//初始工作
    const string vertex[] = {"V0", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8", "V9", "V10", "V11", "V12", "V13"};
    const int map[][2] = {
            0, 11,  0, 5,   0, 4,   1, 8,   1, 4,   1, 2,   2, 9,   2, 6,   2, 5,   3, 13,  3, 2,   4, 7,
            5, 12,  5, 8,   6, 5,   8, 7,   9, 11,  9, 10,  10, 13, 12, 9
    }, Vertexes = 14, Edges = 20;
    int book[Vertexes] {}, v_top;
    AOVNode aov[Vertexes];
    stack<int> v_stack;
    list<string> vertex_list;
    for (int j = 0; j < Vertexes; ++j) aov[j].name = vertex[j], aov[j].in_edge = 0;
    for (int i = 0; i < Edges; ++i) {
        aov[map[i][1]].in_edge = ++book[map[i][1]];  //统计顶点入度
        aov[map[i][0]].adj_list.push_back(map[i][1]);
    }
    //for (int k = 0; k < Vertexes; ++k) {  //展示邻接表
    //    cout << aov[k].name + ": " << aov[k].in_edge << ", ";
    //    for_each(aov[k].adj_list.begin(), aov[k].adj_list.end(), [](const int& n){
    //        cout << "->" << n;
    //    }), cout << endl;
    //}
    //入度为零的顶点入栈
    for (int k = 0; k < Vertexes; ++k) if(aov[k].in_edge == 0) v_stack.push(k);
    //通过栈消除入度为0顶点的出边，减少关联顶点的入度值
    while(!v_stack.empty()) {
        v_top = v_stack.top(), v_stack.pop();
        vertex_list.push_back(vertex[v_top]);
        //遍历出边，改变出边对应顶点的入度
        for_each(aov[v_top].adj_list.begin(), aov[v_top].adj_list.end(), [&](const int& n){
            if(--aov[n].in_edge == 0) v_stack.push(n);  //某顶点入度为0，压入栈中
        });
    }
    //遍历拓扑排序
    if(vertex_list.size() == Vertexes) {
        cout << "Topological Sort: ";
        for_each(vertex_list.begin(), vertex_list.end(), [](const string& s){
            cout << s + " ";
        });
    }
    else cout << "It's not a AOV.";*/

    /*AOE网的关键路径*/
    //初始化
    const int map[][3] = {0,1,2, 0,2,3, 0,3,1, 0,4,4, 1,5,1, 2,5,1, 3,5,1, 4,5,2, 5,6,2}, Vertexes = 7, Edges = 9;
    const char* names = "ABCDEFG";
    int book[Vertexes] {}, earliest_cost[Vertexes] {}, latest_cost[Vertexes], top_index;
    AOENode<char> aoe[Vertexes];
    stack<int> v_stack, pre_v_stack;
    list<pair<pii, int>> critical_path;
    for (int i = 0; i < Vertexes; ++i) aoe[i].in_edges = 0, aoe[i].name = names[i];
    for (int j = 0; j < Edges; ++j) {
        aoe[map[j][1]].in_edges = ++book[map[j][1]];
        aoe[map[j][0]].adj_list.push_back(pii(map[j][1], map[j][2]));
    }
    //for (int k = 0; k < Vertexes; ++k) {  //展示邻接表
    //    cout << aoe[k].name << ": " << aoe[k].in_edges << ", ";
    //    for_each(aoe[k].adj_list.begin(), aoe[k].adj_list.end(), [](const pii& pr){
    //        cout << " =>" << pr.first << "-" << pr.second;
    //    }), cout << endl;
    //}
    //源点入栈
    v_stack.push(0);  //A入栈
    //通过拓扑排序计算每个顶点的最早时间
    while(!v_stack.empty()) {
        top_index = v_stack.top(), v_stack.pop(), pre_v_stack.push(top_index);
        for_each(aoe[top_index].adj_list.begin(), aoe[top_index].adj_list.end(), [&](const pii& pr){
            if(--aoe[pr.first].in_edges == 0) v_stack.push(pr.first);
            if(earliest_cost[top_index] + pr.second > earliest_cost[pr.first])
                earliest_cost[pr.first] = earliest_cost[top_index] + pr.second;
        });
    }
    //初始化最晚时间
    for(auto& x: latest_cost) x = earliest_cost[Vertexes - 1];
    //通过栈计算最晚时间
    while(!pre_v_stack.empty()) {
        top_index = pre_v_stack.top(), pre_v_stack.pop();
        for_each(aoe[top_index].adj_list.begin(), aoe[top_index].adj_list.end(), [&](const pii& pr){
            if(latest_cost[top_index] > latest_cost[pr.first] - pr.second)
                latest_cost[top_index] = latest_cost[pr.first] - pr.second;
        });
    }
    //最早与最晚时间比对，相等则为关键路径（最早时间 == 最晚时间 - 边权值）
    for (int k = 0, ete, lte; k < Vertexes; ++k) {
        ete = earliest_cost[k];
        for_each(aoe[k].adj_list.begin(), aoe[k].adj_list.end(), [&](const pii& pr){
            lte = latest_cost[pr.first] - pr.second;
            if(ete == lte) critical_path.push_back(pair<pii, int>(pii(k, pr.first), pr.second));
        });
    }
    //展示关键路径
    for_each(critical_path.begin(), critical_path.end(), [&](const pair<pii, int>& pp){
        cout << names[pp.first.first] << "->" << names[pp.first.second] << ":" << pp.second << "; ";
    });


    return 0;
}


