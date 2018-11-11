#include "../common.h"
#include "SimHash.h"
#include <cmath>

/*const int Len = 1000;
double hash_arr[Len] {};

int hash_index(unsigned char* pc) {
    int i = 0;
    while(pc[i++]);
    CMD5 cmd5;
    cmd5.GenerateMD5(pc, i);
    const char* re = cmd5.ToString().c_str();
    int sum = 0;
    for(int i = 0; i < 32; ++i) sum += int(re[i]);
    delete [] re;
    return sum % Len - 1;
}

inline void hash_set(const char* key, double value) {
    hash_arr[hash_index((unsigned char*)key)] = value;
}

inline void hash_set(const string& key, double value) {
    const char* p = key.c_str();
    hash_arr[hash_index((unsigned char*)p)] = value;
}

inline double hash_get(const char* key) {
    return hash_arr[hash_index((unsigned char*)key)];
}

inline double hash_get(const string& key) {
    const char* p = key.c_str();
    return hash_arr[hash_index((unsigned char*)p)];
}*/

const int Null = -INT_MAX / 2;
template <typename V>
struct HashTable {
    V* address;  //动态数组首地址
    int size;  //当前元素个数
    int length;  //表长
};
HashTable<int> hashTable;

template <typename V>
void init(int max_size = 100) {  //初始化
    hashTable.size = 0;
    hashTable.length = max_size;
    hashTable.address = new V[max_size];
    for (int i = 0; i < max_size; ++i) hashTable.address[i] = Null;
}

template <typename K>
int getHash(K key) {
    return int(key % hashTable.length);  //求模取址法，适用键值对较少时
}

template <typename K, typename V>
bool insertHash(K key, V val) {
    if(hashTable.size == hashTable.length) return false;
    int i = getHash(key), j = 0, j_ = 0;
    while(hashTable.address[i] != Null) {
        if(++j_ % 2) ++j;
        i = (i + j * j) % hashTable.length;  //开放定址法二元探测（防止关键字对应的值聚集在某一区域）
    }
    hashTable.address[i] = val;
    hashTable.size += 1;
    return true;
}

template <typename K, typename V>
int searchHash(K key, V val) {
    int i = getHash(key), i_ = i, j = 0, j_ = 0;
    if(hashTable.address[i] == Null) return 1;
    while(hashTable.address[i] != val) {
        if(++j_ % 2) ++j;
        i = (i + j * j) % hashTable.length;
        if(hashTable.address[i] == Null) return 2;
        if(i == i_) return 3;
    }
    return 0;
}

int main() {
    /*简易一对多散列表查找算法*/
    int key = 10, val[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, repeat = 20;
    init<int>(500);  //表大小决定一对多的键和值的极限
    for(int i = 1; i <= repeat; ++i)
        for(auto& x: val) cout << insertHash<int, int>(i * key, x) << " ";
    NHR;
    for (int j = 1, j_; j <= repeat; ++j) {
        cout << "Key " << (j_ = j * key) << ": ";
        for(auto& x: val) cout << searchHash<int, int>(j_, x) << " ";
        NHR;
    }
    cout << searchHash(88, 100) << " ";
    cout << searchHash(3 * key, 10) << " ";
    cout << searchHash(key, 100) << " ";
    cout << searchHash(key, 5) << " ";
    NHR;
    for (int i = 0; i < hashTable.length; ++i) cout << hashTable.address[i] << ' ';


    /*基于md5的简易散列表实现*/
    /*hash_set("hehe", 200);
    hash_set("heihei", 300);
    hash_set("haha", 400);
    hash_set("haohao", 500);
    cout << hash_get("hehe") << endl;
    cout << hash_get("heihei") << endl;
    cout << hash_get("haha") << endl;
    cout << hash_get("haohao") << endl;*/

    /*OOP版*/
    /*SimHash<int> sh;
    sh.set("hehe", 123).set("haha", 321).set("heihei", 888).set("lala", 666);
    sh.set("haha", 123123);
    sh["haha"] = 321321;
    cout << sh["haha"];*/

    return 0;
}