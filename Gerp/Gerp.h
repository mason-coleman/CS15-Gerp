/*
 * Gerp.h
 * Nicolas Ferrari & Mason Coleman
 * 4/24/2026
 *
 * CS 15 Project 4: gerp
 *
 * Interface for the Gerp engine class.
 * This class coordinates the indexing and searching of a directory system.
 * It manages the file system traversal, populates dual hash tables for
 * case-sensitive and insensitive searching, and executes the main command
 * loop for user queries.
 */

#ifndef GERP_H
#define GERP_H
#include "HashTable.h"
#include <string>
#include <vector>
#include "DirNode.h"

//Struct for holding each line of text
//Contains index, line number, and text itself
//index is used to identify filepath
struct FileLine {
    int fileIndex;
    int lineNumber;
    std::string text;
};

class Gerp{
public:
    Gerp();
    ~Gerp();

    //main function called from main
    void run(std::string directory, std::string outputFile);

private:
    //filePaths stores each unique filepath to be printed to terminal
    //all Lines store a single copy of each line in a file
    std::vector<std::string> filePaths;
    std::vector<FileLine> allLines;

    HashTable sensitiveTable;
    HashTable insensitiveTable;

    void processFile(std::string filePath, int fileIndex);
    void commandLoop(std::string outputFile);

    std::string stripNonAlphaNum(std::string input);
    void buildFilePaths(DirNode *node, std::string path);
};

#endif