#ifndef HASH_HEAP_H
#define HASH_HEAP_H

#include <vector>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

namespace Heap {

class Solution {
public:
    using prior_queue = std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>>;
    vector<string> topKFrequent(vector<string>& words, int k) {
        std::unordered_multiset<string> ums;
        ums.reserve(words.size());
        for (const auto &word : words) {
            ums.insert(word);
        }
        vector<string> value;
        value.reserve(words.size());
        //const int s = k;
        while (k != 0) {
            auto pq = build(k, ums);
            push(pq, value);
            --k;
        }
        return value;
    }
private:
    prior_queue build(int k, std::unordered_multiset<string> &ums) {
        prior_queue pq;
        // for (auto it = ums.begin(); it != ums.end(); ++it) {
        //     int index = ums.bucket(*it);
        //     if (ums.count(*it) == k) {
        //         const auto &word = *it;
        //         pq.push(word);
        //         it = ums.erase(word);
        //     }
        // }
        //for (int i = 0; i < ums.bucket_count(); ++i) {}
        for (auto it = ums.begin(); it != ums.end();) {
            int index = ums.bucket(*it);
            if ((int)ums.bucket_size(index) == k) {
                const auto &word = *it;
                auto p = ums.equal_range(word);
                //const auto &word = *ums.begin(index);
                pq.push(word);
                it = ums.erase(p.first, p.second);
            } else {
                ++it;
            }
        }
        return pq;
    }
    void push(prior_queue &pq, vector<string> &value) {
        // for (; !pq.empty(); pq.pop()) {
        //     value.push_back(pq.top());
        // }
        while (!pq.empty()) {
            value.push_back(pq.top());
            pq.pop();
        }
    }
};

}

#endif // HASH_HEAP_H
