#include <iostream>
#include "mystring.h"
#include "smart_pointer.h"
#include <memory>
#include <string>
using namespace std;

void CopyString(String str)
{ cout << "Copy of my string: " << str.getString() << endl; }
void ByRefString(String& str)
{ cout << "By ref my string: " << str.getString() << endl; }

int main()
{
    //---------------------------------------------------------------------------------------------
    cout << "-------------------------MyString---------------------------------" << endl;
    cout << "Creating MyString(const char*): " << endl;
    String hello("hello");
    String empty("");
    cout << "My string buffer: " << hello.getString() << endl;
    cout << "My string length: " << hello.getLength() << endl;
    cout << "sizeof(MyString): " << sizeof(String) << endl;
    cout << "sizeof(std::string): " << sizeof(std::string) << endl;
    cout << "sizeof(std::wstring): " << sizeof(std::wstring) << endl;
    cout << "sizeof(std::u16string): " << sizeof(std::u16string) << endl;
    cout << "sizeof(std::u32string): " << sizeof(std::u32string) << endl;
    cout << "sizeof(""): " << sizeof("") << endl;
    cout << "sizeof(empty): " << sizeof(empty) << endl;
    CopyString(hello);
    ByRefString(hello);
    cout << endl;

    cout << "Creating MyString(std::initializer_list<char>): " << endl;
    String initString({'i','n','i','t', 'i'});
    std::initializer_list<char> l1 = {'i','l','i','s','t','\0'};
    std::initializer_list<char> l2 = {'i'};
    cout << "MyString({'i','n','i','t','i'}): " << initString << endl;
    cout << "sizeof(initString): " << sizeof(initString) << endl;
    cout << "sizeof({'i','l','i','s','t','0'}): " << sizeof(l1) << endl;
    cout << "sizeof({'i'}): " << sizeof(l2) << endl;
    cout << endl;

    cout << "My string assign and out by << in ostream cout: ";
    String strAssign = hello;
    cout << strAssign << endl << endl;

    cout << "operator const char* (): ";
    cout << hello << endl << endl;

    cout << "Access by index: ";
    for(int i = 0; i < hello.getLength() ; ++i) cout << hello[i] << ' ';
    cout << endl << endl;

    cout << "Strings concatenation: " << endl;
    String world("world");
    cout << hello + world << endl;

    cout << endl << "Copy constructor: ";
    cout << hello << " is copied to Moon";
    String Moon(hello); cout << endl;
    cout << "Moon = " << Moon << endl;
    cout << "hello (defined) = " << hello << endl;
    cout << endl;

    cout << "Copy operator assignment: ";
    String Mars;
    cout << hello << " is copied to Mars ";
    Mars = hello; cout << endl;
    cout << "Mars = " << Mars << endl;
    cout << "hello (defined) = " << hello << endl;
    cout << endl;

    cout << endl << "Move constructor: ";
    cout << hello << " is moved to bye";
    String bye(std::move(hello)); cout << endl;
    cout << "bye = " << bye << endl;
    cout << "&hello (undefined) = " << &hello << endl;
    cout << endl;

    cout << "Move operator assignment: ";
    hello = strAssign;
    String goodbye("goodbye");
    cout << hello << " is moved to " << goodbye;
    goodbye = std::move(hello); cout << endl;
    cout << "goodbye = " << goodbye << endl;
    cout << "&hello (undefined) = " << &hello << endl;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
