//
// Created by harve on 10/21/2025.
//
#include <iostream>
#include <string>
#include "HashTable.h"
#include <random>

using namespace std;

HashTableBucket::HashTableBucket() {
    type = ESS;
}

HashTableBucket::HashTableBucket(const string& key, size_t value) {
    this -> key = key;
    this -> value = value;
    type = NORMAL;
}

void HashTableBucket::load(string key, size_t value) {
    this -> key = key;
    this -> value = value;
    type = NORMAL;
}

bool HashTableBucket::isEmpty() const {
    if (type == NORMAL) {
        return false;
    }
    else {
        return true;
    }
}

ostream& operator<<(ostream& os, const HashTableBucket& bucket) {
    os << "key: " << bucket.key << endl << "value: " << bucket.value << endl << "TYPE: " << bucket.type << endl;
}
