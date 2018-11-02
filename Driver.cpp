#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;

int main(int argc, char** argv) {
    Simulation s;
    string file;

    //If no file specified when running a.out
    if(argc < 2) {
        cout << "Please Enter Valid File Input" << endl;
    }

    else if(argc >= 2) {
        string file = argv[1];
    }

    s.openFile(file);
    s.moveLine();
    
    return 0;
}
