#include "../common.h"
#include "RBTree.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

/*红黑树存储结构：二叉链表*/
template <typename T>
struct TNode {
    T data;
    bool color;  //true为黑色，false为红色
    TNode* parent;  //父节点
    TNode* l_child;  //左子树
    TNode* r_child;  //右子树
};
typedef TNode<int> ti;
ti* root = nullptr;  //根节点

void LDR(const ti* node_pt, const int depth) {  //中序二叉树遍历
    if(node_pt == nullptr) return;
    LDR(node_pt->l_child, depth + 1);
    cout << node_pt->data << "--" << depth << " ";
    LDR(node_pt->r_child, depth + 1);
}

ti* create(const int data, const bool color = false, ti* parent = nullptr) {  //创建节点，默认红色
    ti* tmp = new ti;
    tmp->data = data, tmp->color = color;
    tmp->l_child = tmp->r_child = nullptr;
    tmp->parent = parent;
}

void left_rotate(ti* left) {  //左旋
/*左旋示意图：对节点l进行左旋
 *     p                       p
 *    /                       /
 *   l                       r
 *  / \                     / \
 * c1  r      ----->       l  c3
 *    / \                 / \
 *   c2 c3               c1 c2
 * 左旋步骤：
 * 1. 将r的左子节点c2赋给l的右子节点,并将l赋给c2节点中父节点指针(y左子节点非空时)
 * 2. 将r的左子节点设为l，将l父节点设为r
 * 3. 将l父节点p赋给r的父节点指针，同时更新p的子节点为y(判断是否存在P) */
    ti* right = left->r_child, * c2 = right->l_child, * p = left->parent;
    //1
    left->r_child = c2;
    if(c2) c2->parent = left;
    //2
    right->l_child = left, left->parent = right;
    //3
    right->parent = p;
    if(p)
        (p->l_child == left ? p->l_child : p->r_child) = right;
    else
        root = right;
}

void right_rotate(ti* right) {  //右旋
/*右旋示意图：对节点r进行右旋
 *        p                   p
 *       /                   /
 *      r                   l
 *     / \                 / \
 *    l  c3   ----->      c1  r
 *   / \                     / \
 * c1  c2                   c2 c3
 * 右旋步骤：
 * 1. 将l的右子节点c2赋给r的左子节点,并将r赋给c2的父指针(x右子节点非空时)
 * 2. 将l的右子节点设为r，将r的父节点设为l
 * 3. 将r的父节点p(非空时)赋给l的父节点，同时更新p的子节点为l(直接引用赋值即可) */
    ti* left = right->l_child, * c2 = left->r_child, * p = right->parent;
    //1
    right->l_child = c2;
    if(c2) c2->parent = right;
    //2
    left->r_child = right, right->parent = left;
    //3
    left->parent = p;
    if(p)
        (p->l_child == right ? p->l_child : p->r_child) = left;
    else
        root = left;
}

ti* search_(ti* node, const int data, ti*& p_node) {  //递归查找
    if(node == nullptr || node->data == data) {
        return node;
    } else if(node->data > data) {
        p_node = node;
        return search_(node->l_child, data, p_node);
    } else if(node->data < data) {
        p_node = node;
        return search_(node->r_child, data, p_node);
    }
}

ti* search(ti* node, const int data, ti*& p_node) {  //循环查找
    while(node) {
        if(data > node->data)
            p_node = node, node = node->r_child;
        else if(data < node->data)
            p_node = node, node = node->l_child;
        else
            return node;
    }
    return nullptr;
}

bool insert(const int data) {
    //1.查找是否存在该节点
    ti* p_node = nullptr, * node = search(root, data, p_node);
    if(node) return false;  //不能插入重复
    //2.不存在则插入之(红节点)
    node = create(data, false, p_node);
    if(!root) {  //为空树
        root = node, root->color = true;
        return true;
    }
    (data > p_node->data ? p_node->r_child : p_node->l_child) = node;
    //cout << p_node->data << " " <<node << " " << node->data << endl;

    //3.调整红黑树：变色->左右旋
    ti* gp_node, * u_node;
    while((p_node = node->parent) && !p_node->color) {  //存在父节点且为红色，必有祖父节点
        gp_node = p_node->parent;
        if(gp_node->l_child == p_node) {  //父节点为左子节点
            u_node = gp_node->r_child;
            //1.插入节点的父节点和其叔叔节点均为红色的：
            // 将当前节点的父节点和叔叔节点涂黑，将祖父节点涂红，再将当前节点指向其祖父节点
            if(u_node && !u_node->color) {
                p_node->color = u_node->color = true;
                gp_node->color = false;
                node = gp_node;
                continue;
            }
            //2.插入节点的父节点（左）是红色，叔叔节点（右）是黑色(包含空节点)，且插入节点是其父节点的右子节点：
            // 将当前节点的父节点作为新的节点，以新的当前节点为支点做左旋操作
            if(node == p_node->r_child) {
                node = p_node;
                left_rotate(node);
                continue;
            }
            //3.插入节点的父节点（左）是红色，叔叔节点（右）是黑色(包含空节点)，且插入节点是其父节点的左子节点：
            // 将当前节点的父节点涂黑，将祖父节点涂红，在祖父节点为支点做右旋操作
            if(node == p_node->l_child) {
                p_node->color = true, gp_node->color = false;
                node = gp_node;
                right_rotate(node);
            }
        } else {
            u_node = gp_node->l_child;
            //1.插入节点的父节点和其叔叔节点均为红色的：将当前节点的父节点和叔叔节点涂黑，将祖父节点涂红，再将当前节点指向其祖父节点
            if (u_node && !u_node->color) {
                p_node->color = u_node->color = true;
                gp_node->color = false;
                node = gp_node;
                continue;
            }
            //2.插入节点的父节点（右）是红色，叔叔节点（左）是黑色，且插入节点是其父节点的左子节点：
            // 将当前节点的父节点作为新的节点，以新的当前节点为支点做右旋操作
            if (node == p_node->l_child) {
                node = p_node;
                right_rotate(node);
                continue;
            }
            //3.插入节点的父节点（右）是红色，叔叔节点（左）是黑色，且插入节点是其父节点的右子节点：
            // 将当前节点的父节点涂黑，将祖父节点涂红，在祖父节点为支点做左旋操作
            if (node == p_node->r_child) {
                p_node->color = true, gp_node->color = false;
                node = gp_node;
                left_rotate(node);
            }
        }
    }
    root->color = true;  //最后根节点设为黑色
    return true;
}

int main() {
    /*红黑树特性：
    (1) 每个节点或者是黑色，或者是红色。
    (2) 根节点是黑色。
    (3) 每个叶子节点是黑色。 [注意：这里叶子节点，是指为空的叶子节点！]
    (4) 如果一个节点是红色的，则它的子节点必须是黑色的。
    (5) 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点。
    注：插入值时，越随机，左右树高越均衡；有序存储时，左右树高最多相差一倍*/

    /*//手动插入及左右旋转、查找
    root = create(80, true);
    ti * n40 = create(40), * n120 = create(120);
    root->l_child = n40, root->r_child = n120, n40->parent = n120->parent = root;
    n120->r_child = create(140, true), n120->l_child = create(100, true);
    n120->r_child->parent = n120->l_child->parent = n120;
    n120->l_child->l_child = create(90), n120->r_child->l_child = create(130);
    n120->l_child->l_child->parent = n120->l_child, n120->r_child->l_child->parent = n120->r_child;
    n120->r_child->r_child = create(150), n40->l_child = create(20, true), n40->r_child = create(60, true);
    n120->r_child->r_child->parent = n120->r_child, n40->l_child->parent = n40->r_child->parent = n40;
    n40->l_child->l_child = create(10), n40->r_child->l_child = create(50);
    n40->l_child->l_child->parent = n40->l_child, n40->r_child->l_child->parent = n40->r_child;
    right_rotate(n120), left_rotate(root), cout << root->data << endl;
    LDR(root);
    ti* pnode = nullptr, * node = search(root, 99, pnode);
    cout << endl << (node ? node->data : 0) << " " << pnode->data;*/

    /*红黑树插入调整情况：
     * 1.插入节点为红色
     * 2.空树，根节点变黑
     * 3.当前节点的父节点为红色，叔节点也为红色，把叔父节点变黑，祖父变红，当前节点更新为祖父节点
     * 4.当前节点的父节点红色，叔节点黑色（或空节点），若父节点为左子节点，当前节点为右子节点，父节点左旋，反之右旋。
     * 5.当前节点的父节点红色，叔节点黑色，若父节点为左子节点，当前节点也为左子节点，祖父右旋，反之左旋
     * 6.最后根节点变黑*/
    /*//插入操作
    for (int i = 1; i <= 100; ++i) {
        insert(i);
    }
    LDR(root, 1);  //构成了不完全平衡二叉树*/

    /*OOP版*/
    srand(time(0));
    RBTree<int> rbTree, rbTree1(1000), rbTree2 = {9,8,7,6,5,4,3,2,1};
    for (int i = 400; i > 0; --i) rbTree.insert(/*rand() % 10000*/i);
    rbTree.show(), NHR;
    for(int i = 100; i < 350; ++i) rbTree.del(i);
    rbTree.del(10);
    rbTree2.update(100, 0);
    rbTree2.update(4, 400);
    rbTree.show(), NHR;
    rbTree1.show(), NHR;
    rbTree2.show(), NHR;
    cout << rbTree.min() << " " << rbTree.max() << endl;
    cout << rbTree2[-1] << " " << rbTree2[1];
    NHR;
    for_each(rbTree.begin(), rbTree.end(), [](const int n){
        cout << n << " ";
    }), NHR;
    for(auto it = rbTree2.begin(); it != rbTree2.end(); ++it) cout << *it << " ";
    NHR;
    for(auto it = rbTree2.rbegin(); it != rbTree2.rend(); --it) cout << *it << " ";


    return 0;
}