#include <iostream>
#include <fstream>
#include "Student.h"
#include "GenQueue.h"
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

    GenQueue<Student> entered;
    GenQueue<Student> regLine;

    int *idleTimes;
    int *waitTimes;
    bool *windows;
    Student *personAtWindow;

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
    void updateWaitTime();
    void printLine();//debugging purposes
    int openFile(string fileName);
    void compute();
};
