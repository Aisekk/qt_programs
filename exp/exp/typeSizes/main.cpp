#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    cout << "-------------------------string-----------------------------------" << endl;
    cout << "sizeof(std::string): " << sizeof(std::string) << endl;
    cout << "sizeof(std::wstring): " << sizeof(std::wstring) << endl;
    cout << "sizeof(std::u16string): " << sizeof(std::u16string) << endl;
    cout << "sizeof(std::u32string): " << sizeof(std::u32string) << endl;
    cout << "-------------------------vector-----------------------------------" << endl;
    cout << "sizeof(vector<int>): " << sizeof(std::vector<int>) << endl;
    cout << "sizeof(vector<double>): " << sizeof(std::vector<double>) << endl;
    cout << "sizeof(vector<string>): " << sizeof(std::vector<string>) << endl;
    cout << "sizeof(vector<bool>): " << sizeof(std::vector<bool>) << endl;

    std::vector<int> vec_int;
    std::vector<double> vec_double;
    std::vector<string> vec_string;
    std::vector<bool> vec_bool;
    cout << "-------------------------vector objs------------------------------" << endl;
    cout << "sizeof(vector<int> obj): " << sizeof(vec_int) << endl;
    cout << "sizeof(vector<double> obj): " << sizeof(vec_double) << endl;
    cout << "sizeof(vector<string> obj): " << sizeof(vec_string) << endl;
    cout << "sizeof(vector<bool> obj): " << sizeof(vec_bool) << endl;

    system("pause");
    return 0;
}
