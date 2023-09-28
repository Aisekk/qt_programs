#ifndef HASH_HEAP_H
#define HASH_HEAP_H

#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <map>
#include <algorithm>

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
        //std::map<int, prior_queue, std::greater<int>> ord;
        std::map<int, vector<string>, std::greater<int>> ord;
        //for (int i = 0; i < ums.bucket_count(); ++i) {
        for (auto it = ums.begin(); it != ums.end();) {
            //int bsize = (int)ums.bucket_size(i);
            //const auto &word = *ums.begin(i);
            const auto &word = *it;
            int bsize = (int)ums.count(word);
            if (ord.find(bsize) == ord.end()) {
                //ord.emplace(std::make_pair(bsize, {word}));
                //prior_queue pq;
                //pq.push(word);
                vector<string> v = {word};
                ord[bsize] = v;
                auto p = ums.equal_range(word);
                it = ums.erase(p.first, p.second);
            } else {
                ord[bsize].push_back(word);
                ++it;
            }
        }
        for (auto it = ord.begin(); it != ord.end(); ++it) {
            if (k == 0) {
                break;
            }
            auto &[i, v] = *it;
            auto last = std::unique(v.begin(), v.end());
            v.erase(last, v.end());
            std::sort(v.begin(), v.end());
            last = std::unique(v.begin(), v.end());
            v.erase(last, v.end());
            push(v, value, k);
        }
        return value;
    }
private:
    void push(vector<string> &v, vector<string> &value, int &k) {
        while (!v.empty()) {
            if (k == 0) {
                break;
            }
            std::make_heap(v.begin(), v.end(), std::greater<>{});
            std::pop_heap(v.begin(), v.end(), std::greater<>{});
            auto top = v.back();
            v.pop_back();
            value.push_back(top);
            --k;
        }
    }
    void push(prior_queue &pq, vector<string> &value, int &k) {
        for (; !pq.empty(); pq.pop(), --k) {
            if (k == 0) {
                break;
            }
            value.push_back(pq.top());
        }
    }
};

}

#endif // HASH_HEAP_H
