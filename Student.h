#include <iostream>

using namespace std;

class Student {
    public:
        Student();
        Student(int t, int e);
        ~Student();

        int timeNeeded;
        int timeSpent;
        int timeWaited;
        int arrivalTime;

        void printPerson();
};
