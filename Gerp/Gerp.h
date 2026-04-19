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

    HashTable sensitveTable;
    HashTable insensitiveTable;

    void processFile(std::string filePath, int fileIndex);
    void commandLoop(std::string outputFile);

    std::string stripNonAlphaNum(std::string input);
    void buildFilePaths(DirNode *node, std::string path);
    std::string toLower(std::string input);
};

#endif