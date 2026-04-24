/*
 * main.cpp
 * Nicolas Ferrari & Mason Coleman
 * 4/24/2026
 *
 * CS 15 Project 4: gerp
 *
 * Driver for the gerp search engine.
 * This file handles command-line argument validation and initializes the
 * Gerp engine to begin the indexing and query process.
 */
#include "Gerp.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * name:      main
 * purpose:   Acts as the entry point for the gerp program
 * arguments: argc (number of arguments), argv (array of argument strings)
 * returns:   0 on success, or 1 (EXIT_FAILURE) on usage error
 * effects:   Validates command-line input and starts the Gerp run loop
 * other:     Requires exactly two arguments: a directory and an output 
 * file .
 */
int main(int argc, char *argv[]){
    //check for exactly 3 arguements
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile\n";
        return EXIT_FAILURE;
    }
    //Begin search engine
    Gerp myGerp;

    //Pass arguemnts to out run function
    myGerp.run(argv[1], argv[2]);

    return 0;
}