

#include "processing.h"
#include <iostream>
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

