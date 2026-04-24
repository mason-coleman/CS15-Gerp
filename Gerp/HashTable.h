/*
 * HashTable.h
 * Nicolas Ferrari & Mason Coleman
 * 4/24/2026
 *
 * CS 15 Project 4: gerp
 *
 * Interface for the HashTable class.
 * Defines the structure for the word index used in the gerp search engine.
 * This class supports efficient storage and retrieval of line numbers
 * associated with unique words, adhering to strict memory constraints.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <functional>

//Node for chained linked list
struct HashNode {
    std::string key;
    std::vector<int> lineNumbers;
    HashNode *next = nullptr;
};

class HashTable {
public:
    HashTable();
    ~HashTable();

    void insert(std::string key, int lineNumber);
    bool get(std::string key, std::vector<int> &result);

private:
    std::vector<HashNode*> table;
    int capacity;
    int numItems;

    void resize();
};

#endif