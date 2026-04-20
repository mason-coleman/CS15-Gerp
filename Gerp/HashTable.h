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