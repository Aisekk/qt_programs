#ifndef HASH_HEAP_H
#define HASH_HEAP_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <queue>
#include "print.h"

using namespace std;

namespace Heap {

struct Elem {
    int size;
    string word;
    friend bool operator<(Elem const& lhs, Elem const& rhs) {
        return lhs.size < rhs.size;
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        std::unordered_map<string, int> um;
        um.reserve(words.size());
        for (const auto &word : words) {
            ++um[word];
        }
        using Elem = std::pair<string, int>;
        vector<Elem> value;
        value.reserve(um.size());
        for (const auto &[word, count] : um) {
            value.emplace_back(word, count);
        }
        std::sort(value.begin(), value.end(), [](const vector<Elem>::value_type &l, const vector<Elem>::value_type &r) {
            if (l.second > r.second) {
                return true;
            }
            if (l.second == r.second) {
                return l.first < r.first ? true : false;
            }
            return false;
        });
        vector<string> res;
        res.reserve(k);
        std::transform(value.cbegin(), value.cbegin() + k, std::back_inserter(res), [](const vector<Elem>::value_type &elem) {
            return elem.first;
        });
        return res;
    }

    //using prior_queue = std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>>;

//    vector<string> topKFrequent(vector<string>& words, int k) {
//        std::unordered_multiset<string> ums;
//        ums.reserve(words.size());
//        for (const auto &word : words) {
//            ums.insert(word);
//        }
//        vector<string> value;
//        value.reserve(words.size());
//        //std::map<int, prior_queue, std::greater<int>> ord;
//        //std::map<int, vector<string>, std::greater<int>> ord;
////        for (int i = 0; i < (int)ums.bucket_count(); ++i) {
////            int bsize = (int)ums.bucket_size(i);
////            const auto &word = *ums.begin(i);
////            std::cout << "bsize = " << bsize << "; word = " << word << std::endl;
////        }

//        std::cout << "ums read: " << std::endl;
//        for (auto it = ums.begin(); it != ums.end(); ++it) {
//            auto index = ums.bucket(*it);
//            int bsize = (int)ums.bucket_size(index);
//            std::cout << "index = " << index << ": " << *it << "; bsize = " << bsize << std::endl;
//        }

//        std::cout << "ums changed: " << std::endl;
//        using prior_queue = std::priority_queue<Elem>;
//        prior_queue pq;
//        for (auto it = ums.begin(); it != ums.end();) {
//            const auto &word = *it;
//            auto index = ums.bucket(*it);
//            int bsize = (int)ums.bucket_size(index);
//            std::cout << "index = " << index << ": " << *it << "; bsize = " << bsize << std::endl;
//            pq.push({.size = bsize, .word = word});
//            auto p = ums.equal_range(word);
//            it = ums.erase(p.first, p.second);
//        }
//        std::cout << "ums.empty() = " << ums.empty() << std::endl;
//        while (!pq.empty()) {
//            if (k == 0) {
//                break;
//            }
//            std::cout << pq.top().size << ' ' << pq.top().word << "; ";
//            //value.push_back(pq.top().second);
//            value.push_back(pq.top().word);
//            pq.pop();
//            --k;
//        }
//        std::cout << std::endl;
////        for (auto it = ums.begin(); it != ums.end();) {
////            const auto &word = *it;
////            int bsize = (int)ums.count(word);
////            if (ord.find(bsize) == ord.end()) {
////                vector<string> v = {word};
////                ord[bsize] = v;
////            } else {
////                ord[bsize].push_back(word);
////                ++it;
////            }
////        }
////        for (auto it = ord.begin(); it != ord.end(); ++it) {
////            if (k == 0) {
////                break;
////            }
////            auto &[i, v] = *it;
////            auto last = std::unique(v.begin(), v.end());
////            v.erase(last, v.end());
////            std::sort(v.begin(), v.end());
////            last = std::unique(v.begin(), v.end());
////            v.erase(last, v.end());
////            push(v, value, k);
////        }
//        return value;
//    }
//private:
//    void push(vector<string> &v, vector<string> &value, int &k) {
//        while (!v.empty()) {
//            if (k == 0) {
//                break;
//            }
//            std::make_heap(v.begin(), v.end(), std::greater<>{});
//            std::pop_heap(v.begin(), v.end(), std::greater<>{});
//            auto top = v.back();
//            v.pop_back();
//            value.push_back(top);
//            --k;
//        }
//    }
//    void push(prior_queue &pq, vector<string> &value, int &k) {
//        for (; !pq.empty(); pq.pop(), --k) {
//            if (k == 0) {
//                break;
//            }
//            value.push_back(pq.top());
//        }
//    }
};

void topKFrequentOut() {
    Heap::Solution sol;
    std::vector<std::string> words {"i","love","leetcode","i","love","coding"};
    std::vector<std::string> words2{"the","day","is","sunny","the","the","the","sunny","is","is"};
    auto topWords = sol.topKFrequent(words, 2);
    auto topWords2 = sol.topKFrequent(words2, 4);
    Print::print(topWords);
    Print::print(topWords2);
}

}

#endif // HASH_HEAP_H
