#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void outputVec(const std::vector<int>& vec)
{
    for(auto elem : vec)
        cout << elem << " ";
    cout << "; size = " << vec.size() << "; capacity = " << vec.capacity() << endl;
}

void RemoveEraseVec()
{
    std::vector<int> vec{2, 4, 3, 6, 4};
    outputVec(vec);

    //auto it = std::remove(vec.begin(), vec.end(), 4);
    auto it = std::remove_if(vec.begin(), vec.end(), [](const std::vector<int>::value_type& val) { if(val == 4) return true; return false; });
    cout << "remove: ";
    outputVec(vec);

    //cout << "erase first removed: ";
    //vec.erase(it);
    //outputVec(vec);

    cout << "erase all removed: ";
    vec.erase(it, vec.end());
    outputVec(vec);
}

int main()
{
    RemoveEraseVec();
    return 0;
}
