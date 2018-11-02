#include <iostream>

using namespace std;

class Student {
public:
    int requiredTime;
    int windowTime;
    int entryTime;
    int queueTime;
    int idleTime;

    Student(){
        requiredTime = 0;
        windowTime = 0;
        entryTime = 0;
        queueTime = 0;
        idleTime = 0;
    }

    Student(int timeArrived,int timeNeeded){
        timeNeeded = requiredTime;
        timeArrived = entryTime;
        queueTime = 0;
        idleTime = 0;
    }

    int getStartTick(){
        return entryTime;
    }

    int getWaitingTime(){
        if(idleTime = 0)
            return 0;
        else return idleTime-1;
    }

    void toString(){
        cout<<"Person"<<endl;
        cout<<"Arrived at: "<<entryTime<<endl;
        cout<<"Needs: "<<requiredTime<<endl;
    }
};
