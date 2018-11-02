#include <iostream>
#include "Student.h"


using namespace std;


Student::Student(){
  timeNeeded = 0;
  timeSpent = 0;
  timeWaited = 0;
  arrivalTime = 0;
}

Student::Student(int needs, int arrived){
  timeNeeded = needs;
  arrivalTime = arrived;
  timeSpent = 0;
  timeWaited = 0;
}

Student::~Student()
{

}
//print the student stats
void Student::printPerson(){
  cout << "" << endl;
  cout << "Student" << endl;
  cout << "Arrived " << arrivalTime << endl;
  cout << "Needs " << timeNeeded << endl;
}
