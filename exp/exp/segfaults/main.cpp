#include <iostream>
using namespace std;

int main()
{
    const char *s = "Hello World!";

    try{ *(char*)s = 'k'; }
    catch(const exception& e){ cerr << "EXCEPTION: " << e.what() << endl; }
    catch(...){ cerr << "EXCEPTION: unknown exception " << endl; }

    cout << s << endl;
    return system("pause");
}

