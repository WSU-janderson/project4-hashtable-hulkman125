/**
 * HashTable.h
 */

#ifndef PROJECT4_HASHTABLEBUCKET_H
#define PROJECT4_HASHTABLEBUCKET_H

#include "HashTableBucket.h"
#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <random>

using namespace std;

class HashTable {
public:



    vector<HashTableBucket>buckets;
    vector<size_t> offsets;

    int sizeOfSequence = 0;

    HashTable(size_t initCapacity = 8);
    bool insert(std::string key, size_t value);

    bool remove(std::string key);
    bool contains(const string& key) const;
    optional<int> get(const string& key) const;
    size_t& operator[](const string& key);
    vector<string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;
    friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);

};
#endif
