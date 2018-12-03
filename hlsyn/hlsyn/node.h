//node.h

#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

/*
Node Class
	Properties:
		1. Operation Type (str)
		2. inputs	(vector<str>)
		3. outputs	(vector<str>)
		4. ASAP TIME
		5. ALAP TIME
		6. TIME FRAME WIDTH
		7. SCHEDULED TIME
		8. CYCLE DELAY

*/


class Node {
public:
	
	//properties
	string operation;

	bool visited;

	int ASAPStart;
	int ALAPStart;
	int width;			//ALAP-ASAP+1
	int scheduledTime;	//scheduled time determined by FDS
	int cycleDelay;		//number of cycles required for operation

	double probVal;		//probability value for FDS

	vector<string> nodeInputs;	
	string nodeOutput;

	vector<Node*> predecessors;
	vector<Node*> succesors;

	vector<tuple<bool, string>>	nodeConditions;		//conditionList contains <True/False condition for if/else, condition variable string> 

	//methods

	Node(string op);
	~Node();

	
	void newInput(string input);
	void newOutput(string output);
	
	void addPred(Node* p);
	void addSucc(Node* s);

	bool isPred(string var);
	bool findSucc(string var);

	void calcWidth();


private:
	void setCycleDelay(string op);

};
