#include "../common.h"

const int map[][3] = {
    1, 2, 2,    2, 3, 3,    1, 5, 10,   2, 5, 7,
    3, 4, 4,    5, 3, 6,    4, 5, 5
}, Nodes = 5, Circles = 7, Inf = INT_MAX / 2;
int dis[Nodes], book[Nodes] {};

struct Node {int pot1; int pot2; int distance; Node* next; };
Node* head[Nodes] {}, * tail[Nodes] {};

struct Pot {int pot; Pot* next;};
Pot* front = 0, * back = 0;

void make_adjacency() {  //组建邻接链表
    Node* tmp;
    for (int j = 0, pot_index; j < Circles; ++j) {
        tmp = new Node;
        tmp->next = 0, tmp->pot1 = map[j][0], tmp->pot2 = map[j][1], tmp->distance = map[j][2];
        pot_index = tmp->pot1 - 1;
        if(head[pot_index] == 0)
            head[pot_index] = tail[pot_index] = tmp;
        else
            tail[pot_index]->next = tmp, tail[pot_index] = tmp;
    }
    /*for (int k = 0; k < Nodes; ++k) {
        tmp = head[k];
        while(tmp) {
            cout << tmp->pot1 << " " << tmp->pot2 << " " << tmp->distance <<"; ";
            tmp = tmp->next;
        }
        cout << endl;
    }*/
}

void del_adjacency() {
    Node* tmp, * tmp_;
    for (int i = 0; i < Nodes; ++i) {
        tmp = head[i];
        while(tmp) {
            tmp_ = tmp->next;
            delete tmp;
            tmp = tmp_;
        }
        head[i] = tail[i] = 0;
    }
}

void init(int node) {  //距离数组初始化
    --node;
    for(int i = 0; i < Nodes; ++i) dis[i] = i == node ? 0 : Inf;
}

void enqueue(int pot) {
    Pot* tmp = new Pot;
    tmp->pot = pot;
    tmp->next = 0;
    if(front == 0) front = back = tmp;
    else back->next = tmp, back = tmp;
}

void dequeue() {
    if(front == 0) return;
    Pot* tmp = front;
    front = front->next;
    delete tmp;
    if(front == 0) back = 0;
}

void bellman_ford(int node) {
    init(node);
    enqueue(node), book[node - 1] = 1;
    Node* tmp;
    while(front) {
        tmp = head[front->pot - 1];
        while(tmp) {
            if(dis[tmp->pot2 - 1] > dis[front->pot - 1] + tmp->distance) {
                dis[tmp->pot2 - 1] = dis[front->pot - 1] + tmp->distance;
                if(book[tmp->pot2 - 1] == 0) enqueue(tmp->pot2), book[tmp->pot2 - 1] = 1;
            }
            tmp = tmp->next;
        }
        book[front->pot - 1] = 0, dequeue();
    }
}

int main() {
    /*队列优化*/
    make_adjacency();
    for (int i = 1; i <= Nodes; ++i) {
        bellman_ford(i), cout << "Node" << i << ": ";
        for(const auto x: dis) cout << x << " ";
        cout << endl;
    }
    del_adjacency();

    return 0;
}