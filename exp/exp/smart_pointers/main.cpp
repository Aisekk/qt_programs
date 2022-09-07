#include <iostream>
#include "mystring.h"
#include "smart_pointer.h"
#include <memory>
#include <string>
using namespace std;

void testUniqPtr()
{
    cout << "--------------------- TESTING UNIQ PTR ---------------------------" << endl;
    cout << "------------------------ uniq_ptr --------------------------------" << endl;
    cout << "--- operator*, operator->, get(), operator bool --- : " << endl;
    uniq_ptr<String> uqMyString(new String("uniq string"));
    cout << "uniq_ptr.operator*() = " << uqMyString.operator*() << endl;
    cout << "*uniq_ptr = " << *uqMyString << endl;
    cout << "uniq_ptr.operator->() = " << uqMyString.operator->() << endl;
    cout << "uniq_ptr.get() = " << uqMyString.get() << endl;
    cout << "sizeof(uniq_ptr) = " << sizeof(uqMyString) << endl;
    if(uqMyString) cout << "&(upMyString.operator bool) == true" << endl;

    cout << endl << "--- RESET() --- : " << endl;
    cout << "Result of uqMyString.reset(new MyString(\"uniq string 2\")): " << endl;
    uqMyString.reset(new String("uniq string 2"));
    cout << "*uniq_ptr = " << *uqMyString << endl;
    cout << "Result of uqMyString.reset(nullptr)): " << endl;
    uqMyString.reset(nullptr);
    cout << "uniq_ptr.get() = " << uqMyString.get() << endl;
    cout << "Result of uqMyString.reset(new MyString(\"uniq string 3\")): " << endl;
    uqMyString.reset(new String("uniq string 3"));
    cout << "uniq_ptr.get() = " << uqMyString.get() << endl;
    cout << "*uniq_ptr = " << *uqMyString << endl;

    cout << endl << "--- RELEASE() --- : " << endl;
    String* pstr = uqMyString.release();
    cout << "uniq_ptr.release() = " << pstr << endl;
    cout << "uniq_ptr.get() = " << uqMyString.get() << endl;
    if(!uqMyString) cout << "&(upMyString.operator bool) == false" << endl;

    cout << endl << "--- SWAP() --- : " << endl;
    uniq_ptr<String> uqMyString3(new String("uniq string 3"));
    uniq_ptr<String> uqMyString4(new String("uniq string 4"));
    cout << "*uqMyString3 = " << *uqMyString3 << endl;
    cout << "*uqMyString4 = " << *uqMyString4 << endl;
    cout << "Result of upMyString3.swap(upMyString4): " << endl;
    uqMyString3.swap(std::move(uqMyString4));
    cout << "*uqMyString3 = " << *uqMyString3 << endl;
    cout << "*uqMyString4 = " << *uqMyString4 << endl;
    cout << "Result of upMyString3.swap(upMyString4): " << endl;
    uqMyString3.swap(std::move(uqMyString4));
    cout << "*uqMyString3 = " << *uqMyString3 << endl;
    cout << "*uqMyString4 = " << *uqMyString4 << endl;

    cout << endl << "--- UNIQ MOVING --- : " << endl;

    cout << endl << "Move constructor: " << endl;
    uniq_ptr<String> uMyString1(new String("u string 1"));
    cout << "*uMyString1(\"u string 1\"): " << *uMyString1 << endl;
    cout << "Result of uniq_ptr<MyString> uMyString2(std::move(uMyString1)): " << endl;
    uniq_ptr<String> uMyString2(std::move(uMyString1));
    cout << "*uMyString2 = "  << *uMyString2 << endl;
    cout << "uMyString1.get() = "  << uMyString1.get() << " (undefined behaviour)" << endl;

    cout << endl << "Assign move operator: " << endl;
    uniq_ptr<String> uqMyString1(new String("uniq string 1"));
    uniq_ptr<String> uqMyString2(new String("uniq string 2"));
    cout << "*uqMyString1(\"uniq string 1\"): " << *uqMyString1 << endl;
    cout << "*uqMyString2(\"uniq string 2\"): " << *uqMyString2 << endl;
    cout << "Result of uqMyString2 = std::move(uqMyString1): " << endl;
    uqMyString2 = std::move(uqMyString1);
    cout << "*uqMyString2 = "  << *uqMyString2 << endl;
    cout << "uqMyString1.get() = "  << uqMyString1.get() << " (undefined behaviour)" << endl;
    cout << endl;

    //---------------------------------------------------------------------------------------------
    cout << "------------------------ std::unique_ptr -------------------------" << endl;
    unique_ptr<String> upMyString(new String("unique string"));
    cout << "unique_ptr.operator*() = " << upMyString.operator*() << endl;
    cout << "*unique_ptr = " << *upMyString << endl;
    cout << "unique_ptr-> = " << upMyString.operator->() << endl;
    cout << "unique_ptr.get() = " << upMyString.get() << endl;
    //cout << "unique_ptr.element_type = " << sizeof(upMyString.element_type) << endl;
    //cout << "unique_ptr.pointer = " << sizeof(upMyString.pointer) << endl;
    cout << "sizeof(unique_ptr) = " << sizeof(upMyString) << endl;
    //if(&(upMyString.operator bool)) cout << "&(upMyString.operator bool) == true" << endl;

    cout << endl << "--- RESET() --- : " << endl;
    cout << "Result of upMyString.reset(new MyString(\"unique string X\")): " << endl;
    upMyString.reset(new String("unique string X"));
    cout << "*unique_ptr = " << *upMyString << endl;
    cout << "Result of upMyString.reset(nullptr): " << endl;
    upMyString.reset(nullptr);
    cout << "upMyString.get() = " << upMyString.get() << endl;
    cout << "Result of upMyString.reset(new MyString(\"unique string\")): " << endl;
    upMyString.reset(new String("unique string"));
    cout << "*upMyString = " << *upMyString << endl;

    cout << endl << "--- SWAP() --- : " << endl;
    unique_ptr<String> upMyString1(new String("unique string 1"));
    unique_ptr<String> upMyString2(new String("unique string 2"));
    cout << "Result of upMyString2.swap(upMyString): " << endl;
    cout << "*unique_ptr 1 = " << *upMyString1 << endl;
    cout << "*unique_ptr 2 = " << *upMyString2 << endl;
    upMyString2.swap(upMyString1);
    cout << "*unique_ptr 1 = " << *upMyString1 << endl;
    cout << "*unique_ptr 2 = " << *upMyString2 << endl;

    cout << endl << "--- RELEASE() --- : " << endl;
    cout << "unique_ptr.release() = " << upMyString.release() << endl;
    cout << "unique_ptr.get() = " << upMyString.get() << endl;
    //---------------------------------------------------------------------------------------------
    cout << endl << "Objects destroying: " << endl;
}
void testSharPtr()
{
    cout << "--------------------- TESTING SHAR PTR ---------------------------" << endl;
    cout << "------------------------- shar_ptr -------------------------------" << endl;
    cout << "--- operator*, operator->, get(), operator bool --- : " << endl;
    shar_ptr<String> shMyString(new String("shar string"));
    cout << "shar_ptr.use_count(): " << shMyString.use_count() << endl;
    cout << "shar_ptr.operator*() = " << shMyString.operator*() << endl;
    cout << "*shar_ptr = " << *shMyString << endl;
    cout << "shar_ptr.operator->() = " << shMyString.operator->() << endl;
    cout << "shar_ptr.get() = " << shMyString.get() << endl;
    cout << "sizeof(shar_ptr) = " << sizeof(shMyString) << endl;
    if(shMyString) cout << "&(spMyString.operator bool) == true" << endl;

    //---------------------------------------------------------------------------------------------
    cout << endl << "--- SHAR COPYING --- : " << endl;

    cout << endl << "Copy constructor: " << endl;
    shar_ptr<String> shString1(new String("string 1"));
    cout << "*shString1(\"string 1\"): " << *shString1 << endl;
    cout << "shString1.use_count(): " << shString1.use_count() << endl;
    cout << "Result of shar_ptr<MyString> shString2(shString1): " << endl;
    shar_ptr<String> shString2(shString1);
    cout << "*shString1 = "  << *shString1 << endl;
    cout << "*shString2 = "  << *shString2 << endl;
    cout << "shString1.use_count(): " << shString1.use_count() << endl;
    cout << "shString2.use_count(): " << shString2.use_count() << endl;

    cout << endl << "Assign copy operator: " << endl;
    shar_ptr<String> shString3(new String("string 3"));
    shar_ptr<String> shString4(new String("string 4"));
    cout << "*shString3(\"string 3\"): " << *shString3 << endl;
    cout << "*shString4(\"string 4\"): " << *shString4 << endl;
    cout << "shString3.use_count(): " << shString3.use_count() << endl;
    cout << "shString4.use_count(): " << shString4.use_count() << endl;
    cout << "Result of shString4 = shString3: " << endl;
    shString4 = shString3;
    cout << "*shString3 = "  << *shString3 << endl;
    cout << "*shString4 = "  << *shString4 << endl;
    cout << "shString3.use_count(): " << shString3.use_count() << endl;
    cout << "shString4.use_count(): " << shString4.use_count() << endl;
    //=============================================================================================
    cout << "------------------------ std::shared_ptr -------------------------" << endl;
    shared_ptr<String> spMyString(new String("shared string"));
    cout << "shared_ptr.operator*() = " << spMyString.operator*() << endl;
    cout << "*shared_ptr = " << *spMyString << endl;
    cout << "shared_ptr-> = " << spMyString.operator->() << endl;
    cout << "shared_ptr.get() = " << spMyString.get() << endl;
    cout << "sizeof(shared_ptr) = " << sizeof(spMyString) << endl;
    //if(&(spMyString.operator bool)) cout << "&(spMyString.operator bool) == true" << endl;

    cout << endl << "--- RESET() --- : " << endl;
    cout << "Result of spMyString.reset(new MyString(\"shared string X\")): " << endl;
    spMyString.reset(new String("shared string X"));
    cout << "*shared_ptr = " << *spMyString << endl;
//    cout << "Result of spMyString.reset(nullptr): " << endl;
//    spMyString.reset(nullptr);
//    cout << "spMyString.get() = " << spMyString.get() << endl;
    cout << "Result of spMyString.reset(new MyString(\"shared string\")): " << endl;
    spMyString.reset(new String("shared string"));
    cout << "*spMyString = " << *spMyString << endl;

    cout << endl << "--- SWAP() --- : " << endl;
    shared_ptr<String> spMyStringX(new String("shared string X"));
    shared_ptr<String> spMyStringY(new String("shared string Y"));
    cout << "Result of spMyStringY.swap(spMyStringX): " << endl;
    cout << "*shared_ptr X = " << *spMyStringX << endl;
    cout << "*shared_ptr Y = " << *spMyStringY << endl;
    spMyStringY.swap(spMyStringX);
    cout << "*shared_ptr X = " << *spMyStringX << endl;
    cout << "*shared_ptr Y = " << *spMyStringY << endl;

    //---------------------------------------------------------------------------------------------
    cout << endl << "--- SHARED COPYING --- : " << endl;

    cout << endl << "Copy constructor: " << endl;
    shared_ptr<String> spString1(new String("string 1"));
    cout << "*spString1(\"string 1\"): " << *spString1 << endl;
    cout << "spString1.use_count(): " << spString1.use_count() << endl;

    cout << "Result of shared_ptr<MyString> spString2(spString1): " << endl;
    shared_ptr<String> spString2(spString1);
    cout << "*spMyString1 = "  << *spString1 << endl;
    cout << "*spMyString2 = "  << *spString2 << endl;
    cout << "spString1.use_count(): " << spString1.use_count() << endl;
    cout << "spString2.use_count(): " << spString2.use_count() << endl;

    cout << "Result of spString2 = nullptr: " << endl;
    spString2 = nullptr;
    cout << "*spMyString1 = "  << *spString1 << endl;
    cout << "spMyString2.get() = "  << spString2.get() << endl;
    cout << "spString1.use_count(): " << spString1.use_count() << endl;
    //cout << "spString2.use_count(): " << spString2.use_count() << endl;

    cout << endl << "Assign copy operator: " << endl;
    shared_ptr<String> spString3(new String("string 3"));
    shared_ptr<String> spString4(new String("string 4"));
    cout << "*spString3(\"string 3\"): " << *spString3 << endl;
    cout << "*spString4(\"string 4\"): " << *spString4 << endl;
    cout << "spString3.use_count(): " << spString3.use_count() << endl;
    cout << "spString4.use_count(): " << spString4.use_count() << endl;
    cout << "Result of spString4 = spString3: " << endl;
    spString4 = spString3;
    cout << "*spString3 = "  << *spString3 << endl;
    cout << "*spString4 = "  << *spString4 << endl;
    cout << "spString3.use_count(): " << spString3.use_count() << endl;
    cout << "spString4.use_count(): " << spString4.use_count() << endl;
    //---------------------------------------------------------------------------------------------
    cout << endl << "--- SHARED MOVING --- : " << endl;

    cout << endl << "Move constructor: " << endl;
    shared_ptr<String> spMyString1(new String("string 1"));
    cout << "*spMyString1(\"string 1\"): " << *spMyString1 << endl;
    cout << "Result of shared_ptr<MyString> spMyString2(std::move(spMyString1)): " << endl;
    shared_ptr<String> spMyString2(std::move(spMyString1));
    cout << "*spMyString2 = "  << *spMyString2 << endl;
    cout << "spMyString1.get() = "  << spMyString1.get() << " (undefined behaviour)" << endl;

    cout << endl << "Assign move operator: " << endl;
    shared_ptr<String> spMyString3(new String("string 3"));
    shared_ptr<String> spMyString4(new String("string 4"));
    cout << "*spMyString3(\"string 3\"): " << *spMyString3 << endl;
    cout << "*spMyString4(\"string 4\"): " << *spMyString4 << endl;
    cout << "Result of spMyString4 = std::move(spMyString3): " << endl;
    spMyString4 = std::move(spMyString3);
    cout << "*spMyString4 = "  << *spMyString4 << endl;
    cout << "spMyString3.get() = "  << spMyString3.get() << " (undefined behaviour)" << endl;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    cout << endl << "Objects destroying: " << endl;
    //spMyString3.owner_before
}

int main()
{
    testUniqPtr(); cout << endl;
    testSharPtr(); cout << endl;

    system("pause");
    return 0;
}
