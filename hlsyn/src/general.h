//general function header
//Trevor Labanz

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

#include "node.h"

using namespace std;

extern vector<vector<double>> typeProb;


enum Probability {
	mult,
	addSub,
	divMod,
	logic
};

void removeSubstrs(string& s, string& p);

bool isVar(string testStr, vector<tuple<string, bool, int>> vect);

Node* createOperation(string line, vector<tuple<string, bool, int>> inputV, vector<tuple<string, bool, int>> outputV, vector<tuple<string, bool, int>> varV);

void connectGraph(vector<Node*> nodeList);

void connectGraphConditions(vector<Node*> nodeList); 

int doASAP(vector<Node*> nodeList);

void doALAP(vector<Node*> nodeList, int lastTime);

void doTypeDistribution(vector<Node*> nodeList);

void resetTypeDistVectors(vector<Node*> nodelist);

void doFDS(vector<Node*> nodeList);

tuple<int, double> forceDir(vector<Node*> nodeList, Node* node, int cycleNum, bool first, bool Successor); 

int convertOpEnum(string s);

int calcNStates(vector<Node*> nodeList);

string convertOp(string val);

string nodeToVerilog(vector<Node*> nodeList);