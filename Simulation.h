#include <iostream>
#include <fstream>
#include "Students.h"
#include "genQueue.h"
using namespace std;

class Simulation
{
  public:
    Simulation();
    Simulation(string fileName);//populate line in here

    int peopleHelped;
    int totalPeople;
    int windowCount;
    int ticks;
    
    GenQueue<person> entered;
    GenQueue<person> regLine;

    int *idleTimes;
    int *waitTimes;
    bool *windows;
    person *personAtWindow;

    string currentLine;
    int arrivalTick;
    int counter;
    ifstream inFile;


    void addToLine();
    bool windowsAreEmpty();
    void moveLine(); //This should be the main loop
    int windowsOpen();
    void clearWindows();
    void updateIdleWindows();
    double findMedian();
    void outputStats();
    void updateWaitTime();
    void printLine();//debugging purposes

};
