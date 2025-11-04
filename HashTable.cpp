/**
 * HashTable.cpp
 */

/*
*Program
 *Written by
 *@Tyler
 *@Raymond
 *@Harvey
 */
/*
 * Project Name:
 *  Project 4: Map ADT: HashTable
 */
/*
 * Description:
 * making a vector of "buckets"
 * and inserting data in them
 * while altering its capacity/size
 * and still altering the data.
 */

#include "HashTable.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <random>
#include <stdexcept>




using namespace std;


//----------------------------------------------------------------
// HashTable: the default constructor to create a number of buckets
//    Returns:  void
//    Parameters: initCapacity (size_t) //number of buckets
//----------------------------------------------------------------
HashTable::HashTable(size_t initCapacity) {
    buckets.resize(initCapacity);

    for (int x = 0; x < initCapacity - 1; x++) {
        offsets.push_back(x +1);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(offsets.begin(), offsets.end(), g);

}

//----------------------------------------------------------------
// insert: inseeting a value into a bucket
//    Returns:  bool
//    Parameters: key (string) (the string used to create a hash), value (size_t) (number to be stored)
//----------------------------------------------------------------

bool HashTable::insert(string key, size_t value) {
    if (contains(key)) {

        return false;
    }

    if (alpha() >= .5) {
        //buckets.resize(capacity() * 2);
        increaseCapacity();
    }

    std::hash<string> hash;
    size_t hashValue = hash(key);             //ask if this returns the value using a key
    int home = hashValue % capacity();



    if (buckets.at(home).type == ESS || buckets.at(home).type == EAR) {
        buckets.at(home  % capacity()).load(key, value);
        sizeOfSequence++;
        return true;
    }



    for (int x = 0; x < offsets.size(); x++) {
        size_t buck = ((home + offsets[x]) % capacity());
        if (buckets.at(buck).type != NORMAL) {
            buckets.at((buck)).load(key, value);
            sizeOfSequence++;
            return true;
        }
    }
    for (int x = 0; x < offsets.size(); x++) {
        size_t Probing = (home + offsets[x]) % capacity();

        if (buckets.at(Probing).type != NORMAL) {

            buckets.at(Probing).load(key, value);
            sizeOfSequence++;
            return true;
        }
        if (x == offsets.size() - 1) {
            return true;
        }
    }
}

//----------------------------------------------------------------
// remove: eliminating the value in a bucket
//    Returns:  bool
//    Parameters: key (string) - the string used to find the value to be removed
//----------------------------------------------------------------

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
    for (int x = 0; x < buckets.capacity(); x++) {
        if (buckets.at((home + offsets[x]) % capacity()).key == key) {
            buckets.at((home + offsets[x]) % capacity()).key = "";
            buckets.at((home + offsets[x]) % capacity()).value = 0;
            buckets.at((home + offsets[x]) % capacity()).type = EAR;
            sizeOfSequence--;
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------
// contains: determining if the key is in the HashTable
//    Returns:  bool
//    Parameters: ke (string&) - the pointer to the key
//----------------------------------------------------------------

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

//----------------------------------------------------------------
// get: returning the value in a bucket
//    Returns:  optional<size_t>
//    Parameters: key (string&) - the pointer to the key
//----------------------------------------------------------------

std::optional<size_t> HashTable::get(const string& key) const {
    std::hash<string> hash;
    size_t hashValue = hash(key);
    size_t home = hashValue % capacity();
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
    return nullopt;
}

//----------------------------------------------------------------
// operator[]: returning the value at an index
//    Returns:  size_t
//    Parameters:  key (string&) - the number of hitpoints to subtract
//----------------------------------------------------------------

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

//----------------------------------------------------------------
// keys(): returning the vector of keys
//    Returns:  vector<string>
//    Parameters: none
//----------------------------------------------------------------

std::vector<string> HashTable::keys() const {
    std::vector<string> keys;

    for (int x = 0; x < buckets.size(); x++) {
        if (buckets.at(x).type == NORMAL) {
            keys.push_back(buckets.at(x).key);
        }
    }
    return keys;
}

//----------------------------------------------------------------
// alpha: returns size/capacity
//    Returns:  double
//    Parameters: none
//----------------------------------------------------------------

double HashTable::alpha() const {
    return static_cast<double>(size())/ static_cast<double>(capacity());
}

//----------------------------------------------------------------
// capacity: damaging the oponent by lowering thier hitpoints
//    Returns:  size_t
//    Parameters: none
//----------------------------------------------------------------

size_t HashTable::capacity() const {
    return buckets.size();
}

//----------------------------------------------------------------
// size(): number of filled buckets
//    Returns:  size_t
//    Parameters: none
//----------------------------------------------------------------

size_t HashTable::size() const {
    return sizeOfSequence;
}

//----------------------------------------------------------------
// operator<<: outputs the string of keys and value
//    Returns:  ostream&
//    Parameters:  os (ostream&) -output, table (HashTable&) -The Hashtable object 
//----------------------------------------------------------------

ostream& operator<<(ostream& os, const HashTable& table) {
    for (int x = 0; x < table.capacity(); x++) {
        if (table.buckets.at(x).type == NORMAL) {
            os << "Bucket " << (x) << ": <" << table.buckets.at(x).key << ", " << table.buckets.at(x).value << ">" << endl;
        }
    }
    return os;
}

//----------------------------------------------------------------
// increaseCapacity: increasing the number of buckets
//    Returns:  void
//    Parameters:  none
//----------------------------------------------------------------

void HashTable:: increaseCapacity() {
    vector<HashTableBucket> oldbuckets = buckets;
    size_t tempSize = oldbuckets.size();

    buckets.clear();
    buckets.resize(tempSize * 2);
    int offesetsize = offsets.size() + 1;

    for (int x = offesetsize; x < buckets.size() - 1; x++) {
        offsets.push_back(x);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(offsets.begin(), offsets.end(), g);



    sizeOfSequence = 0;

    for (int x = 0; x < oldbuckets.size(); x++) {
        if (oldbuckets.at(x).type == NORMAL) {
            insert(oldbuckets.at(x).key, oldbuckets.at(x).value);
        }
    }
}
