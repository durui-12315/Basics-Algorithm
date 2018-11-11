#ifndef ALGORITHM_MAP_LIST_H
#define ALGORITHM_MAP_LIST_H

#include <iostream>
#include <initializer_list>
using std::initializer_list;
using std::pair;
using std::cout;
using std::endl;
using std::move;

template <class K, class V> class Map_list;  //forward declaration
template <typename K, typename V> void swap(Map_list<K, V>&, Map_list<K, V>&);

template <class K, class V>
class Map_list {
private:
    struct Node {
        Node* _pre;
        K _key;
        V _value;
        Node* _next;
    };
    Node* head_;
    Node* tail_;
    Node* cursor_;
    int items_;
    void New();
    Node* create(const K& k, const V& v);
    void destroy(Node*& cur) {delete cur;};
    void insert(Node* pre, Node* next, Node* cur);  //can not operate pointer by reference
    void del(Node* cur);
    void reset();
    void splice(Node* pt, Map_list& ml);
    void quick_sort(Node* ptl, Node* ptr, int left, int right, bool is_value);
    void swap_(Node* p1, Node* p2);
public:
    class Iterator {
    private:
        Node* pt_;
        int index_;
    public:
        explicit Iterator(Node* pt = nullptr, int index = 0): pt_(pt), index_(index) {}
        void operator++() {pt_ = pt_->_next, ++index_;}
        void operator--() {pt_ = pt_->_pre, --index_;}
        Iterator operator+(int n);
        Iterator operator-(int n);
        bool operator==(const Iterator& it) {return pt_ == it.pt_;}
        bool operator!=(const Iterator& it) {return pt_ != it.pt_;}
        bool operator<(const Iterator& it) const;
        bool operator>(const Iterator& it) const {return it < *this;}
        pair<K, V> operator*() {return pair<K, V>(pt_->_key, pt_->_value);}
        void swap(const Iterator& it) const;
        int index() {return index_;}
        void update(const K& k, const V& v) {pt_->_key = k, pt_->_value = v;}
    };
    Map_list() {New();};
    Map_list(const initializer_list<K>& kl, const initializer_list<V>& vl);
    Map_list(const initializer_list<pair<K, V>>& list);
    Map_list(const K& k, const V& v) {New(), push_back(k, v);}
    Map_list(Map_list& ml);  //copy constructor
    Map_list(Map_list&& ml);  //move constructor
    ~Map_list() {truncate();}
    int size() {return items_;}
    Map_list& push_back(const K& k, const V& v);
    Map_list& push_back(const pair<K, V>& pr);
    Map_list& push_back(Iterator& it) {return push_back(*it);}
    Map_list& pop_back();
    Map_list& pop_back(pair<K, V>& pr);
    Map_list& push_front(const K& k, const V& v);
    Map_list& push_front(const pair<K, V>& pr);
    Map_list& push_front(Iterator& it) {return push_front(*it);}
    Map_list& pop_front();
    Map_list& pop_front(pair<K, V>& pr);
    Map_list& truncate() {while(items_) pop_back();}
    void remove(const K& k);
    Map_list& merge_after(Map_list& ml);
    Map_list& merge_before(Map_list& ml);
    void ksplice(const K& k, Map_list& ml);
    void vsplice(const V& v, Map_list& ml);
    pair<K, V>& front() {return *begin();}
    pair<K, V>& back() {return *rbegin();}
    void reverse();
    void sort(bool is_value = true) {quick_sort(head_->_next, tail_->_pre, 1, size(), is_value);}
    void unique(bool is_value = true, bool is_sort = true);  //use ordered set in priority
    pair<K, V>& operator[](int i) {return *(i >= 0 ? begin() + i : rbegin() - (-i - 1));}
    V operator[](const K& k);
    Map_list& operator()(const K& k);
    void operator=(const V& v) {if(cursor_) cursor_->_value = v;};
    Map_list operator+(Map_list& ml);
    Map_list& operator=(Map_list& ml);  //copy assignment
    Map_list& operator=(Map_list&& ml);  //move assignment
    Map_list& operator+=(Map_list& ml) {return merge_after(ml);}
    Iterator begin() {return Iterator(head_->_next);}
    Iterator end() {return Iterator(tail_, size());}
    Iterator rbegin() {return Iterator(tail_->_pre, size() - 1);}
    Iterator rend() {return Iterator(head_, -1);}
    Iterator iter(int i) {return i >= 0 ? begin() + i : rbegin() - (-i - 1);}
    friend void swap<>(Map_list<K, V>& ml1, Map_list<K, V>& ml2);
};

template <class K, class V>
void Map_list<K, V>::New() {
    head_ = new Node;
    tail_ = new Node;
    items_ = 0, cursor_ = nullptr;
    head_->_pre = tail_->_next = nullptr;
    head_->_next = tail_;
    tail_->_pre = head_;
    /*K k;
    head_->_key = tail_->_key = k;
    V v;
    head_->_value = tail_->_value = v;*/
}

template <class K, class V>
typename Map_list<K, V>::Node* Map_list<K, V>::create(const K &k, const V &v) {
    Node* tmp = new Node;
    tmp->_next = tmp->_pre = nullptr;
    tmp->_key = k;
    tmp->_value = v;
    return tmp;
}

template <class K, class V>
void Map_list<K, V>::insert(Map_list<K, V>::Node *pre, Map_list<K, V>::Node *next, Map_list<K, V>::Node *cur) {
    pre->_next = cur;
    cur->_pre = pre;
    next->_pre = cur;
    cur->_next = next;
    items_++;
}

template <class K, class V>
void Map_list<K, V>::del(Map_list<K, V>::Node *cur) {
    Node* pre = cur->_pre, * next = cur->_next;
    pre->_next = next;
    next->_pre = pre;
    destroy(cur);
    items_--;
}

template <class K, class V>
void Map_list<K, V>::reset() {
    head_->_next = tail_, tail_->_pre = head_;
    cursor_ = nullptr, items_ = 0;
}

template <class K, class V>
void Map_list<K, V>::splice(Map_list<K, V>::Node *pt, Map_list &ml) {
    Node* pt_pre = pt->_pre, * left = ml.head_->_next, * right = ml.tail_->_pre;
    pt_pre->_next = left, left->_pre = pt_pre;
    pt->_pre = right, right->_next = pt;
    ml.reset();
}

template <class K, class V>
void Map_list<K, V>::quick_sort(Map_list<K, V>::Node *ptl, Map_list<K, V>::Node *ptr, int left, int right, bool is_value) {
    if(left >= right) return;
    int i = left, j = right;
    Node* pti = ptl, * ptj = ptr;
    while(pti != ptj) {
        if(is_value) {
            while(ptj->_value >= ptl->_value && i < j) ptj = ptj->_pre, --j;
            while(pti->_value <= ptl->_value && i < j) pti = pti->_next, ++i;
        } else {
            while(ptj->_key >= ptl->_key && i < j) ptj = ptj->_pre, --j;
            while(pti->_key <= ptl->_key && i < j) pti = pti->_next, ++i;
        }
        if(i < j) swap_(pti, ptj);
    }
    swap_(ptl, pti);
    quick_sort(ptl, pti->_pre, left, i - 1, is_value);
    quick_sort(ptj->_next, ptr, j + 1, right, is_value);
}

template <class K, class V>
void Map_list<K, V>::swap_(Map_list<K, V>::Node *p1, Map_list<K, V>::Node *p2) {
    K tmp_k = p1->_key;
    p1->_key = p2->_key, p2->_key = tmp_k;
    V tmp_v = p1->_value;
    p1->_value = p2->_value, p2->_value = tmp_v;
}

template <class K, class V>
Map_list<K, V>::Map_list(const initializer_list<K> &kl, const initializer_list<V> &vl) {
    New();
    for(auto it_k = kl.begin(), it_v = vl.begin(); it_k != kl.end() && it_v != vl.end(); ++it_k, ++it_v)
        push_back(*it_k, *it_v);
}

template <class K, class V>
Map_list<K, V>::Map_list(const initializer_list<pair<K, V>> &li) {
    New();
    for(typename initializer_list<pair<K, V>>::iterator it = li.begin(); it != li.end(); ++it)
        push_back((*it).first, (*it).second);
}

template <class K, class V>
Map_list<K, V>::Map_list(Map_list &ml) {
    New();
    for(Iterator it = ml.begin(); it != ml.end(); ++it)
        push_back(*it);
}

template <class K, class V>
Map_list<K, V>::Map_list(Map_list &&ml): items_(ml.items_), head_(ml.head_), tail_(ml.tail_) {
    ml.New();
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::push_back(const K &k, const V &v) {
    Node* tmp = create(k, v);
    insert(tail_->_pre, tail_, tmp);
    return *this;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::push_back(const pair<K, V>& pr) {
    Node* tmp = create(pr.first, pr.second);
    insert(tail_->_pre, tail_, tmp);
    return *this;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::pop_back() {
    if(items_ > 0)
        del(tail_->_pre);
    return *this;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::pop_back(pair<K, V>& pr) {
    try {
        if(items_ <= 0) {
            throw "no member in Map_list\n";
        } else {
            Node* cur = tail_->_pre;
            pr.first = cur->_key;
            pr.second = cur->_value;
            del(cur);
            return *this;
        }
    } catch(const char* s) {
        cout << s << endl;
    }
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::push_front(const K &k, const V &v) {
    Node* tmp = create(k, v);
    insert(head_, head_->_next, tmp);
    return *this;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::push_front(const pair<K, V>& pr) {
    Node* tmp = create(pr.first, pr.second);
    insert(head_, head_->_next, tmp);
    return *this;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::pop_front() {
    if(items_ > 0)
        del(head_->_next);
    return *this;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::pop_front(pair<K, V>& pr) {
    try {
        if(items_ <= 0) {
            throw "no member in Map_list";
        } else {
            Node* cur = head_->_next;
            pr.first = cur->_key;
            pr.second = cur->_value;
            del(cur);
            return *this;
        }
    } catch(const char* s) {
        cout << s << endl;
    }
}

template <class K, class V>
void Map_list<K, V>::remove(const K &k) {
    cursor_ = head_->_next;
    while(cursor_->_next) {
        if(cursor_->_key == k) {
            Node* tmp = cursor_->_pre;
            del(cursor_);
            cursor_ = tmp;
        }
        cursor_ = cursor_->_next;
    }
    cursor_ = nullptr;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::merge_after(Map_list &ml) {
    if(this == &ml) return *this;
    Node* left = tail_->_pre, * right = ml.head_->_next;
    left->_next = right, right->_pre = left, items_ += ml.items_;
    tail_->_pre = ml.tail_->_pre, ml.tail_->_pre->_next = tail_;
    ml.reset();
    return *this;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::merge_before(Map_list &ml) {
    if(this == &ml) return *this;
    Node* left = ml.tail_->_pre, * right = head_->_next;
    left->_next = right, right->_pre = left, items_ += ml.items_;
    head_->_next = ml.head_->_next, ml.head_->_next->_pre = head_;
    ml.reset();
    return *this;
}

template <class K, class V>
void Map_list<K, V>::ksplice(const K &k, Map_list &ml) {
    Node* tmp = head_->_next;
    while(tmp->_next) {
        if(tmp->_key == k) splice(tmp, ml);
        tmp = tmp->_next;
    }
}

template <class K, class V>
void Map_list<K, V>::vsplice(const V &v, Map_list &ml) {
    Node* tmp = head_->_next;
    while(tmp->_next) {
        if(tmp->_value == v) splice(tmp, ml);
        tmp = tmp->_next;
    }
}

template <class K, class V>
void Map_list<K, V>::reverse() {
    if(items_ < 2) return;
    Node* left = head_->_next, * right = tail_->_pre;
    K tmp_k;
    V tmp_v;
    for(int i = 0, n = size() / 2; i < n; ++i) {
        tmp_k = left->_key, left->_key = right->_key, right->_key = tmp_k;
        tmp_v = left->_value, left->_value = right->_value, right->_value = tmp_v;
        left = left->_next, right = right->_pre;
    }
}

template <class K, class V>
void Map_list<K, V>::unique(bool is_value, bool is_sort) {
    if(is_sort) sort(is_value);
    Node* tmp = head_->_next;
    while(tmp->_next) {
        if(is_value ? tmp->_value == tmp->_next->_value : tmp->_key == tmp->_next->_key) {
            cursor_ = tmp, tmp = tmp->_pre;
            del(cursor_);
        }
        tmp = tmp->_next;
    }
    cursor_ = nullptr;
}

template <class K, class V>
V Map_list<K, V>::operator[](const K &k) {
    pair<K, V> pr;
    for(Iterator it = begin(); it != end(); ++it) {
        pr = *it;
        if(pr.first == k) return pr.second;
    }
    return tail_->_value;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::operator()(const K &k) {
    Node* tmp = head_->_next;
    while(tmp->_next) {
        if(tmp->_key == k) {
            cursor_ = tmp;
            break;
        }
        tmp = tmp->_next;
    }
    return *this;
}

template <class K, class V>
Map_list<K, V> Map_list<K, V>::operator+(Map_list &ml) {
    Map_list tmp;
    for(Iterator it = begin(); it != end(); ++it)
        tmp.push_back(*it);
    for(Iterator it = ml.begin(); it != ml.end(); ++it)
        tmp.push_back(*it);
    return tmp;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::operator=(Map_list &ml) {
    if(this == &ml) return *this;
    truncate();
    for(Iterator it = ml.begin(); it != ml.end(); ++it)
        push_back(*it);
    return *this;
}

template <class K, class V>
Map_list<K, V>& Map_list<K, V>::operator=(Map_list &&ml) {
    if(this == &ml) return *this;
    truncate();
    head_ = ml.head_, tail_ = ml.tail_, items_ = ml.items_;
    ml.New();
    return *this;
}

template <class K, class V>
typename Map_list<K, V>::Iterator Map_list<K, V>::Iterator::operator+(int n) {
    Iterator it = *this;
    for (int i = 0; i < n; ++i) {
        if(it.pt_->_next == nullptr) break;
        ++it;
    }
    return it;
}

template <class K, class V>
typename Map_list<K, V>::Iterator Map_list<K, V>::Iterator::operator-(int n) {
    Iterator it = *this;
    for (int i = 0; i < n; ++i) {
        if(it.pt_->_pre == nullptr) break;
        --it;
    }
    return it;
}

template <class K, class V>
bool Map_list<K, V>::Iterator::operator<(const Map_list<K, V>::Iterator &it) const {
    Iterator tmp = *this;
    while(tmp.pt_ != it.pt_) {
        if(tmp.pt_->_next == nullptr) break;
        tmp.pt_ = tmp.pt_->_next;
        if(tmp.pt_ == it.pt_) return true;
    }
    return false;
}

template <class K, class V>
void Map_list<K, V>::Iterator::swap(const Map_list<K, V>::Iterator &it) const {
    K tmp_k = this->pt_->_key;
    this->pt_->_key = it.pt_->_key, it.pt_->_key = tmp_k;
    V tmp_v = this->pt_->_value;
    this->pt_->_value = it.pt_->_value, it.pt_->_value = tmp_v;
}

template <typename K, typename V>
void swap(Map_list<K, V>& ml1, Map_list<K, V>& ml2) {
    Map_list<K, V> tmp;
    tmp = move(ml1), ml1 = move(ml2), ml2 = move(tmp);
}



#endif //ALGORITHM_MAP_LIST_H
