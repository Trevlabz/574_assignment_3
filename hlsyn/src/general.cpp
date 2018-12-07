//genral functions
//Trevor LaBanz

#include "general.h"


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
	string substr1 = "", substr2 = "", substr3 = "", substr4 = "", substr5 = "", substr6 ="", substr7 = "";	//break up line into 7 substrings using string stream
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
			if (sNode->isSucc(pNode->nodeOutput)) {
				sNode->addPred(pNode);			//add pNode as predecessor to sNode
				pNode->addSucc(sNode);			//add sNode as successor to pNode
			}
		}
	}
}


void connectGraphConditions(vector<Node*> nodeList) {		//search through all nodes for conditions and connect them assign predecessors/successsor
	for (Node* cNode : nodeList) {
		for (auto cond : cNode->nodeConditions) {
			for (Node* pNode : nodeList) {
				if (pNode->isPred(get<1>(cond))) {
					cNode->addPred(pNode);
					pNode->addSucc(cNode);
				}
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




int calcNStates(vector<Node*> nodeList) {	//calculate the number of statebits required for the HLSM
	int maxTime = 0;
	for (Node* cNode : nodeList) {
		if (cNode->scheduledTime > maxTime)
			maxTime = cNode->scheduledTime;
	}
	return maxTime;	//fill in with number of bits
}


string convertOp(string val) {
	if (val == "ADD")
		return "+";
	else if (val == "SUB")
		return "-";
	else if (val == "MUL")
		return "*";
	else if (val == "DIV")
		return "/";
	else if (val == "MOD")
		return "%";
	else if (val == "SHR")
		return ">>";
	else if (val == "SHL")
		return "<<";
	else if (val == "GT")
		return ">";
	else if (val == "LT")
		return "<";
	else if (val == "EQ")
		return "==";
	else if (val == "MUX")
		return "?";
	else return val;
}


string nodeToVerilog(vector<Node*> nodeList)
{
	ostringstream oss;
	const int nStates = calcNStates(nodeList);
	for (int i = 1; i <= nStates; i++) {																					//loop through each state
		vector<tuple<bool, string>> conds;
		oss << "\t\t\t\t" << i + 1 << " : begin" << '\n';

		for (int j = 0; j < nodeList.size(); j++) {																			//loop through nodes to determine if node is scheduled in current state
			if (nodeList[j]->scheduledTime == i) {

				for (auto it = nodeList[j]->nodeConditions.begin(); it != nodeList[j]->nodeConditions.end(); it++) {		
					if (conds.size() == 0) {
						conds.push_back(*it);
						if (!get<0>(*it)) {
							oss << "\t\t\t\t\t" << "if (!" << get<1>(*it) << ") begin" << '\n';
						}
						else {
							oss << "\t\t\t\t\t" << "if (" << get<1>(*it) << ") begin" << '\n';
						}
					}
					else {
						auto endit = nodeList[j]->nodeConditions.rbegin();
						if (!get<1>(conds[conds.size() - 1]).compare(get<1>(*endit)) && get<0>(conds[conds.size() - 1]) == get<0>(*endit))
							;
						else if (conds.size() >= 2 && !get<1>(conds[conds.size() - 2]).compare(get<1>(*it))) {
							oss << "\t\t\t\t\t" << "end" << '\n';
							conds.pop_back();
						}
						else if (get<1>(conds.back()).compare(get<1>(*it)) && (get<0>(*it))) {
							conds.push_back(*it);
							oss << "\t\t\t\t\t" << "if (" << get<1>(*it) << ") begin" << '\n';
						}
						else if (get<1>(conds.back()).compare(get<1>(*it)) && !(get<0>(*it))) {
							conds.push_back(*it);
							oss << "\t\t\t\t\t" << "if (!" << get<1>(*it) << ") begin" << '\n';
						}
						else {
							if (get<0>(conds.back()) != get<0>(*it)) {
								oss << "\t\t\t\t\t" << "end else begin" << '\n';
								conds.pop_back();
								conds.push_back(*it);
							}
						}
					}
				}

			outer:
				for (auto it = conds.begin(); it != conds.end(); it++) {													
					bool found2 = false;
					for (auto it2 = nodeList[j]->nodeConditions.begin(); it2 != nodeList[j]->nodeConditions.end(); it2++)
						if (!get<1>(*it).compare(get<1>(*it2)))
							found2 = true;
					if (!found2) {
						conds.erase(it);
						oss << "\t\t\t\t\t" << "end" << '\n';
						goto outer;
					}
				}


				string op = convertOp(nodeList[j]->operation);
				vector<string> ins = nodeList[j]->nodeInputs;
				oss << "\t\t\t\t\t" << nodeList[j]->nodeOutput << " <= ";
				if (op == "INC") {
					oss << ins.front() << " + 1;" << '\n';
				}
				else if (op == "DEC") {
					oss << ins.front() << " - 1;" << '\n';
				}
				else if (op == "?") {
					string in3 = ins.back();
					ins.pop_back();
					string in2 = ins.back();
					ins.pop_back();
					string in1 = ins.back();
					oss << in1 << " " << op << " " << in2 << " : " << in3 << ";" << '\n';
				}
				else {
					oss << ins.front() << " " << op << " " << ins.back() << ";" << '\n';
				}
			}
		}

		for (auto it = conds.begin(); it != conds.end(); it++)
			oss << "\t\t\t\t\t" << "end" << '\n';

		if (i < nStates)
			oss << "\t\t\t\t\t" << "State <= State + 1;" << '\n';
		else
			oss << "\t\t\t\t\t" << "State <= 1;" << '\n';

		oss << "\t\t\t\t" << "end" << '\n';
	}
	return oss.str();
}


