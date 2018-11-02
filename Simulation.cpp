#include <iostream>
#include <fstream>
#include "Simulation.h"
#include <algorithm>

using namespace std;

Simulation::Simulation(){
  peopleHelped = 0;
  ticks = 0;
}

Simulation::Simulation(string fileName){
  ticks = 0;
  peopleHelped = 0;
  arrivalTick = 0;
  totalPeople = 0;
  counter = 0;
}

int Simulation::openFile(string fileName)
{
  cout << "1" << endl;
  inFile.open(fileName); //opens the file
  inFile >> currentLine;
  windowCount = atoi(currentLine.c_str());
  personAtWindow = new Student[windowCount];
  windows = new bool[windowCount];
  idleTimes = new int[windowCount];

  while(!inFile.eof())
  {
      inFile >> currentLine;
      arrivalTick = atoi(currentLine.c_str());
      inFile >> currentLine;
      int peopleArriving = atoi(currentLine.c_str());

      for(int i = 0; i < peopleArriving; i++)
      {
        inFile >> currentLine;
        Student s(atoi(currentLine.c_str()), arrivalTick);
        totalPeople++;
        entered.enqueue(s);
      }
  }
  waitTimes = new int[totalPeople];
  moveLine();
}

void Simulation::clearWindows()
{
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == true)
    {
      if(personAtWindow[i].timeSpent == personAtWindow[i].timeNeeded)
      {
        windows[i] = false;
        Student temp = personAtWindow[i];
        waitTimes[peopleHelped] = temp.timeWaited;
        if (temp.timeWaited != 0){
          waitTimes[peopleHelped] = temp.timeWaited - 1;
        }
        else
        {
          waitTimes[peopleHelped] = 0;
        }
        peopleHelped++; //increments the number of inFile helped
      }
    }
  }
}

void Simulation::compute(){
  double meanWait = 0;
  int medianWait = 0;
  int longestWait = 0;
  double averageIdle = 0;
  double longestIdle = 0;
  int waitedOverTen = 0;
  int idleOverFive = 0;


  for(int i = 0; i < totalPeople; i++){
    meanWait += waitTimes[i];
    if(longestWait < waitTimes[i])
    {
      longestWait = waitTimes[i];
    }
    if(waitTimes[i] > 10)
    {
      waitedOverTen++;
    }
  }

  for(int j = 0; j < windowCount; j++){
    averageIdle += idleTimes[j];
    if(longestIdle < idleTimes[j])
    {
      longestIdle = idleTimes[j];
    }
    if(idleTimes[j] > 5){
      idleOverFive++;
    }
  }
  meanWait = meanWait/totalPeople;
  medianWait = findMedian();
  averageIdle = averageIdle/windowCount;
}

//adds students that arrive at specific tick mark
void Simulation::addToLine(){
  Student s = entered.vFront();
  while(s.arrivalTime == ticks)
  {
    regLine.enqueue(s);
    entered.dequeue();
    s = entered.vFront();
  }
}

//updates the student wait time
void Simulation::updateWaitTime()
{
  GenQueue<Student> copy;
  while(!regLine.isEmpty())
  {
    Student temp1 = regLine.vFront();
    regLine.dequeue();
    copy.enqueue(temp1);
  }
  while(!copy.isEmpty())
  {
    Student temp = copy.vFront();
    copy.dequeue();
    temp.timeWaited++;
    regLine.enqueue(temp);
  }
}

void Simulation::updateIdleWindows()
{
  for(int i = 0; i < windowCount; i++)
  {
    if(!windows[i])
    {
      idleTimes[i]++;
     }
   }
}

bool Simulation::windowsAreEmpty(){
  for(int i = 0; i < windowCount; i++)
  {
    if(windows[i] == true)
    {
      return false;
    }
  }
  return true;
}


void Simulation::moveLine(){
  cout << "2" << endl;
    while(!entered.isEmpty()|| !regLine.isEmpty() || !windowsAreEmpty())
    {
      if(entered.isEmpty() == false)
      {
          addToLine();
      }
      clearWindows();

      while(windowsOpen() != -1 && !regLine.isEmpty())
      {
        Student temp = regLine.vFront();
        int openWindow = windowsOpen();
        windows[openWindow] = true;
        personAtWindow[openWindow] = temp;
        regLine.dequeue();
      }
      for(int i = 0; i < windowCount; i++)
      {
        personAtWindow[i].timeSpent++;
      }

      updateWaitTime();
      updateIdleWindows();

      if(ticks == 5)
      {
        Student test = regLine.vFront();
      }
      ticks++;
    }
    compute();
}

int Simulation::windowsOpen()
{
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == false){
      return i;
    }
  }
  return -1;
}

double Simulation::findMedian(){
  sort(waitTimes, waitTimes + totalPeople - 1);
  if((totalPeople%2) ==1)
  {
    return (waitTimes[(totalPeople/2)]);
  }
    return  (waitTimes[totalPeople/2] + waitTimes[(totalPeople/2)-1]);
}
