#include "../common.h"
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "../Map_list.h"

template <typename T> void swap_(T&, T&);
template <typename T> void quick_sort(T*, int, int);
template <typename T> void min_heap(T [], const int, int);
template <typename T> void max_heap(T [], const int, int);
template <typename K, typename V> void max_heap_list(Map_list<K, V>&, typename Map_list<K, V>::Iterator);
template <typename K, typename V> void min_heap_list(Map_list<K, V>&, typename Map_list<K, V>::Iterator);

int main() {
    /*桶排序、冒泡排序、快速排序的使用场景：
     * 1.排序数的幅度小，适用桶排序；
     * 2.排序数的幅度大但数量小，适用冒泡排序；
     * 3.介于两者之间用快速排序。*/

    /*桶排序*/

    /*//case 1
    cout << "Input some numbers:";
    int x, book[101] = {};  //所有成员都为0
    while(cin >> x) {
        if(x > 100) {
            cout << "Numbers you entered is bigger than 100\n";
            continue;
        }
        ++book[x];
    }
    NHR;
    vector<int> v;
    for (int i = 0; i < 101; ++i)
        for (int j = 0; j < book[i]; ++j)
            v.push_back(i);
    for_each(v.begin(), v.end(), [](int n){cout << n << " ";});*/
    
    /*//case 2
    Map_list<int, string> book[101];
    pair<int, string> pr;
    char flag = 'Y';
    do {
        cout << "Input name:";
        cin >> pr.second;
        eat_line_rest();
        cout << "Input score between 0 and 100:";
        cin >> pr.first;
        eat_line_rest();
        if(pr.first > -1 && pr.first <= 100) book[pr.first].push_back(pr);
        cout << "continue or not[N/Y]";
        cin >> flag;
        eat_line_rest();
        if(flag == 'N') break;
    } while(true);
    for (int i = 100; i >= 0; --i) {
        if(book[i].size())
            for_each(book[i].begin(), book[i].end(), [](const pair<int, string>& pr){
               cout << "score:" << pr.first << ",name:" + pr.second + "; ";
            });
    }*/

    /*冒泡排序*/

    /*vector<double> vd;
    double j;
    while(cin >> j) vd.push_back(j);
    for (int i = vd.size() - 1; i > 0; --i)
        for (int k = 0; k < i; ++k)
            if(vd[k] > vd[k + 1]) swap_(vd[k], vd[k + 1]);
    for_each(vd.begin(), vd.end(), [](double d){cout << d << " ";});*/

    /*快速排序*/

    /*//case 1
    double arr[] = {6,1,2,7,9,3,4,5,10,8};
    quick_sort(arr, 0, 9);
    for(auto x: arr) cout << x << " ";*/

    /*//case 2
    initializer_list<int> k = {6,1,2,7,9,3,4,5,10,8,6};
    initializer_list<double> v = {6,1,2,7,9,3,4,5,10,8,6};
    Map_list<int, double> ml(k, v);
    srand(time(0));
    for (int i = 0; i < 30; ++i) ml.push_front(rand() % 20, rand() % 20);
    auto lambda = [](const pair<int, double>& pr){cout << pr.first << ":" << pr.second << "; ";};
    ml.sort();
    for_each(ml.begin(), ml.end(), lambda);
    NHR;
    ml.sort(false);
    for_each(ml.begin(), ml.end(), lambda);
    NHR;
    ml.unique(false);
    for_each(ml.begin(), ml.end(), lambda);
    NHR;
    ml.unique();
    for_each(ml.begin(), ml.end(), lambda);*/

    /*最小（大）堆、堆排序（完全二叉树排序）*/

    /*//case 1 最小堆堆顶插入元素
    const int N = 14;
    int heap[N] = {23,2,5,12,7,17,25,19,36,99,22,28,46,92}, i_now = 1, tmp;
    bool flag = true;
    while(flag && i_now * 2 <= N) {  //若有左子树
        tmp = i_now;
        if(heap[i_now - 1] > heap[i_now * 2 - 1]) tmp = i_now * 2;  //左子树的值较小
        if(i_now * 2 + 1 <= N) //若有右子树
            if(heap[tmp - 1] > heap[i_now * 2]) tmp = i_now * 2 + 1;  //右子树的值最小
        if(i_now != tmp) {  //最小值不是父节点
            swap_(heap[tmp - 1], heap[i_now - 1]);
            i_now = tmp;
        } else
            flag = false;
    }
    for(auto x: heap) cout << x << " ";*/

    //case 2 最小堆堆底插入元素
    /*const int N = 15;
    int heap[N] = {2,7,5,12,22,17,25,19,36,99,23,28,46,92,3}, i = N;
    bool flag = true;
    while(flag && i != 1)
        if(heap[i - 1] < heap[i / 2 - 1]) {  //与父节点比较
            swap_(heap[i - 1], heap[i / 2 - 1]);
            i /= 2;
        } else
            flag = false;
    for(auto x: heap) cout << x << " ";*/

    /*//case 2 最小堆和最大堆建立
    const int N = 14;
    int heap[N] = {99,5,36,7,22,17,46,12,2,19,25,28,1,92};
    for(int i = N / 2; i > 0; --i) min_heap(heap, N, i);
    for(auto x: heap) cout << x << " ";
    NHR;
    int heap_[N] = {99,5,36,7,22,17,46,12,2,19,25,28,1,92};
    for(int i = N / 2; i > 0; --i) max_heap(heap_, N, i);
    for(auto x: heap_) cout << x << " ";*/

    /*//case 3 堆排序
    const int N = 14;
    int heap[N] = {99,5,36,7,22,17,46,12,2,19,25,28,1,92}, n = N;
    for(int i = N / 2; i > 0; --i) max_heap(heap, N, i);
    vector<int> v;
    while(true) {
        v.push_back(heap[0]);
        if(n == 1) break;
        heap[0] = heap[n - 1];
        --n;
        max_heap(heap, n, 1);
    }
    for_each(v.begin(), v.end(), [](const int& n){cout << n << " ";});*/

    //case 4 堆与链表：最大堆建立求最大数
    Map_list<int, double> ml, ml_;
    srand(time(0));
    for (int i = 0, r; r = rand() % 100, i < 50; ++i) ml.push_front(r, r);
    int i_now = (ml.size() - 1) / 2;
    for(auto it = ml.iter(i_now); it != ml.rend(); --it) max_heap_list(ml, it);
    auto lambda = [](const pair<int, double>& pr){cout << pr.first << ":" << pr.second << "; ";};
    for_each(ml.begin(), ml.end(), lambda);
    NHR;
    //case 5 堆与链表：最小堆排序
    for(auto it = ml.iter(i_now); it != ml.rend(); --it) min_heap_list(ml, it);
    pair<int, double> pr;
    while(true) {
        ml_.push_back(ml.front());
        if(ml.size() == 1) break;
        ml.pop_front().pop_back(pr).push_front(pr);
        min_heap_list(ml, ml.begin());
    }
    for_each(ml_.begin(), ml_.end(), lambda);


    return 0;
}

template <typename T>
void swap_(T& t1, T& t2) {
    T tmp = t1;
    t1 = t2, t2 = tmp;
}

template <typename T>
void quick_sort(T* parr, int left, int right) {
    if(left >= right) return;
    int i = left, j = right;
    while(i != j) {
        while(parr[j] >= parr[left] && i < j) --j;
        while(parr[i] <= parr[left] && i < j) ++i;
        if(i < j) swap_(parr[i], parr[j]);
    }
    swap_(parr[left], parr[i]);
    quick_sort(parr, left, i - 1);
    quick_sort(parr, j + 1, right);
}

template <typename T>
void min_heap(T a[], const int n, int i_now) {  //等价 T* pt
    bool not_end = true;
    int tmp = i_now;
    while(not_end && i_now * 2 <= n) {
        if(a[i_now - 1] > a[i_now * 2 - 1])
            tmp = i_now * 2;
        if(i_now * 2 + 1 <= n && a[tmp - 1] > a[i_now * 2])
            tmp = i_now * 2 + 1;
        if(tmp != i_now) {
            swap_(a[tmp - 1], a[i_now - 1]);
            i_now = tmp;
        } else
            not_end = false;
    }
}

template <typename T>
void max_heap(T* pt, const int n, int i_now) {
    bool not_end = true;
    int tmp = i_now;
    while(not_end && i_now * 2 <= n) {
        if(pt[i_now - 1] < pt[i_now * 2 - 1])
            tmp = i_now * 2;
        if(i_now * 2 + 1 <= n && pt[tmp - 1] < pt[i_now * 2])
            tmp = i_now * 2 + 1;
        if(tmp != i_now) {
            swap_(pt[tmp - 1], pt[i_now - 1]);
            i_now = tmp;
        } else
            not_end = false;
    }
}

template <typename K, typename V>
void max_heap_list(Map_list<K, V>& ml, typename Map_list<K, V>::Iterator it) {
    typename Map_list<K, V>::Iterator it_tmp, itl, itr;
    bool is_continue = true;
    while(is_continue && (it.index() + 1) * 2 <= ml.size()) {
        itl = it + (it.index() + 1), it_tmp = it;
        if((*it).second < (*itl).second) it_tmp = itl;
        if(itl.index() + 2 <= ml.size()) {
            itr = itl + 1;
            if((*it_tmp).second < (*itr).second) it_tmp = itr;
        }
        if(it != it_tmp)
            it.swap(it_tmp), it = it_tmp;
        else
            is_continue = false;
    }
}

template <typename K, typename V>
void min_heap_list(Map_list<K, V>& ml, typename Map_list<K, V>::Iterator it) {
    bool is_continue = true;
    typename Map_list<K, V>::Iterator it_tmp = it, itl, itr;
    while(is_continue && (it.index() + 1) * 2 <= ml.size()) {
        itl = it + (it.index() + 1);
        if((*it).second > (*itl).second) it_tmp = itl;
        if(itl.index() + 2 <= ml.size()) {
            itr = itl + 1;
            if((*it_tmp).second > (*itr).second) it_tmp = itr;
        }
        if(it != it_tmp)
            it.swap(it_tmp), it = it_tmp;
        else
            is_continue = false;
    }
}