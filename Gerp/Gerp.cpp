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

string Gerp::stripNonAlphaNum(string input){
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
    for (size_t i = 0; i < filePaths.size(); i++){
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
                sensitiveTable.insert(stripped, masterIndex);

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

    //check for infile error
    if (not outFile.is_open()){
        std::cerr << "Error: could not open output file" << std::endl;
    }
    string query;
    std::cout << "Query? ";
    //flag to break out of loop
    bool isRunning = true;

    //loop
    while (isRunning and std::cin >> query){
        //quit command
        if (query == "@q" or query == "@quit"){
            //updating this flag quits out the loop
            isRunning = false;
        }
        //new filename output command
        else if (query == "@f"){
            std::string newOutputFilename;
            //take in new filename
            std::cin >> newOutputFilename;
            outFile.close();
            //change outfile
            outFile.open(newOutputFilename);
        }

        //insensitive command handling
        else if (query == "@i" or query == "@insensitive") {
            std::cin >> query;
            std::string stripped = stripNonAlphaNum(query);
            //check if any command exists after stripping
            if(stripped.empty()){
                outFile << query << " Not Found.\n";
            }
            //if so set it to lowercase
            else{
                std::string lowerWord;
                for (size_t i = 0; i < stripped.length(); i++) {
                    lowerWord += tolower(stripped[i]);
                }

                std::vector<int> results;
                if (insensitiveTable.get(lowerWord, results)) {
                    for (size_t i = 0; i < results.size(); i++){
                        //make fl a reference to the file line in all lines
                        //this saves space instead of passing by copy
                        //results holds line numbers, which gives us each
                        //relevent file line
                        FileLine &fl = allLines[results[i]];
                        outFile << filePaths[fl.fileIndex] << ":"
                        << fl.lineNumber << ": "
                        << fl.text << "\n";

                    }
                }
                else {
                    outFile << query << " Not Found.\n";
                }
            }
        }
        //default case sensitive search
        else{
            //strip out non alphanum characters, check for query
            std::string stripped = stripNonAlphaNum(query);
            if (stripped.empty()){
                outFile << query << " Not Found. Try with @insensitive or @i.\n";
            }
            //get fileline from array using line number, send it to outFile
            else{
                std::vector<int> results;
                if(sensitiveTable.get(stripped, results)){
                    for (size_t i = 0; i < results.size(); i++){
                        FileLine &fl = allLines[results[i]];
                        outFile << filePaths[fl.fileIndex] << ":"
                        << fl.lineNumber << ": "
                        << fl.text << "\n";
                    }
                }
                else{
                    outFile << query << " Not Found. Try with @insensitive or @i.\n";
                }
            }
        }
        //make sure quit has not been called, ask for next query
        if (isRunning) {
            std::cout << "Query? ";
        }
    }
    //goodbye message at end of loop
    std::cout << "Goodbye! Thank you and have a nice day.\n";
}