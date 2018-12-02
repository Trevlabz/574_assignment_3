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


void removeSubstrs(string& s, string& p);

bool isVar(string testStr, vector<tuple<string, bool, int>> vect);

Node* createOperation(string line, vector<tuple<string, bool, int>> inputV, vector<tuple<string, bool, int>> outputV, vector<tuple<string, bool, int>> varV);

