#include "Gerp.h"

#include "Gerp.h"
#include "FSTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

Gerp::Gerp() {
    //Vectors and HashTables handle their own memory, nothing is needed here
}

Gerp::~Gerp() {
    //default is fine, no memory allocation in this class
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

void Gerp::buildFilePaths(DirNode *node, string path){
    //base case, adding all files in director to filePaths vector
    for (int i = 0; i < node->numFiles(); i++){
        filePaths.push_back(path + "/" + node->getFile(i));
    }

    //recursive case, going into subdirectories
    for (int i =0; i < node->numSubDirs(); i++) {
        DirNode *subDir = node->getSubDir(i);
        buildFilePaths(subDir, path + "/" + subDir->getName());
    }
}

void Gerp::run(string directory, std::string outputFile){
    //build FSTree from provided directory
    FSTree tree(directory);
    DirNode *root = tree.getRoot();
    //Populate filepaths vector
    buildFilePaths(root, directory);

    //extract every line from every file we found
    for (int i = 0; i < filePaths.size(); i++){
        processFile(filePaths[i], i);
    }

    //now that everything is indexed, we can take in commands
    commandLoop(outputFile);
}

void Gerp::processFile(string filePath, int fileIndex){
    ifstream infile(filePath);
    if (not infile.is_open()){
        cerr << "Could not open file: " << filePath << endl;
        return;
    }

    string line;
    int lineNum = 1;

    while (getline(infile, line)){
        //create a FileLine struct for each
        FileLine currentLine;
        currentLine.fileIndex = fileIndex;
        currentLine.lineNumber = lineNum;
        currentLine.text = line;

        //add line to master vector
        allLines.push_back(currentLine);

        //get index where we just stored this line
        int masterIndex = allLines.size() - 1;

        //use a stringstream to access each individual word
        stringstream ss(line);
        string word;

        while(ss >> word){
            string stripped = stripNonAlphaNum(word);

            if (not stripped.empty()){
                sensitveTable.insert(stripped, masterIndex);

                string lowerWord = "";
                for (int i = 0; i < stripped.length(); i++){
                    lowerWord+= tolower(stripped[i]);
                }
                insensitiveTable.insert(lowerWord, masterIndex);
            }
        }
        lineNum++;
    }
    infile.close();
}

void Gerp::commandLoop(std::string outputFile) {
    std::ofstream outFile(outputFile);

    if (not outFile.is_open()){
        std::cerr << "Error: could not open output file" << std::endl;
    }
    string query;
    std::cout << "Query? ";
    bool isRunning = true;

    while (isRunning and std::cin >> query){
        if (query == "@q" or query == "@quit"){
            isRunning = false;
        }
        else if (query == "@f"){
            std::string newOutputFilename;
            std::cin >> newOutputFilename;
            outFile.close();
            outFile.open(newOutputFilename);
        }
        else if (query == "@i" or query == "@insensitive") {
            std::cin >> query;
            std::string stripped = stripNonAlphaNum(query);

            if(stripped.empty()){
                outFile << query << " Not Found. \n";
            }
            else{
                std::string lowerWord;
                for (int i = 0; i < stripped.length(); i++) {
                    lowerWord += tolower(stripped[i]);
                }

                std::vector<int> results;
                if (insensitiveTable.get(lowerWord, results)) {
                    for (int i = 0; i < results.size(); i++){
                        
                    }
                }
            }
        }
    }
}