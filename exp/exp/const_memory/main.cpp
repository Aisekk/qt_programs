#include <iostream>

using namespace std;

struct A
{
    const char* cstr = "const mem";
    const char cstr2[20] = "const mem 2";
    const char* strs[20] = {cstr, cstr2};
    char str[20] = "auto memory";

    int nums[3] = {1,2,3};
};

void func(const char* strs[])
{
    cout << strs[0] << " " << strs[1] << endl;
}

int main(int argc, char* argv[])
{
    A* a = new A;

    cout << "a.cstr = " << a->cstr << endl;
    cout << "a.str = " << a->str << endl;

    delete a;
    a = nullptr;

    //cout << "a.cstr = " << a->cstr << endl;
    //cout << "a.str = " << a->str << endl;

    const char* strs[] = {"stroka1", "stroka2"};
    func(strs);

    return 0;
}
