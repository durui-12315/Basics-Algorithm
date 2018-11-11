#ifndef ALGORITHM_SIMHASH_H
#define ALGORITHM_SIMHASH_H

#include "md5.h"

template <class T>
class SimHash {
private:
    struct Member {  //链地址存储法
        string key_;
        T val_;
        Member* next_;
    };
    static const int _len = 102 * 32;
    int _members = 0;
    //unique_ptr<Member*[]> _hash_arr;
    Member* _hash_arr[_len] {};
    int get_index(string& key);
    Member* create(string& k, const T& v);
    void destory(const Member* pm) {delete pm;}
public:
    //SimHash(): _hash_arr(new Member*[_len]) {}
    SimHash() {}
    SimHash(const SimHash& sh) {}
    ~SimHash();
    int size() {return _members;}
    SimHash& set(string& key, const T& val);
    SimHash& set(const char* key, const T& val) {string s(key); return set(s, val);}
    T& get(string& key);
    T& get(const char* key) {string s(key); return get(s);}
    SimHash& operator=(const SimHash& sh) {return *this;}
    T& operator[](string& key) {return get(key);}
    T& operator[](const char* key) {return get(key);}
};

template <class T>
int SimHash<T>::get_index(string& key) {
    CMD5 md5;
    md5.GenerateMD5((unsigned char*)(key.c_str()), key.size());
    string re = md5.ToString();
    int sum = 0;
    for(int i = 0; i < 32; ++i) sum += int(re[i]);
    return sum % _len - 1;
}

template <class T>
typename SimHash<T>::Member* SimHash<T>::create(string &k, const T &v) {
    Member* tmp = new Member;
    tmp->val_ = v, tmp->next_ = nullptr, tmp->key_ = k;
}

template <class T>
SimHash<T>& SimHash<T>::set(string &key, const T &val) {
    int i = get_index(key);
    Member* tmp = _hash_arr[i];
    if(tmp) {
        while(true) {
            if(tmp->key_ == key) {
                tmp->val_ = val;
                break;
            }
            if(tmp->next_ == nullptr) {
                tmp->next_ = create(key, val);
                break;
            }
            tmp = tmp->next_;
        }
    } else
        _hash_arr[i] = create(key, val);
    ++_members;
    return *this;
}

template <class T>
T& SimHash<T>::get(string &key) {
    int i = get_index(key);
    Member* tmp = _hash_arr[i];
    while(tmp) {
        if(key == tmp->key_) return tmp->val_;
        tmp = tmp->next_;
    }
}

template <class T>
SimHash<T>::~SimHash() {
    Member* tmp1, * tmp2;
    for (int i = 0; i < _members; ++i)
        if(tmp1 = _hash_arr[i])
            do {
                tmp2 = tmp1->next_, destory(tmp1), tmp1 = tmp2;
            } while(tmp1);
}

#endif //ALGORITHM_SIMHASH_H
