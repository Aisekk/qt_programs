#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <unordered_map>
#include <vector>
#include <forward_list>
#include <iostream>
#include <QDebug>

namespace HashTable {

void outHashTableParams() {
    std::unordered_map<int, int> um;
    auto hf = um.hash_function();
    for (int i = -5; i < 20; ++i) {
        const int key = i + 0;
        qDebug() << "std::hash(" << key << ") = " <<  std::hash<int>()(key);
        qDebug() << "hf(" << key << ") = " <<  hf(key);
        um.insert({key, i});
        //qDebug() << "sizeof(std::unordered_map<int, int>) = " << sizeof(um);
        qDebug() << "um.bucket_count() = " << um.bucket_count();
        //qDebug() << "um.bucket_size() = " << um.bucket_size();
    }
}

class MyHashMap {
    using Chain = std::forward_list<std::pair<const int, int>>;
public:
    MyHashMap() : cap{1}, _size{0} {
        c.reserve(cap);
        fill(0, cap);
    }

    int size() const { return _size; }

    void put(int key, int value) {
        if (_size > cap / 2) {
            rehash();
        }
        int i = hash_int(key);
        auto &l = c[i];
         if (l.empty()) {
            l.push_front({key, value});
            ++_size;
            return;
        }
        auto it = std::find_if(l.begin(), l.end(), [key](const Chain::value_type &p){
            return p.first == key;
        });
        if (it == l.end()) {
            l.push_front({key, value});
            ++_size;
        } else {
            it->second = value;
        };
    }

    int get(int key) {
        auto i = hash_int(key);
        if (i >= (int)c.size()) {
            return -1;
        }
        const auto &l = c[i];
        if (l.empty()) {
            return -1;
        }
        auto it = std::find_if(l.begin(), l.end(), [&key](const auto &p){
            return p.first == key;
        });
        qDebug() << "get(): find()";
        return it == l.end() ? -1 : it->second;
    }

    void remove(int key) {
        qDebug() << "remove()";
        auto i = hash_int(key);
        if (i >= (int)c.size()) {
            return;
        }
        auto &l = c[i];
        if (l.empty()) {
            return;
        }
        auto it = std::find_if(l.begin(), l.end(), [key](const Chain::value_type &p){
            return p.first == key;
        });
        if (it == l.end()) {
            return;
        } else {
            l.remove(*it);
            --_size;
        }
    }

    void rehash() {
        qDebug() << "rehash()";
        cap *= 2;
        auto tmp = c;
        c.clear();
        c.reserve(cap);
        fill(0, cap);
        for (const auto &l : tmp) {
            for (const auto &[key, value] : l) {
                int i = hash_int(key);
                auto &cl = c[i];
                cl.push_front({key, value});
            }
        }
    }

    void print() {
        qDebug() << "print start";
        for (const auto &l : c) {
            for (const auto &p : l) {
                qDebug() << "(" << p.first << "," << p.second << ")";
            }
            //std::cout << std::endl;
        }
        qDebug() << "print end";
    }

private:
    void fill(int start, int end) {
        for (int i = start; i < end; ++i) {
            c.push_back(Chain{});
        }
    }
    int hash_int(int key) {
        return key % cap;
    }

    int cap;
    int _size;
    std::vector<Chain> c;
};

void checkMyHashMap() {
    MyHashMap hashMap;
    hashMap.put(1,1);
    hashMap.put(2,2);
    hashMap.put(3,3);
    hashMap.print();
    hashMap.put(4,4);
    hashMap.put(5,5);
    hashMap.print();
    qDebug() << "hashMap.get(1) = " << hashMap.get(1);
    qDebug() << "hashMap.size() = " << hashMap.size();
    hashMap.put(2, 1);
    //hashMap.remove(2);
    hashMap.put(6,6);
    hashMap.put(7,7);
    hashMap.print();
    qDebug() << "hashMap.get(1) = " << hashMap.get(1);
    qDebug() << "hashMap.size() = " << hashMap.size();
//    hashMap.rehash();
//    qDebug() << "hashMap.rehash()";
//    qDebug() << "hashMap.get(1) = " << hashMap.get(1);
//    qDebug() << "hashMap.size() = " << hashMap.size();
}

}

#endif // HASH_TABLE_H
