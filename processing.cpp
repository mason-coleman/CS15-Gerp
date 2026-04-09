#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <cctype>
using namespace std;

void traverseDirectory(DirNode *node, std::string path)
{
    //Print every file that lives directly in this directory
    for (int i = 0; i < node->numFiles(); i++) {
        std::cout << path << "/" << node->getFile(i) << "\n";
    }
 
    //Recurse into every subdirectory
    for (int i = 0; i < node->numSubDirs(); i++) {
        DirNode *subDir = node->getSubDir(i);
        traverseDirectory(subDir, path + "/" + subDir->getName());
    }
}

string stripNonAlphaNum(string input){
    //check if empty
    if (input.empty()){
        return input;
    }

    int start = 0;
    //increment to find first alphanumeric character
    while(start < input.size() and not isalnum(input[start])){
        start++;
    }

    //if equivalent to size of stirng, no char found
    if (start == (input.size())){
        return "";
    }
    
    //set end to be last char
    int end = input.size() - 1;

    //decrement to find last alphanum char
    while (end >= start and not isalnum(input[end])){
        end--;
    }

    //return string from starting char, with length to the end
    return input.substr(start, end - start + 1);
}