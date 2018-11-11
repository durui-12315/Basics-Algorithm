#include "../common.h"
#include <algorithm>
#include <cmath>
#include "../Map_list.h"

template <typename T> void dfs1(int*, const int, T*, const int, int = 0);
template <typename T> void dfs2(Map_list<int, pair<int, int>>&, int [], const int, T [], const int, int = 0);

int total = 0;

int main() {
    /*栈：判断回文*/
    /*string huiwen = "([{(({[(";
    int len = huiwen.size() / 2, top = 0;
    bool is_odd = huiwen.size() % 2;
    char hw[len];
    for(int i = 0; i < len; ++i) hw[top++] = huiwen[i];
    for(int i = is_odd ? len + 1 : len; i < huiwen.size(); ++i) {
        if(hw[--top] != huiwen[i]) {
            cout << "Not huiwen!\n";
            break;
        }
    }
    for(auto x: hw) cout << x << " ";*/

    /*深度优先遍历 depth first search*/

    /*//case 1 数字排列
    const int N = 5, Step = 4;
    int book[N] {}, a[Step];
    dfs1(book, N, a, Step);
    NHR;*/

    /*//case 2 数字加法遍历
    const int N_ = 9, Step_ = 9;
    int book_[N_] {}, arr[Step_];
    Map_list<int, pair<int, int>> ml, ml_;
    pair<int, int> pr;
    auto lambda = [](const pair<int, pair<int, int>>& pr){
        cout << pr.second.first << "+" << pr.second.second << "=" << pr.first <<  "; ";
    };
    dfs2(ml, book_, N_, arr, Step_);
    for_each(ml.begin(), ml.end(), [&ml_](const pair<int, pair<int, int>>& pr){
        ml_.push_back(abs(pow(pr.second.first, 3) - pow(pr.second.second, 3)), pr.second);  //越高阶，差值越唯一
    });
    ml_.unique(false);
    for(auto it = ml_.begin(); it != ml_.end(); ++it) {
        pr = (*it).second;
        it.update(pr.first + pr.second, pr);
    }
    ml_.sort();
    for_each(ml_.begin(), ml_.end(), lambda);*/

    //case 3


    return 0;
}

template <typename T>
void dfs1(int* pbook, const int len_book, T* parr, const int max_depth, int depth) {
    if(depth == max_depth) {
        for(int i = 0; i < max_depth; ++i) cout << parr[i] << " ";
        cout << "; ";
        return;
    }
    for(int i = 0; i < len_book; ++i) {
        if(pbook[i] == 0) {
            pbook[i] = 1;
            parr[depth] = i + 1;
            dfs1(pbook, len_book, parr, max_depth, depth + 1);
            pbook[i] = 0;
        }
    }
}

template <typename T>
void dfs2(Map_list<int, pair<int, int>>& ml, int book[], const int len_book, T arr[], const int max_depth, int depth) {
    if(depth == max_depth) {
        int i = arr[0] * 100 + arr[1] * 10 + arr[2], j = arr[3] * 100 + arr[4] * 10 + arr[5],
            k = arr[6] * 100 + arr[7] * 10 + arr[8];
        if(i + j == k) ml.push_back(k, pair<int, int>(i, j));
        return;
    }
    for (int i = 0; i < len_book; ++i) {
        if(book[i] == 0) {
            book[i] = 1;
            arr[depth] = i + 1;
            dfs2(ml, book, len_book, arr, max_depth, depth + 1);
            book[i] = 0;
        }
    }
}

