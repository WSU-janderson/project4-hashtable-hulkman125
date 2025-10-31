//
// Created by harve on 10/21/2025.
//

#ifndef PROJECT4_HASHTABLEBUCKET_H
#define PROJECT4_HASHTABLEBUCKET_H

#endif //PROJECT4_HASHTABLEBUCKET_H

typedef enum BucketType : unsigned char {
    NORMAL,
    ESS,
    EAR
    } BucketType;

#include <string>
#include <iostream>
#include "HashTable.h"

using namespace std;

class HashTableBucket {
public:
    HashTableBucket();
    HashTableBucket(const string& key, size_t value);
    void load(string key, size_t value);
    bool isEmpty() const;
    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);


    string key;
    size_t value;
    BucketType type;

};

