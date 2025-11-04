//
// Created by harve on 10/21/2025.
//
#include <iostream>
#include <string>
#include "HashTable.h"
#include <random>

using namespace std;

//----------------------------------------------------------------
//    HashTableBucket: default constructor to set the the type to ESS
//    Returns:  none
//    Parameters: none
//----------------------------------------------------------------

HashTableBucket::HashTableBucket() {
    type = ESS;
}


//----------------------------------------------------------------
//    HashTableBucket: constructor used to set key and value and make type to NORMAL
//    Returns:  none
//    Parameters: key (string&), value (size_t)
//----------------------------------------------------------------

HashTableBucket::HashTableBucket(const string& key, size_t value) {
    this -> key = key;
    this -> value = value;
    type = NORMAL;
}

//----------------------------------------------------------------
//    load: setting the player's Role
//    Returns:  void
//    Parameters: key (string), value(size_t)
//----------------------------------------------------------------

void HashTableBucket::load(string key, size_t value) {
    this -> key = key;
    this -> value = value;
    type = NORMAL;
}

//----------------------------------------------------------------
//    isEmpty: setting the player's Role
//    Returns:  bool
//    Parameters: none
//----------------------------------------------------------------

bool HashTableBucket::isEmpty() const {
    if (type == NORMAL) {
        return false;
    }
    else {
        return true;
    }
}

//----------------------------------------------------------------
//    operator<<: soutputting the buckets contents
//    Returns:  ostream&
//    Parameters: os (ostream&), bucket (HashTableBucket&)
//----------------------------------------------------------------

ostream& operator<<(ostream& os, const HashTableBucket& bucket) {
    os << "key: " << bucket.key << endl << "value: " << bucket.value << endl << "TYPE: " << bucket.type << endl;
}
