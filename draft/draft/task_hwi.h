#ifndef TASK_HWI_H
#define TASK_HWI_H

#include <string>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>

//# Chemical formula task

//Implement a program that gets input, parses it and output a result.
//The general task is to calculate amount of elements in a string according to some rules.
//Output format is completely free, use anything you want, just print all the found elements.
//Make your program extendable as the task will be extended after each part.

//## Part 1

//The input contains a string with chemistry-like elements with its values.
//Each element starts with a UPPER-case letter and may other lower-case letters after it.
//After the element it might be a number of such elements. Do not forget to check for errors.
//Examples of input strings are (# notes a comment and is not a part of an input string):

//```
//Fe   # Fe => 1
//Fe2  # Fe => 2
//Ag12 # Ag => 12
//N0   # Error
//N-1  # Error
//cl   # Error
//2F   # Error
//```

//## Part 2

//Input may contain more than one element. Examples:

//```
//Fe2O3 # => Fe => 2, O => 3
//H2SO4 # => H => 2, S => 1, O => 4
//HOH   # => H => 2, O => 1

namespace Hwi {

bool parse(std::queue<char>& q, std::multimap<std::string, std::string>& res) {
    std::string k;
    std::string v;
    while (!q.empty()) {
        char c = q.front();
        if (!k.empty() && (c >= 'A' && c <= 'Z')) {
            if (v.empty()) {
                v.push_back('1');
            }
            res.emplace(k, v);
            k.clear();
            v.clear();
        }
        if (c >= '1' && c <= '9') {
            if (!k.empty() && (k[0] < 'A' || k[0] > 'Z')) {
                return false;
            }
            v.push_back(c);
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            k.push_back(c);
        } else {
            return false;
        }
        q.pop();
    }
    if (!k.empty() && (k[0] >= 'A' && k[0] <= 'Z')) {
        if (v.empty()) {
            v.push_back('1');
        }
        res.emplace(k, v);
    }
    return true;
}

std::queue<char> convert(const std::string& input) {
    std::queue<char> q;
    for (auto c : input) {
        q.push(c);
    }
    return q;
}

void print_queue(std::queue<char> q) {
    while (!q.empty()) {
        std::cout << q.front();
        q.pop();
    }
    std::cout << '\n';
}

void task() {
    std::queue<char> input = convert("H2SO4");
    print_queue(input);

    std::multimap<std::string, std::string> res;
    if (parse(input, res) && !res.empty()) {
        for (const auto& [k, v] : res) {
            std::cout << k << v;
        }
        std::cout << '\n';
    } else {
        std::cout << "error\n";
    }
}

}

#endif // TASK_HWI_H
