#ifndef BIT_FLAGS_H
#define BIT_FLAGS_H
#include <iostream>

namespace BitFlags {

enum {
    Vaz2107 = 0x01,
    Solaris = 0x02,
    Largus  = 0x04,
    Sonata  = 0x08,
    BatMobile  = 0x10
};

enum {
    Vaz =       1,
    Nissan =    2,
    Hyundai =   4,
    Toyota =    8,
    BMW =       16
};

void test_bit_flags_0x() {
    int car = Vaz2107;
    car |= Solaris;
    if (car & Vaz2107) {
        std::cout << "has vaz2107" << std::endl;
    }
    car |= Sonata;
    if (car & Sonata) {
        std::cout << "has sonata" << std::endl;
    }
    if (car & Solaris) {
        std::cout << "has solaris" << std::endl;
    }
    car |= ~Sonata;
    if (car & ~Sonata) {
        std::cout << "has no sonata" << std::endl;
    }
}

void test_bit_flags() {
    int brand = 0;
    brand = Vaz;
    if (brand & Vaz) {
        std::cout << "has VAZ" << std::endl;
    }
    brand |= BMW;
    if (brand & BMW) {
        std::cout << "has BMW" << std::endl;
    }
    brand |= ~BMW;
    if (brand & ~BMW) {
        std::cout << "has no BMW" << std::endl;
    }
}

}

#endif // BIT_FLAGS_H
