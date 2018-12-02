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



