//
//  Resistor.cpp
//  Lab 3 The Resistor Network Program
// Author: Md Nazmus Saad
// Date: Oct 9 2024

#include "Resistor.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

Resistor::Resistor(string name_, double resistance_, int endpoints_[2]) {
  name = name_;
  resistance = resistance_;
  endpointNodeIDs[0] = endpoints_[0];
  endpointNodeIDs[1] = endpoints_[1];
}
void Resistor::print() {
  cout << std::left << std::setw(20) << name << std::right << std::setw(8)
       << std::fixed << std::setprecision(2) << resistance << " Ohms "
       << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}
string Resistor::getName() { return name; }

double Resistor::getResistance() { return resistance; }

void Resistor::setResistance(double resistance_) { resistance = resistance_; }

// returns the other node ID that the
// resistor is attached to (other than nodeIndex)
int Resistor::getOtherEndpoint(int nodeIndex) {
  if (endpointNodeIDs[0] == nodeIndex) {
    return endpointNodeIDs[1];
  }
  return endpointNodeIDs[0];
}