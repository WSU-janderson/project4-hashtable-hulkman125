/**
 * HashTable.cpp
 */
#include "HashTable.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <random>
#include <stdexcept>


using namespace std;



HashTable::HashTable(size_t initCapacity) {
    buckets.resize(initCapacity);

    for (int x = 0; x < initCapacity - 1; x++) {
        offsets.push_back(x +1);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(offsets.begin(), offsets.end(), g);

}

bool HashTable::insert(string key, size_t value) {


    if (contains(key)) {
        return false;
    }


    std::hash<string> hash;
    size_t hashValue = hash(key);             //ask if this returns the value using a key
    int home = hashValue % capacity();


    if (buckets.at(home).type == ESS || buckets.at(home).type == EAR) {
        buckets.at(home  % capacity()).load(key, value);
        sizeOfSequence++;
        return true;
    }
    for (int x = 0; x < offsets.size(); ++x) {
        size_t buck = ((home + offsets[x]) % capacity());
        if (buckets.at(buck).type != NORMAL) {
            buckets.at((buck)).load(key, value);
            sizeOfSequence++;
            return true;
        }
    }
    for (int x = 0; x < offsets.size() - 1; x++) {
        if (buckets.at((home + offsets[x]) % capacity()).type != NORMAL) {
            buckets.at((home + offsets[x]) % capacity()).load(key, value);
            sizeOfSequence++;
            return true;
        }
    }
}

bool HashTable::remove(std::string key) {
    std::hash<string> hash;
    size_t hashValue = hash(key);
    int home = hashValue % capacity();
    if (buckets.at(home).key == key) {
        buckets.at(home).key = "";
        buckets.at(home).value = 0;
        buckets.at(home).type = EAR;
        sizeOfSequence--;
        return true;
    }
    for (int x = 0; x < offsets.size() - 1; x++) {
        if (buckets.at((home + offsets[x]) % capacity()).key == key) {
            buckets.at((home + offsets[x]) % capacity()).key = nullptr;
            buckets.at((home + offsets[x]) % capacity()).value = 0;
            buckets.at((home + offsets[x]) % capacity()).type = EAR;
            sizeOfSequence--;
            return true;
        }
    }
    return false;
}

bool HashTable::contains(const string& key) const {
    std::hash<string> hash;
    size_t hashValue = hash(key);
    int home = hashValue % capacity();
    if (buckets.at(home).key == key) {
        return true;
    }
    for (int x = 0; x < offsets.size() - 1; x++) {
        if (buckets.at((home + offsets[x]) % capacity()).key == key) {
            return true;
        }
    }
    return false;
}

std::optional<int> HashTable::get(const string& key) const {
    std::hash<string> hash;
    size_t hashValue = hash(key);
    int home = hashValue % capacity();
    if (contains(key)) {
        if (buckets.at(home).key == key) {
            return buckets.at(home).value;
        }
    }
    else {
        for (int x = 0; x < offsets.size() - 1; x++) {
            if (buckets.at((home + offsets[x]) % capacity()).key == key) {
                return buckets.at((home + offsets[x]) % capacity()).value;
            }
        }
    }
}

size_t& HashTable::operator[](const string& key) {
    std::hash<string> hash;
    size_t hashValue = hash(key);
    int home = hashValue % capacity();

    int answer;
    if (buckets.at(home).isEmpty()) {
        throw exception();
    }
    if (buckets.at(home).key == key) {
        return buckets.at(home).value;
    }
    for(int x = 0; x < offsets.size(); x++) {
        if (buckets.at((home + offsets[x]) % capacity()).key == key) {
            return buckets.at((home + offsets[x]) % capacity()).value;
        }
    }
    //return buckets.at(home).value;
}

std::vector<string> HashTable::keys() const {
    std::vector<string> keys;

    for (int x = 0; x < buckets.size(); x++) {
        if (buckets.at(x).type == NORMAL) {
            keys.push_back(buckets.at(x).key);
        }
    }
    return keys;
}

double HashTable::alpha() const {
    return static_cast<double>(size())/ static_cast<double>(capacity());
}

size_t HashTable::capacity() const {
    return buckets.size();
}

size_t HashTable::size() const {
    return sizeOfSequence;
}

ostream& operator<<(ostream& os, const HashTable& table) {
    for (int x = 0; x < table.capacity(); x++) {
        if (table.buckets.at(x).type == NORMAL) {
            os << "Bucket " << (x) << ": <" << table.buckets.at(x).key << ", " << table.buckets.at(x).value << ">" << endl;
        }
    }
    return os;
}

