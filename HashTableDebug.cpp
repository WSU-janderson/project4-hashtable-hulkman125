/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include <iostream>

#include "HashTable.h"

int main() {
    srand(time(nullptr));
    //std::cout << "Hello, World!" << std::endl;

    HashTable pr = HashTable(20);
    pr.insert("Randy", 4);
    pr.insert("Cody", 4);
    pr.insert("Tyler", 1);
    pr.insert("Kim", 6);
    
     //pr.keys();

    //cout << pr.capacity() << endl;
    //cout << pr.size() << endl;
    //cout << pr.alpha() << endl;
    //cout << pr["Tyler"] << endl;
    //cout << pr["Cody"] << endl;

    cout << pr << endl;


    optional<int> a = pr.get("Kim");
    //pr.remove("Tyler");
    return 0;
}
