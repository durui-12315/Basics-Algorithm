#include "../common.h"

/*二叉链表*/
template <typename T>
struct BSTNode {
    BSTNode* l_child;
    T data;
    BSTNode* r_child;
};
typedef BSTNode<int> Bi;

Bi* create(const int n) {
    Bi* tmp = new Bi;
    tmp->data = n;
    tmp->l_child = tmp->r_child = nullptr;
    return tmp;
}

void LDR(const Bi* node_pt) {  //中序二叉树遍历
    if(node_pt == nullptr) return;
    LDR(node_pt->l_child);
    cout << node_pt->data << " ";
    LDR(node_pt->r_child);
}

void LDR(const Bi* node_pt, const int depth) {  //中序二叉树遍历
    if(node_pt == nullptr) return;
    LDR(node_pt->l_child, depth + 1);
    cout << node_pt->data << "--" << depth << " ";
    LDR(node_pt->r_child, depth + 1);
}

Bi* search_BST(Bi* node, const int& value, Bi*& p_node) {  //二叉排序树查找
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

bool insert_BST(Bi* root, const int value) {  //二叉排序树插入
    Bi* p_tmp, * tmp = search_BST(root, value, p_tmp);
    if(tmp) return false;  //不能插入重复值
    (value < p_tmp->data ? p_tmp->l_child : p_tmp->r_child) = create(value);
    return true;
}

bool delete_BST(Bi*& root, const int value) {  //二叉排序树删除
    Bi* p_tmp = nullptr, * tmp = search_BST(root, value, p_tmp);
    if(tmp == nullptr) return false;
    if(tmp->l_child == nullptr || tmp->r_child == nullptr) {
        if(tmp == root) {
            if(root->l_child == nullptr && root->r_child == nullptr) delete root, root = nullptr;
            else if(root->l_child == nullptr) root = root->r_child, delete tmp;
            else if(root->r_child == nullptr) root = root->l_child, delete tmp;
            return true;
        }
        Bi* &tmp_ = p_tmp->l_child == tmp ? p_tmp->l_child : p_tmp->r_child;  //父节点判断并引用
        if(tmp->l_child == nullptr)  //左子树为空，接右子树
            tmp_ = tmp->r_child, delete tmp;
        else  //反之
            tmp_ = tmp->l_child, delete tmp;
    } else {
        Bi* tmp_ = tmp, * _tmp = tmp->l_child;  //先找左子节点
        if(_tmp->r_child) {
            while(_tmp->r_child) tmp_ = _tmp, _tmp = _tmp->r_child;  //转右到尽头找前驱
            tmp->data = _tmp->data, tmp_->r_child = _tmp->l_child, delete _tmp;
        } else  //无法转右
            tmp_->data = _tmp->data, tmp_->l_child = _tmp->l_child, delete _tmp;
    }
    return true;
}

int main() {

    /*非线索二叉排序树*/
    //非线索二叉排序树手动创建
    //Bi* root = create(62), * n58 = create(58), * n88 = create(88), * n47 = create(47);
    //root->l_child = n58, root->r_child = n88, n58->l_child = n47, n88->l_child = create(73);
    //n88->r_child = create(99), n47->l_child = create(35), n47->r_child = create(51);
    //n47->l_child->r_child = create(37), n88->r_child->l_child = create(93);

    //非线索二叉排序树插入（自动创建）
    Bi* root = create(62);
    for(const int& x: {58, 88, 47, 73, 99, 35, 51, 37, 93, 100, 100, 29, 36, 49, 56, 48, 50})
        insert_BST(root, x);
    LDR(root), NHR;

    //非线索二叉排序树查找
    Bi* pNode, * re = search_BST(root, 100, pNode);
    cout << re << " " << (re == nullptr ? -1 : re->data) << " " << pNode << " " << pNode->data << endl;

    //非线索二叉排序树删除
    for(const int x: {29, 47, 35, 36, 37, 49, 50, 51, 62, 58, 48, 88}) delete_BST(root, x);
    LDR(root), NHR;

    //不平衡二叉树展示
    Bi* root_ = create(1);
    for (int i = 2; i <= 100; ++i) insert_BST(root_, i);  //构成了右斜树
    LDR(root_, 1);

    return 0;
}