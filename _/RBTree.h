#ifndef ALGORITHM_RBTREE_H
#define ALGORITHM_RBTREE_H

#include <iostream>
#include <initializer_list>
using std::cout;
using std::endl;
using std::initializer_list;

template <class T>
class RBTree {
private:
    struct Node {
        T data;
        bool color;  //true为黑色，false为红色
        Node* parent;
        Node* l_child;
        Node* r_child;
    };
    Node* root_ = nullptr;
    int size_ = 0;
    Node* create(const T& data, Node* parent = nullptr, bool color = false) const;
    void destroy(Node* node) const {delete node;}
    Node* search(const T& data, Node*& parent) const;
    Node*& parent_child(Node* parent, Node* node) const;
    void left_rotate(Node* left);
    void right_rotate(Node* right);
    void insert_adjust(Node* node);
    Node* previous(Node* node) const;  //前驱节点，小于当前节点的最大节点
    Node* next(Node* node) const;  //后继节点，大于当前节点的最小节点
    void delete_adjust(Node* node, Node* parent);
    void LDR(const Node* node, int depth, int& deepest) const;  //中序遍历
    void setRed(Node* node) {if(node) node->color = false;}
    void setBlack(Node* node) {if(node) node->color = false;}
    void setColor(Node* node, bool color) {if(node) node->color = color;}
    bool isRed(Node* node) {return node && !node->color;}
    bool isBlack(Node* node) {return node && node->color;}
    bool colorOf(Node* node) {return node ? node->color : true;}
    Node* parentOf(Node* node) {return node ? node->parent : nullptr;}
public:
    class iterator {  //简易迭代器
    private:
        Node* node_;
    public:
        explicit iterator(Node* node = nullptr): node_(node) {}
        bool operator!=(const iterator& it) {return node_ != it.node_;}
        void operator++();
        void operator--();
        T operator*() {return node_->data;}
    };
    RBTree() = default;
    explicit RBTree(const T& data) {insert(data);}
    RBTree(const initializer_list<T>& il);
    int size() const {return size_;}
    T min() const;
    T max() const;
    bool insert(const T& data);
    bool del(const T& data);
    bool update(const T& old_data, const T& new_data);
    void show() const {int d = 0; LDR(root_, 1, d), cout << d;}
    T operator[](const int index) const;
    iterator begin() const;
    iterator end() const {return iterator();}
    iterator rbegin() const;
    iterator rend() const {return iterator();}
};

template <typename T>
void RBTree<T>::iterator::operator++() {  //找后继
    Node* node = node_;
    if(node->r_child) {
        node = node->r_child;  //右下
        while(node->l_child) node = node->l_child;  //左下至尽头
        node_ = node;
    } else {
        while(node->parent && node->parent->r_child == node) node = node->parent;  //左上至尽头
        node_ = node->parent;  //右上
    }
}

template <typename T>
void RBTree<T>::iterator::operator--() {
    Node* node = node_;
    if(node->l_child) {
        node = node->l_child;  //左下
        while(node->r_child) node = node->r_child;  //右下至尽头
        node_ = node;
    } else {
        while(node->parent && node->parent->l_child == node) node = node->parent;  //右上至尽头
        node_ = node->parent;  //左上
    }
}

template <class T>
typename RBTree<T>::Node* RBTree<T>::create(const T &data, RBTree<T>::Node *parent, bool color) const {
    Node* tmp = new Node;
    tmp->data = data, tmp->color = color;
    tmp->l_child = tmp->r_child = nullptr;
    tmp->parent = parent;
}

template <class T>
typename RBTree<T>::Node* RBTree<T>::search(const T &data, RBTree<T>::Node *&parent) const {
    Node* node = root_;
    while(node) {
        if(data > node->data)
            parent = node, node = node->r_child;
        else if(data < node->data)
            parent = node, node = node->l_child;
        else
            return node;
    }
    return nullptr;
}

template <class T>
typename RBTree<T>::Node*& RBTree<T>::parent_child(RBTree<T>::Node* parent, RBTree<T>::Node *node) const {
    return parent->l_child == node ? parent->l_child : parent->r_child;
}

template <class T>
void RBTree<T>::left_rotate(RBTree<T>::Node *left) {
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
    Node* right = left->r_child, * c2 = right->l_child, * p = left->parent;
    //1
    left->r_child = c2;
    if(c2) c2->parent = left;
    //2
    right->l_child = left, left->parent = right;
    //3
    right->parent = p;
    if(p)
        //(p->l_child == left ? p->l_child : p->r_child) = right;
        parent_child(p, left) = right;
    else
        root_ = right;
}

template <class T>
void RBTree<T>::right_rotate(RBTree<T>::Node *right) {
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
    Node* left = right->l_child, * c2 = left->r_child, * p = right->parent;
    //1
    right->l_child = c2;
    if(c2) c2->parent = right;
    //2
    left->r_child = right, right->parent = left;
    //3
    left->parent = p;
    if(p)
        //(p->l_child == right ? p->l_child : p->r_child) = left;
        parent_child(p, right) = left;
    else
        root_ = left;
}

template <class T>
void RBTree<T>::insert_adjust(RBTree<T>::Node *node) {
    /*红黑树插入调整口诀总结：
     * 1.父红叔红时：父叔都变黑，祖父变红
     * 2.父红叔黑（包括黑空节点）时：父左儿（新增节点）右父左旋，父右儿左父右旋
     * 3.父红叔黑（包括黑空节点）：父左儿左，父变黑祖父变红祖父右旋；父右儿右，父变黑祖父变红祖父左旋*/
    Node* gparent, * parent, * uncle;
    while((parent = node->parent) && !parent->color) {  //父节点存在且为红色
        gparent = parent->parent;
        if(gparent->l_child == parent) {  //父节点为左子节点
            uncle = gparent->r_child;
            if(uncle && !uncle->color) {  //叔节点为红色
                parent->color = uncle->color = true;  //叔父节点变黑
                gparent->color = false; //祖父节点变红
                node = gparent;  //更新当前节点为祖父节点
            } else if(node == parent->r_child) {  //当前节点为右子节点
                node = parent;  //更新当前节点为父节点
                left_rotate(node);  //左旋
            } else if(node == parent->l_child) {  //当前节点为左子节点
                parent->color = true, gparent->color = false;  //父节点变黑，祖父变红
                node = gparent;  //更新当前节点为祖父节点
                right_rotate(node);  //右旋
            }
        } else {  //父节点为右子节点
            uncle = gparent->l_child;
            if(uncle && !uncle->color) {  //叔节点为红色
                parent->color = uncle->color = true;  //叔父节点变黑
                gparent->color = false;  //祖父节点变红
                node = gparent;  //更新当前节点为祖父节点
            } else if(node == parent->l_child) {  //当前节点为左子节点
                node = parent;  //更新当前节点为父节点
                right_rotate(node);  //右旋
            } else if(node == parent->r_child) {
                parent->color = true, gparent->color = false;  //父节点变黑，祖父变红
                node = gparent;  //更新当前节点为祖父节点
                left_rotate(node);  //左旋
            }
        }
    }
    root_->color = true;  //根节点变黑色
}

template <class T>
typename RBTree<T>::Node* RBTree<T>::previous(RBTree<T>::Node *node) const {
    if(node->l_child) {
        node = node->l_child;  //左下
        while(node->r_child) node = node->r_child;  //右下至尽头
        return node;
    } else {
        while(node->parent && node->parent->l_child == node) node = node->parent;  //右上至尽头
        return node->parent;  //左上
    }
}

template <class T>
typename RBTree<T>::Node* RBTree<T>::next(RBTree<T>::Node *node) const {
    if(node->r_child) {
        node = node->r_child;  //右下
        while(node->l_child) node = node->l_child;  //左下至尽头
        return node;
    } else {
        while(node->parent && node->parent->r_child == node) node = node->parent;  //左上至尽头
        return node->parent;  //右上
    }
}

template <class T>
void RBTree<T>::delete_adjust(RBTree<T>::Node *node, RBTree<T>::Node *parent) {
    Node* other;
    /*while((!node || node->color) && node != root_) {
        if(parent->l_child == node) {  //node是左子节点
            other = parent->r_child;  //other是右兄弟节点
            //case1: node的兄弟节点other是红色的
            if(other && !other->color)  {
                other->color = true;  //other变黑
                parent->color = false;  //父变红
                left_rotate(parent);  //父左旋
                other = parent->r_child;  //other变成父右子
            }
            //case2: node的兄弟节点other是黑色的，且other的两个子节点也都是黑色的
            if((!other->l_child || other->l_child->color) && (!other->r_child || other->r_child->color)) {
                other->color = false;  //other变红
                if(!parent->color) parent->color = false;  //parent若为红，变黑
                node = parent;  //node更新为父节点
                parent = node->parent;
            } else {
                //case3: node的兄弟节点other是黑色的，且other的左子节点是红色，右子节点是黑色
                if(!other->r_child || other->r_child->color) {
                    if(other->l_child) other->l_child->color = true;  //左子黑
                    other->color = false;  //other红
                    right_rotate(other);  //右旋
                    other = parent->r_child;  //跟新other节点
                }
                //case4: node的兄弟节点other是黑色的，且other的右子节点是红色，左子节点任意颜色
                other->color = parent->color;  //other的颜色和父节点颜色一致
                parent->color = true;
                if(other->r_child) other->r_child->color = true;  //父和other变黑
                left_rotate(parent);  //父节点左旋
                node = root_;
                break;
            }
        } else {  //node是右子节点
            other = parent->l_child;  //node的左兄弟节点
            //Case 1: node的兄弟other是红色的
            if (other && !other->color) {
                other->color = true;
                parent->color = false;
                right_rotate(parent);
                other = parent->l_child;
            }
            //Case 2: node的兄弟other是黑色，且other的俩个子节点都是黑色的
            if ((!other->l_child || other->l_child->color) && (!other->r_child || other->r_child->color)) {
                other->color = false;  //other变红
                if(!parent->color) parent->color = false;  //parent若为红，变黑
                node = parent;  //node更新为父节点
                parent = node->parent;  //考虑node变成根节点时
            } else {
                // Case 3: node的兄弟other是黑色的，并且other的左子节点是黑色，右子节点红色。
                if (!other->l_child || other->l_child->color) {
                    if(other->r_child) other->r_child->color = true;
                    other->color = false;
                    left_rotate(other);
                    other = parent->l_child;
                }
                // Case 4: node的兄弟other是黑色的；并且other的左子节点是红色的，右子节点任意颜色
                other->color = parent->color;  //other的颜色和父节点颜色一致
                parent->color = true;
                if(other->r_child) other->r_child->color = true;  //父和other变黑
                right_rotate(parent);
                node = root_;
                break;
            }
        }
    }
    if(node) node->color = true;  //变黑*/
    while((!node || isBlack(node)) && (node != root_)) {
        if(parent->l_child == node) { //node是左子节点
            other = parent->r_child; //other是的右子节点
            //case1: node的兄弟节点other是红色的
            if(isRed(other)) {
                setBlack(other);
                setRed(parent);
                left_rotate(parent);
                other = parent->r_child;
            }
            //case2: node的兄弟节点other是黑色的，且other的两个子节点也都是黑色的
            if((!other->l_child || isBlack(other->l_child)) &&
               (!other->r_child || isBlack(other->r_child))) {
                setRed(other);
                node = parent;
                parent = parentOf(node);
            } else {
                //case3: node的兄弟节点other是黑色的，且other的左子节点是红色，右子节点是黑色
                if(!other->r_child || isBlack(other->r_child)) {
                    setBlack(other->l_child);
                    setRed(other);
                    right_rotate(other);
                    other = parent->r_child;
                }
                //case4: node的兄弟节点other是黑色的，且other的右子节点是红色，左子节点任意颜色
                setColor(other, colorOf(parent));
                setBlack(parent);
                setBlack(other->r_child);
                left_rotate(parent);
                node = root_;
                break;
            }
        } else { //与上面的对称
            other = parent->l_child;
            // Case 1: node的兄弟other是红色的
            if (isRed(other)) {
                setBlack(other);
                setRed(parent);
                right_rotate(parent);
                other = parent->l_child;
            }
            // Case 2: node的兄弟other是黑色，且other的俩个子节点都是黑色的
            if ((!other->l_child || isBlack(other->l_child)) &&
                (!other->r_child || isBlack(other->r_child))) {
                setRed(other);
                node = parent;
                parent = parentOf(node);
            } else {
                // Case 3: node的兄弟other是黑色的，并且other的左子节点是红色，右子节点为黑色。
                if (!other->l_child || isBlack(other->l_child)) {
                    setBlack(other->r_child);
                    setRed(other);
                    left_rotate(other);
                    other = parent->l_child;
                }
                // Case 4: node的兄弟other是黑色的；并且other的左子节点是红色的，右子节点任意颜色
                setColor(other, colorOf(parent));
                setBlack(parent);
                setBlack(other->l_child);
                right_rotate(parent);
                node = root_;
                break;
            }
        }
    }
    if (node) setBlack(node);
}

template <class T>
void RBTree<T>::LDR(const RBTree<T>::Node *node, int depth, int& deepest) const {
    if(node == nullptr) return;
    LDR(node->l_child, depth + 1, deepest);
    cout << node->data << "--" << depth << " ";
    if(depth > deepest) deepest = depth;
    LDR(node->r_child, depth + 1, deepest);
}

template <class T>
RBTree<T>::RBTree(const initializer_list<T> &il) {
    for(auto it = il.begin(); it != il.end(); ++it)
        insert(*it);
}

template <class T>
T RBTree<T>::min() const {
    Node* node = root_;
    while(node->l_child) node = node->l_child;
    return node->data;
}

template <class T>
T RBTree<T>::max() const {
    Node* node = root_;
    while(node->r_child) node = node->r_child;
    return node->data;
}

template <class T>
bool RBTree<T>::insert(const T &data) {
    Node* parent = nullptr, * node = search(data, parent);
    if(node) return false;  //不能重复插入
    node = create(data, parent);  //新增节点为红色
    if(parent)
        (parent->data > data ? parent->l_child : parent->r_child) = node;
    else
        root_ = node;  //空树时
    insert_adjust(node);  //调整红黑树
    ++size_;
    return true;
}

template <class T>
bool RBTree<T>::del(const T &data) {  //删除时，为提高效率，不进行值替换
    Node* parent = nullptr, * node = search(data, parent);
    if(!node) return false;  //不能删除不存在的
    if(node->l_child && node->r_child) {  //左右子节点都有时
        Node* after = next(node);  //找后继(无左子节点)，一定在其后代中
        Node* after_child = after->r_child, * after_parent = after->parent;  //后继子与父
        bool after_color = after->color;  //保存后继节点的颜色
        //处理后继与被删除节点的父节点关系
        if(parent) {
            parent_child(parent, node) = after;
        } else root_ = after;  //根节点
        after->parent = parent;
        //链接后继子与后继父、后继与右子节点
        if(after_parent != node) {
            after_parent->l_child = after_child;
            if(after_child) after_child->parent = after_parent;
            after->r_child = node->r_child, node->r_child->parent = after;
        } else after_parent = after;  //后继是被删节点的右子节点时
        //左子节点与后继
        after->l_child = node->l_child, node->l_child->parent = after;
        after->color = node->color;  //保持原来位置的颜色
        if(after_color) delete_adjust(after_child, after_parent);  //若移走的后继节点是黑色，修整红黑树
    } else {  //至少有一个为空时
        if(parent) {
            bool is_left = parent->l_child == node, color;
            if(node->l_child == nullptr && node->r_child == nullptr) {  //没有子树
                (is_left ? parent->l_child : parent->r_child) = nullptr;
            } else if(node->l_child == nullptr) {  //左子树不存在
                node->r_child->parent = parent;  //接右子树
                (is_left ? parent->l_child : parent->r_child) = node->r_child;
                if(node->color) delete_adjust(node->r_child, parent);  //若被删除到的节点是黑色，调整红黑树
            } else {  //右子树不存在
                node->l_child->parent = parent;  //接左子树
                (is_left ? parent->l_child : parent->r_child) = node->l_child;
                if(node->color) delete_adjust(node->l_child, parent);  //若被删除到的节点是黑色，调整红黑树
            }
        } else {  //为根节点
            if(size() == 1) //删除最后一个
                root_ = nullptr;
            else if(root_->l_child)
                root_ = root_->l_child;
            else
                root_ = root_->r_child;
            if(root_) root_->parent = nullptr, root_->color = true;
        }
    }
    destroy(node);
    --size_;
    return true;
}

template <class T>
bool RBTree<T>::update(const T &old_data, const T &new_data) {
    if(del(old_data)) {
        if(insert(new_data))
            return true;
        else {
            insert(old_data);
            return false;
        }
    } else {
        return false;
    }
}

template <class T>
T RBTree<T>::operator[](const int index) const  {
    Node* node = root_;
    if(index >= 0 && index < size()) {
        while(node->l_child) node = node->l_child;
        for(int i = 1; i <= index; ++i) node = next(node);
        return node->data;
    } else if(-index <= size()){
        while(node->r_child) node = node->r_child;
        for(int i = 2; i <= -index; ++i) node = previous(node);
        return node->data;
    }
}

template <class T>
typename RBTree<T>::iterator RBTree<T>::begin() const {
    Node* node = root_;
    while(node->l_child) node = node->l_child;
    return iterator(node);
}

template <class T>
typename RBTree<T>::iterator RBTree<T>::rbegin() const {
    Node* node = root_;
    while(node->r_child) node = node->r_child;
    return iterator(node);
}

#endif //ALGORITHM_RBTREE_H
