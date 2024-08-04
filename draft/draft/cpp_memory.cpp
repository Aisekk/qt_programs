#include "cpp_memory.h"
#include <vector>

namespace {
//const Number<int> num_int{1};
}
//static const Number<int> num_int{1};
const Number<int> num_int{1};

namespace CppMemory {

void test() {
    char szData[] = "abc";
    szData[0] = 'A';
    std::cout << szData << std::endl;
    const char *pszData = "abc";
    //pszData[0] = 'A'; // compile error
    std::cout << pszData << std::endl;
}

void test_number_template() {
    Number<int> n1(1);
    Number<double> n2(2.0);
    Number<long long> n3(100);

    std::cout << *n1.get() << std::endl;
    std::cout << *n2.get() << std::endl;
    std::cout << *n3.get() << std::endl;
}

void test_global_template() {
    std::cout << *num_int.get() << std::endl;
}

}
