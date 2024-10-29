//
//  main.cpp
//  Lab 3 The Resistor Network Program
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-30
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Node.h"
#include "Resistor.h"

using namespace std;

Resistor** resistors =
    nullptr;  // Pointer that should point to an array of Resistor pointers
Node* nodes = nullptr;  // pointer that should hold address to an array of Nodes
int maxNodeNumber = 0;  // maximum number of nodes as set in the command line
int maxResistors = 0;  // maximum number of resistors as set in the command line
int resistorsCount = 0;  // count the number of resistors

string errorArray[10] = {
    "invalid command",                                  // 0
    "invalid argument",                                 // 1
    "negative resistance",                              // 2
    "node value is out of permitted range",             // 3
    "resistor name cannot be keyword \"all\"",          // 4
    "both terminals of resistor connect to same node",  // 5
    "too few arguments",                                // 6
};

string commands[7] = {
    "maxVal",   // 0
    "insertR",  // 1
    "modifyR",  // 2
    "printR",   // 3
    "deleteR",  // 4
    "setV",     // 5
    "solve",    // 6
};

// Function Prototypes
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);
bool getDouble(stringstream& ss, double& s);

bool isvalidInput(stringstream& ss);

void handleMaxVal(stringstream& ss);
void handleInsertR(stringstream& ss);
void handleModifyR(stringstream& ss);
void handlePrintR(stringstream& ss);
void handleDeleteR(stringstream& ss);
void handleSetV(stringstream& ss);
void handleSolve();

int main() {
  string line;
  cout << ">>> ";
  cout.flush();  // flushes current output buffer which means it will print the
                 // >>> live during the program
  // TODO: Implement the main function here

  int q = 0;
  while (true) {
    // parse input and check if its legal
    if (q != 0) {
      cout << ">>> ";
      cout.flush();
    }
    q = 1;
    // get user input and put it into line string
    getline(cin, line);
    line.erase(
        line.find_last_not_of(" \t\n\r\f\v") +
        1);  // This line is from piazza, from Vir Patel from @569_f4, link to
             // it: https://piazza.com/class/m05lz5509hj15x/post/569_f4
    if (cin.eof() || line.empty()) {
      break;
    }

    // create string stream for input
    stringstream stream(line);

    // parse string stream for command
    string command;
    stream >> command;

    // check if command is valid
    bool validCommand = false;
    if (stream.fail()) {
      if (stream.eof()) {
        cout << "Error: too few arguments" << endl;
        cout.flush();
      } else {
        cout << "Error: invalid argument" << endl;
        cout.flush();
      }
      // reset the flags and discard the line
      stream.clear();
      continue;
    }
    for (int i = 0; i < 7; i++) {
      if (command == commands[i]) {
        validCommand = true;
        break;
      }
    }

    if (validCommand == false) {
      cout << "Error: invalid command" << endl;
      continue;
    }

    // if valid command, follow command

    // reference to pass to the handle command functions
    stringstream& rstream = stream;

    // maxVal --> takes in max # of nodes and resistors, creates both arrays,
    // prints network info
    if (command == "maxVal") {
      handleMaxVal(rstream);
    } else if (command == "insertR") {
      handleInsertR(rstream);
    } else if (command == "modifyR") {
      handleModifyR(rstream);
    } else if (command == "printR") {
      handlePrintR(rstream);
    } else if (command == "deleteR") {
      handleDeleteR(rstream);
    } else if (command == "setV") {
      handleSetV(rstream);
    } else {
      handleSolve();
    }
  }
  return 0;
}

// TODO: Implement functions here

bool isvalidInput(stringstream& ss) {
  // check if valid
  if (ss.fail()) {
    if (ss.eof()) {
      cout << "Error: too few arguments" << endl;
      cout.flush();
    } else {
      cout << "Error: invalid argument" << endl;
      cout.flush();
    }
    // reset the flags and discard the line
    ss.clear();
    return false;
  }
  return true;
}

void handleMaxVal(stringstream& ss) {
  // !!! ---------        check if the network is empty, if not then delete old
  // network -----------------!!!
  if (nodes != nullptr) {
    delete[] nodes;
    nodes = nullptr;
  }
  if (resistors != nullptr) {
    for (int i = 0; i < maxResistors; i++) {
      if (resistors[i] != nullptr) {
        // delete each resistor
        delete resistors[i];
        // good practice to set them to nullptr
        resistors[i] = nullptr;
      }
    }

    // delete resistor ptr array
    delete[] resistors;
    resistors = nullptr;
  }

  // take in input
  ss >> maxNodeNumber;
  if (!isvalidInput(ss)) {
    return;
  }

  ss >> maxResistors;
  if (!isvalidInput(ss)) {
    return;
  }

  // initialize the network
  nodes = new Node[maxNodeNumber];
  resistors = new Resistor*[maxResistors];

  // make sure all of the elements are nullptrs (to fix issue with segmentation)
  for (int i = 0; i < maxResistors; i++) {
    resistors[i] = nullptr;
  }

  // print output message
  cout << "New network: max node number is " << maxNodeNumber
       << "; max resistors is " << maxResistors << endl;
}

// adds 1 resistor to resistor array, updates 2 nodes, print confirmation of
// action
void handleInsertR(stringstream& ss) {
  string name;
  double resistance;
  int nodes2[2];
  // take input
  ss >> name;
  if (!isvalidInput(ss)) {
    return;
  }
  // make sure name isnt all
  if (name == "all") {
    cout << "Error: resistor name cannot be keyword \"all\"" << endl;
    cout.flush();
    return;
  }

  // check if the name isnt already in the array. Before that check if any
  // resistor objects have been defined or else getName() will try to read when
  // there isnt any object created leading to segmentation error
  if (resistors != nullptr) {
    for (int i = 0; i < maxResistors; i++) {
      if (resistors[i] != nullptr && resistors[i]->getName() == name) {
        cout << "Error: resistor name already exists" << endl;
        cout.flush();
        return;
      }
    }
  }

  ss >> resistance;
  if (!isvalidInput(ss)) {
    return;
  }

  // make sure resistance is not negative
  if (resistance < 0) {
    cout << "Error: negative resistance" << endl;
    cout.flush();
    return;
  }

  ss >> nodes2[0];
  if (!isvalidInput(ss)) {
    return;
  }

  ss >> nodes2[1];
  if (!isvalidInput(ss)) {
    return;
  }

  // check if valid range of node numbers (1 - maxNodeNumber)
  if ((nodes2[0] < 1 || nodes2[0] > maxNodeNumber) ||
      (nodes2[1] < 1 || nodes2[1] > maxNodeNumber)) {
    cout << "Error: node value is out of permitted range 1 - " << maxNodeNumber
         << endl;
    cout.flush();
    return;
  }
  // make sure both terminals are not to the same node
  if (nodes2[0] == nodes2[1]) {
    cout << "Error: both terminals of resistor connect to same node" << endl;
    cout.flush();
    return;
  }

  // adjust to resistor array
  int endpoints[2] = {nodes2[0] - 1, nodes2[1] - 1};
  // create resistor object
  resistors[resistorsCount] = new Resistor(name, resistance, endpoints);

  // update the nodes
  nodes[endpoints[0]].addResistor(resistorsCount);
  nodes[endpoints[1]].addResistor(resistorsCount);

  // output
  // resistors[resistorsCount]->print();  // might have to change
  cout << "Inserted: resistor " << name << " " << fixed << setprecision(2)
       << resistance << " Ohms " << nodes2[0] << " -> " << nodes2[1] << endl;

  resistorsCount++;
}

// takes in the name and new resistance and updates resistor. Prints out
// resistor name, old and new resistance
void handleModifyR(stringstream& ss) {
  string name;
  double oldR, newR;

  ss >> name;
  if (!isvalidInput(ss)) {
    return;
  }

  // name cant be all
  if (name == "all") {
    cout << "Error: resistor name cannot be keyword \"all\"" << endl;
    cout.flush();
    return;
  }

  // make sure name in array
  int rID = -1;
  for (int i = 0; i < maxResistors; i++) {
    if (resistors[i] != nullptr && resistors[i]->getName() == name) {
      rID = i;
      break;
    }
  }

  if (rID < 0) {
    cout << "Error: resistor name not found" << endl;
    cout.flush();
    return;
  }

  ss >> newR;
  if (!isvalidInput(ss)) {
    return;
  }

  // make sure resistance is not negative
  if (newR < 0) {
    cout << "Error: negative resistance" << endl;
    cout.flush();
    return;
  }

  oldR = resistors[rID]->getResistance();
  // update resistance
  resistors[rID]->setResistance(newR);

  // print
  cout << "Modified: resistor " << name << " from " << fixed << setprecision(2)
       << oldR << " Ohms to " << fixed << setprecision(2) << newR << " Ohms"
       << endl;
}

void handlePrintR(stringstream& ss) {
  string name;

  ss >> name;
  if (!isvalidInput(ss)) {
    return;
  }

  // make sure name in array
  int rID = -1;

  for (int i = 0; i < maxResistors; i++) {
    if (resistors[i] != nullptr && resistors[i]->getName() == name) {
      rID = i;
      break;
    }
  }
  if (rID < 0) {
    cout << "Error: resistor name not found" << endl;
    cout.flush();
    return;
  }

  resistors[rID]->print();
}

void handleDeleteR(stringstream& ss) {
  string all;

  ss >> all;
  if (!isvalidInput(ss)) {
    return;
  }

  // free the resistors
  for (int i = 0; i < maxResistors; i++) {
    delete resistors[i];
    // good practice
    resistors[i] = nullptr;
  }

  // reset the node network by freeing and declaring it again
  delete[] nodes;
  nodes = nullptr;
  nodes = new Node[maxNodeNumber];

  cout << "Deleted: all resistors" << endl;
}

void handleSetV(stringstream& ss) {
  int nId;
  double voltage;

  ss >> nId;
  if (!isvalidInput(ss)) {
    return;
  }

  ss >> voltage;
  if (!isvalidInput(ss)) {
    return;
  }

  nodes[nId - 1].setVoltage(voltage);

  // output
  cout << "Set: node " << nId << " to " << fixed << setprecision(2) << voltage
       << " Volts" << endl;
}

void handleSolve() {
  // first set voltage of all nodes without specified voltage to 0
  for (int i = 0; i < maxNodeNumber; i++) {
    if (!nodes[i].isVoltageSet()) {
      nodes[i].setVoltageInternally(0);
    }
  }

  // Overall Proccess: keep looping through all the uninitialized nodes and use
  // eqn 3 to calculate the voltage until the volatges change by less than
  // 0.0001

  bool bigChange = true;
  while (bigChange) {
    bigChange = false;

    // for every uninitialized node, get resistance of every resistor connected
    // to them and volatge of the other node.
    for (int i = 0; i < maxNodeNumber; i++) {
      if (!nodes[i].isVoltageSet()) {
        int numRes = nodes[i].getNumRes();
        // get resistors connected to this node
        int* rIDs = nodes[i].getResIDArray();

        // eq3 is a product of 2 main parts:
        // part A is a reciprocal sum of the resistor resistances
        // part B is a sum of each other node volatges divied the respective
        // resistor
        double partA = 0.0;
        double partB = 0.0;

        // loop thru these resistors and calculate
        for (int j = 0; j < numRes; j++) {
          // resistance of resistor
          double r = resistors[rIDs[j]]->getResistance();
          // voltage of the other node
          double v =
              nodes[resistors[rIDs[j]]->getOtherEndpoint(i)].getVoltage();

          // calculate A & B
          partA += 1.0 / r;
          partB += v / r;
        }

        // Calculate new voltage for this node
        double newV = (1.0 / partA) * partB;

        // check if bigChange
        if (newV - nodes[i].getVoltage() > 0.0001) {
          bigChange = true;
        }
        nodes[i].setVoltageInternally(newV);
      }
    }
  }

  // print out node voltages
  cout << "Solve:" << endl;
  for (int i = 0; i < maxNodeNumber; i++) {
    if (nodes[i].getNumRes() > 0) {
      cout << "Node " << i + 1 << ": " << fixed << setprecision(2)
           << nodes[i].getVoltage() << " V" << endl;
    }
  }
}