#ifndef ALGORITHM_CIRCULARQUEUE_H
#define ALGORITHM_CIRCULARQUEUE_H

#include <iostream>
#include <initializer_list>
using std::initializer_list;

template <class T, int MaxSize>
class CircularQueue {  //循环双向数组队列
private:
    T data_[MaxSize];
    int size_ = 0;
    int front_ = 0;
    int rear_ = 0;
public:
    explicit CircularQueue() = default;  //use compiler-generated default constructor
    CircularQueue(const initializer_list<T>& il);
    CircularQueue(const CircularQueue& cq) = delete;  //copy constructor forbidden
    CircularQueue(CircularQueue&& cq) = delete;  //move constructor forbidden
    CircularQueue& operator=(const CircularQueue& cq) = delete;  //copy assignment forbidden
    CircularQueue& operator=(CircularQueue&& cq) = delete;  //move assignment forbidden
    void clear() const {front_ = size_ = rear_ = 0;}
    bool is_empty() const {return size_ == 0;}
    bool is_full() const {return size_ == MaxSize;}
    int size() const {return size_;}
    bool push_back(const T& t);
    bool push_front(const T& t);
    bool pop_front(T& t);
    bool pop_front();
    bool pop_back(T& t);
    bool pop_back();
    T& operator[](const int n);
};

template <class T, int MaxSize>
CircularQueue<T, MaxSize>::CircularQueue(const initializer_list<T> &il) {
    for(auto it = il.begin(); it != il.end(); ++it)
        push_back(*it);
}

template <class T, int MaxSize>
bool CircularQueue<T, MaxSize>::push_back(const T &t) {
    if(is_full()) return false;
    if(rear_ == MaxSize) rear_ = 0;
    data_[rear_++] = t;
    ++size_;
    return true;
}

template <class T, int MaxSize>
bool CircularQueue<T, MaxSize>::push_front(const T &t) {
    if(is_full()) return false;
    if(is_empty()) {
        rear_ += 1;
    } else {
        --front_;
        if(front_ == -1) front_ = MaxSize - 1;
    }
    data_[front_] = t;
    ++size_;
    return true;
}

template <class T, int MaxSize>
bool CircularQueue<T, MaxSize>::pop_front() {
    if(is_empty()) return false;
    ++front_;
    if(front_ == MaxSize) front_ = 0;
    --size_;
    return true;
}

template <class T, int MaxSize>
bool CircularQueue<T, MaxSize>::pop_front(T &t) {
    if(is_empty()) return false;
    t = data_[front_++];
    if(front_ == MaxSize) front_ = 0;
    --size_;
    return true;
}

template <class T, int MaxSize>
bool CircularQueue<T, MaxSize>::pop_back() {
    if(is_empty()) return false;
    --rear_;
    --size_;
    if(!is_empty() && rear_ == 0) rear_ = MaxSize;
    return true;
}

template <class T, int MaxSize>
bool CircularQueue<T, MaxSize>::pop_back(T &t) {
    if(is_empty()) return false;
    t = data_[--rear_];
    --size_;
    if(!is_empty() && rear_ == 0) rear_ = MaxSize;
    return true;
}

template <class T, int MaxSize>
T& CircularQueue<T, MaxSize>::operator[](const int n) {
    int i, error = 0;
    if(is_empty() || n < 0)
        error = 1;
    else if(rear_ > front_)
        if(front_ + n >= rear_)
            error = 1;
        else
            i = front_ + n;
    else
        if(front_ + n - MaxSize >= rear_)
            error = 1;
        else
            i = front_ + n < MaxSize ? front_ + n : front_ + n - MaxSize;
    try {
        if(error)
            throw "The index is out of range!";
        else
            return data_[i];
    } catch (const char* ps) {
        std::cout << ps << std::endl;
    }
}

#endif //ALGORITHM_CIRCULARQUEUE_H
