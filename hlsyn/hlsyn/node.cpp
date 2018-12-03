//node.cpp
//Trevor LaBanz
//contains node class

#include "node.h"


using namespace std;

Node::Node(string op) {
	this->visited = false;
	this->operation = op;
	this->ASAPStart = 0;
	this->ALAPStart = 0;
	this->width = 0;
	this->scheduledTime = 0;

	setCycleDelay(operation);
}


Node::~Node(){}


void Node::setCycleDelay(string op) {	//set cycle delay based on operation
	if (op == "MUL") {					
		this->cycleDelay = 2;
	}
	else if (op == "DIV" || op == "MOD") {
		this->cycleDelay = 3;
	}
	else {
		this->cycleDelay = 1;
	}
}


void Node::newInput(string input) {		//add input name to input vector	
	this->nodeInputs.push_back(input);
}


void Node::newOutput(string output) {	//add output to output vector
	this->nodeOutput = output;
}


void Node::addPred(Node* p) {			//add predecessor node
	this->predecessors.push_back(p);
}


void Node::addSucc(Node* s) {			//add successor node
	this->succesors.push_back(s);
}

bool Node::isPred(string var) {			//returns true if var is contained within nodeInputs
	auto loc = find(this->nodeInputs.begin(), this->nodeInputs.end(), var);
	if (loc != this->nodeInputs.end())
		return true;
	return false;
}


bool Node::findSucc(string var) {
	if (var.compare(this->nodeOutput))
		return true;
	return false;
}


void Node::calcWidth() {
	this->width = this->ALAPStart - this->ASAPStart + 1;
	this->probVal = 1.0 / this->width;						//calculate operation probability
}