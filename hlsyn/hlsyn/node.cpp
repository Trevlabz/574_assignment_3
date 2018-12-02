//node.cpp
//Trevor LaBanz
//contains node class

#include "node.h"


using namespace std;

Node::Node(string op) {
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