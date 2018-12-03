//genral functions
//Trevor LaBanz

#include "general.h"

#include <iomanip>

using namespace std;

void removeSubstrs(string& s, string& p) {					//removes substring p from string s
	string::size_type n = p.length();
	for (string::size_type i = s.find(p);
		i != string::npos;
		i = s.find(p))
		s.erase(i, n);
}

bool isVar(string testStr, vector<tuple<string, bool, int>> vect) {			//checks that testStr is contained in input/output/var list vector
	
	for (auto tempTup : vect) {
		if (get<0>(tempTup) == testStr)
			return true;
	}
	return false;
}


Node* createOperation(string line, vector<tuple<string,bool,int>> inputV, vector<tuple<string, bool, int>> outputV, vector<tuple<string, bool, int>> varV){			//reads an input line, currently defined inputs,outputs,vars and returns a Node object
	string substr1 = "", substr2 = "", substr3 = "", substr4 = "", substr5 = "", substr6 ="", substr7 = "";//break up line into 7 substrings using string stream
	string op = "";

	stringstream ss(line);

	ss >> substr1;				//output variable
	ss >> substr2;				//=
	ss >> substr3;				//input 1
	ss >> substr4;				//operator
	ss >> substr5;				//input 2
	ss >> substr6;				// : operator for mux
	ss >> substr7;				//input 3

	if (substr2 != "=") {															//if substr2 isn't =; then error
		cerr << "Error on Line: " << line << endl;
		return NULL;
	}
	
	if(!isVar(substr1,outputV) && !isVar(substr1, varV)){												//check output is defined
		cerr << "Undefined output " << substr1 << " in line: " << line << endl;
		return NULL;
	}
	
	if (!isVar(substr3, inputV) && !isVar(substr3, varV)) {					//check input 1 is defined
		cerr << "Undefined input " << substr3 << " in line: " << line << endl;
		return NULL;
	}
	
	
	if (substr4 == "+") {			//add
		if (substr5 == "1") {//inc if substr5 is 1
			op = "INC";
		}
		else {		//else add
			op = "ADD";
		}
	}
	else if (substr4 == "-") {		//sub
		if (substr5 == "1") {	//dec if substr5 is 1
			op = "DEC";
		}
		else {			//else sub
			op = "SUB";
		}

	}
	else if (substr4 == "*") {		//if MUL
		op = "MUL";	//create MUL Node
	}
	else if (substr4 == "/") {		//if DIV
		op = "DIV";	//create DIV Node	
	}
	else if (substr4 == "%") {		//if MOD
		op = "MOD";	//create MOD Node	
	}
	else if (substr4 == "<<") {		//if SHL
		op = "SHL";	//create SHL Node	
	}
	else if (substr4 == ">>") {		//if SHR
		op = "SHR";	//create SHR Node	
	}
	else if (substr4 == ">") {		//if GT
		op = "GT";	//create COMP Node
	}
	else if (substr4 == "<") {		//if LT
		op = "LT";	//create COMP Node
	}
	else if (substr4 == "==") {		//if EQ
		op = "EQ";	//create COMP Node
	}
	else if (substr4 == "?") {				//if MUX
		op = "MUX";	//create MUX Node
		if (substr6 != ":") {
			cerr << "Expected ':' in line: " << line << endl;
			return NULL;
		}
	}
	else {
		cerr << "Unknown operator in line: " << line << endl;
		return NULL;
	}

	
	 
	Node* nNode = new Node(op);
	nNode->newOutput(substr1);
	nNode->newInput(substr3);


	if (op == "DEC" || op == "INC") {
		return nNode;
	}


	if (!isVar(substr5, inputV) && !isVar(substr5, varV)) {						//check input 2 is defined
		cerr << "Undefined input " << substr5 << " in line: " << line << endl;
		return NULL;
	}
	nNode->newInput(substr5);		//add input 2 to node

	if (op == "MUX") {
		if (!isVar(substr7, inputV) && !isVar(substr7, varV)) {					//check input 3 is defined
			cerr << "Undefined input " << substr7 << " in line: " << line << endl;
			return NULL;
		}
		nNode->newInput(substr7);	//add input 3 to node
	}
	 

	return nNode;

}



void connectGraph(vector<Node*> nodeList) {		//make all connections between nodes in nodeList
	for (Node* pNode : nodeList) {				//loop through all nodes 
		for (Node* sNode : nodeList) {			//loop through all nodes and check if pNode is a predecessor of nNode
			if (sNode->isPred(pNode->nodeOutput)) {
				sNode->addPred(pNode);			//add pNode as predecessor to sNode
				pNode->addSucc(sNode);			//add sNode as successor to pNode
			}
		}
	}
}



int doASAP(vector<Node*> nodeList) {		//perform ASAP scheduling on the nodeList and return number of cycles required
	int timeReq = 0;
	int time = 0;
	int temp = 0;
	bool done = false;

	while (!done) {									//loop until scheduling complete
		done = true;
		for (Node* cNode : nodeList) {				//cycle through each node
			if (cNode->predecessors.size() == 0) {	//if top of graph
				cNode->ASAPStart = 1;					//set asap start time to 1
			}
			else {
				for (Node* pNode : cNode->predecessors) {	//look at each predecessor
					if (pNode->ASAPStart == 0) {	//if pNode hasn't been scheduled set done false and break predecessor loop
						done = false;
						break;
					}
					temp = pNode->ASAPStart + pNode->cycleDelay;	//store sum of parent start and parent cycle delay in temp
					if (temp > time)	//if temp greater than time; save
						time = temp;
				}
				if (done) {								//if node is done
					cNode->ASAPStart = time;				//set asap start
					if (time + cNode->cycleDelay > timeReq)		//update timeReq based on current node's start time + cycleDelay
						timeReq = time + cNode->cycleDelay - 1;
				}
			}
		}
	}
	return timeReq;
}



void doALAP(vector<Node*> nodeList, int lastTime) {		//perform ALAP scheduling on the nodeList and return number of cycles required
	int time = 0;
	int temp = 0;
	bool done1 = false;
	bool done2 = false;

	while (!done1) {				//loop until scheduling complete
		done1 = true;
		for (Node* cNode : nodeList) {		//cycle through nodeList
			done2 = true;
			if (cNode->succesors.size() == 0) {		//if bottom of graph
				cNode->ALAPStart = lastTime - cNode->cycleDelay + 1;
			}
			else {
				time = lastTime + 1;
				temp = 0;
				for (Node* sNode : cNode->succesors) {		//look through successors of current node
					if (sNode->ALAPStart == 0) {
						done1 = false;
						done2 = false;
						break;
					}
					temp = sNode->ALAPStart - cNode->cycleDelay;	//store start time of successor - cycle delay of current node
					if (temp < time)
						time = temp;	//if temp less than time store temp
				}
				if (done2)
					cNode->ALAPStart = time;		//if node is done set ALAP start time
			}
		}
	}
}



void doTypeDistribution(vector<Node*> nodeList){					//calculate sum of probabilities by a specific resource at any step of interest
	for (int i = 0; i < nodeList.size(); i++) {
		for (int j = nodeList[i]->ASAPStart; j <= nodeList[i]->ALAPStart; j++) {
			if (!nodeList[i]->operation.compare("MUL"))
				typeProb[mult][j] += nodeList[i]->probVal;
			else if (!nodeList[i]->operation.compare("ADD") || !nodeList[i]->operation.compare("SUB"))	
				typeProb[addSub][j] += nodeList[i]->probVal;
			else if (!nodeList[i]->operation.compare("DIV") || !nodeList[i]->operation.compare("MOD"))	
				typeProb[divMod][j] += nodeList[i]->probVal;
			else														
				typeProb[logic][j] += nodeList[i]->probVal;
		}
	}
}

void resetTypeDistVectors(vector<Node*> nodeList) {				//restore typeProb vectors
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j < typeProb[i].size(); j++) {
				typeProb[i][j] = 0.0;
		}
	}
	doTypeDistribution(nodeList);
}



void doFDS(vector<Node*> nodeList){
	for (Node* cNode : nodeList){
		cNode->scheduledTime = get<0>(forceDir(nodeList, cNode, 0, true, true));	// send in zero to begin (no interference for node)
		cNode->ALAPStart = cNode->scheduledTime;
		cNode->ASAPStart = cNode->scheduledTime;
		cNode->probVal = 1.0;
		resetTypeDistVectors(nodeList);						//reset type dist vectors
	}
}


tuple<int, double> forceDir(vector<Node*> nodeList, Node* node, int cycleNum, bool first, bool isSucc) {			//schedule a node using FDS
	node->visited = true;
	if (((cycleNum < node->ASAPStart) || (node->ALAPStart < cycleNum)) && !first) {		//check if predecessor node affects current nodes schedule
		return make_tuple<int, double>(0,0.0);
	}

	//tuple<int, double> tempForce(0, 0.0);
	tuple<int, double> forceSum(0, 10000.0);

	double prob;
	int timing = 0;

	int typeProbI = convertOpEnum(node->operation);

	for (int cycle = node->ASAPStart; cycle <= node->ALAPStart; cycle++) {
		if (first) {															//if first reset all visited flags
			for (Node* cnode : nodeList) {
				cnode->visited = false;
			}
		}
		tuple<int, double> tempForce(0, 0.0);
		bool skipFlag = false;

		if (!first && (cycle <= cycleNum))
			skipFlag = true;

		if (!skipFlag) {
			for (int k = node->ASAPStart; k <= node->ALAPStart; k++) {			//Calculate self force of current Node											 
				if (!first) {
					if (isSucc && (k <= cycleNum)) {
						prob = 0.0;
					}
					else if (!isSucc && (k >= cycleNum)) {
						prob = 0.0;
					}
					else if (cycle == k) {
						prob = 1;
					}
					else {
						prob = 0.0;
					}
				}
				else if (cycle == k) {
					prob = 1;
				}
				else {
					prob = 0.0;
				}
				get<1>(tempForce) += typeProb[typeProbI][k] * (prob - node->probVal);
			}

			for (int i = 0; i < node->predecessors.size(); i++) {		// Calculate the predecessor forces
				if (!node->predecessors[i]->visited)
					get<1>(tempForce) += get<1>(forceDir(nodeList, node->predecessors[i], cycle, false, false));
			}
			for (int i = 0; i < node->succesors.size(); i++) {	// Calculate the successor forces
				if (!node->succesors[i]->visited)
					get<1>(tempForce) += get<1>(forceDir(nodeList, node->succesors[i], cycle, false, true));
			}
			if (get<1>(tempForce) < get<1>(forceSum)) {
				get<1>(forceSum) = get<1>(tempForce);
				if (first) {
					get<0>(forceSum) = cycle;
				}
			}
		}
	}
	return forceSum;
}




int convertOpEnum(string s) {		//quickly convert node operation to enumerated value for use in typeProb
	if (!s.compare("MUL"))
		return mult;
	else if (!s.compare("ADD") || !s.compare("SUB"))
		return addSub;
	else if (!s.compare("DIV") || !s.compare("MOD"))
		return divMod;
	else
		return logic;
}

