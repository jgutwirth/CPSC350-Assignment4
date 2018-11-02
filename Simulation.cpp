#include <iostream>
#include <fstream>
#include "Simulation.h"
#include "GenQueue.h"
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

int Simulation::openFile()
{
  inFile.open(fileName); //opens the file
  inFile >> currentLine;

  windowCount = stoi(currentLine);

  personAtWindow = new person[windowCount];
  windows = new bool[windowCount];
  idleTimes = new int[windowCount];

  while(!inFile.eof()){
    inFile >> currentLine;
    arrivalTick = stoi(currentLine);
    inFile >> currentLine;
    int peopleArriving = stoi(currentLine);

    for(int i = 0; i < peopleArriving; i++){
      inFile >> currentLine;
      person p(stoi(currentLine), arrivalTick);
      totalPeople++;
      entered.enqueue(p);
    }
  }
  waitTimes = new int[totalPeople];

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

void Simulation::clearWindows()
{
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == true)
    {
      if(personAtWindow[i].isFinished())
      {
        windows[i] = false;
        person temp = personAtWindow[i];
        waitTimes[peopleHelped] = temp.getWaitTime();
        peopleHelped++; //increments the number of inFile helped
      }
    }
  }
}

//finds the median wait time of the students
double Simulation::findMedian(){
  sort(waitTimes, waitTimes + totalPeople - 1);
  if((totalPeople%2) ==1)
  {
    return (waitTimes[(totalPeople/2)]);
  }
    return  (waitTimes[totalPeople/2]+waitTimes[(totalPeople/2)-1)]);
  }
}

//outputs the stats of the studnet times and window times
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
  person p = entered.vFront();
  while(p.getArrivalTick() == ticks)
  {
    regLine.enqueue(p);
    entered.dequeue();
    p = entered.vFront();
  }
}

//updates the student wait time
void Simulation::updateWaitTime()
{
  GenQueue<person> copy;
  while(!regLine.isEmpty())
  {
    person temp1 = regLine.vFront();
    regLine.dequeue();
    copy.enqueue(temp1);
  }
  while(!copy.isEmpty())
  {
    person temp = copy.vFront();
    copy.dequeue();
    temp.isWaiting();
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
    while(!entered.isEmpty()|| !regLine.isEmpty() || !windowsAreEmpty())
    {
      if(entered.isEmpty() == false)
      {
          addToLine();
      }
      clearWindows();

      while(windowsOpen() != -1 && !regLine.isEmpty())
      {
        person temp = regLine.vFront();
        int openWindow = windowsOpen();
        windows[openWindow] = true;
        personAtWindow[openWindow] = temp;
        regLine.dequeue();
      }
      for(int i = 0; i < windowCount; i++)
      {
        personAtWindow[i].isAtWindow();
      }

      updateWaitTime();
      updateIdleWindows();

      if(ticks == 5)
      {
        person test = regLine.vFront();
      }
      ticks++;
    }
    outputStats();
}
