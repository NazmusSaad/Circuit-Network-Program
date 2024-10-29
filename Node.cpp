//
//  Node.cpp
//  Lab 3 The Resistor Network Program
// Author: Md Nazmus Saad
// Date: Oct 7 2024

#include "Node.h"

using namespace std;

Node::Node() {
  numRes = 0;
  voltage = 0;
  voltageIsSet = false;
}

bool Node::canAddResistor(){
    if (getNumRes() < 5){
        return true;
    }
    return false;
}


// adds a resistor to resIDArray array and increments number of resistors
void Node::addResistor(int rIndex){
    resIDArray[numRes] = rIndex;
    numRes++;
}

double Node::getVoltage(){
    return voltage;
}

void Node::setVoltage(double voltage_) {
    voltage = voltage_;
    voltageIsSet = true;
}

// for bonus
void Node::setVoltageInternally(double voltage_){
    voltage = voltage_;
}

bool Node::isVoltageSet(){
    return voltageIsSet;
}

int Node::getNumRes(){
    return numRes;
}

int* Node::getResIDArray(){
    return resIDArray;
}