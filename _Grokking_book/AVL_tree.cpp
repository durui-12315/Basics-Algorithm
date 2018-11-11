#include "../common.h"

/*ALV树节点存储结构*/
template <typename T>
struct ALVTNode {
    T data;
    int bf;  //平衡因子
    ALVTNode* l_child, * r_child;
};
typedef ALVTNode<int> Ai;

template <typename T>
Ai* create(const T t) {
    Ai* tmp = new Ai;
    tmp->data = t, tmp->bf = 0;
    tmp->l_child = tmp->r_child = nullptr;
    return tmp;
}

void r_rotate(Ai*& node) {  //右旋
    Ai* L = node->l_child;
    node->l_child = L->r_child;
    L->r_child = node;
    node = L;  //改变子树根节点
}

void l_rotate(Ai*& node) {  //左旋
    Ai* R = node->r_child;
    node->r_child = R->l_child;
    R->l_child = node;
    node = R;
}

void left_balance(Ai*& node) {  //左平衡旋转处理
    const int LH = 1, EH = 0, RH = -1;
    Ai* L = node->l_child, * Lr;  //L指向node的左子节点
    switch (L->bf) {
        case LH:  //新节点插入在左孩子的左子树上，做单右旋处理
            node->bf = L->bf = EH;
            r_rotate(node);
            break;
        case RH:  //新节点插入在左孩子的右子树上，做双旋处理
            Lr = L->r_child;  //指向node的左子节点的右子节点
            switch (Lr->bf) {
                case LH:
                    node->bf = RH;
                    L->bf = EH;
                    break;
                case EH:
                    node->bf = L->bf = EH;
                    break;
                case RH:
                    node->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            l_rotate(node->l_child);
            r_rotate(node);
    }
}

void LDR(const Ai* node_pt) {  //中序二叉树遍历
    if(node_pt == nullptr) return;
    LDR(node_pt->l_child);
    cout << node_pt->data << " ";
    LDR(node_pt->r_child);
}

Ai* search_BST(Ai* node, const int& value, Ai*& p_node) {  //二叉排序树查找
    if(node == nullptr) return nullptr;
    if(node->data > value) {
        p_node = node;  //当前节点是子节点的父节点
        return search_BST(node->l_child, value, p_node);
    }
    else if(node->data < value) {
        p_node = node;
        return search_BST(node->r_child, value, p_node);
    }
    else return node;
}

bool insert_BST(Ai* root, const int value) {  //二叉排序树插入
    Ai* p_tmp, * tmp = search_BST(root, value, p_tmp);
    if(tmp) return false;  //不能插入重复值
    (value < p_tmp->data ? p_tmp->l_child : p_tmp->r_child) = create(value);
    return true;
}



int main() {
    /*平衡二叉树*/
    Ai* root = create<int>(40);
    for(int x: {20,10,30,60,50,70}) insert_BST(root, x);
    //r_rotate(root); cout << root->data << endl;
    //l_rotate(root); cout << root->data << endl;
    //LDR(root);

    return 0;
}