#include "Gerp.h"
#include <iostream>
#include <cstdlib>

using namespace std;

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