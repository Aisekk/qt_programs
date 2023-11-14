#ifndef COPY_ALGS_H
#define COPY_ALGS_H

#include <array>
#include <algorithm>
#include <iostream>

namespace CopyAlgs {

void print(const std::array<char, 20> arr) {
    for (char ch : arr) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

template <int N>
void copyStdStringToStdArray(std::array<char, N> &arr, const std::string &str){
    int index = 0;
    int size = static_cast<int>(str.size());
    if (N == size) {
        return;
    }
    std::for_each(arr.begin(), arr.end(), [&str, &index, &size](char &ch) {
        ch = str[index++];
        if (size < index) {
            ch = '\0';
        }
    });
};

void copy_string_to_std_array() {
    std::array<char, 20> arr{};
    print(arr);
    std::string str{"stroka"};
//    int index = 0;
//    int size = (int)str.size();
//    std::for_each(arr.begin(), arr.end(), [&str, &index, &size](char &ch) {
//        ch = str[index++];
//        if (size < index) {
//            ch = '\0';
//        }
//    });
    copyStdStringToStdArray<(int)arr.size()>(arr, str);
    print(arr);
}

void test() {
    copy_string_to_std_array();
}

}

#endif // COPY_ALGS_H
