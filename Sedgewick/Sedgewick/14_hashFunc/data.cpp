#pragma once
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------------------------
const int N = 10; int k[N];
void calcKeys(){ for(int i = 0; i < N; i++) k[i] = rand() % 100; }
//---------------------------------------------------------------------------------------------
char key[] = {'h', 'e', 'l', 'l', 'o', '\0'};
char key2[] = {'h', 'e', 'l', 'l', '\0'};
char key3[] = {'h', 'e', 'l', 'l', 'y', '\0'};
char key4[] = {'h', 'e', 'l', 'l', 'i', '\0'};
char key5[] = {'h', 'a', 'l', 'k', '\0'};

char key6[] = {'w', 'o', 'r', 'l', 'd', '\0'};
char key7[] = {'w', 'o', 'r', 'm', '\0'};
char key8[] = {'w', 'o', 'r', 'd', '\0'};
char key9[] = {'w', 'o', 'r', 'k', '\0'};
char key10[] = {'w', 'i', 'l', 'l', 'y', '\0'};
//---------------------------------------------------------------------------------------------
void show(int M, int (*hash1)(int, int), int (*hash2)(int, int))
{
    cout << "Hash table size: " << M << endl;
    for(int i = 0; i < N; ++i)
        cout << "hash1 & hash2 for key \'" << k[i] << "\':\t"
             << hash1(k[i], M) << "\t" << hash2(k[i], M) << endl;
}
void show(int M, int (*fhash)(char*, int))
{
    cout << "Hash table size: " << M << endl;
    cout << "hash for key \'" << key << "\': " << fhash(key, M) << endl;
    cout << "hash for key \'" << key2 << "\': " << fhash(key2, M) << endl;
    cout << "hash for key \'" << key3 << "\': " << fhash(key3, M) << endl;
    cout << "hash for key \'" << key4 << "\': " << fhash(key4, M) << endl;
    cout << "hash for key \'" << key5 << "\': " << fhash(key5, M) << endl;
    cout << "hash for key \'" << key6 << "\': " << fhash(key6, M) << endl;
    cout << "hash for key \'" << key7 << "\': " << fhash(key7, M) << endl;
    cout << "hash for key \'" << key8 << "\': " << fhash(key8, M) << endl;
    cout << "hash for key \'" << key9 << "\': " << fhash(key9, M) << endl;
    cout << "hash for key \'" << key10 << "\': " << fhash(key10, M) << endl;
}
void show(int M, int (*hash1)(char*, int), int (*hash2)(char*, int))
{
    cout << "Hash table size: " << M << endl;

    cout << "hash1 & hash2 for key \'" << key << "\':\t"
         << hash1(key, M) << "\t" << hash2(key, M) << endl;

    cout << "hash1 & hash2 for key \'" << key2 << "\':\t"
         << hash1(key2, M) << "\t" << hash2(key2, M) << endl;

    cout << "hash1 & hash2 for key \'" << key3 << "\':\t"
         << hash1(key3, M) << "\t" << hash2(key3, M) << endl;

    cout << "hash1 & hash2 for key \'" << key4 << "\':\t"
         << hash1(key4, M) << "\t" << hash2(key4, M) << endl;

    cout << "hash1 & hash2 for key \'" << key5 << "\':\t"
         << hash1(key5, M) << "\t" << hash2(key5, M) << endl;

    cout << "hash1 & hash2 for key \'" << key6 << "\':\t"
         << hash1(key6, M) << "\t" << hash2(key6, M) << endl;

    cout << "hash1 & hash2 for key \'" << key7 << "\':\t"
         << hash1(key7, M) << "\t" << hash2(key7, M) << endl;

    cout << "hash1 & hash2 for key \'" << key8 << "\':\t"
         << hash1(key8, M) << "\t" << hash2(key8, M) << endl;

    cout << "hash1 & hash2 for key \'" << key9 << "\':\t"
         << hash1(key9, M) << "\t" << hash2(key9, M) << endl;

    cout << "hash1 & hash2 for key \'" << key10 << "\':\t"
         << hash1(key10, M) << "\t" << hash2(key10, M) << endl;
}
//---------------------------------------------------------------------------------------------
class HashValues
{ int h[100], i;
public:
    HashValues(){ i = 0; }
    void addHashV(int hashV) { if(i < 100) h[i] = hashV; ++i; }
};
