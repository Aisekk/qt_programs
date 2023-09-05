#ifndef UNIONS_H
#define UNIONS_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

union U1 {
    std::int32_t n;     // occupies 4 bytes
    std::uint16_t s[2]; // occupies 4 bytes
    std::uint8_t c;     // occupies 1 byte
};                      // the whole union occupies 4 bytes

union U2
{
    std::string str;
    std::vector<int> vec;
    ~U2() {} // needs to know which member is active, only possible in union-like class
};          // the whole union occupies max(sizeof(string), sizeof(vector<int>))

void outUnion_U1();

void outUnion_U2();

#endif // UNIONS_H
