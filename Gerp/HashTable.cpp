#include "HashTable.h"

HashTable::HashTable(){
    capacity = 1000;
    numItems = 0;
    //set vector to inital size, fill all values with nullptr
    table.assign(capacity, nullptr);
}

HashTable::~HashTable(){
    for (int i = 0; i < capacity; i++){
        HashNode *curr = table[i];
        while (curr != nullptr){
            HashNode *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
}

void HashTable::insert(std::string key, int lineNumber)
{
    //check load factor to maintain speed
    if (numItems >= capacity * 0.75){
        resize();
    }

    size_t index = std::hash<std::string>{}(key) % capacity;
    HashNode *curr = table[index];

    //check each node in bucket for word
    while (curr!= nullptr){
        if (curr->key == key){
            //word found!
            if (curr->lineNumbers.back() != lineNumber){
                //if this is a new line, insert it in array
                curr->lineNumbers.push_back(lineNumber);
            }
            return;
        }
        //check next node
        curr = curr->next;
    }

    //if we get here, node is not in table yet
    //make new node
    HashNode *newNode = new HashNode;
    newNode->key = key;
    newNode->lineNumbers.push_back(lineNumber);

    //put our node at the front of the list in this bucket
    newNode->next = table[index];
    table[index]= newNode;

    numItems++;
}

bool HashTable::get(std::string key, std::vector<int> &result)
{
    //get index
    size_t index = std::hash<std::string>{}(key) % capacity;
    HashNode *curr = table[index];

    //check each bucket at that index
    while (curr != nullptr){
        //if we found it, return true and update reference array with numbers
        if (curr->key == key){
            result = curr->lineNumbers;
            return true;
        }
        curr = curr->next;
    }
    //if we get here, key not found
    return false;
}

void HashTable::resize(){
    int oldCapacity = capacity;
    //double capacity
    capacity = capacity * 2;

    //create our new nullptr filled table
    std::vector<HashNode *> newTable;
    newTable.assign(capacity, nullptr);

    //Rehash all existing nodes into the new table
    for (int i = 0; i < oldCapacity; i++){
        HashNode *curr = table[i];
        while (curr != nullptr){
            //save next node before moving curr
            HashNode *nextNode = curr->next;

            size_t newIndex = std::hash<std::string>{}(curr->key) % capacity;

            //add node to front of bucket at new table
            curr->next = newTable[newIndex];
            newTable[newIndex] = curr;
            
            //go to next node
            curr = nextNode;
        }
    }

    //replace old table with new table
    table = newTable;
}