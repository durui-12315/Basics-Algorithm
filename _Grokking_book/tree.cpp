#include "../common.h"
#include <iomanip>
#include <vector>
#include <algorithm>
#include <memory>
#include <cstring>
#include "CircularQueue.h"

/*树的存储：父节点表示法*/
/*template <typename T>
struct TNode {
    T data;  //节点数据
    int parent;  //父节点位置
    int first_child;  //长子节点位置
};*/

/*树的存储：父子节点表示法*/
/*template <typename T>
struct TNode {
    T data;
    int parent;
    vector<int> children;
};*/

/*树的存储：父子节点表示法（纯结构体）*/
/*struct CNode {
    int index;  //该节点在数组中的索引
    CNode* next_sibling_pt;  //指向下一个兄弟节点
};
template <typename T>
struct TNode {
    T data;
    int parent;
    int children_size;  //子节点个数
    CNode* first_child_pt;  //指向第一个子节点
};
TNode<string> tree[10];*/

/*二叉树链式存储：二叉链表*/
/*template <typename T>
struct BTNode {
    BTNode* left_child_pt;  //指向左子节点
    T data;
    BTNode* right_child_pt;  //指向右子节点
};
typedef BTNode<char> bc;*/

/*二叉树链式存储：线索二叉链表*/
template <typename T>
struct BTNode {
    BTNode* l_child;
    bool l_tag;  //为true时指向节点前驱，false时指向左子节点
    T data;
    bool r_tag;  //为true时指向节点后继，false时指向右子节点
    BTNode* r_child;
};
typedef BTNode<char> bc;
bc* pre_node;

int main() {
    /*循环双向数组队列*/
    /*CircularQueue<double, 10> cq;
    cq.push_front(1.1);cq.push_front(2.2); cq.push_front(3.3); cq.push_front(4.4);
    cq.push_front(5.5); cq.push_front(6.6); cq.push_front(7.7); cq.push_front(8.8);
    cq.push_front(9.9); cq.push_front(10.10); cq.push_front(11.11); cq.push_front(12.12);
    cq.pop_back(); cq.pop_back(); cq.pop_back(); cq.pop_back();
    cq.push_front(11.11); cq.push_front(12.12);
    cq.pop_front();cq.pop_front();cq.pop_front();cq.pop_front();cq.pop_front();
    cq.push_back(1.1);cq.push_back(2.2);cq.push_back(3.3);cq.push_back(4.4);
    cout << cq.size() << endl;
    cq[0] = 100;
    for (int i = 0; i < cq.size(); ++i) {
        cout << cq[i] << " ";
    }*/

    /*获取子串在字符串中首次出现的索引（朴素模式匹配算法）*/
    /*const char* str = "goodhahagoogbadgooglehehegooglelala", * sub_str = "google";
    int len = 0, sub_len = 0, index = -1;
    while(str[len]) ++len;
    while(sub_str[sub_len]) ++sub_len;
    for (int i = 0, diff = len - sub_len, j, flag; i < diff; ++i) {
        if(str[i] != sub_str[0]) continue;
        flag = 1;
        for (j = 0; j < sub_len && flag; ++j, ++i)
            if(str[i] != sub_str[j]) flag = 0;
        if(flag) {
            index = i - j;
            break;
        }
        i -= j;
    }
    cout << index;*/

    /*树的存储：父节点表示法*/
    /*TNode<char> tree[10];
    tree[0].data = 'A', tree[0].parent = -1, tree[0].first_child = 1;
    tree[1].data = 'B', tree[1].parent = 0, tree[1].first_child = 3;
    tree[2].data = 'C', tree[2].parent = 0, tree[2].first_child = 4;
    tree[3].data = 'D', tree[3].parent = 1, tree[3].first_child = 6;
    tree[4].data = 'E', tree[4].parent = 2, tree[4].first_child = 9;
    tree[5].data = 'F', tree[5].parent = 2, tree[5].first_child = -1;
    tree[6].data = 'G', tree[6].parent = 3, tree[6].first_child = -1;
    tree[7].data = 'H', tree[7].parent = 3, tree[7].first_child = -1;
    tree[8].data = 'I', tree[8].parent = 3, tree[8].first_child = -1;
    tree[9].data = 'J', tree[9].parent = 4, tree[9].first_child = -1;
    for (int i = 0; i < 10; ++i)
        cout << i << " " << tree[i].data << " " << tree[i].parent << " " << tree[i].first_child << endl;*/

    /*树的存储：父子节点表示法*/
    /*const int Size = 10;
    TNode<char> tree[Size];
    tree[0].data = 'A', tree[0].parent = -1, tree[0].children.push_back(1), tree[0].children.push_back(2);
    tree[1].data = 'B', tree[1].parent = 0, tree[1].children.push_back(3);
    tree[2].data = 'C', tree[2].parent = 0, tree[2].children.push_back(4), tree[2].children.push_back(5);
    tree[3].data = 'D', tree[3].parent = 1, tree[3].children.push_back(6), tree[3].children.push_back(7), tree[3].children.push_back(8);
    tree[4].data = 'E', tree[4].parent = 2, tree[4].children.push_back(9);
    tree[5].data = 'F', tree[5].parent = 2;
    tree[6].data = 'G', tree[6].parent = 3;
    tree[7].data = 'H', tree[7].parent = 3;
    tree[8].data = 'I', tree[8].parent = 3;
    tree[9].data = 'J', tree[9].parent = 4;
    for (int i = 0; i < Size; ++i) {
        cout << "Index:" << i << "; Data:" << tree[i].data << "; Parent:" <<
            (tree[i].parent == -1 ? ' ' : tree[tree[i].parent].data) << "; ";
        if(tree[i].children.size()) {
            cout << "Children:";
            for_each(tree[i].children.begin(), tree[i].children.end(), [&](const int& ci){
                cout << tree[ci].data << ", ";
            });
        }
        cout << endl;
    }*/

    /*二叉链表手动建立*/
    /*bc* create(const char);
    bc* root = create('A'), * b = create('B'), * c = create('C'), * d = create('D'), * e = create('E');
    root->left_child_pt = b, root->right_child_pt = c;
    b->left_child_pt = d, c->left_child_pt = e, c->right_child_pt = create('F');
    d->left_child_pt = create('G'), d->right_child_pt = create('H'), e->right_child_pt = create('I');*/

    /*二叉链表自动建立*/
    /*bc* binary_tree(const char*, const int, int = 1);
    const char* pc = "ABCD#EFGH###I";
    bc* root = binary_tree(pc, strlen(pc));*/

    /*二叉链表遍历*/
    /*//层序遍历，按层级从上到下、从左到右显示
    void LOD(const bc*);
    LOD(root), NHR;
    //前序遍历，根节点在最前显示
    void DLR(const bc*);
    DLR(root), NHR;
    //中序遍历，根节点在中间显示
    void LDR(const bc*);
    LDR(root), NHR;
    //后序遍历，根节点在最后显示。并销毁二叉链表
    void LRD(const bc*);
    LRD(root);*/

    /*二叉树链式存储：线索二叉链表*/
    bc* binary_tree(const char*, const int, int = 1);
    void threaded_binary_tree(bc*);
    const char* pc = "ABCDEFGHIJ";
    bc* root = binary_tree(pc, strlen(pc));
    threaded_binary_tree(pre_node = root);  //建立线索二叉链表
    //CircularQueue<const bc*, 20> cq({root});  //层序遍历
    //for (int i = 0; i < cq.size(); ++i) {
    //    if(!cq[i]->l_tag && cq[i]->l_child != nullptr) cq.push_back(cq[i]->l_child);
    //    if(!cq[i]->r_tag && cq[i]->r_child != nullptr) cq.push_back(cq[i]->r_child);
    //    cout << cq[i]->data;
    //}

    /*线索二叉树遍历*/
    void set_ldr_node_null(bc*);
    void TBTree_foreach(bc*);
    void TBTree_foreach_reverse(bc*);
    set_ldr_node_null(root);
    TBTree_foreach(root), NHR;  //正序
    TBTree_foreach_reverse(root);  //倒序


    return 0;
}

/*bc* create(const char c) {
    bc* tmp = new bc;
    tmp->data = c;
    tmp->left_child_pt = tmp->right_child_pt = nullptr;
    return tmp;
}

void DLR(const bc* node_pt) {  //前序遍历
    if(node_pt == nullptr) return;
    cout << node_pt->data;
    DLR(node_pt->left_child_pt);
    DLR(node_pt->right_child_pt);
}

void LDR(const bc* node_pt) {  //中序遍历
    if(node_pt == nullptr) return;
    LDR(node_pt->left_child_pt);
    cout << node_pt->data;
    LDR(node_pt->right_child_pt);
}

void LRD(const bc* node_pt) {  //后序遍历
    if(node_pt == nullptr) return;
    LRD(node_pt->left_child_pt);
    LRD(node_pt->right_child_pt);
    cout << node_pt->data;
    delete node_pt;  //只能用后序遍历销毁二叉链表
}

void LOD(const bc* root_pt) {  //层序遍历
    CircularQueue<const bc*, 20> cq({root_pt});
    for (int i = 0; i < cq.size(); ++i) {
        if(cq[i]->left_child_pt != nullptr) cq.push_back(cq[i]->left_child_pt);
        if(cq[i]->right_child_pt != nullptr) cq.push_back(cq[i]->right_child_pt);
        cout << cq[i]->data;
    }
}

bc* binary_tree(const char* pc, const int size, int n) {  //建立二叉链表
    if(pc[n - 1] == '#') return nullptr;
    bc* tmp = new bc;
    tmp->data = pc[n - 1], tmp->left_child_pt = tmp->right_child_pt = nullptr;
    if(2 * n <= size)
        tmp->left_child_pt = binary_tree(pc, size, 2 * n);
    if(2 * n + 1 <= size)
        tmp->right_child_pt = binary_tree(pc, size, 2 * n + 1);
    return tmp;
}*/

bc* binary_tree(const char* pc, const int size, int n) {  //建立初始线索二叉链表
    if(n > size) return nullptr;
    bc* tmp = new bc;
    tmp->data = pc[n - 1], tmp->l_child = tmp->r_child = nullptr, tmp->l_tag = tmp->r_tag = false;
    tmp->l_child = binary_tree(pc, size, 2 * n);
    tmp->r_child = binary_tree(pc, size, 2 * n + 1);
    return tmp;
};

void threaded_binary_tree(bc* node_pt) {  //建立线索二叉链表
    if(node_pt->l_child) threaded_binary_tree(node_pt->l_child);
    if(node_pt->l_child == nullptr)
        node_pt->l_tag = true, node_pt->l_child = pre_node;  //当前节点没左子节点，则左子节点指向上一个中序节点
    if(pre_node->r_child == nullptr)
        pre_node->r_tag = true, pre_node->r_child = node_pt;  //上一个中序节点没右子节点，则右子节点指向当前节点
    pre_node = node_pt;  //上一个中序节点变成当前节点
    if(node_pt->r_child) threaded_binary_tree(node_pt->r_child);
}

void set_ldr_node_null(bc* tmp) {
    while(!tmp->l_tag) tmp = tmp->l_child;  //找到该二叉树第一个中序节点
    tmp->l_child = nullptr;  //设置第一个中序节点的左字节点为空指针，便于倒序遍历
    tmp->l_tag = false;  //没有前驱
}

void TBTree_foreach(bc* node_pt) {  //线索二叉链表中序遍历
    while(node_pt) {
        while(!node_pt->l_tag && node_pt->l_child)  //找到当前节点的第一个中序节点（最左子树）
            node_pt = node_pt->l_child;
        cout << node_pt->data;
        while(node_pt->r_tag) {  //是否有后继节点
            node_pt = node_pt->r_child;
            cout << node_pt->data;
        }
        node_pt = node_pt->r_child;  //当前节点变为其右子树，从而继续找右子树的第一个中序节点
    }
}

void TBTree_foreach_reverse(bc* node_pt) {  //线索二叉链表倒中序遍历
    while(node_pt) {
        while(!node_pt->r_tag && node_pt->r_child)  //找到当前节点的第一个倒中序节点（最右子树）
            node_pt = node_pt->r_child;
        cout << node_pt->data;
        while(node_pt->l_tag) {  //是否有前驱节点
            node_pt = node_pt->l_child;
            cout << node_pt->data;
        }
        node_pt = node_pt->l_child;  //当前节点变为其左子树，继续找左子树的第一个倒中序节点
    }
}
