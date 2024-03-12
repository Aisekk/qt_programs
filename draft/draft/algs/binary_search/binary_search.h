#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <vector>
#include "print.h"

namespace BinarySearch {

class Solution {
public:
    void b_search() {
        std::vector<int> v{0,1,2,3,4,5,6,7,8,9};
        Print::print(v);
        std::cout << "search(v, 2) = " << search(v, 2) << std::endl;
        std::cout << "search(v, 9) = " << search(v, 9) << std::endl;
    }

    int search(const std::vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        return searchR(nums, 0, nums.size() - 1, target);
    }
private:
    int searchR(const std::vector<int>& nums, int l, int r, int target) {
        if (l > r) return -1;
        int m = (l + r) / 2;
        if (nums[m] == target) return m;
        if (l == r) return -1;
        if (target < nums[m]) return searchR(nums, l, m - 1, target);
        else return searchR(nums, m + 1, r, target);
    }
};

}

#endif // BINARY_SEARCH_H
