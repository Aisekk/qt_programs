#ifndef REVERSE_H
#define REVERSE_H

#include <string>
#include <cstring>
#include <iostream>

namespace Reverse {
void reverse(std::string &s);
void reverse(char *s);

void outReverseResults() {
    std::string stroka("alibaba"); reverse(stroka); std::cout << stroka << std::endl;
    //int n = 0;
    //char s[8] = "alibaba"; n = sizeof("alibaba");

    char *s = new char[8];
    //for (char c = 'a'; c != 'f'; ++c, ++s) { *s = c; }; // s -> '\0'
    char *ss = s;
    for (char c = 'a'; c != 'h'; ++c, ++ss) { *ss = c; };
    *ss = '\0';
    std::cout << s << "; std::strlen(s) = " << std::strlen(s) << std::endl;
    Reverse::reverse(s); std::cout << s << std::endl;
    delete [] s;

    std::cout << "sizeof(alibaba) = " << sizeof("alibaba") << std::endl;
}

void reverse(std::string &s) {
    auto first = s.begin(), last = s.end();
    while (first != last) {
        --last;
        if (first == last) {
            break;
        }
        std::swap(*first, *last);
        ++first;
    }
}

void reverse(char *s) {
    char *l = &s[std::strlen(s)];
    while (*s != '\0') {
        --l;
        if (s == l) {
            break;
        }
        std::swap(*s, *l);
        ++s;
    }
}

}

#endif // REVERSE_H
