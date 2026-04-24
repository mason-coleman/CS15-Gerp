/*
 * HashTable.cpp
 * Nicolas Ferrari & Mason Coleman
 * 4/24/2026
 *
 * CS 15 Project 4: gerp
 *
 * Implementation of a custom hash table for efficient word indexing.
 * This class provides near-constant time search functionality for a string
 * search engine. It handles collisions via separate chaining and maintains
 * performance by dynamically doubling its capacity when the load factor 
 * reaches 0.75.
 */
#include "HashTable.h"

/*
 * name:      HashTable (constructor)
 * purpose:   Initializes a hash table with a default capacity of 1000
 * arguments: none
 * returns:   none
 * effects:   allocates the internal table vector and fills it with nullptrs
 * other:     none
 */
HashTable::HashTable(){
    capacity = 1000;
    numItems = 0;
    //set vector to inital size, fill all values with nullptr
    table.assign(capacity, nullptr);
}

/*
 * name:      ~HashTable (destructor)
 * purpose:   Cleans up all heap memory allocated for the hash table
 * arguments: none
 * returns:   none
 * effects:   deletes every HashNode in every chain in the table
 * other:     none
 */
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

/*
 * name:      insert
 * purpose:   Adds a word and its corresponding line number to the index
 * arguments: a string (key) and an integer (lineNumber)
 * returns:   none
 * effects:   updates existing nodes or inserts a new HashNode; triggers 
 * resize if load factor threshold is met
 * other:     ensures a line number is only added once per word to save space
 */
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

/*
 * name:      get
 * purpose:   Retrieves the list of line numbers associated with a word
 * arguments: string key to find, and a vector reference to store results
 * returns:   true if the key was found, false otherwise
 * effects:   populates the result vector with the key's line numbers
 * other:     none
 */
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

/*
 * name:      resize
 * purpose:   Expands the hash table to maintain efficient search times
 * arguments: none
 * returns:   none
 * effects:   doubles capacity and rehashes all existing nodes into a new vector
 * other:     maintains the required speed for large data sets
 */
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